/***************************************************************************//**
* \file USBCOMM_drv.c
* \version 3.20
*
* \brief
*  This file contains the Endpoint 0 Driver for the USBFS Component.  
*
********************************************************************************
* \copyright
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "USBCOMM_pvt.h"
#include "cyapicallbacks.h"


/***************************************
* Global data allocation
***************************************/

volatile T_USBCOMM_EP_CTL_BLOCK USBCOMM_EP[USBCOMM_MAX_EP];

/** Contains the current configuration number, which is set by the host using a 
 * SET_CONFIGURATION request. This variable is initialized to zero in 
 * USBFS_InitComponent() API and can be read by the USBFS_GetConfiguration() 
 * API.*/
volatile uint8 USBCOMM_configuration;

/** Contains the current interface number.*/
volatile uint8 USBCOMM_interfaceNumber;

/** This variable is set to one after SET_CONFIGURATION and SET_INTERFACE 
 *requests. It can be read by the USBFS_IsConfigurationChanged() API */
volatile uint8 USBCOMM_configurationChanged;

/** Contains the current device address.*/
volatile uint8 USBCOMM_deviceAddress;

/** This is a two-bit variable that contains power status in the bit 0 
 * (DEVICE_STATUS_BUS_POWERED or DEVICE_STATUS_SELF_POWERED) and remote wakeup 
 * status (DEVICE_STATUS_REMOTE_WAKEUP) in the bit 1. This variable is 
 * initialized to zero in USBFS_InitComponent() API, configured by the 
 * USBFS_SetPowerStatus() API. The remote wakeup status cannot be set using the 
 * API SetPowerStatus(). */
volatile uint8 USBCOMM_deviceStatus;

volatile uint8 USBCOMM_interfaceSetting[USBCOMM_MAX_INTERFACES_NUMBER];
volatile uint8 USBCOMM_interfaceSetting_last[USBCOMM_MAX_INTERFACES_NUMBER];
volatile uint8 USBCOMM_interfaceStatus[USBCOMM_MAX_INTERFACES_NUMBER];

/** Contains the started device number. This variable is set by the 
 * USBFS_Start() or USBFS_InitComponent() APIs.*/
volatile uint8 USBCOMM_device;

/** Initialized class array for each interface. It is used for handling Class 
 * specific requests depend on interface class. Different classes in multiple 
 * alternate settings are not supported.*/
const uint8 CYCODE *USBCOMM_interfaceClass;


/***************************************
* Local data allocation
***************************************/

volatile uint8  USBCOMM_ep0Toggle;
volatile uint8  USBCOMM_lastPacketSize;

/** This variable is used by the communication functions to handle the current 
* transfer state.
* Initialized to TRANS_STATE_IDLE in the USBFS_InitComponent() API and after a 
* complete transfer in the status stage.
* Changed to the TRANS_STATE_CONTROL_READ or TRANS_STATE_CONTROL_WRITE in setup 
* transaction depending on the request type.
*/
volatile uint8  USBCOMM_transferState;
volatile T_USBCOMM_TD USBCOMM_currentTD;
volatile uint8  USBCOMM_ep0Mode;
volatile uint8  USBCOMM_ep0Count;
volatile uint16 USBCOMM_transferByteCount;


/*******************************************************************************
* Function Name: USBCOMM_ep_0_Interrupt
****************************************************************************//**
*
*  This Interrupt Service Routine handles Endpoint 0 (Control Pipe) traffic.
*  It dispatches setup requests and handles the data and status stages.
*
*
*******************************************************************************/
CY_ISR(USBCOMM_EP_0_ISR)
{
    uint8 tempReg;
    uint8 modifyReg;

#ifdef USBCOMM_EP_0_ISR_ENTRY_CALLBACK
    USBCOMM_EP_0_ISR_EntryCallback();
#endif /* (USBCOMM_EP_0_ISR_ENTRY_CALLBACK) */
    
    tempReg = USBCOMM_EP0_CR_REG;
    if ((tempReg & USBCOMM_MODE_ACKD) != 0u)
    {
        modifyReg = 1u;
        if ((tempReg & USBCOMM_MODE_SETUP_RCVD) != 0u)
        {
            if ((tempReg & USBCOMM_MODE_MASK) != USBCOMM_MODE_NAK_IN_OUT)
            {
                /* Mode not equal to NAK_IN_OUT: invalid setup */
                modifyReg = 0u;
            }
            else
            {
                USBCOMM_HandleSetup();
                
                if ((USBCOMM_ep0Mode & USBCOMM_MODE_SETUP_RCVD) != 0u)
                {
                    /* SETUP bit set: exit without mode modificaiton */
                    modifyReg = 0u;
                }
            }
        }
        else if ((tempReg & USBCOMM_MODE_IN_RCVD) != 0u)
        {
            USBCOMM_HandleIN();
        }
        else if ((tempReg & USBCOMM_MODE_OUT_RCVD) != 0u)
        {
            USBCOMM_HandleOUT();
        }
        else
        {
            modifyReg = 0u;
        }
        
        /* Modify the EP0_CR register */
        if (modifyReg != 0u)
        {
            
            tempReg = USBCOMM_EP0_CR_REG;
            
            /* Make sure that SETUP bit is cleared before modification */
            if ((tempReg & USBCOMM_MODE_SETUP_RCVD) == 0u)
            {
                /* Update count register */
                tempReg = (uint8) USBCOMM_ep0Toggle | USBCOMM_ep0Count;
                USBCOMM_EP0_CNT_REG = tempReg;
               
                /* Make sure that previous write operaiton was successful */
                if (tempReg == USBCOMM_EP0_CNT_REG)
                {
                    /* Repeat until next successful write operation */
                    do
                    {
                        /* Init temporary variable */
                        modifyReg = USBCOMM_ep0Mode;
                        
                        /* Unlock register */
                        tempReg = (uint8) (USBCOMM_EP0_CR_REG & USBCOMM_MODE_SETUP_RCVD);
                        
                        /* Check if SETUP bit is not set */
                        if (0u == tempReg)
                        {
                            /* Set the Mode Register  */
                            USBCOMM_EP0_CR_REG = USBCOMM_ep0Mode;
                            
                            /* Writing check */
                            modifyReg = USBCOMM_EP0_CR_REG & USBCOMM_MODE_MASK;
                        }
                    }
                    while (modifyReg != USBCOMM_ep0Mode);
                }
            }
        }
    }

    USBCOMM_ClearSieInterruptSource(USBCOMM_INTR_SIE_EP0_INTR);
	
#ifdef USBCOMM_EP_0_ISR_EXIT_CALLBACK
    USBCOMM_EP_0_ISR_ExitCallback();
#endif /* (USBCOMM_EP_0_ISR_EXIT_CALLBACK) */
}


/*******************************************************************************
* Function Name: USBCOMM_HandleSetup
****************************************************************************//**
*
*  This Routine dispatches requests for the four USB request types
*
*
* \reentrant
*  No.
*
*******************************************************************************/
void USBCOMM_HandleSetup(void) 
{
    uint8 requestHandled;
    
    /* Clear register lock by SIE (read register) and clear setup bit 
    * (write any value in register).
    */
    requestHandled = (uint8) USBCOMM_EP0_CR_REG;
    USBCOMM_EP0_CR_REG = (uint8) requestHandled;
    requestHandled = (uint8) USBCOMM_EP0_CR_REG;

    if ((requestHandled & USBCOMM_MODE_SETUP_RCVD) != 0u)
    {
        /* SETUP bit is set: exit without mode modification. */
        USBCOMM_ep0Mode = requestHandled;
    }
    else
    {
        /* In case the previous transfer did not complete, close it out */
        USBCOMM_UpdateStatusBlock(USBCOMM_XFER_PREMATURE);

        /* Check request type. */
        switch (USBCOMM_bmRequestTypeReg & USBCOMM_RQST_TYPE_MASK)
        {
            case USBCOMM_RQST_TYPE_STD:
                requestHandled = USBCOMM_HandleStandardRqst();
                break;
                
            case USBCOMM_RQST_TYPE_CLS:
                requestHandled = USBCOMM_DispatchClassRqst();
                break;
                
            case USBCOMM_RQST_TYPE_VND:
                requestHandled = USBCOMM_HandleVendorRqst();
                break;
                
            default:
                requestHandled = USBCOMM_FALSE;
                break;
        }
        
        /* If request is not recognized. Stall endpoint 0 IN and OUT. */
        if (requestHandled == USBCOMM_FALSE)
        {
            USBCOMM_ep0Mode = USBCOMM_MODE_STALL_IN_OUT;
        }
    }
}


/*******************************************************************************
* Function Name: USBCOMM_HandleIN
****************************************************************************//**
*
*  This routine handles EP0 IN transfers.
*
*
* \reentrant
*  No.
*
*******************************************************************************/
void USBCOMM_HandleIN(void) 
{
    switch (USBCOMM_transferState)
    {
        case USBCOMM_TRANS_STATE_IDLE:
            break;
        
        case USBCOMM_TRANS_STATE_CONTROL_READ:
            USBCOMM_ControlReadDataStage();
            break;
            
        case USBCOMM_TRANS_STATE_CONTROL_WRITE:
            USBCOMM_ControlWriteStatusStage();
            break;
            
        case USBCOMM_TRANS_STATE_NO_DATA_CONTROL:
            USBCOMM_NoDataControlStatusStage();
            break;
            
        default:    /* there are no more states */
            break;
    }
}


/*******************************************************************************
* Function Name: USBCOMM_HandleOUT
****************************************************************************//**
*
*  This routine handles EP0 OUT transfers.
*
*
* \reentrant
*  No.
*
*******************************************************************************/
void USBCOMM_HandleOUT(void) 
{
    switch (USBCOMM_transferState)
    {
        case USBCOMM_TRANS_STATE_IDLE:
            break;
        
        case USBCOMM_TRANS_STATE_CONTROL_READ:
            USBCOMM_ControlReadStatusStage();
            break;
            
        case USBCOMM_TRANS_STATE_CONTROL_WRITE:
            USBCOMM_ControlWriteDataStage();
            break;
            
        case USBCOMM_TRANS_STATE_NO_DATA_CONTROL:
            /* Update the completion block */
            USBCOMM_UpdateStatusBlock(USBCOMM_XFER_ERROR);
            
            /* We expect no more data, so stall INs and OUTs */
            USBCOMM_ep0Mode = USBCOMM_MODE_STALL_IN_OUT;
            break;
            
        default:    
            /* There are no more states */
            break;
    }
}


/*******************************************************************************
* Function Name: USBCOMM_LoadEP0
****************************************************************************//**
*
*  This routine loads the EP0 data registers for OUT transfers. It uses the
*  currentTD (previously initialized by the _InitControlWrite function and
*  updated for each OUT transfer, and the bLastPacketSize) to determine how
*  many uint8s to transfer on the current OUT.
*
*  If the number of uint8s remaining is zero and the last transfer was full,
*  we need to send a zero length packet.  Otherwise we send the minimum
*  of the control endpoint size (8) or remaining number of uint8s for the
*  transaction.
*
*
* \globalvars
*  USBCOMM_transferByteCount - Update the transfer byte count from the
*     last transaction.
*  USBCOMM_ep0Count - counts the data loaded to the SIE memory in
*     current packet.
*  USBCOMM_lastPacketSize - remembers the USBFS_ep0Count value for the
*     next packet.
*  USBCOMM_transferByteCount - sum of the previous bytes transferred
*     on previous packets(sum of USBFS_lastPacketSize)
*  USBCOMM_ep0Toggle - inverted
*  USBCOMM_ep0Mode  - prepare for mode register content.
*  USBCOMM_transferState - set to TRANS_STATE_CONTROL_READ
*
* \reentrant
*  No.
*
*******************************************************************************/
void USBCOMM_LoadEP0(void) 
{
    uint8 ep0Count = 0u;

    /* Update the transfer byte count from the last transaction */
    USBCOMM_transferByteCount += USBCOMM_lastPacketSize;

    /* Now load the next transaction */
    while ((USBCOMM_currentTD.count > 0u) && (ep0Count < 8u))
    {
        USBCOMM_EP0_DR_BASE.epData[ep0Count] = (uint8) *USBCOMM_currentTD.pData;
        USBCOMM_currentTD.pData = &USBCOMM_currentTD.pData[1u];
        ep0Count++;
        USBCOMM_currentTD.count--;
    }

    /* Support zero-length packet */
    if ((USBCOMM_lastPacketSize == 8u) || (ep0Count > 0u))
    {
        /* Update the data toggle */
        USBCOMM_ep0Toggle ^= USBCOMM_EP0_CNT_DATA_TOGGLE;
        /* Set the Mode Register  */
        USBCOMM_ep0Mode = USBCOMM_MODE_ACK_IN_STATUS_OUT;
        /* Update the state (or stay the same) */
        USBCOMM_transferState = USBCOMM_TRANS_STATE_CONTROL_READ;
    }
    else
    {
        /* Expect Status Stage Out */
        USBCOMM_ep0Mode = USBCOMM_MODE_STATUS_OUT_ONLY;
        /* Update the state (or stay the same) */
        USBCOMM_transferState = USBCOMM_TRANS_STATE_CONTROL_READ;
    }

    /* Save the packet size for next time */
    USBCOMM_ep0Count =       (uint8) ep0Count;
    USBCOMM_lastPacketSize = (uint8) ep0Count;
}


/*******************************************************************************
* Function Name: USBCOMM_InitControlRead
****************************************************************************//**
*
*  Initialize a control read transaction. It is used to send data to the host.
*  The following global variables should be initialized before this function
*  called. To send zero length packet use InitZeroLengthControlTransfer
*  function.
*
*
* \return
*  requestHandled state.
*
* \globalvars
*  USBCOMM_currentTD.count - counts of data to be sent.
*  USBCOMM_currentTD.pData - data pointer.
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 USBCOMM_InitControlRead(void) 
{
    uint16 xferCount;

    if (USBCOMM_currentTD.count == 0u)
    {
        (void) USBCOMM_InitZeroLengthControlTransfer();
    }
    else
    {
        /* Set up the state machine */
        USBCOMM_transferState = USBCOMM_TRANS_STATE_CONTROL_READ;
        
        /* Set the toggle, it gets updated in LoadEP */
        USBCOMM_ep0Toggle = 0u;
        
        /* Initialize the Status Block */
        USBCOMM_InitializeStatusBlock();
        
        xferCount = ((uint16)((uint16) USBCOMM_lengthHiReg << 8u) | ((uint16) USBCOMM_lengthLoReg));

        if (USBCOMM_currentTD.count > xferCount)
        {
            USBCOMM_currentTD.count = xferCount;
        }
        
        USBCOMM_LoadEP0();
    }

    return (USBCOMM_TRUE);
}


/*******************************************************************************
* Function Name: USBCOMM_InitZeroLengthControlTransfer
****************************************************************************//**
*
*  Initialize a zero length data IN transfer.
*
* \return
*  requestHandled state.
*
* \globalvars
*  USBCOMM_ep0Toggle - set to EP0_CNT_DATA_TOGGLE
*  USBCOMM_ep0Mode  - prepare for mode register content.
*  USBCOMM_transferState - set to TRANS_STATE_CONTROL_READ
*  USBCOMM_ep0Count - cleared, means the zero-length packet.
*  USBCOMM_lastPacketSize - cleared.
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 USBCOMM_InitZeroLengthControlTransfer(void)
                                                
{
    /* Update the state */
    USBCOMM_transferState = USBCOMM_TRANS_STATE_CONTROL_READ;
    
    /* Set the data toggle */
    USBCOMM_ep0Toggle = USBCOMM_EP0_CNT_DATA_TOGGLE;
    
    /* Set the Mode Register  */
    USBCOMM_ep0Mode = USBCOMM_MODE_ACK_IN_STATUS_OUT;
    
    /* Save the packet size for next time */
    USBCOMM_lastPacketSize = 0u;
    
    USBCOMM_ep0Count = 0u;

    return (USBCOMM_TRUE);
}


/*******************************************************************************
* Function Name: USBCOMM_ControlReadDataStage
****************************************************************************//**
*
*  Handle the Data Stage of a control read transfer.
*
*
* \reentrant
*  No.
*
*******************************************************************************/
void USBCOMM_ControlReadDataStage(void) 

{
    USBCOMM_LoadEP0();
}


/*******************************************************************************
* Function Name: USBCOMM_ControlReadStatusStage
****************************************************************************//**
*
*  Handle the Status Stage of a control read transfer.
*
*
* \globalvars
*  USBCOMM_USBFS_transferByteCount - updated with last packet size.
*  USBCOMM_transferState - set to TRANS_STATE_IDLE.
*  USBCOMM_ep0Mode  - set to MODE_STALL_IN_OUT.
*
* \reentrant
*  No.
*
*******************************************************************************/
void USBCOMM_ControlReadStatusStage(void) 
{
    /* Update the transfer byte count */
    USBCOMM_transferByteCount += USBCOMM_lastPacketSize;
    
    /* Go Idle */
    USBCOMM_transferState = USBCOMM_TRANS_STATE_IDLE;
    
    /* Update the completion block */
    USBCOMM_UpdateStatusBlock(USBCOMM_XFER_STATUS_ACK);
    
    /* We expect no more data, so stall INs and OUTs */
    USBCOMM_ep0Mode = USBCOMM_MODE_STALL_IN_OUT;
}


/*******************************************************************************
* Function Name: USBCOMM_InitControlWrite
****************************************************************************//**
*
*  Initialize a control write transaction
*
* \return
*  requestHandled state.
*
* \globalvars
*  USBCOMM_USBFS_transferState - set to TRANS_STATE_CONTROL_WRITE
*  USBCOMM_ep0Toggle - set to EP0_CNT_DATA_TOGGLE
*  USBCOMM_ep0Mode  - set to MODE_ACK_OUT_STATUS_IN
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 USBCOMM_InitControlWrite(void) 
{
    uint16 xferCount;

    /* Set up the state machine */
    USBCOMM_transferState = USBCOMM_TRANS_STATE_CONTROL_WRITE;
    
    /* This might not be necessary */
    USBCOMM_ep0Toggle = USBCOMM_EP0_CNT_DATA_TOGGLE;
    
    /* Initialize the Status Block */
    USBCOMM_InitializeStatusBlock();

    xferCount = ((uint16)((uint16) USBCOMM_lengthHiReg << 8u) | ((uint16) USBCOMM_lengthLoReg));

    if (USBCOMM_currentTD.count > xferCount)
    {
        USBCOMM_currentTD.count = xferCount;
    }

    /* Expect Data or Status Stage */
    USBCOMM_ep0Mode = USBCOMM_MODE_ACK_OUT_STATUS_IN;

    return(USBCOMM_TRUE);
}


/*******************************************************************************
* Function Name: USBCOMM_ControlWriteDataStage
****************************************************************************//**
*
*  Handle the Data Stage of a control write transfer
*       1. Get the data (We assume the destination was validated previously)
*       2. Update the count and data toggle
*       3. Update the mode register for the next transaction
*
*
* \globalvars
*  USBCOMM_transferByteCount - Update the transfer byte count from the
*    last transaction.
*  USBCOMM_ep0Count - counts the data loaded from the SIE memory
*    in current packet.
*  USBCOMM_transferByteCount - sum of the previous bytes transferred
*    on previous packets(sum of USBFS_lastPacketSize)
*  USBCOMM_ep0Toggle - inverted
*  USBCOMM_ep0Mode  - set to MODE_ACK_OUT_STATUS_IN.
*
* \reentrant
*  No.
*
*******************************************************************************/
void USBCOMM_ControlWriteDataStage(void) 
{
    uint8 ep0Count;
    uint8 regIndex = 0u;

    ep0Count = (USBCOMM_EP0_CNT_REG & USBCOMM_EPX_CNT0_MASK) - USBCOMM_EPX_CNTX_CRC_COUNT;

    USBCOMM_transferByteCount += (uint8)ep0Count;

    while ((USBCOMM_currentTD.count > 0u) && (ep0Count > 0u))
    {
        *USBCOMM_currentTD.pData = (uint8) USBCOMM_EP0_DR_BASE.epData[regIndex];
        USBCOMM_currentTD.pData = &USBCOMM_currentTD.pData[1u];
        regIndex++;
        ep0Count--;
        USBCOMM_currentTD.count--;
    }
    
    USBCOMM_ep0Count = (uint8)ep0Count;
    
    /* Update the data toggle */
    USBCOMM_ep0Toggle ^= USBCOMM_EP0_CNT_DATA_TOGGLE;
    
    /* Expect Data or Status Stage */
    USBCOMM_ep0Mode = USBCOMM_MODE_ACK_OUT_STATUS_IN;
}


/*******************************************************************************
* Function Name: USBCOMM_ControlWriteStatusStage
****************************************************************************//**
*
*  Handle the Status Stage of a control write transfer
*
* \globalvars
*  USBCOMM_transferState - set to TRANS_STATE_IDLE.
*  USBCOMM_USBFS_ep0Mode  - set to MODE_STALL_IN_OUT.
*
* \reentrant
*  No.
*
*******************************************************************************/
void USBCOMM_ControlWriteStatusStage(void) 
{
    /* Go Idle */
    USBCOMM_transferState = USBCOMM_TRANS_STATE_IDLE;
    
    /* Update the completion block */    
    USBCOMM_UpdateStatusBlock(USBCOMM_XFER_STATUS_ACK);
    
    /* We expect no more data, so stall INs and OUTs */
    USBCOMM_ep0Mode = USBCOMM_MODE_STALL_IN_OUT;
}


/*******************************************************************************
* Function Name: USBCOMM_InitNoDataControlTransfer
****************************************************************************//**
*
*  Initialize a no data control transfer
*
* \return
*  requestHandled state.
*
* \globalvars
*  USBCOMM_transferState - set to TRANS_STATE_NO_DATA_CONTROL.
*  USBCOMM_ep0Mode  - set to MODE_STATUS_IN_ONLY.
*  USBCOMM_ep0Count - cleared.
*  USBCOMM_ep0Toggle - set to EP0_CNT_DATA_TOGGLE
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 USBCOMM_InitNoDataControlTransfer(void) 
{
    USBCOMM_transferState = USBCOMM_TRANS_STATE_NO_DATA_CONTROL;
    USBCOMM_ep0Mode       = USBCOMM_MODE_STATUS_IN_ONLY;
    USBCOMM_ep0Toggle     = USBCOMM_EP0_CNT_DATA_TOGGLE;
    USBCOMM_ep0Count      = 0u;

    return (USBCOMM_TRUE);
}


/*******************************************************************************
* Function Name: USBCOMM_NoDataControlStatusStage
****************************************************************************//**
*  Handle the Status Stage of a no data control transfer.
*
*  SET_ADDRESS is special, since we need to receive the status stage with
*  the old address.
*
* \globalvars
*  USBCOMM_transferState - set to TRANS_STATE_IDLE.
*  USBCOMM_ep0Mode  - set to MODE_STALL_IN_OUT.
*  USBCOMM_ep0Toggle - set to EP0_CNT_DATA_TOGGLE
*  USBCOMM_deviceAddress - used to set new address and cleared
*
* \reentrant
*  No.
*
*******************************************************************************/
void USBCOMM_NoDataControlStatusStage(void) 
{
    if (0u != USBCOMM_deviceAddress)
    {
        /* Update device address if we got new address. */
        USBCOMM_CR0_REG = (uint8) USBCOMM_deviceAddress | USBCOMM_CR0_ENABLE;
        USBCOMM_deviceAddress = 0u;
    }

    USBCOMM_transferState = USBCOMM_TRANS_STATE_IDLE;
    
    /* Update the completion block. */
    USBCOMM_UpdateStatusBlock(USBCOMM_XFER_STATUS_ACK);
    
    /* Stall IN and OUT, no more data is expected. */
    USBCOMM_ep0Mode = USBCOMM_MODE_STALL_IN_OUT;
}


/*******************************************************************************
* Function Name: USBCOMM_UpdateStatusBlock
****************************************************************************//**
*
*  Update the Completion Status Block for a Request.  The block is updated
*  with the completion code the USBCOMM_transferByteCount.  The
*  StatusBlock Pointer is set to NULL.
*
*  completionCode - status.
*
*
* \globalvars
*  USBCOMM_currentTD.pStatusBlock->status - updated by the
*    completionCode parameter.
*  USBCOMM_currentTD.pStatusBlock->length - updated.
*  USBCOMM_currentTD.pStatusBlock - cleared.
*
* \reentrant
*  No.
*
*******************************************************************************/
void USBCOMM_UpdateStatusBlock(uint8 completionCode) 
{
    if (USBCOMM_currentTD.pStatusBlock != NULL)
    {
        USBCOMM_currentTD.pStatusBlock->status = completionCode;
        USBCOMM_currentTD.pStatusBlock->length = USBCOMM_transferByteCount;
        USBCOMM_currentTD.pStatusBlock = NULL;
    }
}


/*******************************************************************************
* Function Name: USBCOMM_InitializeStatusBlock
****************************************************************************//**
*
*  Initialize the Completion Status Block for a Request.  The completion
*  code is set to USB_XFER_IDLE.
*
*  Also, initializes USBCOMM_transferByteCount.  Save some space,
*  this is the only consumer.
*
* \globalvars
*  USBCOMM_currentTD.pStatusBlock->status - set to XFER_IDLE.
*  USBCOMM_currentTD.pStatusBlock->length - cleared.
*  USBCOMM_transferByteCount - cleared.
*
* \reentrant
*  No.
*
*******************************************************************************/
void USBCOMM_InitializeStatusBlock(void) 
{
    USBCOMM_transferByteCount = 0u;
    
    if (USBCOMM_currentTD.pStatusBlock != NULL)
    {
        USBCOMM_currentTD.pStatusBlock->status = USBCOMM_XFER_IDLE;
        USBCOMM_currentTD.pStatusBlock->length = 0u;
    }
}


/* [] END OF FILE */

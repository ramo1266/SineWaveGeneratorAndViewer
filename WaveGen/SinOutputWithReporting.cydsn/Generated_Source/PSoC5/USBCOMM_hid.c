/***************************************************************************//**
* \file USBCOMM_hid.c
* \version 3.20
*
* \brief
*  This file contains the USB HID Class request handler. 
*
* Related Document:
*  Device Class Definition for Human Interface Devices (HID) Version 1.11
*
********************************************************************************
* \copyright
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "USBCOMM_hid.h"
#include "USBCOMM_pvt.h"
#include "cyapicallbacks.h"


#if defined(USBCOMM_ENABLE_HID_CLASS)

/***************************************
*    HID Variables
***************************************/
/** This variable is initialized in the USBFS_InitComponent() API to the 
 * PROTOCOL_REPORT value. It is controlled by the host using the 
 * HID_SET_PROTOCOL request. The value is returned to the user code by the 
 * USBFS_GetProtocol() API.*/
volatile uint8 USBCOMM_hidProtocol[USBCOMM_MAX_INTERFACES_NUMBER];

/** This variable controls the HID report rate. It is controlled by the host 
 * using the HID_SET_IDLE request and used by the USBFS_UpdateHIDTimer() API to 
 * reload timer.*/
volatile uint8 USBCOMM_hidIdleRate[USBCOMM_MAX_INTERFACES_NUMBER];

/** This variable contains the timer counter, which is decremented and reloaded 
 * by the USBFS_UpdateHIDTimer() API.*/
volatile uint8 USBCOMM_hidIdleTimer[USBCOMM_MAX_INTERFACES_NUMBER]; /* HID device idle rate value */


/***************************************
* Custom Declarations
***************************************/

/* `#START HID_CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */


/*******************************************************************************
* Function Name: USBCOMM_UpdateHIDTimer
****************************************************************************//**
*
*  This function updates the HID Report idle timer and returns the status and 
*  reloads the timer if it expires.
*
*  \param interface Contains the interface number.
*
* \return
*  Returns the state of the HID timer. Symbolic names and their associated values are given here:
*  Return Value               |Notes
*  ---------------------------|------------------------------------------------
*  USBFS_IDLE_TIMER_EXPIRED   | The timer expired.
*  USBFS_IDLE_TIMER_RUNNING   | The timer is running.
*  USBFS_IDLE_TIMER_IDEFINITE | The report is sent when data or state changes.
*
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 USBCOMM_UpdateHIDTimer(uint8 interface) 
{
    uint8 stat = USBCOMM_IDLE_TIMER_INDEFINITE;

    if(USBCOMM_hidIdleRate[interface] != 0u)
    {
        if(USBCOMM_hidIdleTimer[interface] > 0u)
        {
            USBCOMM_hidIdleTimer[interface]--;
            stat = USBCOMM_IDLE_TIMER_RUNNING;
        }
        else
        {
            USBCOMM_hidIdleTimer[interface] = USBCOMM_hidIdleRate[interface];
            stat = USBCOMM_IDLE_TIMER_EXPIRED;
        }
    }

    return((uint8)stat);
}


/*******************************************************************************
* Function Name: USBCOMM_GetProtocol
****************************************************************************//**
*
*  This function returns the HID protocol value for the selected interface.
*
*  \param interface:  Contains the interface number.
*
*  \return
*  Returns the protocol value. 
*
*******************************************************************************/
uint8 USBCOMM_GetProtocol(uint8 interface) 
{
    return(USBCOMM_hidProtocol[interface]);
}


/*******************************************************************************
* Function Name: USBCOMM_DispatchHIDClassRqst
****************************************************************************//**
*
*  This routine dispatches class requests
*
* \return
*  Results of HID Class request handling: 
*  - USBCOMM_TRUE  - request was handled without errors
*  - USBCOMM_FALSE - error occurs during handling of request  
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 USBCOMM_DispatchHIDClassRqst(void) 
{
    uint8 requestHandled = USBCOMM_FALSE;

    uint8 interfaceNumber = (uint8) USBCOMM_wIndexLoReg;
    
    /* Check request direction: D2H or H2D. */
    if (0u != (USBCOMM_bmRequestTypeReg & USBCOMM_RQST_DIR_D2H))
    {
        /* Handle direction from device to host. */
        
        switch (USBCOMM_bRequestReg)
        {
            case USBCOMM_GET_DESCRIPTOR:
                if (USBCOMM_wValueHiReg == USBCOMM_DESCR_HID_CLASS)
                {
                    USBCOMM_FindHidClassDecriptor();
                    if (USBCOMM_currentTD.count != 0u)
                    {
                        requestHandled = USBCOMM_InitControlRead();
                    }
                }
                else if (USBCOMM_wValueHiReg == USBCOMM_DESCR_HID_REPORT)
                {
                    USBCOMM_FindReportDescriptor();
                    if (USBCOMM_currentTD.count != 0u)
                    {
                        requestHandled = USBCOMM_InitControlRead();
                    }
                }
                else
                {   
                    /* Do not handle this request. */
                }
                break;
                
            case USBCOMM_HID_GET_REPORT:
                USBCOMM_FindReport();
                if (USBCOMM_currentTD.count != 0u)
                {
                    requestHandled = USBCOMM_InitControlRead();
                }
                break;

            case USBCOMM_HID_GET_IDLE:
                /* This function does not support multiple reports per interface*/
                /* Validate interfaceNumber and Report ID (should be 0): Do not support Idle per Report ID */
                if ((interfaceNumber < USBCOMM_MAX_INTERFACES_NUMBER) && (USBCOMM_wValueLoReg == 0u)) 
                {
                    USBCOMM_currentTD.count = 1u;
                    USBCOMM_currentTD.pData = &USBCOMM_hidIdleRate[interfaceNumber];
                    requestHandled  = USBCOMM_InitControlRead();
                }
                break;
                
            case USBCOMM_HID_GET_PROTOCOL:
                /* Validate interfaceNumber */
                if( interfaceNumber < USBCOMM_MAX_INTERFACES_NUMBER)
                {
                    USBCOMM_currentTD.count = 1u;
                    USBCOMM_currentTD.pData = &USBCOMM_hidProtocol[interfaceNumber];
                    requestHandled  = USBCOMM_InitControlRead();
                }
                break;
                
            default:    /* requestHandled is initialized as FALSE by default */
                break;
        }
    }
    else
    {   
        /* Handle direction from host to device. */
        
        switch (USBCOMM_bRequestReg)
        {
            case USBCOMM_HID_SET_REPORT:
                USBCOMM_FindReport();
                if (USBCOMM_currentTD.count != 0u)
                {
                    requestHandled = USBCOMM_InitControlWrite();
                }
                break;
                
            case USBCOMM_HID_SET_IDLE:
                /* This function does not support multiple reports per interface */
                /* Validate interfaceNumber and Report ID (should be 0): Do not support Idle per Report ID */
                if ((interfaceNumber < USBCOMM_MAX_INTERFACES_NUMBER) && (USBCOMM_wValueLoReg == 0u))
                {
                    USBCOMM_hidIdleRate[interfaceNumber] = (uint8)USBCOMM_wValueHiReg;
                    /* With regards to HID spec: "7.2.4 Set_Idle Request"
                    *  Latency. If the current period has gone past the
                    *  newly proscribed time duration, then a report
                    *  will be generated immediately.
                    */
                    if(USBCOMM_hidIdleRate[interfaceNumber] <
                       USBCOMM_hidIdleTimer[interfaceNumber])
                    {
                        /* Set the timer to zero and let the UpdateHIDTimer() API return IDLE_TIMER_EXPIRED status*/
                        USBCOMM_hidIdleTimer[interfaceNumber] = 0u;
                    }
                    /* If the new request is received within 4 milliseconds
                    *  (1 count) of the end of the current period, then the
                    *  new request will have no effect until after the report.
                    */
                    else if(USBCOMM_hidIdleTimer[interfaceNumber] <= 1u)
                    {
                        /* Do nothing.
                        *  Let the UpdateHIDTimer() API continue to work and
                        *  return IDLE_TIMER_EXPIRED status
                        */
                    }
                    else
                    {   /* Reload the timer*/
                        USBCOMM_hidIdleTimer[interfaceNumber] =
                        USBCOMM_hidIdleRate[interfaceNumber];
                    }
                    requestHandled = USBCOMM_InitNoDataControlTransfer();
                }
                break;

            case USBCOMM_HID_SET_PROTOCOL:
                /* Validate interfaceNumber and protocol (must be 0 or 1) */
                if ((interfaceNumber < USBCOMM_MAX_INTERFACES_NUMBER) && (USBCOMM_wValueLoReg <= 1u))
                {
                    USBCOMM_hidProtocol[interfaceNumber] = (uint8)USBCOMM_wValueLoReg;
                    requestHandled = USBCOMM_InitNoDataControlTransfer();
                }
                break;
            
            default:    
                /* Unknown class request is not handled. */
                break;
        }
    }

    return (requestHandled);
}


/*******************************************************************************
* Function Name: USB_FindHidClassDescriptor
****************************************************************************//**
*
*  This routine find Hid Class Descriptor pointer based on the Interface number
*  and Alternate setting then loads the currentTD structure with the address of
*  the buffer and the size.
*  The HID Class Descriptor resides inside the config descriptor.
*
* \return
*  currentTD
*
* \reentrant
*  No.
*
*******************************************************************************/
void USBCOMM_FindHidClassDecriptor(void) 
{
    const T_USBCOMM_LUT CYCODE *pTmp;
    volatile uint8 *pDescr;
    uint8 interfaceN;

    pTmp = USBCOMM_GetConfigTablePtr(USBCOMM_configuration - 1u);
    
    interfaceN = (uint8) USBCOMM_wIndexLoReg;
    /* Third entry in the LUT starts the Interface Table pointers */
    /* Now use the request interface number*/
    pTmp = &pTmp[interfaceN + 2u];
    
    /* USB_DEVICEx_CONFIGURATIONy_INTERFACEz_TABLE */
    pTmp = (const T_USBCOMM_LUT CYCODE *) pTmp->p_list;
    
    /* Now use Alternate setting number */
    pTmp = &pTmp[USBCOMM_interfaceSetting[interfaceN]];
    
    /* USB_DEVICEx_CONFIGURATIONy_INTERFACEz_ALTERNATEi_HID_TABLE */
    pTmp = (const T_USBCOMM_LUT CYCODE *) pTmp->p_list;
    
    /* Fifth entry in the LUT points to Hid Class Descriptor in Configuration Descriptor */
    pTmp = &pTmp[4u];
    pDescr = (volatile uint8 *)pTmp->p_list;
    
    /* The first byte contains the descriptor length */
    USBCOMM_currentTD.count = *pDescr;
    USBCOMM_currentTD.pData = pDescr;
}


/*******************************************************************************
* Function Name: USB_FindReportDescriptor
****************************************************************************//**
*
*  This routine find Hid Report Descriptor pointer based on the Interface
*  number, then loads the currentTD structure with the address of the buffer
*  and the size.
*  Hid Report Descriptor is located after IN/OUT/FEATURE reports.
*
* \return
*  currentTD
*
* \reentrant
*  No.
*
*******************************************************************************/
void USBCOMM_FindReportDescriptor(void) 
{
    const T_USBCOMM_LUT CYCODE *pTmp;
    volatile uint8 *pDescr;
    uint8 interfaceN;

    pTmp = USBCOMM_GetConfigTablePtr(USBCOMM_configuration - 1u);
    interfaceN = (uint8) USBCOMM_wIndexLoReg;
    
    /* Third entry in the LUT starts the Interface Table pointers */
    /* Now use the request interface number */
    pTmp = &pTmp[interfaceN + 2u];
    
    /* USB_DEVICEx_CONFIGURATIONy_INTERFACEz_TABLE */
    pTmp = (const T_USBCOMM_LUT CYCODE *) pTmp->p_list;
    
    /* Now use Alternate setting number */
    pTmp = &pTmp[USBCOMM_interfaceSetting[interfaceN]];
    
    /* USB_DEVICEx_CONFIGURATIONy_INTERFACEz_ALTERNATEi_HID_TABLE */
    pTmp = (const T_USBCOMM_LUT CYCODE *) pTmp->p_list;
    
    /* Fourth entry in the LUT starts the Hid Report Descriptor */
    pTmp = &pTmp[3u];
    pDescr = (volatile uint8 *)pTmp->p_list;
    
    /* The 1st and 2nd bytes of descriptor contain its length. LSB is 1st. */
    USBCOMM_currentTD.count =  ((uint16)((uint16) pDescr[1u] << 8u) | pDescr[0u]);
    USBCOMM_currentTD.pData = &pDescr[2u];
}


/*******************************************************************************
* Function Name: USBCOMM_FindReport
****************************************************************************//**
*
*  This routine sets up a transfer based on the Interface number, Report Type
*  and Report ID, then loads the currentTD structure with the address of the
*  buffer and the size.  The caller has to decide if it is a control read or
*  control write.
*
* \return
*  currentTD
*
* \reentrant
*  No.
*
*******************************************************************************/
void USBCOMM_FindReport(void) 
{
    const T_USBCOMM_LUT CYCODE *pTmp;
    T_USBCOMM_TD *pTD;
    uint8 reportType;
    uint8 interfaceN;
 
    /* `#START HID_FINDREPORT` Place custom handling here */

    /* `#END` */
    
#ifdef USBCOMM_FIND_REPORT_CALLBACK
    USBCOMM_FindReport_Callback();
#endif /* (USBCOMM_FIND_REPORT_CALLBACK) */
    
    USBCOMM_currentTD.count = 0u;   /* Init not supported condition */
    pTmp = USBCOMM_GetConfigTablePtr(USBCOMM_configuration - 1u);
    reportType = (uint8) USBCOMM_wValueHiReg;
    interfaceN = (uint8) USBCOMM_wIndexLoReg;
    
    /* Third entry in the LUT Configuration Table starts the Interface Table pointers */
    /* Now use the request interface number */
    pTmp = &pTmp[interfaceN + 2u];
    
    /* USB_DEVICEx_CONFIGURATIONy_INTERFACEz_TABLE */
    pTmp = (const T_USBCOMM_LUT CYCODE *) pTmp->p_list;
    if (interfaceN < USBCOMM_MAX_INTERFACES_NUMBER)
    {
        /* Now use Alternate setting number */
        pTmp = &pTmp[USBCOMM_interfaceSetting[interfaceN]];
        
        /* USB_DEVICEx_CONFIGURATIONy_INTERFACEz_ALTERNATEi_HID_TABLE */
        pTmp = (const T_USBCOMM_LUT CYCODE *) pTmp->p_list;
        
        /* Validate reportType to comply with "7.2.1 Get_Report Request" */
        if ((reportType >= USBCOMM_HID_GET_REPORT_INPUT) &&
            (reportType <= USBCOMM_HID_GET_REPORT_FEATURE))
        {
            /* Get the entry proper TD (IN, OUT or Feature Report Table)*/
            pTmp = &pTmp[reportType - 1u];
            
            /* Get reportID */
            reportType = (uint8) USBCOMM_wValueLoReg;
            
            /* Validate table support by the HID descriptor, compare table count with reportID */
            if (pTmp->c >= reportType)
            {
                pTD = (T_USBCOMM_TD *) pTmp->p_list;
                pTD = &pTD[reportType];                          /* select entry depend on report ID*/
                USBCOMM_currentTD.pData = pTD->pData;   /* Buffer pointer */
                USBCOMM_currentTD.count = pTD->count;   /* Buffer Size */
                USBCOMM_currentTD.pStatusBlock = pTD->pStatusBlock;
            }
        }
    }
}


/*******************************************************************************
* Additional user functions supporting HID Requests
********************************************************************************/

/* `#START HID_FUNCTIONS` Place any additional functions here */

/* `#END` */

#endif  /*  USBCOMM_ENABLE_HID_CLASS */


/* [] END OF FILE */

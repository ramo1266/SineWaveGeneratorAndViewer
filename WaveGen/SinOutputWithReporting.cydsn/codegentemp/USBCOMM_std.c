/***************************************************************************//**
* \file USBCOMM_std.c
* \version 3.20
*
* \brief
*  This file contains the USB Standard request handler.
*
********************************************************************************
* \copyright
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "USBCOMM_pvt.h"

/***************************************
*   Static data allocation
***************************************/

#if defined(USBCOMM_ENABLE_FWSN_STRING)
    static volatile uint8* USBCOMM_fwSerialNumberStringDescriptor;
    static volatile uint8  USBCOMM_snStringConfirm = USBCOMM_FALSE;
#endif  /* (USBCOMM_ENABLE_FWSN_STRING) */

#if defined(USBCOMM_ENABLE_FWSN_STRING)
    /***************************************************************************
    * Function Name: USBCOMM_SerialNumString
    ************************************************************************//**
    *
    *  This function is available only when the User Call Back option in the 
    *  Serial Number String descriptor properties is selected. Application 
    *  firmware can provide the source of the USB device serial number string 
    *  descriptor during run time. The default string is used if the application 
    *  firmware does not use this function or sets the wrong string descriptor.
    *
    *  \param snString:  Pointer to the user-defined string descriptor. The 
    *  string descriptor should meet the Universal Serial Bus Specification 
    *  revision 2.0 chapter 9.6.7
    *  Offset|Size|Value|Description
    *  ------|----|------|---------------------------------
    *  0     |1   |N     |Size of this descriptor in bytes
    *  1     |1   |0x03  |STRING Descriptor Type
    *  2     |N-2 |Number|UNICODE encoded string
    *  
    * *For example:* uint8 snString[16]={0x0E,0x03,'F',0,'W',0,'S',0,'N',0,'0',0,'1',0};
    *
    * \reentrant
    *  No.
    *
    ***************************************************************************/
    void  USBCOMM_SerialNumString(uint8 snString[]) 
    {
        USBCOMM_snStringConfirm = USBCOMM_FALSE;
        
        if (snString != NULL)
        {
            /* Check descriptor validation */
            if ((snString[0u] > 1u) && (snString[1u] == USBCOMM_DESCR_STRING))
            {
                USBCOMM_fwSerialNumberStringDescriptor = snString;
                USBCOMM_snStringConfirm = USBCOMM_TRUE;
            }
        }
    }
#endif  /* USBCOMM_ENABLE_FWSN_STRING */


/*******************************************************************************
* Function Name: USBCOMM_HandleStandardRqst
****************************************************************************//**
*
*  This Routine dispatches standard requests
*
*
* \return
*  TRUE if request handled.
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 USBCOMM_HandleStandardRqst(void) 
{
    uint8 requestHandled = USBCOMM_FALSE;
    uint8 interfaceNumber;
    uint8 configurationN;
    uint8 bmRequestType = USBCOMM_bmRequestTypeReg;

#if defined(USBCOMM_ENABLE_STRINGS)
    volatile uint8 *pStr = 0u;
    #if defined(USBCOMM_ENABLE_DESCRIPTOR_STRINGS)
        uint8 nStr;
        uint8 descrLength;
    #endif /* (USBCOMM_ENABLE_DESCRIPTOR_STRINGS) */
#endif /* (USBCOMM_ENABLE_STRINGS) */
    
    static volatile uint8 USBCOMM_tBuffer[USBCOMM_STATUS_LENGTH_MAX];
    const T_USBCOMM_LUT CYCODE *pTmp;

    USBCOMM_currentTD.count = 0u;

    if (USBCOMM_RQST_DIR_D2H == (bmRequestType & USBCOMM_RQST_DIR_MASK))
    {
        /* Control Read */
        switch (USBCOMM_bRequestReg)
        {
            case USBCOMM_GET_DESCRIPTOR:
                if (USBCOMM_DESCR_DEVICE ==USBCOMM_wValueHiReg)
                {
                    pTmp = USBCOMM_GetDeviceTablePtr();
                    USBCOMM_currentTD.pData = (volatile uint8 *)pTmp->p_list;
                    USBCOMM_currentTD.count = USBCOMM_DEVICE_DESCR_LENGTH;
                    
                    requestHandled  = USBCOMM_InitControlRead();
                }
                else if (USBCOMM_DESCR_CONFIG == USBCOMM_wValueHiReg)
                {
                    pTmp = USBCOMM_GetConfigTablePtr((uint8) USBCOMM_wValueLoReg);
                    
                    /* Verify that requested descriptor exists */
                    if (pTmp != NULL)
                    {
                        USBCOMM_currentTD.pData = (volatile uint8 *)pTmp->p_list;
                        USBCOMM_currentTD.count = (uint16)((uint16)(USBCOMM_currentTD.pData)[USBCOMM_CONFIG_DESCR_TOTAL_LENGTH_HI] << 8u) | \
                                                                            (USBCOMM_currentTD.pData)[USBCOMM_CONFIG_DESCR_TOTAL_LENGTH_LOW];
                        requestHandled  = USBCOMM_InitControlRead();
                    }
                }
                
            #if(USBCOMM_BOS_ENABLE)
                else if (USBCOMM_DESCR_BOS == USBCOMM_wValueHiReg)
                {
                    pTmp = USBCOMM_GetBOSPtr();
                    
                    /* Verify that requested descriptor exists */
                    if (pTmp != NULL)
                    {
                        USBCOMM_currentTD.pData = (volatile uint8 *)pTmp;
                        USBCOMM_currentTD.count = ((uint16)((uint16)(USBCOMM_currentTD.pData)[USBCOMM_BOS_DESCR_TOTAL_LENGTH_HI] << 8u)) | \
                                                                             (USBCOMM_currentTD.pData)[USBCOMM_BOS_DESCR_TOTAL_LENGTH_LOW];
                        requestHandled  = USBCOMM_InitControlRead();
                    }
                }
            #endif /*(USBCOMM_BOS_ENABLE)*/
            
            #if defined(USBCOMM_ENABLE_STRINGS)
                else if (USBCOMM_DESCR_STRING == USBCOMM_wValueHiReg)
                {
                /* Descriptor Strings */
                #if defined(USBCOMM_ENABLE_DESCRIPTOR_STRINGS)
                    nStr = 0u;
                    pStr = (volatile uint8 *) &USBCOMM_STRING_DESCRIPTORS[0u];
                    
                    while ((USBCOMM_wValueLoReg > nStr) && (*pStr != 0u))
                    {
                        /* Read descriptor length from 1st byte */
                        descrLength = *pStr;
                        /* Move to next string descriptor */
                        pStr = &pStr[descrLength];
                        nStr++;
                    }
                #endif /* (USBCOMM_ENABLE_DESCRIPTOR_STRINGS) */
                
                /* Microsoft OS String */
                #if defined(USBCOMM_ENABLE_MSOS_STRING)
                    if (USBCOMM_STRING_MSOS == USBCOMM_wValueLoReg)
                    {
                        pStr = (volatile uint8 *)& USBCOMM_MSOS_DESCRIPTOR[0u];
                    }
                #endif /* (USBCOMM_ENABLE_MSOS_STRING) */
                
                /* SN string */
                #if defined(USBCOMM_ENABLE_SN_STRING)
                    if ((USBCOMM_wValueLoReg != 0u) && 
                        (USBCOMM_wValueLoReg == USBCOMM_DEVICE0_DESCR[USBCOMM_DEVICE_DESCR_SN_SHIFT]))
                    {
                    #if defined(USBCOMM_ENABLE_IDSN_STRING)
                        /* Read DIE ID and generate string descriptor in RAM */
                        USBCOMM_ReadDieID(USBCOMM_idSerialNumberStringDescriptor);
                        pStr = USBCOMM_idSerialNumberStringDescriptor;
                    #elif defined(USBCOMM_ENABLE_FWSN_STRING)
                        
                        if(USBCOMM_snStringConfirm != USBCOMM_FALSE)
                        {
                            pStr = USBCOMM_fwSerialNumberStringDescriptor;
                        }
                        else
                        {
                            pStr = (volatile uint8 *)&USBCOMM_SN_STRING_DESCRIPTOR[0u];
                        }
                    #else
                        pStr = (volatile uint8 *)&USBCOMM_SN_STRING_DESCRIPTOR[0u];
                    #endif  /* (USBCOMM_ENABLE_IDSN_STRING) */
                    }
                #endif /* (USBCOMM_ENABLE_SN_STRING) */
                
                    if (*pStr != 0u)
                    {
                        USBCOMM_currentTD.count = *pStr;
                        USBCOMM_currentTD.pData = pStr;
                        requestHandled  = USBCOMM_InitControlRead();
                    }
                }
            #endif /*  USBCOMM_ENABLE_STRINGS */
                else
                {
                    requestHandled = USBCOMM_DispatchClassRqst();
                }
                break;
                
            case USBCOMM_GET_STATUS:
                switch (bmRequestType & USBCOMM_RQST_RCPT_MASK)
                {
                    case USBCOMM_RQST_RCPT_EP:
                        USBCOMM_currentTD.count = USBCOMM_EP_STATUS_LENGTH;
                        USBCOMM_tBuffer[0u]     = USBCOMM_EP[USBCOMM_wIndexLoReg & USBCOMM_DIR_UNUSED].hwEpState;
                        USBCOMM_tBuffer[1u]     = 0u;
                        USBCOMM_currentTD.pData = &USBCOMM_tBuffer[0u];
                        
                        requestHandled  = USBCOMM_InitControlRead();
                        break;
                    case USBCOMM_RQST_RCPT_DEV:
                        USBCOMM_currentTD.count = USBCOMM_DEVICE_STATUS_LENGTH;
                        USBCOMM_tBuffer[0u]     = USBCOMM_deviceStatus;
                        USBCOMM_tBuffer[1u]     = 0u;
                        USBCOMM_currentTD.pData = &USBCOMM_tBuffer[0u];
                        
                        requestHandled  = USBCOMM_InitControlRead();
                        break;
                    default:    /* requestHandled is initialized as FALSE by default */
                        break;
                }
                break;
                
            case USBCOMM_GET_CONFIGURATION:
                USBCOMM_currentTD.count = 1u;
                USBCOMM_currentTD.pData = (volatile uint8 *) &USBCOMM_configuration;
                requestHandled  = USBCOMM_InitControlRead();
                break;
                
            case USBCOMM_GET_INTERFACE:
                USBCOMM_currentTD.count = 1u;
                USBCOMM_currentTD.pData = (volatile uint8 *) &USBCOMM_interfaceSetting[USBCOMM_wIndexLoReg];
                requestHandled  = USBCOMM_InitControlRead();
                break;
                
            default: /* requestHandled is initialized as FALSE by default */
                break;
        }
    }
    else
    {
        /* Control Write */
        switch (USBCOMM_bRequestReg)
        {
            case USBCOMM_SET_ADDRESS:
                /* Store address to be set in USBCOMM_NoDataControlStatusStage(). */
                USBCOMM_deviceAddress = (uint8) USBCOMM_wValueLoReg;
                requestHandled = USBCOMM_InitNoDataControlTransfer();
                break;
                
            case USBCOMM_SET_CONFIGURATION:
                configurationN = USBCOMM_wValueLoReg;
                
                /* Verify that configuration descriptor exists */
                if(configurationN > 0u)
                {
                    pTmp = USBCOMM_GetConfigTablePtr((uint8) configurationN - 1u);
                }
                
                /* Responds with a Request Error when configuration number is invalid */
                if (((configurationN > 0u) && (pTmp != NULL)) || (configurationN == 0u))
                {
                    /* Set new configuration if it has been changed */
                    if(configurationN != USBCOMM_configuration)
                    {
                        USBCOMM_configuration = (uint8) configurationN;
                        USBCOMM_configurationChanged = USBCOMM_TRUE;
                        USBCOMM_Config(USBCOMM_TRUE);
                    }
                    requestHandled = USBCOMM_InitNoDataControlTransfer();
                }
                break;
                
            case USBCOMM_SET_INTERFACE:
                if (0u != USBCOMM_ValidateAlternateSetting())
                {
                    /* Get interface number from the request. */
                    interfaceNumber = USBCOMM_wIndexLoReg;
                    USBCOMM_interfaceNumber = (uint8) USBCOMM_wIndexLoReg;
                     
                    /* Check if alternate settings is changed for interface. */
                    if (USBCOMM_interfaceSettingLast[interfaceNumber] != USBCOMM_interfaceSetting[interfaceNumber])
                    {
                        USBCOMM_configurationChanged = USBCOMM_TRUE;
                    
                        /* Change alternate setting for the endpoints. */
                    #if (USBCOMM_EP_MANAGEMENT_MANUAL && USBCOMM_EP_ALLOC_DYNAMIC)
                        USBCOMM_Config(USBCOMM_FALSE);
                    #else
                        USBCOMM_ConfigAltChanged();
                    #endif /* (USBCOMM_EP_MANAGEMENT_MANUAL && USBCOMM_EP_ALLOC_DYNAMIC) */
                    }
                    
                    requestHandled = USBCOMM_InitNoDataControlTransfer();
                }
                break;
                
            case USBCOMM_CLEAR_FEATURE:
                switch (bmRequestType & USBCOMM_RQST_RCPT_MASK)
                {
                    case USBCOMM_RQST_RCPT_EP:
                        if (USBCOMM_wValueLoReg == USBCOMM_ENDPOINT_HALT)
                        {
                            requestHandled = USBCOMM_ClearEndpointHalt();
                        }
                        break;
                    case USBCOMM_RQST_RCPT_DEV:
                        /* Clear device REMOTE_WAKEUP */
                        if (USBCOMM_wValueLoReg == USBCOMM_DEVICE_REMOTE_WAKEUP)
                        {
                            USBCOMM_deviceStatus &= (uint8)~USBCOMM_DEVICE_STATUS_REMOTE_WAKEUP;
                            requestHandled = USBCOMM_InitNoDataControlTransfer();
                        }
                        break;
                    case USBCOMM_RQST_RCPT_IFC:
                        /* Validate interfaceNumber */
                        if (USBCOMM_wIndexLoReg < USBCOMM_MAX_INTERFACES_NUMBER)
                        {
                            USBCOMM_interfaceStatus[USBCOMM_wIndexLoReg] &= (uint8) ~USBCOMM_wValueLoReg;
                            requestHandled = USBCOMM_InitNoDataControlTransfer();
                        }
                        break;
                    default:    /* requestHandled is initialized as FALSE by default */
                        break;
                }
                break;
                
            case USBCOMM_SET_FEATURE:
                switch (bmRequestType & USBCOMM_RQST_RCPT_MASK)
                {
                    case USBCOMM_RQST_RCPT_EP:
                        if (USBCOMM_wValueLoReg == USBCOMM_ENDPOINT_HALT)
                        {
                            requestHandled = USBCOMM_SetEndpointHalt();
                        }
                        break;
                        
                    case USBCOMM_RQST_RCPT_DEV:
                        /* Set device REMOTE_WAKEUP */
                        if (USBCOMM_wValueLoReg == USBCOMM_DEVICE_REMOTE_WAKEUP)
                        {
                            USBCOMM_deviceStatus |= USBCOMM_DEVICE_STATUS_REMOTE_WAKEUP;
                            requestHandled = USBCOMM_InitNoDataControlTransfer();
                        }
                        break;
                        
                    case USBCOMM_RQST_RCPT_IFC:
                        /* Validate interfaceNumber */
                        if (USBCOMM_wIndexLoReg < USBCOMM_MAX_INTERFACES_NUMBER)
                        {
                            USBCOMM_interfaceStatus[USBCOMM_wIndexLoReg] &= (uint8) ~USBCOMM_wValueLoReg;
                            requestHandled = USBCOMM_InitNoDataControlTransfer();
                        }
                        break;
                    
                    default:    /* requestHandled is initialized as FALSE by default */
                        break;
                }
                break;
                
            default:    /* requestHandled is initialized as FALSE by default */
                break;
        }
    }
    
    return (requestHandled);
}


#if defined(USBCOMM_ENABLE_IDSN_STRING)
    /***************************************************************************
    * Function Name: USBCOMM_ReadDieID
    ************************************************************************//**
    *
    *  This routine read Die ID and generate Serial Number string descriptor.
    *
    *  \param descr:  pointer on string descriptor. This string size has to be equal or
    *          greater than USBCOMM_IDSN_DESCR_LENGTH.
    *
    *
    * \reentrant
    *  No.
    *
    ***************************************************************************/
    void USBCOMM_ReadDieID(uint8 descr[]) 
    {
        const char8 CYCODE hex[] = "0123456789ABCDEF";
        uint8 i;
        uint8 j = 0u;
        uint8 uniqueId[8u];

        if (NULL != descr)
        {
            /* Initialize descriptor header. */
            descr[0u] = USBCOMM_IDSN_DESCR_LENGTH;
            descr[1u] = USBCOMM_DESCR_STRING;
            
            /* Unique ID size is 8 bytes. */
            CyGetUniqueId((uint32 *) uniqueId);

            /* Fill descriptor with unique device ID. */
            for (i = 2u; i < USBCOMM_IDSN_DESCR_LENGTH; i += 4u)
            {
                descr[i]      = (uint8) hex[(uniqueId[j] >> 4u)];
                descr[i + 1u] = 0u;
                descr[i + 2u] = (uint8) hex[(uniqueId[j] & 0x0Fu)];
                descr[i + 3u] = 0u;
                ++j;
            }
        }
    }
#endif /* (USBCOMM_ENABLE_IDSN_STRING) */


/*******************************************************************************
* Function Name: USBCOMM_ConfigReg
****************************************************************************//**
*
*  This routine configures hardware registers from the variables.
*  It is called from USBCOMM_Config() function and from RestoreConfig
*  after Wakeup.
*
*******************************************************************************/
void USBCOMM_ConfigReg(void) 
{
    uint8 ep;

#if (USBCOMM_EP_MANAGEMENT_DMA_AUTO)
    uint8 epType = 0u;
#endif /* (USBCOMM_EP_MANAGEMENT_DMA_AUTO) */

    /* Go thought all endpoints and set hardware configuration */
    for (ep = USBCOMM_EP1; ep < USBCOMM_MAX_EP; ++ep)
    {
        USBCOMM_ARB_EP_BASE.arbEp[ep].epCfg = USBCOMM_ARB_EPX_CFG_DEFAULT;
        
    #if (USBCOMM_EP_MANAGEMENT_DMA)
        /* Enable arbiter endpoint interrupt sources */
        USBCOMM_ARB_EP_BASE.arbEp[ep].epIntEn = USBCOMM_ARB_EPX_INT_MASK;
    #endif /* (USBCOMM_EP_MANAGEMENT_DMA) */
    
        if (USBCOMM_EP[ep].epMode != USBCOMM_MODE_DISABLE)
        {
            if (0u != (USBCOMM_EP[ep].addr & USBCOMM_DIR_IN))
            {
                USBCOMM_SIE_EP_BASE.sieEp[ep].epCr0 = USBCOMM_MODE_NAK_IN;
                
            #if (USBCOMM_EP_MANAGEMENT_DMA_AUTO && CY_PSOC4)
                /* Clear DMA_TERMIN for IN endpoint. */
                USBCOMM_ARB_EP_BASE.arbEp[ep].epIntEn &= (uint32) ~USBCOMM_ARB_EPX_INT_DMA_TERMIN;
            #endif /* (USBCOMM_EP_MANAGEMENT_DMA_AUTO && CY_PSOC4) */
            }
            else
            {
                USBCOMM_SIE_EP_BASE.sieEp[ep].epCr0 = USBCOMM_MODE_NAK_OUT;

            #if (USBCOMM_EP_MANAGEMENT_DMA_AUTO)
                /* (CY_PSOC4): DMA_TERMIN for OUT endpoint is set above. */
                
                /* Prepare endpoint type mask. */
                epType |= (uint8) (0x01u << (ep - USBCOMM_EP1));
            #endif /* (USBCOMM_EP_MANAGEMENT_DMA_AUTO) */
            }
        }
        else
        {
            USBCOMM_SIE_EP_BASE.sieEp[ep].epCr0 = USBCOMM_MODE_STALL_DATA_EP;
        }
        
    #if (!USBCOMM_EP_MANAGEMENT_DMA_AUTO)
        #if (CY_PSOC4)
            USBCOMM_ARB_EP16_BASE.arbEp[ep].rwRa16  = (uint32) USBCOMM_EP[ep].buffOffset;
            USBCOMM_ARB_EP16_BASE.arbEp[ep].rwWa16  = (uint32) USBCOMM_EP[ep].buffOffset;
        #else
            USBCOMM_ARB_EP_BASE.arbEp[ep].rwRa    = LO8(USBCOMM_EP[ep].buffOffset);
            USBCOMM_ARB_EP_BASE.arbEp[ep].rwRaMsb = HI8(USBCOMM_EP[ep].buffOffset);
            USBCOMM_ARB_EP_BASE.arbEp[ep].rwWa    = LO8(USBCOMM_EP[ep].buffOffset);
            USBCOMM_ARB_EP_BASE.arbEp[ep].rwWaMsb = HI8(USBCOMM_EP[ep].buffOffset);
        #endif /* (CY_PSOC4) */
    #endif /* (!USBCOMM_EP_MANAGEMENT_DMA_AUTO) */
    }

#if (USBCOMM_EP_MANAGEMENT_DMA_AUTO)
     /* BUF_SIZE depend on DMA_THRESS value:0x55-32 bytes  0x44-16 bytes 0x33-8 bytes 0x22-4 bytes 0x11-2 bytes */
    USBCOMM_BUF_SIZE_REG = USBCOMM_DMA_BUF_SIZE;

    /* Configure DMA burst threshold */
#if (CY_PSOC4)
    USBCOMM_DMA_THRES16_REG   = USBCOMM_DMA_BYTES_PER_BURST;
#else
    USBCOMM_DMA_THRES_REG     = USBCOMM_DMA_BYTES_PER_BURST;
    USBCOMM_DMA_THRES_MSB_REG = 0u;
#endif /* (CY_PSOC4) */
    USBCOMM_EP_ACTIVE_REG = USBCOMM_DEFAULT_ARB_INT_EN;
    USBCOMM_EP_TYPE_REG   = epType;
    
    /* Cfg_cmp bit set to 1 once configuration is complete. */
    /* Lock arbiter configtuation */
    USBCOMM_ARB_CFG_REG |= (uint8)  USBCOMM_ARB_CFG_CFG_CMP;
    /* Cfg_cmp bit set to 0 during configuration of PFSUSB Registers. */
    USBCOMM_ARB_CFG_REG &= (uint8) ~USBCOMM_ARB_CFG_CFG_CMP;

#endif /* (USBCOMM_EP_MANAGEMENT_DMA_AUTO) */

    /* Enable interrupt SIE interurpt source from EP0-EP1 */
    USBCOMM_SIE_EP_INT_EN_REG = (uint8) USBCOMM_DEFAULT_SIE_EP_INT_EN;
}


/*******************************************************************************
* Function Name: USBCOMM_EpStateInit
****************************************************************************//**
*
*  This routine initialize state of Data end points based of its type: 
*   IN  - USBCOMM_IN_BUFFER_EMPTY (USBCOMM_EVENT_PENDING)
*   OUT - USBCOMM_OUT_BUFFER_EMPTY (USBCOMM_NO_EVENT_PENDING)
*
*******************************************************************************/
void USBCOMM_EpStateInit(void) 
{
    uint8 i;

    for (i = USBCOMM_EP1; i < USBCOMM_MAX_EP; i++)
    { 
        if (0u != (USBCOMM_EP[i].addr & USBCOMM_DIR_IN))
        {
            /* IN Endpoint */
            USBCOMM_EP[i].apiEpState = USBCOMM_EVENT_PENDING;
        }
        else
        {
            /* OUT Endpoint */
            USBCOMM_EP[i].apiEpState = USBCOMM_NO_EVENT_PENDING;
        }
    }
                    
}


/*******************************************************************************
* Function Name: USBCOMM_Config
****************************************************************************//**
*
*  This routine configures endpoints for the entire configuration by scanning
*  the configuration descriptor.
*
*  \param clearAltSetting: It configures the bAlternateSetting 0 for each interface.
*
* USBCOMM_interfaceClass - Initialized class array for each interface.
*   It is used for handling Class specific requests depend on interface class.
*   Different classes in multiple Alternate settings does not supported.
*
* \reentrant
*  No.
*
*******************************************************************************/
void USBCOMM_Config(uint8 clearAltSetting) 
{
    uint8 ep;
    uint8 curEp;
    uint8 i;
    uint8 epType;
    const uint8 *pDescr;
    
    #if (!USBCOMM_EP_MANAGEMENT_DMA_AUTO)
        uint16 buffCount = 0u;
    #endif /* (!USBCOMM_EP_MANAGEMENT_DMA_AUTO) */

    const T_USBCOMM_LUT CYCODE *pTmp;
    const T_USBCOMM_EP_SETTINGS_BLOCK CYCODE *pEP;

    /* Clear endpoints settings */
    for (ep = 0u; ep < USBCOMM_MAX_EP; ++ep)
    {
        USBCOMM_EP[ep].attrib     = 0u;
        USBCOMM_EP[ep].hwEpState  = 0u;
        USBCOMM_EP[ep].epToggle   = 0u;
        USBCOMM_EP[ep].bufferSize = 0u;
        USBCOMM_EP[ep].interface  = 0u;
        USBCOMM_EP[ep].apiEpState = USBCOMM_NO_EVENT_PENDING;
        USBCOMM_EP[ep].epMode     = USBCOMM_MODE_DISABLE;   
    }

    /* Clear Alternate settings for all interfaces. */
    if (0u != clearAltSetting)
    {
        for (i = 0u; i < USBCOMM_MAX_INTERFACES_NUMBER; ++i)
        {
            USBCOMM_interfaceSetting[i]     = 0u;
            USBCOMM_interfaceSettingLast[i] = 0u;
        }
    }

    /* Init Endpoints and Device Status if configured */
    if (USBCOMM_configuration > 0u)
    {
        #if defined(USBCOMM_ENABLE_CDC_CLASS)
            uint8 cdcComNums = 0u;
        #endif  /* (USBCOMM_ENABLE_CDC_CLASS) */  

        pTmp = USBCOMM_GetConfigTablePtr(USBCOMM_configuration - 1u);
        
        /* Set Power status for current configuration */
        pDescr = (const uint8 *)pTmp->p_list;
        if ((pDescr[USBCOMM_CONFIG_DESCR_ATTRIB] & USBCOMM_CONFIG_DESCR_ATTRIB_SELF_POWERED) != 0u)
        {
            USBCOMM_deviceStatus |= (uint8)  USBCOMM_DEVICE_STATUS_SELF_POWERED;
        }
        else
        {
            USBCOMM_deviceStatus &= (uint8) ~USBCOMM_DEVICE_STATUS_SELF_POWERED;
        }
        
        /* Move to next element */
        pTmp = &pTmp[1u];
        ep = pTmp->c;  /* For this table, c is the number of endpoints configurations  */

        #if (USBCOMM_EP_MANAGEMENT_MANUAL && USBCOMM_EP_ALLOC_DYNAMIC)
            /* Configure for dynamic EP memory allocation */
            /* p_list points the endpoint setting table. */
            pEP = (T_USBCOMM_EP_SETTINGS_BLOCK *) pTmp->p_list;
            
            for (i = 0u; i < ep; i++)
            {     
                /* Compare current Alternate setting with EP Alt */
                if (USBCOMM_interfaceSetting[pEP->interface] == pEP->altSetting)
                {                                                          
                    curEp  = pEP->addr & USBCOMM_DIR_UNUSED;
                    epType = pEP->attributes & USBCOMM_EP_TYPE_MASK;
                    
                    USBCOMM_EP[curEp].addr       = pEP->addr;
                    USBCOMM_EP[curEp].attrib     = pEP->attributes;
                    USBCOMM_EP[curEp].bufferSize = pEP->bufferSize;

                    if (0u != (pEP->addr & USBCOMM_DIR_IN))
                    {
                        /* IN Endpoint */
                        USBCOMM_EP[curEp].epMode     = USBCOMM_GET_ACTIVE_IN_EP_CR0_MODE(epType);
                        USBCOMM_EP[curEp].apiEpState = USBCOMM_EVENT_PENDING;
                    
                    #if (defined(USBCOMM_ENABLE_MIDI_STREAMING) && (USBCOMM_MIDI_IN_BUFF_SIZE > 0))
                        if ((pEP->bMisc == USBCOMM_CLASS_AUDIO) && (epType == USBCOMM_EP_TYPE_BULK))
                        {
                            USBCOMM_midi_in_ep = curEp;
                        }
                    #endif  /* (USBCOMM_ENABLE_MIDI_STREAMING) */
                    }
                    else
                    {
                        /* OUT Endpoint */
                        USBCOMM_EP[curEp].epMode     = USBCOMM_GET_ACTIVE_OUT_EP_CR0_MODE(epType);
                        USBCOMM_EP[curEp].apiEpState = USBCOMM_NO_EVENT_PENDING;
                        
                    #if (defined(USBCOMM_ENABLE_MIDI_STREAMING) && (USBCOMM_MIDI_OUT_BUFF_SIZE > 0))
                        if ((pEP->bMisc == USBCOMM_CLASS_AUDIO) && (epType == USBCOMM_EP_TYPE_BULK))
                        {
                            USBCOMM_midi_out_ep = curEp;
                        }
                    #endif  /* (USBCOMM_ENABLE_MIDI_STREAMING) */
                    }

                #if(defined (USBCOMM_ENABLE_CDC_CLASS))
                    if((pEP->bMisc == USBCOMM_CLASS_CDC_DATA) ||(pEP->bMisc == USBCOMM_CLASS_CDC))
                    {
                        cdcComNums = USBCOMM_Cdc_EpInit(pEP, curEp, cdcComNums);
                    }
                #endif  /* (USBCOMM_ENABLE_CDC_CLASS) */
                }
                
                pEP = &pEP[1u];
            }
            
        #else
            for (i = USBCOMM_EP1; i < USBCOMM_MAX_EP; ++i)
            {
                /* p_list points the endpoint setting table. */
                pEP = (const T_USBCOMM_EP_SETTINGS_BLOCK CYCODE *) pTmp->p_list;
                /* Find max length for each EP and select it (length could be different in different Alt settings) */
                /* but other settings should be correct with regards to Interface alt Setting */
                
                for (curEp = 0u; curEp < ep; ++curEp)
                {
                    if (i == (pEP->addr & USBCOMM_DIR_UNUSED))
                    {
                        /* Compare endpoint buffers size with current size to find greater. */
                        if (USBCOMM_EP[i].bufferSize < pEP->bufferSize)
                        {
                            USBCOMM_EP[i].bufferSize = pEP->bufferSize;
                        }
                        
                        /* Compare current Alternate setting with EP Alt */
                        if (USBCOMM_interfaceSetting[pEP->interface] == pEP->altSetting)
                        {                            
                            USBCOMM_EP[i].addr = pEP->addr;
                            USBCOMM_EP[i].attrib = pEP->attributes;
                            
                            epType = pEP->attributes & USBCOMM_EP_TYPE_MASK;
                            
                            if (0u != (pEP->addr & USBCOMM_DIR_IN))
                            {
                                /* IN Endpoint */
                                USBCOMM_EP[i].epMode     = USBCOMM_GET_ACTIVE_IN_EP_CR0_MODE(epType);
                                USBCOMM_EP[i].apiEpState = USBCOMM_EVENT_PENDING;
                                
                            #if (defined(USBCOMM_ENABLE_MIDI_STREAMING) && (USBCOMM_MIDI_IN_BUFF_SIZE > 0))
                                if ((pEP->bMisc == USBCOMM_CLASS_AUDIO) && (epType == USBCOMM_EP_TYPE_BULK))
                                {
                                    USBCOMM_midi_in_ep = i;
                                }
                            #endif  /* (USBCOMM_ENABLE_MIDI_STREAMING) */
                            }
                            else
                            {
                                /* OUT Endpoint */
                                USBCOMM_EP[i].epMode     = USBCOMM_GET_ACTIVE_OUT_EP_CR0_MODE(epType);
                                USBCOMM_EP[i].apiEpState = USBCOMM_NO_EVENT_PENDING;
                                
                            #if (defined(USBCOMM_ENABLE_MIDI_STREAMING) && (USBCOMM_MIDI_OUT_BUFF_SIZE > 0))
                                if ((pEP->bMisc == USBCOMM_CLASS_AUDIO) && (epType == USBCOMM_EP_TYPE_BULK))
                                {
                                    USBCOMM_midi_out_ep = i;
                                }
                            #endif  /* (USBCOMM_ENABLE_MIDI_STREAMING) */
                            }

                        #if (defined(USBCOMM_ENABLE_CDC_CLASS))
                            if((pEP->bMisc == USBCOMM_CLASS_CDC_DATA) ||(pEP->bMisc == USBCOMM_CLASS_CDC))
                            {
                                cdcComNums = USBCOMM_Cdc_EpInit(pEP, i, cdcComNums);
                            }
                        #endif  /* (USBCOMM_ENABLE_CDC_CLASS) */

                            #if (USBCOMM_EP_MANAGEMENT_DMA_AUTO)
                                break;  /* Use first EP setting in Auto memory management */
                            #endif /* (USBCOMM_EP_MANAGEMENT_DMA_AUTO) */
                        }
                    }
                    
                    pEP = &pEP[1u];
                }
            }
        #endif /*  (USBCOMM_EP_MANAGEMENT_MANUAL && USBCOMM_EP_ALLOC_DYNAMIC) */

        /* Init class array for each interface and interface number for each EP.
        *  It is used for handling Class specific requests directed to either an
        *  interface or the endpoint.
        */
        /* p_list points the endpoint setting table. */
        pEP = (const T_USBCOMM_EP_SETTINGS_BLOCK CYCODE *) pTmp->p_list;
        for (i = 0u; i < ep; i++)
        {
            /* Configure interface number for each EP */
            USBCOMM_EP[pEP->addr & USBCOMM_DIR_UNUSED].interface = pEP->interface;
            pEP = &pEP[1u];
        }
        
        /* Init pointer on interface class table */
        USBCOMM_interfaceClass = USBCOMM_GetInterfaceClassTablePtr();
        
    /* Set the endpoint buffer addresses */
    #if (!USBCOMM_EP_MANAGEMENT_DMA_AUTO)
        buffCount = 0u;
        for (ep = USBCOMM_EP1; ep < USBCOMM_MAX_EP; ++ep)
        {
            USBCOMM_EP[ep].buffOffset = buffCount;        
            buffCount += USBCOMM_EP[ep].bufferSize;
            
        #if (USBCOMM_GEN_16BITS_EP_ACCESS)
            /* Align EP buffers to be event size to access 16-bits DR register. */
            buffCount += (0u != (buffCount & 0x01u)) ? 1u : 0u;
        #endif /* (USBCOMM_GEN_16BITS_EP_ACCESS) */            
        }
    #endif /* (!USBCOMM_EP_MANAGEMENT_DMA_AUTO) */

        /* Configure hardware registers */
        USBCOMM_ConfigReg();
    }
}


/*******************************************************************************
* Function Name: USBCOMM_ConfigAltChanged
****************************************************************************//**
*
*  This routine update configuration for the required endpoints only.
*  It is called after SET_INTERFACE request when Static memory allocation used.
*
* \reentrant
*  No.
*
*******************************************************************************/
void USBCOMM_ConfigAltChanged(void) 
{
    uint8 ep;
    uint8 curEp;
    uint8 epType;
    uint8 i;
    uint8 interfaceNum;

    const T_USBCOMM_LUT CYCODE *pTmp;
    const T_USBCOMM_EP_SETTINGS_BLOCK CYCODE *pEP;

    /* Init Endpoints and Device Status if configured */
    if (USBCOMM_configuration > 0u)
    {
        /* Get number of endpoints configurations (ep). */
        pTmp = USBCOMM_GetConfigTablePtr(USBCOMM_configuration - 1u);
        pTmp = &pTmp[1u];
        ep = pTmp->c;

        /* Get pointer to endpoints setting table (pEP). */
        pEP = (const T_USBCOMM_EP_SETTINGS_BLOCK CYCODE *) pTmp->p_list;
        
        /* Look through all possible endpoint configurations. Find endpoints 
        * which belong to current interface and alternate settings for 
        * re-configuration.
        */
        interfaceNum = USBCOMM_interfaceNumber;
        for (i = 0u; i < ep; i++)
        {
            /* Find endpoints which belong to current interface and alternate settings. */
            if ((interfaceNum == pEP->interface) && 
                (USBCOMM_interfaceSetting[interfaceNum] == pEP->altSetting))
            {
                curEp  = ((uint8) pEP->addr & USBCOMM_DIR_UNUSED);
                epType = ((uint8) pEP->attributes & USBCOMM_EP_TYPE_MASK);
                
                /* Change the SIE mode for the selected EP to NAK ALL */
                USBCOMM_EP[curEp].epToggle   = 0u;
                USBCOMM_EP[curEp].addr       = pEP->addr;
                USBCOMM_EP[curEp].attrib     = pEP->attributes;
                USBCOMM_EP[curEp].bufferSize = pEP->bufferSize;

                if (0u != (pEP->addr & USBCOMM_DIR_IN))
                {
                    /* IN Endpoint */
                    USBCOMM_EP[curEp].epMode     = USBCOMM_GET_ACTIVE_IN_EP_CR0_MODE(epType);
                    USBCOMM_EP[curEp].apiEpState = USBCOMM_EVENT_PENDING;
                }
                else
                {
                    /* OUT Endpoint */
                    USBCOMM_EP[curEp].epMode     = USBCOMM_GET_ACTIVE_OUT_EP_CR0_MODE(epType);
                    USBCOMM_EP[curEp].apiEpState = USBCOMM_NO_EVENT_PENDING;
                }
                
                /* Make SIE to NAK any endpoint requests */
                USBCOMM_SIE_EP_BASE.sieEp[curEp].epCr0 = USBCOMM_MODE_NAK_IN_OUT;

            #if (USBCOMM_EP_MANAGEMENT_DMA_AUTO)
                /* Clear IN data ready. */
                USBCOMM_ARB_EP_BASE.arbEp[curEp].epCfg &= (uint8) ~USBCOMM_ARB_EPX_CFG_IN_DATA_RDY;

                /* Select endpoint number of reconfiguration */
                USBCOMM_DYN_RECONFIG_REG = (uint8) ((curEp - 1u) << USBCOMM_DYN_RECONFIG_EP_SHIFT);
                
                /* Request for dynamic re-configuration of endpoint. */
                USBCOMM_DYN_RECONFIG_REG |= USBCOMM_DYN_RECONFIG_ENABLE;
                
                /* Wait until block is ready for re-configuration */
                while (0u == (USBCOMM_DYN_RECONFIG_REG & USBCOMM_DYN_RECONFIG_RDY_STS))
                {
                }
                
                /* Once DYN_RECONFIG_RDY_STS bit is set, FW can change the EP configuration. */
                /* Change EP Type with new direction */
                if (0u != (pEP->addr & USBCOMM_DIR_IN))
                {
                    /* Set endpoint type: 0 - IN and 1 - OUT. */
                    USBCOMM_EP_TYPE_REG &= (uint8) ~(uint8)((uint8) 0x01u << (curEp - 1u));
                    
                #if (CY_PSOC4)
                    /* Clear DMA_TERMIN for IN endpoint */
                    USBCOMM_ARB_EP_BASE.arbEp[curEp].epIntEn &= (uint32) ~USBCOMM_ARB_EPX_INT_DMA_TERMIN;
                #endif /* (CY_PSOC4) */
                }
                else
                {
                    /* Set endpoint type: 0 - IN and 1- OUT. */
                    USBCOMM_EP_TYPE_REG |= (uint8) ((uint8) 0x01u << (curEp - 1u));
                    
                #if (CY_PSOC4)
                    /* Set DMA_TERMIN for OUT endpoint */
                    USBCOMM_ARB_EP_BASE.arbEp[curEp].epIntEn |= (uint32) USBCOMM_ARB_EPX_INT_DMA_TERMIN;
                #endif /* (CY_PSOC4) */
                }
                
                /* Complete dynamic re-configuration: all endpoint related status and signals 
                * are set into the default state.
                */
                USBCOMM_DYN_RECONFIG_REG &= (uint8) ~USBCOMM_DYN_RECONFIG_ENABLE;

            #else
                USBCOMM_SIE_EP_BASE.sieEp[curEp].epCnt0 = HI8(USBCOMM_EP[curEp].bufferSize);
                USBCOMM_SIE_EP_BASE.sieEp[curEp].epCnt1 = LO8(USBCOMM_EP[curEp].bufferSize);
                
                #if (CY_PSOC4)
                    USBCOMM_ARB_EP16_BASE.arbEp[curEp].rwRa16  = (uint32) USBCOMM_EP[curEp].buffOffset;
                    USBCOMM_ARB_EP16_BASE.arbEp[curEp].rwWa16  = (uint32) USBCOMM_EP[curEp].buffOffset;
                #else
                    USBCOMM_ARB_EP_BASE.arbEp[curEp].rwRa    = LO8(USBCOMM_EP[curEp].buffOffset);
                    USBCOMM_ARB_EP_BASE.arbEp[curEp].rwRaMsb = HI8(USBCOMM_EP[curEp].buffOffset);
                    USBCOMM_ARB_EP_BASE.arbEp[curEp].rwWa    = LO8(USBCOMM_EP[curEp].buffOffset);
                    USBCOMM_ARB_EP_BASE.arbEp[curEp].rwWaMsb = HI8(USBCOMM_EP[curEp].buffOffset);
                #endif /* (CY_PSOC4) */                
            #endif /* (USBCOMM_EP_MANAGEMENT_DMA_AUTO) */
            }
            
            pEP = &pEP[1u]; /* Get next EP element */
        }
        
        /* The main loop has to re-enable DMA and OUT endpoint */
    }
}


/*******************************************************************************
* Function Name: USBCOMM_GetConfigTablePtr
****************************************************************************//**
*
*  This routine returns a pointer a configuration table entry
*
*  \param confIndex:  Configuration Index
*
* \return
*  Device Descriptor pointer or NULL when descriptor does not exist.
*
*******************************************************************************/
const T_USBCOMM_LUT CYCODE *USBCOMM_GetConfigTablePtr(uint8 confIndex)
                                                        
{
    /* Device Table */
    const T_USBCOMM_LUT CYCODE *pTmp;

    pTmp = (const T_USBCOMM_LUT CYCODE *) USBCOMM_TABLE[USBCOMM_device].p_list;

    /* The first entry points to the Device Descriptor,
    *  the second entry point to the BOS Descriptor
    *  the rest configuration entries.
    *  Set pointer to the first Configuration Descriptor
    */
    pTmp = &pTmp[2u];
    /* For this table, c is the number of configuration descriptors  */
    if(confIndex >= pTmp->c)   /* Verify that required configuration descriptor exists */
    {
        pTmp = (const T_USBCOMM_LUT CYCODE *) NULL;
    }
    else
    {
        pTmp = (const T_USBCOMM_LUT CYCODE *) pTmp[confIndex].p_list;
    }

    return (pTmp);
}


#if (USBCOMM_BOS_ENABLE)
    /*******************************************************************************
    * Function Name: USBCOMM_GetBOSPtr
    ****************************************************************************//**
    *
    *  This routine returns a pointer a BOS table entry
    *
    *  
    *
    * \return
    *  BOS Descriptor pointer or NULL when descriptor does not exist.
    *
    *******************************************************************************/
    const T_USBCOMM_LUT CYCODE *USBCOMM_GetBOSPtr(void)
                                                            
    {
        /* Device Table */
        const T_USBCOMM_LUT CYCODE *pTmp;

        pTmp = (const T_USBCOMM_LUT CYCODE *) USBCOMM_TABLE[USBCOMM_device].p_list;

        /* The first entry points to the Device Descriptor,
        *  the second entry points to the BOS Descriptor
        */
        pTmp = &pTmp[1u];
        pTmp = (const T_USBCOMM_LUT CYCODE *) pTmp->p_list;
        return (pTmp);
    }
#endif /* (USBCOMM_BOS_ENABLE) */


/*******************************************************************************
* Function Name: USBCOMM_GetDeviceTablePtr
****************************************************************************//**
*
*  This routine returns a pointer to the Device table
*
* \return
*  Device Table pointer
*
*******************************************************************************/
const T_USBCOMM_LUT CYCODE *USBCOMM_GetDeviceTablePtr(void)
                                                            
{
    /* Device Table */
    return( (const T_USBCOMM_LUT CYCODE *) USBCOMM_TABLE[USBCOMM_device].p_list );
}


/*******************************************************************************
* Function Name: USB_GetInterfaceClassTablePtr
****************************************************************************//**
*
*  This routine returns Interface Class table pointer, which contains
*  the relation between interface number and interface class.
*
* \return
*  Interface Class table pointer.
*
*******************************************************************************/
const uint8 CYCODE *USBCOMM_GetInterfaceClassTablePtr(void)
                                                        
{
    const T_USBCOMM_LUT CYCODE *pTmp;
    const uint8 CYCODE *pInterfaceClass;
    uint8 currentInterfacesNum;

    pTmp = USBCOMM_GetConfigTablePtr(USBCOMM_configuration - 1u);
    if (pTmp != NULL)
    {
        currentInterfacesNum  = ((const uint8 *) pTmp->p_list)[USBCOMM_CONFIG_DESCR_NUM_INTERFACES];
        /* Third entry in the LUT starts the Interface Table pointers */
        /* The INTERFACE_CLASS table is located after all interfaces */
        pTmp = &pTmp[currentInterfacesNum + 2u];
        pInterfaceClass = (const uint8 CYCODE *) pTmp->p_list;
    }
    else
    {
        pInterfaceClass = (const uint8 CYCODE *) NULL;
    }

    return (pInterfaceClass);
}


/*******************************************************************************
* Function Name: USBCOMM_TerminateEP
****************************************************************************//**
*
*  This function terminates the specified USBFS endpoint.
*  This function should be used before endpoint reconfiguration.
*
*  \param ep Contains the data endpoint number.
*
*  \reentrant
*  No.
*
* \sideeffect
* 
* The device responds with a NAK for any transactions on the selected endpoint.
*   
*******************************************************************************/
void USBCOMM_TerminateEP(uint8 epNumber) 
{
    /* Get endpoint number */
    epNumber &= USBCOMM_DIR_UNUSED;

    if ((epNumber > USBCOMM_EP0) && (epNumber < USBCOMM_MAX_EP))
    {
        /* Set the endpoint Halt */
        USBCOMM_EP[epNumber].hwEpState |= USBCOMM_ENDPOINT_STATUS_HALT;

        /* Clear the data toggle */
        USBCOMM_EP[epNumber].epToggle = 0u;
        USBCOMM_EP[epNumber].apiEpState = USBCOMM_NO_EVENT_ALLOWED;

        if ((USBCOMM_EP[epNumber].addr & USBCOMM_DIR_IN) != 0u)
        {   
            /* IN Endpoint */
            USBCOMM_SIE_EP_BASE.sieEp[epNumber].epCr0 = USBCOMM_MODE_NAK_IN;
        }
        else
        {
            /* OUT Endpoint */
            USBCOMM_SIE_EP_BASE.sieEp[epNumber].epCr0 = USBCOMM_MODE_NAK_OUT;
        }
    }
}


/*******************************************************************************
* Function Name: USBCOMM_SetEndpointHalt
****************************************************************************//**
*
*  This routine handles set endpoint halt.
*
* \return
*  requestHandled.
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 USBCOMM_SetEndpointHalt(void) 
{
    uint8 requestHandled = USBCOMM_FALSE;
    uint8 ep;
    
    /* Set endpoint halt */
    ep = USBCOMM_wIndexLoReg & USBCOMM_DIR_UNUSED;

    if ((ep > USBCOMM_EP0) && (ep < USBCOMM_MAX_EP))
    {
        /* Set the endpoint Halt */
        USBCOMM_EP[ep].hwEpState |= (USBCOMM_ENDPOINT_STATUS_HALT);

        /* Clear the data toggle */
        USBCOMM_EP[ep].epToggle = 0u;
        USBCOMM_EP[ep].apiEpState |= USBCOMM_NO_EVENT_ALLOWED;

        if ((USBCOMM_EP[ep].addr & USBCOMM_DIR_IN) != 0u)
        {
            /* IN Endpoint */
            USBCOMM_SIE_EP_BASE.sieEp[ep].epCr0 = (USBCOMM_MODE_STALL_DATA_EP | 
                                                            USBCOMM_MODE_ACK_IN);
        }
        else
        {
            /* OUT Endpoint */
            USBCOMM_SIE_EP_BASE.sieEp[ep].epCr0 = (USBCOMM_MODE_STALL_DATA_EP | 
                                                            USBCOMM_MODE_ACK_OUT);
        }
        requestHandled = USBCOMM_InitNoDataControlTransfer();
    }

    return (requestHandled);
}


/*******************************************************************************
* Function Name: USBCOMM_ClearEndpointHalt
****************************************************************************//**
*
*  This routine handles clear endpoint halt.
*
* \return
*  requestHandled.
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 USBCOMM_ClearEndpointHalt(void) 
{
    uint8 requestHandled = USBCOMM_FALSE;
    uint8 ep;

    /* Clear endpoint halt */
    ep = USBCOMM_wIndexLoReg & USBCOMM_DIR_UNUSED;

    if ((ep > USBCOMM_EP0) && (ep < USBCOMM_MAX_EP))
    {
        /* Clear the endpoint Halt */
        USBCOMM_EP[ep].hwEpState &= (uint8) ~USBCOMM_ENDPOINT_STATUS_HALT;

        /* Clear the data toggle */
        USBCOMM_EP[ep].epToggle = 0u;
        
        /* Clear toggle bit for already armed packet */
        USBCOMM_SIE_EP_BASE.sieEp[ep].epCnt0 &= (uint8) ~(uint8)USBCOMM_EPX_CNT_DATA_TOGGLE;
        
        /* Return API State as it was defined before */
        USBCOMM_EP[ep].apiEpState &= (uint8) ~USBCOMM_NO_EVENT_ALLOWED;

        if ((USBCOMM_EP[ep].addr & USBCOMM_DIR_IN) != 0u)
        {
            /* IN Endpoint */
            if(USBCOMM_EP[ep].apiEpState == USBCOMM_IN_BUFFER_EMPTY)
            {       
                /* Wait for next packet from application */
                USBCOMM_SIE_EP_BASE.sieEp[ep].epCr0 = USBCOMM_MODE_NAK_IN;
            }
            else    /* Continue armed transfer */
            {
                USBCOMM_SIE_EP_BASE.sieEp[ep].epCr0 = USBCOMM_MODE_ACK_IN;
            }
        }
        else
        {
            /* OUT Endpoint */
            if (USBCOMM_EP[ep].apiEpState == USBCOMM_OUT_BUFFER_FULL)
            {       
                /* Allow application to read full buffer */
                USBCOMM_SIE_EP_BASE.sieEp[ep].epCr0 = USBCOMM_MODE_NAK_OUT;
            }
            else    /* Mark endpoint as empty, so it will be reloaded */
            {
                USBCOMM_SIE_EP_BASE.sieEp[ep].epCr0 = USBCOMM_MODE_ACK_OUT;
            }
        }
        
        requestHandled = USBCOMM_InitNoDataControlTransfer();
    }

    return(requestHandled);
}


/*******************************************************************************
* Function Name: USBCOMM_ValidateAlternateSetting
****************************************************************************//**
*
*  Validates (and records) a SET INTERFACE request.
*
* \return
*  requestHandled.
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 USBCOMM_ValidateAlternateSetting(void) 
{
    uint8 requestHandled = USBCOMM_FALSE;
    
    uint8 interfaceNum;
    uint8 curInterfacesNum;
    const T_USBCOMM_LUT CYCODE *pTmp;
    
    /* Get interface number from the request. */
    interfaceNum = (uint8) USBCOMM_wIndexLoReg;
    
    /* Get number of interfaces for current configuration. */
    pTmp = USBCOMM_GetConfigTablePtr(USBCOMM_configuration - 1u);
    curInterfacesNum  = ((const uint8 *) pTmp->p_list)[USBCOMM_CONFIG_DESCR_NUM_INTERFACES];

    /* Validate that interface number is within range. */
    if ((interfaceNum <= curInterfacesNum) || (interfaceNum <= USBCOMM_MAX_INTERFACES_NUMBER))
    {
        /* Save current and new alternate settings (come with request) to make 
        * desicion about following endpoint re-configuration.
        */
        USBCOMM_interfaceSettingLast[interfaceNum] = USBCOMM_interfaceSetting[interfaceNum];
        USBCOMM_interfaceSetting[interfaceNum]     = (uint8) USBCOMM_wValueLoReg;
        
        requestHandled = USBCOMM_TRUE;
    }

    return (requestHandled);
}


/* [] END OF FILE */

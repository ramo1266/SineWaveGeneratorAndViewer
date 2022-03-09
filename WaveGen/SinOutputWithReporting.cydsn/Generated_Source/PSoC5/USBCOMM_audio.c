/***************************************************************************//**
* \file USBCOMM_audio.c
* \version 3.20
*
* \brief
*  This file contains the USB AUDIO Class request handler.
*
* Related Document:
*  Universal Serial Bus Device Class Definition for Audio Devices Release 1.0
*
********************************************************************************
* \copyright
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "USBCOMM_audio.h"
#include "USBCOMM_pvt.h"
#include "cyapicallbacks.h"

#if defined(USBCOMM_ENABLE_AUDIO_CLASS)

/***************************************
* Custom Declarations
***************************************/

/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */


#if !defined(USER_SUPPLIED_AUDIO_HANDLER)

/***************************************
*    AUDIO Variables
***************************************/

#if defined(USBCOMM_ENABLE_AUDIO_STREAMING)
    /** Contains the current audio sample frequency. It is set by the host using a SET_CUR request to the endpoint.*/
    volatile uint8 USBCOMM_currentSampleFrequency[USBCOMM_MAX_EP][USBCOMM_SAMPLE_FREQ_LEN];
    /** Used as a flag for the user code, to inform it that the host has been sent a request 
     * to change the sample frequency. The sample frequency will be sent on the next OUT transaction. 
     * It contains the endpoint address when set. The following code is recommended for 
     * detecting new sample frequency in main code:
     * \snippet  /USBFS_sut_02.cydsn/main.c Detecting new Sample Frequency
     *     
     * The USBFS_transferState variable is checked to make sure that the transfer completes. */
    volatile uint8 USBCOMM_frequencyChanged;
    /** Contains the mute configuration set by the host.*/
    volatile uint8 USBCOMM_currentMute;
    /** Contains the volume level set by the host.*/
    volatile uint8 USBCOMM_currentVolume[USBCOMM_VOLUME_LEN];
    volatile uint8 USBCOMM_minimumVolume[USBCOMM_VOLUME_LEN] = {USBCOMM_VOL_MIN_LSB,
                                                                                  USBCOMM_VOL_MIN_MSB};
    volatile uint8 USBCOMM_maximumVolume[USBCOMM_VOLUME_LEN] = {USBCOMM_VOL_MAX_LSB,
                                                                                  USBCOMM_VOL_MAX_MSB};
    volatile uint8 USBCOMM_resolutionVolume[USBCOMM_VOLUME_LEN] = {USBCOMM_VOL_RES_LSB,
                                                                                     USBCOMM_VOL_RES_MSB};
#endif /*  USBCOMM_ENABLE_AUDIO_STREAMING */


/*******************************************************************************
* Function Name: USBCOMM_DispatchAUDIOClassRqst
****************************************************************************//**
*
*  This routine dispatches class requests
*
* \return
*  Results of Audio Class request handling: 
*  - USBCOMM_TRUE  - request was handled without errors
*  - USBCOMM_FALSE - error occurs during handling of request     
*
* \globalvars
*   USBCOMM_currentSampleFrequency: Contains the current audio Sample
*       Frequency. It is set by the Host using SET_CUR request to the endpoint.
*   USBCOMM_frequencyChanged: This variable is used as a flag for the
*       user code, to be aware that Host has been sent request for changing
*       Sample Frequency. Sample frequency will be sent on the next OUT
*       transaction. It is contains endpoint address when set. The following
*       code is recommended for detecting new Sample Frequency in main code:
*       
*  \snippet  /USBFS_sut_02.cydsn/main.c Detecting new Sample Frequency
*      
*   USBCOMM_transferState variable is checked to be sure that transfer
*              completes.
*   USBCOMM_currentMute: Contains mute configuration set by Host.
*   USBCOMM_currentVolume: Contains volume level set by Host.
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 USBCOMM_DispatchAUDIOClassRqst(void) 
{
    uint8 requestHandled = USBCOMM_FALSE;
    
    uint8 RqstRcpt = (uint8)(USBCOMM_bmRequestTypeReg & USBCOMM_RQST_RCPT_MASK);
#if defined(USBCOMM_ENABLE_AUDIO_STREAMING)
    uint8 wValueHi = (uint8) USBCOMM_wValueHiReg;
    uint8 epNumber = (uint8) USBCOMM_wIndexLoReg & USBCOMM_DIR_UNUSED;
#endif /* (USBCOMM_ENABLE_AUDIO_STREAMING) */
    
    /* Check request direction: D2H or H2D. */
    if (0u != (USBCOMM_bmRequestTypeReg & USBCOMM_RQST_DIR_D2H))
    {
        /* Handle direction from device to host. */
        
        if (USBCOMM_RQST_RCPT_EP == RqstRcpt)
        {
            /* Request recipient is to endpoint. */
            switch (USBCOMM_bRequestReg)
            {
                case USBCOMM_GET_CUR:
                #if defined(USBCOMM_ENABLE_AUDIO_STREAMING)
                    if (wValueHi == USBCOMM_SAMPLING_FREQ_CONTROL)
                    {
                         /* point Control Selector is Sampling Frequency */
                        USBCOMM_currentTD.wCount = USBCOMM_SAMPLE_FREQ_LEN;
                        USBCOMM_currentTD.pData  = USBCOMM_currentSampleFrequency[epNumber];
                        
                        requestHandled   = USBCOMM_InitControlRead();
                    }
                #endif /* (USBCOMM_ENABLE_AUDIO_STREAMING) */
                
                    /* `#START AUDIO_READ_REQUESTS` Place other request handler here */

                    /* `#END` */
                
                #ifdef USBCOMM_DISPATCH_AUDIO_CLASS_AUDIO_READ_REQUESTS_CALLBACK    
                    USBCOMM_DispatchAUDIOClass_AUDIO_READ_REQUESTS_Callback();
                #endif /* (USBCOMM_DISPATCH_AUDIO_CLASS_AUDIO_READ_REQUESTS_CALLBACK) */                   
                break;
                
                default:
                    /* Do not handle this request unless callback is defined. */
                    break;
            }
        
        }
        else if (USBCOMM_RQST_RCPT_IFC == RqstRcpt)
        {
            /* Request recipient is interface or entity ID. */
            switch (USBCOMM_bRequestReg)
            {
                case USBCOMM_GET_CUR:
                #if defined(USBCOMM_ENABLE_AUDIO_STREAMING)
                    if (wValueHi == USBCOMM_MUTE_CONTROL)
                    {
                        /* `#START MUTE_CONTROL_GET_REQUEST` Place multi-channel handler here */

                        /* `#END` */

                    #ifdef USBCOMM_DISPATCH_AUDIO_CLASS_MUTE_CONTROL_GET_REQUEST_CALLBACK
                        USBCOMM_DispatchAUDIOClass_MUTE_CONTROL_GET_REQUEST_Callback();
                    #endif /* (USBCOMM_DISPATCH_AUDIO_CLASS_MUTE_CONTROL_GET_REQUEST_CALLBACK) */

                        /* Entity ID Control Selector is MUTE */
                        USBCOMM_currentTD.wCount = 1u;
                        USBCOMM_currentTD.pData  = &USBCOMM_currentMute;
                        
                        requestHandled = USBCOMM_InitControlRead();
                    }
                    else if (wValueHi == USBCOMM_VOLUME_CONTROL)
                    {
                        /* `#START VOLUME_CONTROL_GET_REQUEST` Place multi-channel handler here */

                        /* `#END` */

                    #ifdef USBCOMM_DISPATCH_AUDIO_CLASS_VOLUME_CONTROL_GET_REQUEST_CALLBACK
                        USBCOMM_DispatchAUDIOClass_VOLUME_CONTROL_GET_REQUEST_Callback();
                    #endif /* (USBCOMM_DISPATCH_AUDIO_CLASS_VOLUME_CONTROL_GET_REQUEST_CALLBACK) */

                        /* Entity ID Control Selector is VOLUME, */
                        USBCOMM_currentTD.wCount = USBCOMM_VOLUME_LEN;
                        USBCOMM_currentTD.pData  = USBCOMM_currentVolume;
                        
                        requestHandled = USBCOMM_InitControlRead();
                    }
                    else
                    {
                        /* `#START OTHER_GET_CUR_REQUESTS` Place other request handler here */

                        /* `#END` */

                    #ifdef USBCOMM_DISPATCH_AUDIO_CLASS_OTHER_GET_CUR_REQUESTS_CALLBACK
                        USBCOMM_DispatchAUDIOClass_OTHER_GET_CUR_REQUESTS_Callback();
                    #endif /* (USBCOMM_DISPATCH_AUDIO_CLASS_OTHER_GET_CUR_REQUESTS_CALLBACK) */
                    }
                    break;
                    
                case USBCOMM_GET_MIN:
                    if (wValueHi == USBCOMM_VOLUME_CONTROL)
                    {
                        /* Entity ID Control Selector is VOLUME, */
                        USBCOMM_currentTD.wCount = USBCOMM_VOLUME_LEN;
                        USBCOMM_currentTD.pData  = &USBCOMM_minimumVolume[0];
                        
                        requestHandled = USBCOMM_InitControlRead();
                    }
                    break;
                    
                case USBCOMM_GET_MAX:
                    if (wValueHi == USBCOMM_VOLUME_CONTROL)
                    {
                        /* Entity ID Control Selector is VOLUME, */
                        USBCOMM_currentTD.wCount = USBCOMM_VOLUME_LEN;
                        USBCOMM_currentTD.pData  = &USBCOMM_maximumVolume[0];
                        
                        requestHandled = USBCOMM_InitControlRead();
                    }
                    break;
                    
                case USBCOMM_GET_RES:
                    if (wValueHi == USBCOMM_VOLUME_CONTROL)
                    {
                         /* Entity ID Control Selector is VOLUME, */
                        USBCOMM_currentTD.wCount = USBCOMM_VOLUME_LEN;
                        USBCOMM_currentTD.pData  = &USBCOMM_resolutionVolume[0];
                        
                        requestHandled   = USBCOMM_InitControlRead();
                    }
                    break;
                    
                /* The contents of the status message is reserved for future use.
                * For the time being, a null packet should be returned in the data stage of the
                * control transfer, and the received null packet should be ACKed.
                */
                case USBCOMM_GET_STAT:
                    USBCOMM_currentTD.wCount = 0u;    
                    
                    requestHandled = USBCOMM_InitControlWrite();

                #endif /* (USBCOMM_ENABLE_AUDIO_STREAMING) */
                
                    /* `#START AUDIO_WRITE_REQUESTS` Place other request handler here */

                    /* `#END` */
                
                #ifdef USBCOMM_DISPATCH_AUDIO_CLASS_AUDIO_WRITE_REQUESTS_CALLBACK
                    USBCOMM_DispatchAUDIOClass_AUDIO_WRITE_REQUESTS_Callback();
                #endif /* (USBCOMM_DISPATCH_AUDIO_CLASS_AUDIO_WRITE_REQUESTS_CALLBACK) */
                    break;
                
                default:
                    /* Do not handle this request. */
                    break;
            }
        }
        else
        {   
            /* Do not handle other requests recipients. */
        }
    }
    else
    {
        /* Handle direction from host to device. */
        
        if (USBCOMM_RQST_RCPT_EP == RqstRcpt)
        {
            /* Request recipient is endpoint. */
            switch (USBCOMM_bRequestReg)
            {
                case USBCOMM_SET_CUR:
                #if defined(USBCOMM_ENABLE_AUDIO_STREAMING)
                    if (wValueHi == USBCOMM_SAMPLING_FREQ_CONTROL)
                    {
                         /* point Control Selector is Sampling Frequency */
                        USBCOMM_currentTD.wCount = USBCOMM_SAMPLE_FREQ_LEN;
                        USBCOMM_currentTD.pData  = USBCOMM_currentSampleFrequency[epNumber];
                        USBCOMM_frequencyChanged = (uint8) epNumber;
                        
                        requestHandled   = USBCOMM_InitControlWrite();
                    }
                #endif /* (USBCOMM_ENABLE_AUDIO_STREAMING) */

                    /* `#START AUDIO_SAMPLING_FREQ_REQUESTS` Place other request handler here */

                    /* `#END` */

                #ifdef USBCOMM_DISPATCH_AUDIO_CLASS_AUDIO_SAMPLING_FREQ_REQUESTS_CALLBACK
                    USBCOMM_DispatchAUDIOClass_AUDIO_SAMPLING_FREQ_REQUESTS_Callback();
                #endif /* (USBCOMM_DISPATCH_AUDIO_CLASS_AUDIO_SAMPLING_FREQ_REQUESTS_CALLBACK) */
                    break;
                
                default:
                    /* Do not handle this request. */
                    break;
            }
        }
        else if(USBCOMM_RQST_RCPT_IFC == RqstRcpt)
        {
            /* Request recipient is interface or entity ID. */
            switch (USBCOMM_bRequestReg)
            {
                case USBCOMM_SET_CUR:
                #if defined(USBCOMM_ENABLE_AUDIO_STREAMING)
                    if (wValueHi == USBCOMM_MUTE_CONTROL)
                    {
                        /* `#START MUTE_SET_REQUEST` Place multi-channel handler here */

                        /* `#END` */

                    #ifdef USBCOMM_DISPATCH_AUDIO_CLASS_MUTE_SET_REQUEST_CALLBACK
                        USBCOMM_DispatchAUDIOClass_MUTE_SET_REQUEST_Callback();
                    #endif /* (USBCOMM_DISPATCH_AUDIO_CLASS_MUTE_SET_REQUEST_CALLBACK) */

                        /* Entity ID Control Selector is MUTE */
                        USBCOMM_currentTD.wCount = 1u;
                        USBCOMM_currentTD.pData  = &USBCOMM_currentMute;
                        
                        requestHandled = USBCOMM_InitControlWrite();
                    }
                    else if (wValueHi == USBCOMM_VOLUME_CONTROL)
                    {
                        /* `#START VOLUME_CONTROL_SET_REQUEST` Place multi-channel handler here */

                        /* `#END` */

                    #ifdef USBCOMM_DISPATCH_AUDIO_CLASS_VOLUME_CONTROL_SET_REQUEST_CALLBACK
                        USBCOMM_DispatchAUDIOClass_VOLUME_CONTROL_SET_REQUEST_Callback();
                    #endif /* (USBCOMM_DISPATCH_AUDIO_CLASS_VOLUME_CONTROL_SET_REQUEST_CALLBACK) */

                        /* Entity ID Control Selector is VOLUME */
                        USBCOMM_currentTD.wCount = USBCOMM_VOLUME_LEN;
                        USBCOMM_currentTD.pData  = USBCOMM_currentVolume;
                        
                        requestHandled = USBCOMM_InitControlWrite();
                    }
                    else
                    {
                        /* `#START OTHER_SET_CUR_REQUESTS` Place other request handler here */

                        /* `#END` */

                    #ifdef USBCOMM_DISPATCH_AUDIO_CLASS_OTHER_SET_CUR_REQUESTS_CALLBACK
                        USBCOMM_DispatchAUDIOClass_OTHER_SET_CUR_REQUESTS_Callback();
                    #endif /* (USBCOMM_DISPATCH_AUDIO_CLASS_OTHER_SET_CUR_REQUESTS_CALLBACK) */
                    }
                #endif /*  USBCOMM_ENABLE_AUDIO_STREAMING */
                
                
                    /* `#START AUDIO_CONTROL_SEL_REQUESTS` Place other request handler here */

                    /* `#END` */
                    
                #ifdef USBCOMM_DISPATCH_AUDIO_CLASS_AUDIO_CONTROL_SEL_REQUESTS_CALLBACK
                    USBCOMM_DispatchAUDIOClass_AUDIO_CONTROL_SEL_REQUESTS_Callback();
                #endif /* (USBCOMM_DISPATCH_AUDIO_CLASS_AUDIO_CONTROL_SEL_REQUESTS_CALLBACK) */
                break;

                default:
                    /* Do not handle this request. */
                break;
            }
        }
        else
        {
            /* Do not handle other requests recipients. */
        }
    }

    return (requestHandled);
}
#endif /* (USER_SUPPLIED_AUDIO_HANDLER) */


/*******************************************************************************
* Additional user functions supporting AUDIO Requests
********************************************************************************/

/* `#START AUDIO_FUNCTIONS` Place any additional functions here */

/* `#END` */

#endif  /* (USBCOMM_ENABLE_AUDIO_CLASS) */


/* [] END OF FILE */

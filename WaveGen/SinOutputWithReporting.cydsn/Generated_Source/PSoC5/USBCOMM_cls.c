/***************************************************************************//**
* \file USBCOMM_cls.c
* \version 3.20
*
* \brief
*  This file contains the USB Class request handler.
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

#if(USBCOMM_EXTERN_CLS == USBCOMM_FALSE)

/***************************************
* User Implemented Class Driver Declarations.
***************************************/
/* `#START USER_DEFINED_CLASS_DECLARATIONS` Place your declaration here */

/* `#END` */


/*******************************************************************************
* Function Name: USBCOMM_DispatchClassRqst
****************************************************************************//**
*  This routine dispatches class specific requests depend on interface class.
*
* \return
*  requestHandled.
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 USBCOMM_DispatchClassRqst(void) 
{
    uint8 interfaceNumber;
    uint8 requestHandled = USBCOMM_FALSE;

    /* Get interface to which request is intended. */
    switch (USBCOMM_bmRequestTypeReg & USBCOMM_RQST_RCPT_MASK)
    {
        case USBCOMM_RQST_RCPT_IFC:
            /* Class-specific request directed to interface: wIndexLoReg 
            * contains interface number.
            */
            interfaceNumber = (uint8) USBCOMM_wIndexLoReg;
            break;
        
        case USBCOMM_RQST_RCPT_EP:
            /* Class-specific request directed to endpoint: wIndexLoReg contains 
            * endpoint number. Find interface related to endpoint. 
            */
            interfaceNumber = USBCOMM_EP[USBCOMM_wIndexLoReg & USBCOMM_DIR_UNUSED].interface;
            break;
            
        default:
            /* Default interface is zero. */
            interfaceNumber = 0u;
            break;
    }
    
    /* Check that interface is within acceptable range */
    if (interfaceNumber <= USBCOMM_MAX_INTERFACES_NUMBER)
    {
    #if (defined(USBCOMM_ENABLE_HID_CLASS)   || \
         defined(USBCOMM_ENABLE_AUDIO_CLASS) || \
         defined(USBCOMM_ENABLE_CDC_CLASS)   || \
         USBCOMM_ENABLE_MSC_CLASS)

        /* Handle class request depends on interface type. */
        switch (USBCOMM_interfaceClass[interfaceNumber])
        {
        #if defined(USBCOMM_ENABLE_HID_CLASS)
            case USBCOMM_CLASS_HID:
                requestHandled = USBCOMM_DispatchHIDClassRqst();
                break;
        #endif /* (USBCOMM_ENABLE_HID_CLASS) */
                
        #if defined(USBCOMM_ENABLE_AUDIO_CLASS)
            case USBCOMM_CLASS_AUDIO:
                requestHandled = USBCOMM_DispatchAUDIOClassRqst();
                break;
        #endif /* (USBCOMM_CLASS_AUDIO) */
                
        #if defined(USBCOMM_ENABLE_CDC_CLASS)
            case USBCOMM_CLASS_CDC:
                requestHandled = USBCOMM_DispatchCDCClassRqst();
                break;
        #endif /* (USBCOMM_ENABLE_CDC_CLASS) */
            
        #if (USBCOMM_ENABLE_MSC_CLASS)
            case USBCOMM_CLASS_MSD:
            #if (USBCOMM_HANDLE_MSC_REQUESTS)
                /* MSC requests are handled by the component. */
                requestHandled = USBCOMM_DispatchMSCClassRqst();
            #elif defined(USBCOMM_DISPATCH_MSC_CLASS_RQST_CALLBACK)
                /* MSC requests are handled by user defined callbcak. */
                requestHandled = USBCOMM_DispatchMSCClassRqst_Callback();
            #else
                /* MSC requests are not handled. */
                requestHandled = USBCOMM_FALSE;
            #endif /* (USBCOMM_HANDLE_MSC_REQUESTS) */
                break;
        #endif /* (USBCOMM_ENABLE_MSC_CLASS) */
            
            default:
                /* Request is not handled: unknown class request type. */
                requestHandled = USBCOMM_FALSE;
                break;
        }
    #endif /* Class support is enabled */
    }
    
    /* `#START USER_DEFINED_CLASS_CODE` Place your Class request here */

    /* `#END` */

#ifdef USBCOMM_DISPATCH_CLASS_RQST_CALLBACK
    if (USBCOMM_FALSE == requestHandled)
    {
        requestHandled = USBCOMM_DispatchClassRqst_Callback(interfaceNumber);
    }
#endif /* (USBCOMM_DISPATCH_CLASS_RQST_CALLBACK) */

    return (requestHandled);
}


/*******************************************************************************
* Additional user functions supporting Class Specific Requests
********************************************************************************/

/* `#START CLASS_SPECIFIC_FUNCTIONS` Place any additional functions here */

/* `#END` */

#endif /* USBCOMM_EXTERN_CLS */


/* [] END OF FILE */

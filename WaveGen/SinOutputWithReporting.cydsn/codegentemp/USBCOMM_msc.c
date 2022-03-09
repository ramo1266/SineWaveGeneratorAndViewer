/***************************************************************************//**
* \file USBCOMM_cdc.c
* \version 3.20
*
* \brief
*  This file contains the USB MSC Class request handler and global API for MSC 
*  class.
*
* Related Document:
*  Universal Serial Bus Class Definitions for Communication Devices Version 1.1
*
********************************************************************************
* \copyright
* Copyright 2012-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "USBCOMM_msc.h"
#include "USBCOMM_pvt.h"
#include "cyapicallbacks.h"

#if (USBCOMM_HANDLE_MSC_REQUESTS)

/***************************************
*          Internal variables
***************************************/

static uint8 USBCOMM_lunCount = USBCOMM_MSC_LUN_NUMBER;


/*******************************************************************************
* Function Name: USBCOMM_DispatchMSCClassRqst
****************************************************************************//**
*   
*  \internal 
*  This routine dispatches MSC class requests.
*
* \return
*  Status of request processing: handled or not handled.
*
* \globalvars
*  USBCOMM_lunCount - stores number of LUN (logical units).
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 USBCOMM_DispatchMSCClassRqst(void) 
{
    uint8 requestHandled = USBCOMM_FALSE;
    
    /* Get request data. */
    uint16 value  = USBCOMM_GET_UINT16(USBCOMM_wValueHiReg,  USBCOMM_wValueLoReg);
    uint16 dataLength = USBCOMM_GET_UINT16(USBCOMM_wLengthHiReg, USBCOMM_wLengthLoReg);
       
    /* Check request direction: D2H or H2D. */
    if (0u != (USBCOMM_bmRequestTypeReg & USBCOMM_RQST_DIR_D2H))
    {
        /* Handle direction from device to host. */
        
        if (USBCOMM_MSC_GET_MAX_LUN == USBCOMM_bRequestReg)
        {
            /* Check request fields. */
            if ((value  == USBCOMM_MSC_GET_MAX_LUN_WVALUE) &&
                (dataLength == USBCOMM_MSC_GET_MAX_LUN_WLENGTH))
            {
                /* Reply to Get Max LUN request: setup control read. */
                USBCOMM_currentTD.pData = &USBCOMM_lunCount;
                USBCOMM_currentTD.count =  USBCOMM_MSC_GET_MAX_LUN_WLENGTH;
                
                requestHandled  = USBCOMM_InitControlRead();
            }
        }
    }
    else
    {
        /* Handle direction from host to device. */
        
        if (USBCOMM_MSC_RESET == USBCOMM_bRequestReg)
        {
            /* Check request fields. */
            if ((value  == USBCOMM_MSC_RESET_WVALUE) &&
                (dataLength == USBCOMM_MSC_RESET_WLENGTH))
            {
                /* Handle to Bulk-Only Reset request: no data control transfer. */
                USBCOMM_currentTD.count = USBCOMM_MSC_RESET_WLENGTH;
                
            #ifdef USBCOMM_DISPATCH_MSC_CLASS_MSC_RESET_RQST_CALLBACK
                USBCOMM_DispatchMSCClass_MSC_RESET_RQST_Callback();
            #endif /* (USBCOMM_DISPATCH_MSC_CLASS_MSC_RESET_RQST_CALLBACK) */
                
                requestHandled = USBCOMM_InitNoDataControlTransfer();
            }
        }
    }
    
    return (requestHandled);
}


/*******************************************************************************
* Function Name: USBCOMM_MSC_SetLunCount
****************************************************************************//**
*
*  This function sets the number of logical units supported in the application. 
*  The default number of logical units is set in the component customizer.
*
*  \param lunCount: Count of the logical units. Valid range is between 1 and 16.
*
*
* \globalvars
*  USBCOMM_lunCount - stores number of LUN (logical units).
*
* \reentrant
*  No.
*
*******************************************************************************/
void USBCOMM_MSC_SetLunCount(uint8 lunCount) 
{
    USBCOMM_lunCount = (lunCount - 1u);
}


/*******************************************************************************
* Function Name: USBCOMM_MSC_GetLunCount
****************************************************************************//**
*
*  This function returns the number of logical units.
*
* \return
*   Number of the logical units.
*
* \globalvars
*  USBCOMM_lunCount - stores number of LUN (logical units).
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 USBCOMM_MSC_GetLunCount(void) 
{
    return (USBCOMM_lunCount + 1u);
}   

#endif /* (USBCOMM_HANDLE_MSC_REQUESTS) */


/* [] END OF FILE */

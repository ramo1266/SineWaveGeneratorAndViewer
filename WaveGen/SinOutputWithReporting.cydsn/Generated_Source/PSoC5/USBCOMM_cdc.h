/***************************************************************************//**
* \file USBCOMM_cdc.h
* \version 3.20
*
* \brief
*  This file provides function prototypes and constants for the USBFS component 
*  CDC class.
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

#if !defined(CY_USBFS_USBCOMM_cdc_H)
#define CY_USBFS_USBCOMM_cdc_H

#include "USBCOMM.h"


/*******************************************************************************
* Prototypes of the USBCOMM_cdc API.
*******************************************************************************/
/**
* \addtogroup group_cdc
* @{
*/
#if (USBCOMM_ENABLE_CDC_CLASS_API != 0u)
    uint8 USBCOMM_CDC_Init(void)            ;
    void USBCOMM_PutData(const uint8* pData, uint16 length) ;
    void USBCOMM_PutString(const char8 string[])            ;
    void USBCOMM_PutChar(char8 txDataByte) ;
    void USBCOMM_PutCRLF(void)             ;
    uint16 USBCOMM_GetCount(void)          ;
    uint8  USBCOMM_CDCIsReady(void)        ;
    uint8  USBCOMM_DataIsReady(void)       ;
    uint16 USBCOMM_GetData(uint8* pData, uint16 length)     ;
    uint16 USBCOMM_GetAll(uint8* pData)    ;
    uint8  USBCOMM_GetChar(void)           ;
    uint8  USBCOMM_IsLineChanged(void)     ;
    uint32 USBCOMM_GetDTERate(void)        ;
    uint8  USBCOMM_GetCharFormat(void)     ;
    uint8  USBCOMM_GetParityType(void)     ;
    uint8  USBCOMM_GetDataBits(void)       ;
    uint16 USBCOMM_GetLineControl(void)    ;
    void USBCOMM_SendSerialState (uint16 serialState) ;
    uint16 USBCOMM_GetSerialState (void)   ;
    void USBCOMM_SetComPort (uint8 comNumber) ;
    uint8 USBCOMM_GetComPort (void)        ;
    uint8 USBCOMM_NotificationIsReady(void) ;

#endif  /* (USBCOMM_ENABLE_CDC_CLASS_API) */
/** @} cdc */

/*******************************************************************************
*  Constants for USBCOMM_cdc API.
*******************************************************************************/

/* CDC Class-Specific Request Codes (CDC ver 1.2 Table 19) */
#define USBCOMM_CDC_SET_LINE_CODING        (0x20u)
#define USBCOMM_CDC_GET_LINE_CODING        (0x21u)
#define USBCOMM_CDC_SET_CONTROL_LINE_STATE (0x22u)

/*PSTN Subclass Specific Notifications (CDC ver 1.2 Table 30)*/
#define USBCOMM_SERIAL_STATE               (0x20u)

#define USBCOMM_LINE_CODING_CHANGED        (0x01u)
#define USBCOMM_LINE_CONTROL_CHANGED       (0x02u)

#define USBCOMM_1_STOPBIT                  (0x00u)
#define USBCOMM_1_5_STOPBITS               (0x01u)
#define USBCOMM_2_STOPBITS                 (0x02u)

#define USBCOMM_PARITY_NONE                (0x00u)
#define USBCOMM_PARITY_ODD                 (0x01u)
#define USBCOMM_PARITY_EVEN                (0x02u)
#define USBCOMM_PARITY_MARK                (0x03u)
#define USBCOMM_PARITY_SPACE               (0x04u)

#define USBCOMM_LINE_CODING_SIZE           (0x07u)
#define USBCOMM_LINE_CODING_RATE           (0x00u)
#define USBCOMM_LINE_CODING_STOP_BITS      (0x04u)
#define USBCOMM_LINE_CODING_PARITY         (0x05u)
#define USBCOMM_LINE_CODING_DATA_BITS      (0x06u)

#define USBCOMM_LINE_CONTROL_DTR           (0x01u)
#define USBCOMM_LINE_CONTROL_RTS           (0x02u)

#define USBCOMM_MAX_MULTI_COM_NUM          (2u) 

#define USBCOMM_COM_PORT1                  (0u) 
#define USBCOMM_COM_PORT2                  (1u) 

#define USBCOMM_SUCCESS                    (0u)
#define USBCOMM_FAILURE                    (1u)

#define USBCOMM_SERIAL_STATE_SIZE          (10u)

/* SerialState constants*/
#define USBCOMM_SERIAL_STATE_REQUEST_TYPE  (0xA1u)
#define USBCOMM_SERIAL_STATE_LENGTH        (0x2u)

/*******************************************************************************
* External data references
*******************************************************************************/
/**
* \addtogroup group_cdc
* @{
*/
extern volatile uint8  USBCOMM_linesCoding[USBCOMM_MAX_MULTI_COM_NUM][USBCOMM_LINE_CODING_SIZE];
extern volatile uint8  USBCOMM_linesChanged[USBCOMM_MAX_MULTI_COM_NUM];
extern volatile uint16 USBCOMM_linesControlBitmap[USBCOMM_MAX_MULTI_COM_NUM];
extern volatile uint16 USBCOMM_serialStateBitmap[USBCOMM_MAX_MULTI_COM_NUM];
extern volatile uint8  USBCOMM_cdcDataInEp[USBCOMM_MAX_MULTI_COM_NUM];
extern volatile uint8  USBCOMM_cdcDataOutEp[USBCOMM_MAX_MULTI_COM_NUM];
extern volatile uint8  USBCOMM_cdcCommInInterruptEp[USBCOMM_MAX_MULTI_COM_NUM];
/** @} cdc */

/*******************************************************************************
* The following code is DEPRECATED and
* must not be used.
*******************************************************************************/


#define USBCOMM_lineCoding             USBCOMM_linesCoding[0]
#define USBCOMM_lineChanged            USBCOMM_linesChanged[0]
#define USBCOMM_lineControlBitmap      USBCOMM_linesControlBitmap[0]
#define USBCOMM_cdc_data_in_ep         USBCOMM_cdcDataInEp[0]
#define USBCOMM_cdc_data_out_ep        USBCOMM_cdcDataOutEp[0]

#endif /* (CY_USBFS_USBCOMM_cdc_H) */


/* [] END OF FILE */

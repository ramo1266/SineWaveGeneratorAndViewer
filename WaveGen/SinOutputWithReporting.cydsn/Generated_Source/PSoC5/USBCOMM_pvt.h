/***************************************************************************//**
* \file .h
* \version 3.20
*
* \brief
*  This file provides private function prototypes and constants for the 
*  USBFS component. It is not intended to be used in the user project.
*
********************************************************************************
* \copyright
* Copyright 2013-2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_USBFS_USBCOMM_pvt_H)
#define CY_USBFS_USBCOMM_pvt_H

#include "USBCOMM.h"
   
#ifdef USBCOMM_ENABLE_AUDIO_CLASS
    #include "USBCOMM_audio.h"
#endif /* USBCOMM_ENABLE_AUDIO_CLASS */

#ifdef USBCOMM_ENABLE_CDC_CLASS
    #include "USBCOMM_cdc.h"
#endif /* USBCOMM_ENABLE_CDC_CLASS */

#if (USBCOMM_ENABLE_MIDI_CLASS)
    #include "USBCOMM_midi.h"
#endif /* (USBCOMM_ENABLE_MIDI_CLASS) */

#if (USBCOMM_ENABLE_MSC_CLASS)
    #include "USBCOMM_msc.h"
#endif /* (USBCOMM_ENABLE_MSC_CLASS) */

#if (USBCOMM_EP_MANAGEMENT_DMA)
    #if (CY_PSOC4)
        #include <CyDMA.h>
    #else
        #include <CyDmac.h>
        #if ((USBCOMM_EP_MANAGEMENT_DMA_AUTO) && (USBCOMM_EP_DMA_AUTO_OPT == 0u))
            #include "USBCOMM_EP_DMA_Done_isr.h"
            #include "USBCOMM_EP8_DMA_Done_SR.h"
            #include "USBCOMM_EP17_DMA_Done_SR.h"
        #endif /* ((USBCOMM_EP_MANAGEMENT_DMA_AUTO) && (USBCOMM_EP_DMA_AUTO_OPT == 0u)) */
    #endif /* (CY_PSOC4) */
#endif /* (USBCOMM_EP_MANAGEMENT_DMA) */

#if (USBCOMM_DMA1_ACTIVE)
    #include "USBCOMM_ep1_dma.h"
    #define USBCOMM_EP1_DMA_CH     (USBCOMM_ep1_dma_CHANNEL)
#endif /* (USBCOMM_DMA1_ACTIVE) */

#if (USBCOMM_DMA2_ACTIVE)
    #include "USBCOMM_ep2_dma.h"
    #define USBCOMM_EP2_DMA_CH     (USBCOMM_ep2_dma_CHANNEL)
#endif /* (USBCOMM_DMA2_ACTIVE) */

#if (USBCOMM_DMA3_ACTIVE)
    #include "USBCOMM_ep3_dma.h"
    #define USBCOMM_EP3_DMA_CH     (USBCOMM_ep3_dma_CHANNEL)
#endif /* (USBCOMM_DMA3_ACTIVE) */

#if (USBCOMM_DMA4_ACTIVE)
    #include "USBCOMM_ep4_dma.h"
    #define USBCOMM_EP4_DMA_CH     (USBCOMM_ep4_dma_CHANNEL)
#endif /* (USBCOMM_DMA4_ACTIVE) */

#if (USBCOMM_DMA5_ACTIVE)
    #include "USBCOMM_ep5_dma.h"
    #define USBCOMM_EP5_DMA_CH     (USBCOMM_ep5_dma_CHANNEL)
#endif /* (USBCOMM_DMA5_ACTIVE) */

#if (USBCOMM_DMA6_ACTIVE)
    #include "USBCOMM_ep6_dma.h"
    #define USBCOMM_EP6_DMA_CH     (USBCOMM_ep6_dma_CHANNEL)
#endif /* (USBCOMM_DMA6_ACTIVE) */

#if (USBCOMM_DMA7_ACTIVE)
    #include "USBCOMM_ep7_dma.h"
    #define USBCOMM_EP7_DMA_CH     (USBCOMM_ep7_dma_CHANNEL)
#endif /* (USBCOMM_DMA7_ACTIVE) */

#if (USBCOMM_DMA8_ACTIVE)
    #include "USBCOMM_ep8_dma.h"
    #define USBCOMM_EP8_DMA_CH     (USBCOMM_ep8_dma_CHANNEL)
#endif /* (USBCOMM_DMA8_ACTIVE) */


/***************************************
*     Private Variables
***************************************/

/* Generated external references for descriptors. */
extern const uint8 CYCODE USBCOMM_DEVICE0_DESCR[18u];
extern const uint8 CYCODE USBCOMM_DEVICE0_CONFIGURATION0_DESCR[32u];
extern const T_USBCOMM_EP_SETTINGS_BLOCK CYCODE USBCOMM_DEVICE0_CONFIGURATION0_EP_SETTINGS_TABLE[2u];
extern const uint8 CYCODE USBCOMM_DEVICE0_CONFIGURATION0_INTERFACE_CLASS[1u];
extern const T_USBCOMM_LUT CYCODE USBCOMM_DEVICE0_CONFIGURATION0_TABLE[4u];
extern const T_USBCOMM_LUT CYCODE USBCOMM_DEVICE0_TABLE[3u];
extern const T_USBCOMM_LUT CYCODE USBCOMM_TABLE[1u];
extern const uint8 CYCODE USBCOMM_SN_STRING_DESCRIPTOR[2];
extern const uint8 CYCODE USBCOMM_STRING_DESCRIPTORS[211u];


extern const uint8 CYCODE USBCOMM_MSOS_DESCRIPTOR[USBCOMM_MSOS_DESCRIPTOR_LENGTH];
extern const uint8 CYCODE USBCOMM_MSOS_CONFIGURATION_DESCR[USBCOMM_MSOS_CONF_DESCR_LENGTH];
#if defined(USBCOMM_ENABLE_IDSN_STRING)
    extern uint8 USBCOMM_idSerialNumberStringDescriptor[USBCOMM_IDSN_DESCR_LENGTH];
#endif /* (USBCOMM_ENABLE_IDSN_STRING) */

extern volatile uint8 USBCOMM_interfaceNumber;
extern volatile uint8 USBCOMM_interfaceSetting[USBCOMM_MAX_INTERFACES_NUMBER];
extern volatile uint8 USBCOMM_interfaceSettingLast[USBCOMM_MAX_INTERFACES_NUMBER];
extern volatile uint8 USBCOMM_deviceAddress;
extern volatile uint8 USBCOMM_interfaceStatus[USBCOMM_MAX_INTERFACES_NUMBER];
extern const uint8 CYCODE *USBCOMM_interfaceClass;

extern volatile T_USBCOMM_EP_CTL_BLOCK USBCOMM_EP[USBCOMM_MAX_EP];
extern volatile T_USBCOMM_TD USBCOMM_currentTD;

#if (USBCOMM_EP_MANAGEMENT_DMA)
    #if (CY_PSOC4)
        extern const uint8 USBCOMM_DmaChan[USBCOMM_MAX_EP];
    #else
        extern uint8 USBCOMM_DmaChan[USBCOMM_MAX_EP];
        extern uint8 USBCOMM_DmaTd  [USBCOMM_MAX_EP];
    #endif /* (CY_PSOC4) */
#endif /* (USBCOMM_EP_MANAGEMENT_DMA) */

#if (USBCOMM_EP_MANAGEMENT_DMA_AUTO)
#if (CY_PSOC4)
    extern uint8  USBCOMM_DmaEpBurstCnt   [USBCOMM_MAX_EP];
    extern uint8  USBCOMM_DmaEpLastBurstEl[USBCOMM_MAX_EP];

    extern uint8  USBCOMM_DmaEpBurstCntBackup  [USBCOMM_MAX_EP];
    extern uint32 USBCOMM_DmaEpBufferAddrBackup[USBCOMM_MAX_EP];
    
    extern const uint8 USBCOMM_DmaReqOut     [USBCOMM_MAX_EP];    
    extern const uint8 USBCOMM_DmaBurstEndOut[USBCOMM_MAX_EP];
#else
    #if (USBCOMM_EP_DMA_AUTO_OPT == 0u)
        extern uint8 USBCOMM_DmaNextTd[USBCOMM_MAX_EP];
        extern volatile uint16 USBCOMM_inLength [USBCOMM_MAX_EP];
        extern volatile uint8  USBCOMM_inBufFull[USBCOMM_MAX_EP];
        extern const uint8 USBCOMM_epX_TD_TERMOUT_EN[USBCOMM_MAX_EP];
        extern const uint8 *USBCOMM_inDataPointer[USBCOMM_MAX_EP];
    #endif /* (USBCOMM_EP_DMA_AUTO_OPT == 0u) */
#endif /* CY_PSOC4 */
#endif /* (USBCOMM_EP_MANAGEMENT_DMA_AUTO) */

extern volatile uint8 USBCOMM_ep0Toggle;
extern volatile uint8 USBCOMM_lastPacketSize;
extern volatile uint8 USBCOMM_ep0Mode;
extern volatile uint8 USBCOMM_ep0Count;
extern volatile uint16 USBCOMM_transferByteCount;


/***************************************
*     Private Function Prototypes
***************************************/
void  USBCOMM_ReInitComponent(void)            ;
void  USBCOMM_HandleSetup(void)                ;
void  USBCOMM_HandleIN(void)                   ;
void  USBCOMM_HandleOUT(void)                  ;
void  USBCOMM_LoadEP0(void)                    ;
uint8 USBCOMM_InitControlRead(void)            ;
uint8 USBCOMM_InitControlWrite(void)           ;
void  USBCOMM_ControlReadDataStage(void)       ;
void  USBCOMM_ControlReadStatusStage(void)     ;
void  USBCOMM_ControlReadPrematureStatus(void) ;
uint8 USBCOMM_InitControlWrite(void)           ;
uint8 USBCOMM_InitZeroLengthControlTransfer(void) ;
void  USBCOMM_ControlWriteDataStage(void)      ;
void  USBCOMM_ControlWriteStatusStage(void)    ;
void  USBCOMM_ControlWritePrematureStatus(void);
uint8 USBCOMM_InitNoDataControlTransfer(void)  ;
void  USBCOMM_NoDataControlStatusStage(void)   ;
void  USBCOMM_InitializeStatusBlock(void)      ;
void  USBCOMM_UpdateStatusBlock(uint8 completionCode) ;
uint8 USBCOMM_DispatchClassRqst(void)          ;

void USBCOMM_Config(uint8 clearAltSetting) ;
void USBCOMM_ConfigAltChanged(void)        ;
void USBCOMM_ConfigReg(void)               ;
void USBCOMM_EpStateInit(void)             ;


const T_USBCOMM_LUT CYCODE *USBCOMM_GetConfigTablePtr(uint8 confIndex);
const T_USBCOMM_LUT CYCODE *USBCOMM_GetDeviceTablePtr(void)           ;
#if (USBCOMM_BOS_ENABLE)
    const T_USBCOMM_LUT CYCODE *USBCOMM_GetBOSPtr(void)               ;
#endif /* (USBCOMM_BOS_ENABLE) */
const uint8 CYCODE *USBCOMM_GetInterfaceClassTablePtr(void)                    ;
uint8 USBCOMM_ClearEndpointHalt(void)                                          ;
uint8 USBCOMM_SetEndpointHalt(void)                                            ;
uint8 USBCOMM_ValidateAlternateSetting(void)                                   ;

void USBCOMM_SaveConfig(void)      ;
void USBCOMM_RestoreConfig(void)   ;

#if (CY_PSOC3 || CY_PSOC5LP)
    #if (USBCOMM_EP_MANAGEMENT_DMA_AUTO && (USBCOMM_EP_DMA_AUTO_OPT == 0u))
        void USBCOMM_LoadNextInEP(uint8 epNumber, uint8 mode)  ;
    #endif /* (USBCOMM_EP_MANAGEMENT_DMA_AUTO && (USBCOMM_EP_DMA_AUTO_OPT == 0u)) */
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

#if defined(USBCOMM_ENABLE_IDSN_STRING)
    void USBCOMM_ReadDieID(uint8 descr[])  ;
#endif /* USBCOMM_ENABLE_IDSN_STRING */

#if defined(USBCOMM_ENABLE_HID_CLASS)
    uint8 USBCOMM_DispatchHIDClassRqst(void) ;
#endif /* (USBCOMM_ENABLE_HID_CLASS) */

#if defined(USBCOMM_ENABLE_AUDIO_CLASS)
    uint8 USBCOMM_DispatchAUDIOClassRqst(void) ;
#endif /* (USBCOMM_ENABLE_AUDIO_CLASS) */

#if defined(USBCOMM_ENABLE_CDC_CLASS)
    uint8 USBCOMM_DispatchCDCClassRqst(void) ;
#endif /* (USBCOMM_ENABLE_CDC_CLASS) */

#if (USBCOMM_ENABLE_MSC_CLASS)
    #if (USBCOMM_HANDLE_MSC_REQUESTS)
        uint8 USBCOMM_DispatchMSCClassRqst(void) ;
    #endif /* (USBCOMM_HANDLE_MSC_REQUESTS) */
#endif /* (USBCOMM_ENABLE_MSC_CLASS */

CY_ISR_PROTO(USBCOMM_EP_0_ISR);
CY_ISR_PROTO(USBCOMM_BUS_RESET_ISR);

#if (USBCOMM_SOF_ISR_ACTIVE)
    CY_ISR_PROTO(USBCOMM_SOF_ISR);
#endif /* (USBCOMM_SOF_ISR_ACTIVE) */

#if (USBCOMM_EP1_ISR_ACTIVE)
    CY_ISR_PROTO(USBCOMM_EP_1_ISR);
#endif /* (USBCOMM_EP1_ISR_ACTIVE) */

#if (USBCOMM_EP2_ISR_ACTIVE)
    CY_ISR_PROTO(USBCOMM_EP_2_ISR);
#endif /* (USBCOMM_EP2_ISR_ACTIVE) */

#if (USBCOMM_EP3_ISR_ACTIVE)
    CY_ISR_PROTO(USBCOMM_EP_3_ISR);
#endif /* (USBCOMM_EP3_ISR_ACTIVE) */

#if (USBCOMM_EP4_ISR_ACTIVE)
    CY_ISR_PROTO(USBCOMM_EP_4_ISR);
#endif /* (USBCOMM_EP4_ISR_ACTIVE) */

#if (USBCOMM_EP5_ISR_ACTIVE)
    CY_ISR_PROTO(USBCOMM_EP_5_ISR);
#endif /* (USBCOMM_EP5_ISR_ACTIVE) */

#if (USBCOMM_EP6_ISR_ACTIVE)
    CY_ISR_PROTO(USBCOMM_EP_6_ISR);
#endif /* (USBCOMM_EP6_ISR_ACTIVE) */

#if (USBCOMM_EP7_ISR_ACTIVE)
    CY_ISR_PROTO(USBCOMM_EP_7_ISR);
#endif /* (USBCOMM_EP7_ISR_ACTIVE) */

#if (USBCOMM_EP8_ISR_ACTIVE)
    CY_ISR_PROTO(USBCOMM_EP_8_ISR);
#endif /* (USBCOMM_EP8_ISR_ACTIVE) */

#if (USBCOMM_EP_MANAGEMENT_DMA)
    CY_ISR_PROTO(USBCOMM_ARB_ISR);
#endif /* (USBCOMM_EP_MANAGEMENT_DMA) */

#if (USBCOMM_DP_ISR_ACTIVE)
    CY_ISR_PROTO(USBCOMM_DP_ISR);
#endif /* (USBCOMM_DP_ISR_ACTIVE) */

#if (CY_PSOC4)
    CY_ISR_PROTO(USBCOMM_INTR_HI_ISR);
    CY_ISR_PROTO(USBCOMM_INTR_MED_ISR);
    CY_ISR_PROTO(USBCOMM_INTR_LO_ISR);
    #if (USBCOMM_LPM_ACTIVE)
        CY_ISR_PROTO(USBCOMM_LPM_ISR);
    #endif /* (USBCOMM_LPM_ACTIVE) */
#endif /* (CY_PSOC4) */

#if (USBCOMM_EP_MANAGEMENT_DMA_AUTO)
#if (CY_PSOC4)
    #if (USBCOMM_DMA1_ACTIVE)
        void USBCOMM_EP1_DMA_DONE_ISR(void);
    #endif /* (USBCOMM_DMA1_ACTIVE) */

    #if (USBCOMM_DMA2_ACTIVE)
        void USBCOMM_EP2_DMA_DONE_ISR(void);
    #endif /* (USBCOMM_DMA2_ACTIVE) */

    #if (USBCOMM_DMA3_ACTIVE)
        void USBCOMM_EP3_DMA_DONE_ISR(void);
    #endif /* (USBCOMM_DMA3_ACTIVE) */

    #if (USBCOMM_DMA4_ACTIVE)
        void USBCOMM_EP4_DMA_DONE_ISR(void);
    #endif /* (USBCOMM_DMA4_ACTIVE) */

    #if (USBCOMM_DMA5_ACTIVE)
        void USBCOMM_EP5_DMA_DONE_ISR(void);
    #endif /* (USBCOMM_DMA5_ACTIVE) */

    #if (USBCOMM_DMA6_ACTIVE)
        void USBCOMM_EP6_DMA_DONE_ISR(void);
    #endif /* (USBCOMM_DMA6_ACTIVE) */

    #if (USBCOMM_DMA7_ACTIVE)
        void USBCOMM_EP7_DMA_DONE_ISR(void);
    #endif /* (USBCOMM_DMA7_ACTIVE) */

    #if (USBCOMM_DMA8_ACTIVE)
        void USBCOMM_EP8_DMA_DONE_ISR(void);
    #endif /* (USBCOMM_DMA8_ACTIVE) */

#else
    #if (USBCOMM_EP_DMA_AUTO_OPT == 0u)
        CY_ISR_PROTO(USBCOMM_EP_DMA_DONE_ISR);
    #endif /* (USBCOMM_EP_DMA_AUTO_OPT == 0u) */
#endif /* (CY_PSOC4) */
#endif /* (USBCOMM_EP_MANAGEMENT_DMA_AUTO) */


/***************************************
*         Request Handlers
***************************************/

uint8 USBCOMM_HandleStandardRqst(void) ;
uint8 USBCOMM_DispatchClassRqst(void)  ;
uint8 USBCOMM_HandleVendorRqst(void)   ;


/***************************************
*    HID Internal references
***************************************/

#if defined(USBCOMM_ENABLE_HID_CLASS)
    void USBCOMM_FindReport(void)            ;
    void USBCOMM_FindReportDescriptor(void)  ;
    void USBCOMM_FindHidClassDecriptor(void) ;
#endif /* USBCOMM_ENABLE_HID_CLASS */


/***************************************
*    MIDI Internal references
***************************************/

#if defined(USBCOMM_ENABLE_MIDI_STREAMING)
    void USBCOMM_MIDI_IN_EP_Service(void)  ;
#endif /* (USBCOMM_ENABLE_MIDI_STREAMING) */


/***************************************
*    CDC Internal references
***************************************/

#if defined(USBCOMM_ENABLE_CDC_CLASS)

    typedef struct
    {
        uint8  bRequestType;
        uint8  bNotification;
        uint8  wValue;
        uint8  wValueMSB;
        uint8  wIndex;
        uint8  wIndexMSB;
        uint8  wLength;
        uint8  wLengthMSB;
        uint8  wSerialState;
        uint8  wSerialStateMSB;
    } t_USBCOMM_cdc_notification;

    uint8 USBCOMM_GetInterfaceComPort(uint8 interface) ;
    uint8 USBCOMM_Cdc_EpInit( const T_USBCOMM_EP_SETTINGS_BLOCK CYCODE *pEP, uint8 epNum, uint8 cdcComNums) ;

    extern volatile uint8  USBCOMM_cdc_dataInEpList[USBCOMM_MAX_MULTI_COM_NUM];
    extern volatile uint8  USBCOMM_cdc_dataOutEpList[USBCOMM_MAX_MULTI_COM_NUM];
    extern volatile uint8  USBCOMM_cdc_commInEpList[USBCOMM_MAX_MULTI_COM_NUM];
#endif /* (USBCOMM_ENABLE_CDC_CLASS) */


#endif /* CY_USBFS_USBCOMM_pvt_H */


/* [] END OF FILE */

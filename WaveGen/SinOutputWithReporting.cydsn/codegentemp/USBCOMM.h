/***************************************************************************//**
* \file  USBCOMM.h
* \version 3.20
*
* \brief
*  This file provides function prototypes and constants for the USBFS component. 
*
********************************************************************************
* \copyright
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_USBFS_USBCOMM_H)
#define CY_USBFS_USBCOMM_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h"
#include "cyapicallbacks.h"

/*  User supplied definitions. */
/* `#START USER_DEFINITIONS` Place your declaration here */

/* `#END` */

/***************************************
* Enumerated Types and Parameters
***************************************/

/* USB IP memory management options. */
#define USBCOMM__EP_MANUAL    (0u)
#define USBCOMM__EP_DMAMANUAL (1u)
#define USBCOMM__EP_DMAAUTO   (2u)

/* USB IP memory allocation options. */
#define USBCOMM__MA_STATIC    (0u)
#define USBCOMM__MA_DYNAMIC   (1u)


/***************************************
*    Initial Parameter Constants
***************************************/

#define USBCOMM_NUM_DEVICES                    (1u)
#define USBCOMM_ENABLE_MIDI_CLASS              (0u)
#define USBCOMM_ENABLE_MSC_CLASS               (0u)
#define USBCOMM_BOS_ENABLE                     (0u)
#define USBCOMM_ENABLE_DESCRIPTOR_STRINGS      
#define USBCOMM_ENABLE_SN_STRING               
#define USBCOMM_ENABLE_IDSN_STRING             
#define USBCOMM_ENABLE_STRINGS                 
#define USBCOMM_MAX_REPORTID_NUMBER            (0u)

#define USBCOMM_MON_VBUS               (0u)
#define USBCOMM_EXTERN_VBUS            (0u)
#define USBCOMM_POWER_PAD_VBUS         (0u)
#define USBCOMM_EXTERN_VND             (0u)
#define USBCOMM_EXTERN_CLS             (0u)
#define USBCOMM_MAX_INTERFACES_NUMBER  (1u)
#define USBCOMM_EP_MM                  (0u)
#define USBCOMM_EP_MA                  (0u)
#define USBCOMM_ENABLE_BATT_CHARG_DET  (0u)
#define USBCOMM_GEN_16BITS_EP_ACCESS   (1u)

/* Enable Class APIs: MIDI, CDC, MSC. */         
#define USBCOMM_ENABLE_CDC_CLASS_API   (0u != (1u))

/* General parameters */
#define USBCOMM_EP_ALLOC_STATIC            (USBCOMM_EP_MA == USBCOMM__MA_STATIC)
#define USBCOMM_EP_ALLOC_DYNAMIC           (USBCOMM_EP_MA == USBCOMM__MA_DYNAMIC)
#define USBCOMM_EP_MANAGEMENT_MANUAL       (USBCOMM_EP_MM == USBCOMM__EP_MANUAL)
#define USBCOMM_EP_MANAGEMENT_DMA          (USBCOMM_EP_MM != USBCOMM__EP_MANUAL)
#define USBCOMM_EP_MANAGEMENT_DMA_MANUAL   (USBCOMM_EP_MM == USBCOMM__EP_DMAMANUAL)
#define USBCOMM_EP_MANAGEMENT_DMA_AUTO     (USBCOMM_EP_MM == USBCOMM__EP_DMAAUTO)
#define USBCOMM_BATT_CHARG_DET_ENABLE      (CY_PSOC4 && (0u != USBCOMM_ENABLE_BATT_CHARG_DET))
#define USBCOMM_16BITS_EP_ACCESS_ENABLE    (CY_PSOC4 && (0u != USBCOMM_GEN_16BITS_EP_ACCESS))
#define USBCOMM_VBUS_MONITORING_ENABLE     (0u != USBCOMM_MON_VBUS)
#define USBCOMM_VBUS_MONITORING_INTERNAL   (0u == USBCOMM_EXTERN_VBUS)
#define USBCOMM_VBUS_POWER_PAD_ENABLE      (0u != USBCOMM_POWER_PAD_VBUS)

/* Control endpoints availability */
#define USBCOMM_SOF_ISR_REMOVE       (0u)
#define USBCOMM_BUS_RESET_ISR_REMOVE (0u)
#define USBCOMM_EP0_ISR_REMOVE       (0u)
#define USBCOMM_ARB_ISR_REMOVE       (0u)
#define USBCOMM_DP_ISR_REMOVE        (0u)
#define USBCOMM_LPM_REMOVE           (1u)
#define USBCOMM_SOF_ISR_ACTIVE       ((0u == USBCOMM_SOF_ISR_REMOVE) ? 1u: 0u)
#define USBCOMM_BUS_RESET_ISR_ACTIVE ((0u == USBCOMM_BUS_RESET_ISR_REMOVE) ? 1u: 0u)
#define USBCOMM_EP0_ISR_ACTIVE       ((0u == USBCOMM_EP0_ISR_REMOVE) ? 1u: 0u)
#define USBCOMM_ARB_ISR_ACTIVE       ((0u == USBCOMM_ARB_ISR_REMOVE) ? 1u: 0u)
#define USBCOMM_DP_ISR_ACTIVE        ((0u == USBCOMM_DP_ISR_REMOVE) ? 1u: 0u)
#define USBCOMM_LPM_ACTIVE           ((CY_PSOC4 && (0u == USBCOMM_LPM_REMOVE)) ? 1u: 0u)

/* Data endpoints availability */
#define USBCOMM_EP1_ISR_REMOVE     (0u)
#define USBCOMM_EP2_ISR_REMOVE     (0u)
#define USBCOMM_EP3_ISR_REMOVE     (1u)
#define USBCOMM_EP4_ISR_REMOVE     (1u)
#define USBCOMM_EP5_ISR_REMOVE     (1u)
#define USBCOMM_EP6_ISR_REMOVE     (1u)
#define USBCOMM_EP7_ISR_REMOVE     (1u)
#define USBCOMM_EP8_ISR_REMOVE     (1u)
#define USBCOMM_EP1_ISR_ACTIVE     ((0u == USBCOMM_EP1_ISR_REMOVE) ? 1u: 0u)
#define USBCOMM_EP2_ISR_ACTIVE     ((0u == USBCOMM_EP2_ISR_REMOVE) ? 1u: 0u)
#define USBCOMM_EP3_ISR_ACTIVE     ((0u == USBCOMM_EP3_ISR_REMOVE) ? 1u: 0u)
#define USBCOMM_EP4_ISR_ACTIVE     ((0u == USBCOMM_EP4_ISR_REMOVE) ? 1u: 0u)
#define USBCOMM_EP5_ISR_ACTIVE     ((0u == USBCOMM_EP5_ISR_REMOVE) ? 1u: 0u)
#define USBCOMM_EP6_ISR_ACTIVE     ((0u == USBCOMM_EP6_ISR_REMOVE) ? 1u: 0u)
#define USBCOMM_EP7_ISR_ACTIVE     ((0u == USBCOMM_EP7_ISR_REMOVE) ? 1u: 0u)
#define USBCOMM_EP8_ISR_ACTIVE     ((0u == USBCOMM_EP8_ISR_REMOVE) ? 1u: 0u)

#define USBCOMM_EP_DMA_AUTO_OPT    ((CY_PSOC4) ? (1u) : (0u))
#define USBCOMM_DMA1_REMOVE        (1u)
#define USBCOMM_DMA2_REMOVE        (1u)
#define USBCOMM_DMA3_REMOVE        (1u)
#define USBCOMM_DMA4_REMOVE        (1u)
#define USBCOMM_DMA5_REMOVE        (1u)
#define USBCOMM_DMA6_REMOVE        (1u)
#define USBCOMM_DMA7_REMOVE        (1u)
#define USBCOMM_DMA8_REMOVE        (1u)
#define USBCOMM_DMA1_ACTIVE        ((0u == USBCOMM_DMA1_REMOVE) ? 1u: 0u)
#define USBCOMM_DMA2_ACTIVE        ((0u == USBCOMM_DMA2_REMOVE) ? 1u: 0u)
#define USBCOMM_DMA3_ACTIVE        ((0u == USBCOMM_DMA3_REMOVE) ? 1u: 0u)
#define USBCOMM_DMA4_ACTIVE        ((0u == USBCOMM_DMA4_REMOVE) ? 1u: 0u)
#define USBCOMM_DMA5_ACTIVE        ((0u == USBCOMM_DMA5_REMOVE) ? 1u: 0u)
#define USBCOMM_DMA6_ACTIVE        ((0u == USBCOMM_DMA6_REMOVE) ? 1u: 0u)
#define USBCOMM_DMA7_ACTIVE        ((0u == USBCOMM_DMA7_REMOVE) ? 1u: 0u)
#define USBCOMM_DMA8_ACTIVE        ((0u == USBCOMM_DMA8_REMOVE) ? 1u: 0u)


/***************************************
*    Data Structures Definition
***************************************/

typedef struct
{
    uint8  attrib;
    uint8  apiEpState;
    uint8  hwEpState;
    uint8  epToggle;
    uint8  addr;
    uint8  epMode;
    uint16 buffOffset;
    uint16 bufferSize;
    uint8  interface;
} T_USBCOMM_EP_CTL_BLOCK;

typedef struct
{
    uint8  interface;
    uint8  altSetting;
    uint8  addr;
    uint8  attributes;
    uint16 bufferSize;
    uint8  bMisc;
} T_USBCOMM_EP_SETTINGS_BLOCK;

typedef struct
{
    uint8  status;
    uint16 length;
} T_USBCOMM_XFER_STATUS_BLOCK;

typedef struct
{
    uint16  count;
    volatile uint8 *pData;
    T_USBCOMM_XFER_STATUS_BLOCK *pStatusBlock;
} T_USBCOMM_TD;

typedef struct
{
    uint8   c;
    const void *p_list;
} T_USBCOMM_LUT;

/* Resume/Suspend API Support */
typedef struct
{
    uint8 enableState;
    uint8 mode;
#if (CY_PSOC4)
    uint8 intrSeiMask;
#endif /* (CY_PSOC4) */
} USBCOMM_BACKUP_STRUCT;

/* Number of endpoint 0 data registers. */
#define USBCOMM_EP0_DR_MAPPED_REG_CNT  (8u)

/* Structure to access data registers for EP0. */
typedef struct
{
    uint8 epData[USBCOMM_EP0_DR_MAPPED_REG_CNT];
} USBCOMM_ep0_data_struct;

/* Number of SIE endpoint registers group. */
#define USBCOMM_SIE_EP_REG_SIZE   (USBCOMM_USB__SIE_EP1_CR0 - \
                                            USBCOMM_USB__SIE_EP1_CNT0)

/* Size of gap between SIE endpoint registers groups. */
#define USBCOMM_SIE_GAP_CNT        (((USBCOMM_USB__SIE_EP2_CNT0 - \
                                             (USBCOMM_USB__SIE_EP1_CNT0 + \
                                              USBCOMM_SIE_EP_REG_SIZE)) / sizeof(reg8)) - 1u)

/* Structure to access to SIE registers for endpoint. */
typedef struct
{
    uint8 epCnt0;
    uint8 epCnt1;
    uint8 epCr0;
    uint8 gap[USBCOMM_SIE_GAP_CNT];
} USBCOMM_sie_ep_struct;

/* Number of ARB endpoint registers group. */
#define USBCOMM_ARB_EP_REG_SIZE    (USBCOMM_USB__ARB_RW1_DR - \
                                             USBCOMM_USB__ARB_EP1_CFG)

/* Size of gap between ARB endpoint registers groups. */
#define USBCOMM_ARB_GAP_CNT        (((USBCOMM_USB__ARB_EP2_CFG - \
                                             (USBCOMM_USB__ARB_EP1_CFG + \
                                              USBCOMM_ARB_EP_REG_SIZE)) / sizeof(reg8)) - 1u)

/* Structure to access to ARB registers for endpoint. */
typedef struct
{
    uint8 epCfg;
    uint8 epIntEn;
    uint8 epSr;
    uint8 reserved;
    uint8 rwWa;
    uint8 rwWaMsb;
    uint8 rwRa;
    uint8 rwRaMsb;
    uint8 rwDr;
    uint8 gap[USBCOMM_ARB_GAP_CNT];
} USBCOMM_arb_ep_struct;

#if (CY_PSOC4)
    /* Number of ARB endpoint registers group (16-bits access). */
    #define USBCOMM_ARB_EP_REG16_SIZE      (USBCOMM_USB__ARB_RW1_DR16 - \
                                                     USBCOMM_USB__ARB_RW1_WA16)

    /* Size of gap between ARB endpoint registers groups (16-bits access). */
    #define USBCOMM_ARB_EP_REG16_GAP_CNT   (((USBCOMM_USB__ARB_RW2_WA16 - \
                                                     (USBCOMM_USB__ARB_RW1_WA16 + \
                                                      USBCOMM_ARB_EP_REG16_SIZE)) / sizeof(reg8)) - 1u)

    /* Structure to access to ARB registers for endpoint (16-bits access). */
    typedef struct
    {
        uint8 rwWa16;
        uint8 reserved0;
        uint8 rwRa16;
        uint8 reserved1;
        uint8 rwDr16;
        uint8 gap[USBCOMM_ARB_EP_REG16_GAP_CNT];
    } USBCOMM_arb_ep_reg16_struct;
#endif /* (CY_PSOC4) */

/* Number of endpoint (takes to account that endpoints numbers are 1-8). */
#define USBCOMM_NUMBER_EP  (9u)

/* Consoled SIE register groups for endpoints 1-8. */
typedef struct
{
    USBCOMM_sie_ep_struct sieEp[USBCOMM_NUMBER_EP];
} USBCOMM_sie_eps_struct;

/* Consolidate ARB register groups for endpoints 1-8.*/
typedef struct
{
    USBCOMM_arb_ep_struct arbEp[USBCOMM_NUMBER_EP];
} USBCOMM_arb_eps_struct;

#if (CY_PSOC4)
    /* Consolidate ARB register groups for endpoints 1-8 (16-bits access). */
    typedef struct
    {
        USBCOMM_arb_ep_reg16_struct arbEp[USBCOMM_NUMBER_EP];
    } USBCOMM_arb_eps_reg16_struct;
#endif /* (CY_PSOC4) */


/***************************************
*       Function Prototypes
***************************************/
/**
* \addtogroup group_general
* @{
*/
void   USBCOMM_InitComponent(uint8 device, uint8 mode) ;
void   USBCOMM_Start(uint8 device, uint8 mode)         ;
void   USBCOMM_Init(void)                              ;
void   USBCOMM_Stop(void)                              ;
uint8  USBCOMM_GetConfiguration(void)                  ;
uint8  USBCOMM_IsConfigurationChanged(void)            ;
uint8  USBCOMM_GetInterfaceSetting(uint8 interfaceNumber) ;
uint8  USBCOMM_GetEPState(uint8 epNumber)              ;
uint16 USBCOMM_GetEPCount(uint8 epNumber)              ;
void   USBCOMM_LoadInEP(uint8 epNumber, const uint8 pData[], uint16 length)
                                                                ;
uint16 USBCOMM_ReadOutEP(uint8 epNumber, uint8 pData[], uint16 length)
                                                                ;
void   USBCOMM_EnableOutEP(uint8 epNumber)             ;
void   USBCOMM_DisableOutEP(uint8 epNumber)            ;
void   USBCOMM_Force(uint8 bState)                     ;
uint8  USBCOMM_GetEPAckState(uint8 epNumber)           ;
void   USBCOMM_SetPowerStatus(uint8 powerStatus)       ;
void   USBCOMM_TerminateEP(uint8 epNumber)             ;

uint8 USBCOMM_GetDeviceAddress(void) ;

void USBCOMM_EnableSofInt(void)  ;
void USBCOMM_DisableSofInt(void) ;


#if defined(USBCOMM_ENABLE_FWSN_STRING)
    void   USBCOMM_SerialNumString(uint8 snString[]) ;
#endif  /* USBCOMM_ENABLE_FWSN_STRING */

#if (USBCOMM_VBUS_MONITORING_ENABLE)
    uint8  USBCOMM_VBusPresent(void) ;
#endif /*  (USBCOMM_VBUS_MONITORING_ENABLE) */

#if (USBCOMM_16BITS_EP_ACCESS_ENABLE)
    /* PSoC4 specific functions for 16-bit data register access. */
    void   USBCOMM_LoadInEP16 (uint8 epNumber, const uint8 pData[], uint16 length);
    uint16 USBCOMM_ReadOutEP16(uint8 epNumber,       uint8 pData[], uint16 length);
#endif /* (USBCOMM_16BITS_EP_ACCESS_ENABLE) */

#if (USBCOMM_BATT_CHARG_DET_ENABLE)
        uint8 USBCOMM_Bcd_DetectPortType(void);
#endif /* (USBCOMM_BATT_CHARG_DET_ENABLE) */

#if (USBCOMM_EP_MANAGEMENT_DMA)
    void USBCOMM_InitEP_DMA(uint8 epNumber, const uint8 *pData) ;   
    void USBCOMM_Stop_DMA(uint8 epNumber) ;
/** @} general */ 
#endif /* (USBCOMM_EP_MANAGEMENT_DMA) */

/**
* \addtogroup group_power
* @{
*/
uint8  USBCOMM_CheckActivity(void) ;
void   USBCOMM_Suspend(void)       ;
void   USBCOMM_Resume(void)        ;
uint8  USBCOMM_RWUEnabled(void)    ;

#if (USBCOMM_LPM_ACTIVE)
    uint32 USBCOMM_Lpm_GetBeslValue(void);
    uint32 USBCOMM_Lpm_RemoteWakeUpAllowed(void);
    void   USBCOMM_Lpm_SetResponse(uint32 response);
    uint32 USBCOMM_Lpm_GetResponse(void);
#endif /* (USBCOMM_LPM_ACTIVE) */

/** @} power */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_USBCOMM) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
/**
* \addtogroup group_bootloader
* @{
*/
    void USBCOMM_CyBtldrCommStart(void)        ;
    void USBCOMM_CyBtldrCommStop(void)         ;
    void USBCOMM_CyBtldrCommReset(void)        ;
    cystatus USBCOMM_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 *count, uint8 timeOut) CYSMALL
                                                        ;
    cystatus USBCOMM_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 *count, uint8 timeOut) CYSMALL
                                                        ;
/** @} bootloader */

    #define USBCOMM_BTLDR_OUT_EP   (0x01u)
    #define USBCOMM_BTLDR_IN_EP    (0x02u)

    #define USBCOMM_BTLDR_SIZEOF_WRITE_BUFFER  (64u)   /* Endpoint 1 (OUT) buffer size. */
    #define USBCOMM_BTLDR_SIZEOF_READ_BUFFER   (64u)   /* Endpoint 2 (IN)  buffer size. */
    #define USBCOMM_BTLDR_MAX_PACKET_SIZE      USBCOMM_BTLDR_SIZEOF_WRITE_BUFFER

    #define USBCOMM_BTLDR_WAIT_1_MS            (1u)    /* Time Out quantity equal 1mS */

    /* Map-specific USB bootloader communication functions to common bootloader functions */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_USBCOMM)
        #define CyBtldrCommStart        USBCOMM_CyBtldrCommStart
        #define CyBtldrCommStop         USBCOMM_CyBtldrCommStop
        #define CyBtldrCommReset        USBCOMM_CyBtldrCommReset
        #define CyBtldrCommWrite        USBCOMM_CyBtldrCommWrite
        #define CyBtldrCommRead         USBCOMM_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_USBCOMM) */
#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/

#define USBCOMM_EP0                        (0u)
#define USBCOMM_EP1                        (1u)
#define USBCOMM_EP2                        (2u)
#define USBCOMM_EP3                        (3u)
#define USBCOMM_EP4                        (4u)
#define USBCOMM_EP5                        (5u)
#define USBCOMM_EP6                        (6u)
#define USBCOMM_EP7                        (7u)
#define USBCOMM_EP8                        (8u)
#define USBCOMM_MAX_EP                     (9u)

#define USBCOMM_TRUE                       (1u)
#define USBCOMM_FALSE                      (0u)

#define USBCOMM_NO_EVENT_ALLOWED           (2u)
#define USBCOMM_EVENT_PENDING              (1u)
#define USBCOMM_NO_EVENT_PENDING           (0u)

#define USBCOMM_IN_BUFFER_FULL             USBCOMM_NO_EVENT_PENDING
#define USBCOMM_IN_BUFFER_EMPTY            USBCOMM_EVENT_PENDING
#define USBCOMM_OUT_BUFFER_FULL            USBCOMM_EVENT_PENDING
#define USBCOMM_OUT_BUFFER_EMPTY           USBCOMM_NO_EVENT_PENDING

#define USBCOMM_FORCE_J                    (0xA0u)
#define USBCOMM_FORCE_K                    (0x80u)
#define USBCOMM_FORCE_SE0                  (0xC0u)
#define USBCOMM_FORCE_NONE                 (0x00u)

#define USBCOMM_IDLE_TIMER_RUNNING         (0x02u)
#define USBCOMM_IDLE_TIMER_EXPIRED         (0x01u)
#define USBCOMM_IDLE_TIMER_INDEFINITE      (0x00u)

#define USBCOMM_DEVICE_STATUS_BUS_POWERED  (0x00u)
#define USBCOMM_DEVICE_STATUS_SELF_POWERED (0x01u)

#define USBCOMM_3V_OPERATION               (0x00u)
#define USBCOMM_5V_OPERATION               (0x01u)
#define USBCOMM_DWR_POWER_OPERATION        (0x02u)

#define USBCOMM_MODE_DISABLE               (0x00u)
#define USBCOMM_MODE_NAK_IN_OUT            (0x01u)
#define USBCOMM_MODE_STATUS_OUT_ONLY       (0x02u)
#define USBCOMM_MODE_STALL_IN_OUT          (0x03u)
#define USBCOMM_MODE_RESERVED_0100         (0x04u)
#define USBCOMM_MODE_ISO_OUT               (0x05u)
#define USBCOMM_MODE_STATUS_IN_ONLY        (0x06u)
#define USBCOMM_MODE_ISO_IN                (0x07u)
#define USBCOMM_MODE_NAK_OUT               (0x08u)
#define USBCOMM_MODE_ACK_OUT               (0x09u)
#define USBCOMM_MODE_RESERVED_1010         (0x0Au)
#define USBCOMM_MODE_ACK_OUT_STATUS_IN     (0x0Bu)
#define USBCOMM_MODE_NAK_IN                (0x0Cu)
#define USBCOMM_MODE_ACK_IN                (0x0Du)
#define USBCOMM_MODE_RESERVED_1110         (0x0Eu)
#define USBCOMM_MODE_ACK_IN_STATUS_OUT     (0x0Fu)
#define USBCOMM_MODE_MASK                  (0x0Fu)
#define USBCOMM_MODE_STALL_DATA_EP         (0x80u)

#define USBCOMM_MODE_ACKD                  (0x10u)
#define USBCOMM_MODE_OUT_RCVD              (0x20u)
#define USBCOMM_MODE_IN_RCVD               (0x40u)
#define USBCOMM_MODE_SETUP_RCVD            (0x80u)

#define USBCOMM_RQST_TYPE_MASK             (0x60u)
#define USBCOMM_RQST_TYPE_STD              (0x00u)
#define USBCOMM_RQST_TYPE_CLS              (0x20u)
#define USBCOMM_RQST_TYPE_VND              (0x40u)
#define USBCOMM_RQST_DIR_MASK              (0x80u)
#define USBCOMM_RQST_DIR_D2H               (0x80u)
#define USBCOMM_RQST_DIR_H2D               (0x00u)
#define USBCOMM_RQST_RCPT_MASK             (0x03u)
#define USBCOMM_RQST_RCPT_DEV              (0x00u)
#define USBCOMM_RQST_RCPT_IFC              (0x01u)
#define USBCOMM_RQST_RCPT_EP               (0x02u)
#define USBCOMM_RQST_RCPT_OTHER            (0x03u)

#if (USBCOMM_LPM_ACTIVE)
    #define USBCOMM_LPM_REQ_ACK            (0x01u << USBCOMM_LPM_CTRL_LPM_ACK_RESP_POS)
    #define USBCOMM_LPM_REQ_NACK           (0x00u)
    #define USBCOMM_LPM_REQ_NYET           (0x01u << USBCOMM_LPM_CTRL_NYET_EN_POS)
#endif /*(USBCOMM_LPM_ACTIVE)*/

/* USB Class Codes */
#define USBCOMM_CLASS_DEVICE               (0x00u)     /* Use class code info from Interface Descriptors */
#define USBCOMM_CLASS_AUDIO                (0x01u)     /* Audio device */
#define USBCOMM_CLASS_CDC                  (0x02u)     /* Communication device class */
#define USBCOMM_CLASS_HID                  (0x03u)     /* Human Interface Device */
#define USBCOMM_CLASS_PDC                  (0x05u)     /* Physical device class */
#define USBCOMM_CLASS_IMAGE                (0x06u)     /* Still Imaging device */
#define USBCOMM_CLASS_PRINTER              (0x07u)     /* Printer device  */
#define USBCOMM_CLASS_MSD                  (0x08u)     /* Mass Storage device  */
#define USBCOMM_CLASS_HUB                  (0x09u)     /* Full/Hi speed Hub */
#define USBCOMM_CLASS_CDC_DATA             (0x0Au)     /* CDC data device */
#define USBCOMM_CLASS_SMART_CARD           (0x0Bu)     /* Smart Card device */
#define USBCOMM_CLASS_CSD                  (0x0Du)     /* Content Security device */
#define USBCOMM_CLASS_VIDEO                (0x0Eu)     /* Video device */
#define USBCOMM_CLASS_PHD                  (0x0Fu)     /* Personal Health care device */
#define USBCOMM_CLASS_WIRELESSD            (0xDCu)     /* Wireless Controller */
#define USBCOMM_CLASS_MIS                  (0xE0u)     /* Miscellaneous */
#define USBCOMM_CLASS_APP                  (0xEFu)     /* Application Specific */
#define USBCOMM_CLASS_VENDOR               (0xFFu)     /* Vendor specific */

/* Standard Request Types (Table 9-4) */
#define USBCOMM_GET_STATUS                 (0x00u)
#define USBCOMM_CLEAR_FEATURE              (0x01u)
#define USBCOMM_SET_FEATURE                (0x03u)
#define USBCOMM_SET_ADDRESS                (0x05u)
#define USBCOMM_GET_DESCRIPTOR             (0x06u)
#define USBCOMM_SET_DESCRIPTOR             (0x07u)
#define USBCOMM_GET_CONFIGURATION          (0x08u)
#define USBCOMM_SET_CONFIGURATION          (0x09u)
#define USBCOMM_GET_INTERFACE              (0x0Au)
#define USBCOMM_SET_INTERFACE              (0x0Bu)
#define USBCOMM_SYNCH_FRAME                (0x0Cu)

/* Vendor Specific Request Types */
/* Request for Microsoft OS String Descriptor */
#define USBCOMM_GET_EXTENDED_CONFIG_DESCRIPTOR (0x01u)

/* Descriptor Types (Table 9-5) */
#define USBCOMM_DESCR_DEVICE                   (1u)
#define USBCOMM_DESCR_CONFIG                   (2u)
#define USBCOMM_DESCR_STRING                   (3u)
#define USBCOMM_DESCR_INTERFACE                (4u)
#define USBCOMM_DESCR_ENDPOINT                 (5u)
#define USBCOMM_DESCR_DEVICE_QUALIFIER         (6u)
#define USBCOMM_DESCR_OTHER_SPEED              (7u)
#define USBCOMM_DESCR_INTERFACE_POWER          (8u)
#if (USBCOMM_BOS_ENABLE)
    #define USBCOMM_DESCR_BOS                  (15u)
#endif /* (USBCOMM_BOS_ENABLE) */
/* Device Descriptor Defines */
#define USBCOMM_DEVICE_DESCR_LENGTH            (18u)
#define USBCOMM_DEVICE_DESCR_SN_SHIFT          (16u)

/* Config Descriptor Shifts and Masks */
#define USBCOMM_CONFIG_DESCR_LENGTH                (0u)
#define USBCOMM_CONFIG_DESCR_TYPE                  (1u)
#define USBCOMM_CONFIG_DESCR_TOTAL_LENGTH_LOW      (2u)
#define USBCOMM_CONFIG_DESCR_TOTAL_LENGTH_HI       (3u)
#define USBCOMM_CONFIG_DESCR_NUM_INTERFACES        (4u)
#define USBCOMM_CONFIG_DESCR_CONFIG_VALUE          (5u)
#define USBCOMM_CONFIG_DESCR_CONFIGURATION         (6u)
#define USBCOMM_CONFIG_DESCR_ATTRIB                (7u)
#define USBCOMM_CONFIG_DESCR_ATTRIB_SELF_POWERED   (0x40u)
#define USBCOMM_CONFIG_DESCR_ATTRIB_RWU_EN         (0x20u)

#if (USBCOMM_BOS_ENABLE)
    /* Config Descriptor BOS */
    #define USBCOMM_BOS_DESCR_LENGTH               (0u)
    #define USBCOMM_BOS_DESCR_TYPE                 (1u)
    #define USBCOMM_BOS_DESCR_TOTAL_LENGTH_LOW     (2u)
    #define USBCOMM_BOS_DESCR_TOTAL_LENGTH_HI      (3u)
    #define USBCOMM_BOS_DESCR_NUM_DEV_CAPS         (4u)
#endif /* (USBCOMM_BOS_ENABLE) */

/* Feature Selectors (Table 9-6) */
#define USBCOMM_DEVICE_REMOTE_WAKEUP           (0x01u)
#define USBCOMM_ENDPOINT_HALT                  (0x00u)
#define USBCOMM_TEST_MODE                      (0x02u)

/* USB Device Status (Figure 9-4) */
#define USBCOMM_DEVICE_STATUS_BUS_POWERED      (0x00u)
#define USBCOMM_DEVICE_STATUS_SELF_POWERED     (0x01u)
#define USBCOMM_DEVICE_STATUS_REMOTE_WAKEUP    (0x02u)

/* USB Endpoint Status (Figure 9-4) */
#define USBCOMM_ENDPOINT_STATUS_HALT           (0x01u)

/* USB Endpoint Directions */
#define USBCOMM_DIR_IN                         (0x80u)
#define USBCOMM_DIR_OUT                        (0x00u)
#define USBCOMM_DIR_UNUSED                     (0x7Fu)

/* USB Endpoint Attributes */
#define USBCOMM_EP_TYPE_CTRL                   (0x00u)
#define USBCOMM_EP_TYPE_ISOC                   (0x01u)
#define USBCOMM_EP_TYPE_BULK                   (0x02u)
#define USBCOMM_EP_TYPE_INT                    (0x03u)
#define USBCOMM_EP_TYPE_MASK                   (0x03u)

#define USBCOMM_EP_SYNC_TYPE_NO_SYNC           (0x00u)
#define USBCOMM_EP_SYNC_TYPE_ASYNC             (0x04u)
#define USBCOMM_EP_SYNC_TYPE_ADAPTIVE          (0x08u)
#define USBCOMM_EP_SYNC_TYPE_SYNCHRONOUS       (0x0Cu)
#define USBCOMM_EP_SYNC_TYPE_MASK              (0x0Cu)

#define USBCOMM_EP_USAGE_TYPE_DATA             (0x00u)
#define USBCOMM_EP_USAGE_TYPE_FEEDBACK         (0x10u)
#define USBCOMM_EP_USAGE_TYPE_IMPLICIT         (0x20u)
#define USBCOMM_EP_USAGE_TYPE_RESERVED         (0x30u)
#define USBCOMM_EP_USAGE_TYPE_MASK             (0x30u)

/* Point Status defines */
#define USBCOMM_EP_STATUS_LENGTH               (0x02u)

/* Point Device defines */
#define USBCOMM_DEVICE_STATUS_LENGTH           (0x02u)

#define USBCOMM_STATUS_LENGTH_MAX \
                 ((USBCOMM_EP_STATUS_LENGTH > USBCOMM_DEVICE_STATUS_LENGTH) ? \
                        USBCOMM_EP_STATUS_LENGTH : USBCOMM_DEVICE_STATUS_LENGTH)

/* Transfer Completion Notification */
#define USBCOMM_XFER_IDLE                      (0x00u)
#define USBCOMM_XFER_STATUS_ACK                (0x01u)
#define USBCOMM_XFER_PREMATURE                 (0x02u)
#define USBCOMM_XFER_ERROR                     (0x03u)

/* Driver State defines */
#define USBCOMM_TRANS_STATE_IDLE               (0x00u)
#define USBCOMM_TRANS_STATE_CONTROL_READ       (0x02u)
#define USBCOMM_TRANS_STATE_CONTROL_WRITE      (0x04u)
#define USBCOMM_TRANS_STATE_NO_DATA_CONTROL    (0x06u)

/* String Descriptor defines */
#define USBCOMM_STRING_MSOS                    (0xEEu)
#define USBCOMM_MSOS_DESCRIPTOR_LENGTH         (18u)
#define USBCOMM_MSOS_CONF_DESCR_LENGTH         (40u)

/* Return values */
#define USBCOMM_BCD_PORT_SDP       (1u) /* Standard downstream port detected */
#define USBCOMM_BCD_PORT_CDP       (2u) /* Charging downstream port detected */
#define USBCOMM_BCD_PORT_DCP       (3u) /* Dedicated charging port detected */
#define USBCOMM_BCD_PORT_UNKNOWN   (0u) /* Unable to detect charging port */
#define USBCOMM_BCD_PORT_ERR       (4u) /* Error condition in detection process*/


/* Timeouts for BCD */
#define USBCOMM_BCD_TIMEOUT                (400u)  /* Copied from PBK#163 TIMEOUT (300 ms) */
#define USBCOMM_BCD_TDCD_DBNC              (10u)  /*BCD v1.2: DCD debounce time 10 ms*/
#define USBCOMM_BCD_PRIMARY_WAIT           (40u)   /* Copied from PBK#163 TIMEOUT (40 ms)  */
#define USBCOMM_BCD_SECONDARY_WAIT         (47u)   /* Copied from PBK#163 TIMEOUT (40 ms)  */
#define USBCOMM_BCD_SUSPEND_DISABLE_WAIT   (2u)    /* Copied from PBK#163 TIMEOUT (2 us)   */

/* Wait cycles required before clearing SUSPEND_DEL in POWER_CTRL: 2us */
#define USBCOMM_WAIT_SUSPEND_DEL_DISABLE   (2u)

/* Wait cycles required for USB regulator stabilization after it is enabled : 50ns */
#define USBCOMM_WAIT_VREF_STABILITY        (0u)

#if (CY_PSOC3 || CY_PSOC5LP)
/* Wait cycles required for USB reference restore: 40us */
#define USBCOMM_WAIT_VREF_RESTORE          (40u)

/* Wait cycles required for stabilization after register is written : 50ns */
#define USBCOMM_WAIT_REG_STABILITY_50NS    (0u)
#define USBCOMM_WAIT_REG_STABILITY_1US     (1u)

/* Wait cycles required after CR0 register write: 1 cycle */
#define USBCOMM_WAIT_CR0_REG_STABILITY     (1u)

/* Wait cycles required after PD_PULLUP_N bit is set in PM_USB_CR0: 2us */
#define USBCOMM_WAIT_PD_PULLUP_N_ENABLE    (2u)
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

#if (CY_PSOC4)
    #if (USBCOMM_EP_MANAGEMENT_DMA)
        #define USBCOMM_DMA_DESCR0         (0u)
        #define USBCOMM_DMA_DESCR1         (1u)
    #endif /* (USBCOMM_EP_MANAGEMENT_DMA) */

    #if (USBCOMM_EP_MANAGEMENT_DMA_AUTO)
        /* BUF_SIZE-BYTES_PER_BURST examples: 0x55 - 32 bytes, 0x44 - 16 bytes, 0x33 - 8 bytes, etc. */
        #define USBCOMM_DMA_BUF_SIZE             (0x55u)
        #define USBCOMM_DMA_BYTES_PER_BURST      (32u)
        #define USBCOMM_DMA_HALFWORDS_PER_BURST  (16u)
        #define USBCOMM_DMA_BURST_BYTES_MASK     (USBCOMM_DMA_BYTES_PER_BURST - 1u)

        #define USBCOMM_DMA_DESCR0_MASK        (0x00u)
        #define USBCOMM_DMA_DESCR1_MASK        (0x80u)
        #define USBCOMM_DMA_DESCR_REVERT       (0x40u)
        #define USBCOMM_DMA_DESCR_16BITS       (0x20u)
        #define USBCOMM_DMA_DESCR_SHIFT        (7u)

        #define USBCOMM_DMA_GET_DESCR_NUM(desrc)
        #define USBCOMM_DMA_GET_BURST_CNT(dmaBurstCnt) \
                    (((dmaBurstCnt) > 2u)? ((dmaBurstCnt) - 2u) : 0u)

        #define USBCOMM_DMA_GET_MAX_ELEM_PER_BURST(dmaLastBurstEl) \
                    ((0u != ((dmaLastBurstEl) & USBCOMM_DMA_DESCR_16BITS)) ? \
                                (USBCOMM_DMA_HALFWORDS_PER_BURST - 1u) : (USBCOMM_DMA_BYTES_PER_BURST - 1u))
    #endif /* (USBCOMM_EP_MANAGEMENT_DMA_AUTO) */
#else
    #if (USBCOMM_EP_MANAGEMENT_DMA_MANUAL)
        #define USBCOMM_DMA_BYTES_PER_BURST    (0u)
        #define USBCOMM_DMA_REQUEST_PER_BURST  (0u)
    #endif /* (USBCOMM_EP_MANAGEMENT_DMA_MANUAL) */

    #if (USBCOMM_EP_MANAGEMENT_DMA_AUTO)
        #define USBCOMM_DMA_BYTES_PER_BURST    (32u)
        #define USBCOMM_DMA_BYTES_REPEAT       (2u)

        /* BUF_SIZE-BYTES_PER_BURST examples: 0x55 - 32 bytes, 0x44 - 16 bytes, 0x33 - 8 bytes, etc. */
        #define USBCOMM_DMA_BUF_SIZE           (0x55u)
        #define USBCOMM_DMA_REQUEST_PER_BURST  (1u)

        #define USBCOMM_EP17_SR_MASK           (0x7Fu)
        #define USBCOMM_EP8_SR_MASK            (0x03u)
    #endif /* (USBCOMM_EP_MANAGEMENT_DMA_AUTO) */
#endif /* (CY_PSOC4) */

/* DIE ID string descriptor defines */
#if defined(USBCOMM_ENABLE_IDSN_STRING)
    #define USBCOMM_IDSN_DESCR_LENGTH      (0x22u)
#endif /* (USBCOMM_ENABLE_IDSN_STRING) */


/***************************************
*     Vars with External Linkage
***************************************/

/**
* \addtogroup group_globals
* @{
*/
extern uint8 USBCOMM_initVar;
extern volatile uint8 USBCOMM_device;
extern volatile uint8 USBCOMM_transferState;
extern volatile uint8 USBCOMM_configuration;
extern volatile uint8 USBCOMM_configurationChanged;
extern volatile uint8 USBCOMM_deviceStatus;
/** @} globals */

/**
* \addtogroup group_hid
* @{
*/
/* HID Variables */
#if defined(USBCOMM_ENABLE_HID_CLASS)
    extern volatile uint8 USBCOMM_hidProtocol [USBCOMM_MAX_INTERFACES_NUMBER]; 
    extern volatile uint8 USBCOMM_hidIdleRate [USBCOMM_MAX_INTERFACES_NUMBER];
    extern volatile uint8 USBCOMM_hidIdleTimer[USBCOMM_MAX_INTERFACES_NUMBER];
#endif /* (USBCOMM_ENABLE_HID_CLASS) */
/** @} hid */


/***************************************
*              Registers
***************************************/

/* Common registers for all PSoCs: 3/4/5LP */
#define USBCOMM_ARB_CFG_PTR        ( (reg8 *) USBCOMM_USB__ARB_CFG)
#define USBCOMM_ARB_CFG_REG        (*(reg8 *) USBCOMM_USB__ARB_CFG)

#define USBCOMM_ARB_EP1_CFG_PTR    ( (reg8 *) USBCOMM_USB__ARB_EP1_CFG)
#define USBCOMM_ARB_EP1_CFG_REG    (*(reg8 *) USBCOMM_USB__ARB_EP1_CFG)
#define USBCOMM_ARB_EP1_INT_EN_PTR ( (reg8 *) USBCOMM_USB__ARB_EP1_INT_EN)
#define USBCOMM_ARB_EP1_INT_EN_REG (*(reg8 *) USBCOMM_USB__ARB_EP1_INT_EN)
#define USBCOMM_ARB_EP1_SR_PTR     ( (reg8 *) USBCOMM_USB__ARB_EP1_SR)
#define USBCOMM_ARB_EP1_SR_REG     (*(reg8 *) USBCOMM_USB__ARB_EP1_SR)
#define USBCOMM_ARB_EP1_CFG_IND    USBCOMM_USB__ARB_EP1_CFG
#define USBCOMM_ARB_EP1_INT_EN_IND USBCOMM_USB__ARB_EP1_INT_EN
#define USBCOMM_ARB_EP1_SR_IND     USBCOMM_USB__ARB_EP1_SR
#define USBCOMM_ARB_EP_BASE        (*(volatile USBCOMM_arb_eps_struct CYXDATA *) \
                                            (USBCOMM_USB__ARB_EP1_CFG - sizeof(USBCOMM_arb_ep_struct)))

#define USBCOMM_ARB_EP2_CFG_PTR    ( (reg8 *) USBCOMM_USB__ARB_EP2_CFG)
#define USBCOMM_ARB_EP2_CFG_REG    (*(reg8 *) USBCOMM_USB__ARB_EP2_CFG)
#define USBCOMM_ARB_EP2_INT_EN_PTR ( (reg8 *) USBCOMM_USB__ARB_EP2_INT_EN)
#define USBCOMM_ARB_EP2_INT_EN_REG (*(reg8 *) USBCOMM_USB__ARB_EP2_INT_EN)
#define USBCOMM_ARB_EP2_SR_PTR     ( (reg8 *) USBCOMM_USB__ARB_EP2_SR)
#define USBCOMM_ARB_EP2_SR_REG     (*(reg8 *) USBCOMM_USB__ARB_EP2_SR)

#define USBCOMM_ARB_EP3_CFG_PTR    ( (reg8 *) USBCOMM_USB__ARB_EP3_CFG)
#define USBCOMM_ARB_EP3_CFG_REG    (*(reg8 *) USBCOMM_USB__ARB_EP3_CFG)
#define USBCOMM_ARB_EP3_INT_EN_PTR ( (reg8 *) USBCOMM_USB__ARB_EP3_INT_EN)
#define USBCOMM_ARB_EP3_INT_EN_REG (*(reg8 *) USBCOMM_USB__ARB_EP3_INT_EN)
#define USBCOMM_ARB_EP3_SR_PTR     ( (reg8 *) USBCOMM_USB__ARB_EP3_SR)
#define USBCOMM_ARB_EP3_SR_REG     (*(reg8 *) USBCOMM_USB__ARB_EP3_SR)

#define USBCOMM_ARB_EP4_CFG_PTR    ( (reg8 *) USBCOMM_USB__ARB_EP4_CFG)
#define USBCOMM_ARB_EP4_CFG_REG    (*(reg8 *) USBCOMM_USB__ARB_EP4_CFG)
#define USBCOMM_ARB_EP4_INT_EN_PTR ( (reg8 *) USBCOMM_USB__ARB_EP4_INT_EN)
#define USBCOMM_ARB_EP4_INT_EN_REG (*(reg8 *) USBCOMM_USB__ARB_EP4_INT_EN)
#define USBCOMM_ARB_EP4_SR_PTR     ( (reg8 *) USBCOMM_USB__ARB_EP4_SR)
#define USBCOMM_ARB_EP4_SR_REG     (*(reg8 *) USBCOMM_USB__ARB_EP4_SR)

#define USBCOMM_ARB_EP5_CFG_PTR    ( (reg8 *) USBCOMM_USB__ARB_EP5_CFG)
#define USBCOMM_ARB_EP5_CFG_REG    (*(reg8 *) USBCOMM_USB__ARB_EP5_CFG)
#define USBCOMM_ARB_EP5_INT_EN_PTR ( (reg8 *) USBCOMM_USB__ARB_EP5_INT_EN)
#define USBCOMM_ARB_EP5_INT_EN_REG (*(reg8 *) USBCOMM_USB__ARB_EP5_INT_EN)
#define USBCOMM_ARB_EP5_SR_PTR     ( (reg8 *) USBCOMM_USB__ARB_EP5_SR)
#define USBCOMM_ARB_EP5_SR_REG     (*(reg8 *) USBCOMM_USB__ARB_EP5_SR)

#define USBCOMM_ARB_EP6_CFG_PTR    ( (reg8 *) USBCOMM_USB__ARB_EP6_CFG)
#define USBCOMM_ARB_EP6_CFG_REG    (*(reg8 *) USBCOMM_USB__ARB_EP6_CFG)
#define USBCOMM_ARB_EP6_INT_EN_PTR ( (reg8 *) USBCOMM_USB__ARB_EP6_INT_EN)
#define USBCOMM_ARB_EP6_INT_EN_REG (*(reg8 *) USBCOMM_USB__ARB_EP6_INT_EN)
#define USBCOMM_ARB_EP6_SR_PTR     ( (reg8 *) USBCOMM_USB__ARB_EP6_SR)
#define USBCOMM_ARB_EP6_SR_REG     (*(reg8 *) USBCOMM_USB__ARB_EP6_SR)

#define USBCOMM_ARB_EP7_CFG_PTR    ( (reg8 *) USBCOMM_USB__ARB_EP7_CFG)
#define USBCOMM_ARB_EP7_CFG_REG    (*(reg8 *) USBCOMM_USB__ARB_EP7_CFG)
#define USBCOMM_ARB_EP7_INT_EN_PTR ( (reg8 *) USBCOMM_USB__ARB_EP7_INT_EN)
#define USBCOMM_ARB_EP7_INT_EN_REG (*(reg8 *) USBCOMM_USB__ARB_EP7_INT_EN)
#define USBCOMM_ARB_EP7_SR_PTR     ( (reg8 *) USBCOMM_USB__ARB_EP7_SR)
#define USBCOMM_ARB_EP7_SR_REG     (*(reg8 *) USBCOMM_USB__ARB_EP7_SR)

#define USBCOMM_ARB_EP8_CFG_PTR    ( (reg8 *) USBCOMM_USB__ARB_EP8_CFG)
#define USBCOMM_ARB_EP8_CFG_REG    (*(reg8 *) USBCOMM_USB__ARB_EP8_CFG)
#define USBCOMM_ARB_EP8_INT_EN_PTR ( (reg8 *) USBCOMM_USB__ARB_EP8_INT_EN)
#define USBCOMM_ARB_EP8_INT_EN_REG (*(reg8 *) USBCOMM_USB__ARB_EP8_INT_EN)
#define USBCOMM_ARB_EP8_SR_PTR     ( (reg8 *) USBCOMM_USB__ARB_EP8_SR)
#define USBCOMM_ARB_EP8_SR_REG     (*(reg8 *) USBCOMM_USB__ARB_EP8_SR)

#define USBCOMM_ARB_INT_EN_PTR     ( (reg8 *) USBCOMM_USB__ARB_INT_EN)
#define USBCOMM_ARB_INT_EN_REG     (*(reg8 *) USBCOMM_USB__ARB_INT_EN)
#define USBCOMM_ARB_INT_SR_PTR     ( (reg8 *) USBCOMM_USB__ARB_INT_SR)
#define USBCOMM_ARB_INT_SR_REG     (*(reg8 *) USBCOMM_USB__ARB_INT_SR)

#define USBCOMM_ARB_RW1_DR_PTR     ( (reg8 *) USBCOMM_USB__ARB_RW1_DR)
#define USBCOMM_ARB_RW1_RA_PTR     ( (reg8 *) USBCOMM_USB__ARB_RW1_RA)

#define USBCOMM_ARB_RW1_RA_MSB_PTR ( (reg8 *) USBCOMM_USB__ARB_RW1_RA_MSB)
#define USBCOMM_ARB_RW1_WA_PTR     ( (reg8 *) USBCOMM_USB__ARB_RW1_WA)
#define USBCOMM_ARB_RW1_WA_MSB_PTR ( (reg8 *) USBCOMM_USB__ARB_RW1_WA_MSB)
#define USBCOMM_ARB_RW1_DR_IND     USBCOMM_USB__ARB_RW1_DR
#define USBCOMM_ARB_RW1_RA_IND     USBCOMM_USB__ARB_RW1_RA
#define USBCOMM_ARB_RW1_RA_MSB_IND USBCOMM_USB__ARB_RW1_RA_MSB
#define USBCOMM_ARB_RW1_WA_IND     USBCOMM_USB__ARB_RW1_WA
#define USBCOMM_ARB_RW1_WA_MSB_IND USBCOMM_USB__ARB_RW1_WA_MSB

#define USBCOMM_ARB_RW2_DR_PTR     ( (reg8 *) USBCOMM_USB__ARB_RW2_DR)
#define USBCOMM_ARB_RW2_RA_PTR     ( (reg8 *) USBCOMM_USB__ARB_RW2_RA)
#define USBCOMM_ARB_RW2_RA_MSB_PTR ( (reg8 *) USBCOMM_USB__ARB_RW2_RA_MSB)
#define USBCOMM_ARB_RW2_WA_PTR     ( (reg8 *) USBCOMM_USB__ARB_RW2_WA)
#define USBCOMM_ARB_RW2_WA_MSB_PTR ( (reg8 *) USBCOMM_USB__ARB_RW2_WA_MSB)

#define USBCOMM_ARB_RW3_DR_PTR     ( (reg8 *) USBCOMM_USB__ARB_RW3_DR)
#define USBCOMM_ARB_RW3_RA_PTR     ( (reg8 *) USBCOMM_USB__ARB_RW3_RA)
#define USBCOMM_ARB_RW3_RA_MSB_PTR ( (reg8 *) USBCOMM_USB__ARB_RW3_RA_MSB)
#define USBCOMM_ARB_RW3_WA_PTR     ( (reg8 *) USBCOMM_USB__ARB_RW3_WA)
#define USBCOMM_ARB_RW3_WA_MSB_PTR ( (reg8 *) USBCOMM_USB__ARB_RW3_WA_MSB)

#define USBCOMM_ARB_RW4_DR_PTR     ( (reg8 *) USBCOMM_USB__ARB_RW4_DR)
#define USBCOMM_ARB_RW4_RA_PTR     ( (reg8 *) USBCOMM_USB__ARB_RW4_RA)
#define USBCOMM_ARB_RW4_RA_MSB_PTR ( (reg8 *) USBCOMM_USB__ARB_RW4_RA_MSB)
#define USBCOMM_ARB_RW4_WA_PTR     ( (reg8 *) USBCOMM_USB__ARB_RW4_WA)
#define USBCOMM_ARB_RW4_WA_MSB_PTR ( (reg8 *) USBCOMM_USB__ARB_RW4_WA_MSB)

#define USBCOMM_ARB_RW5_DR_PTR     ( (reg8 *) USBCOMM_USB__ARB_RW5_DR)
#define USBCOMM_ARB_RW5_RA_PTR     ( (reg8 *) USBCOMM_USB__ARB_RW5_RA)
#define USBCOMM_ARB_RW5_RA_MSB_PTR ( (reg8 *) USBCOMM_USB__ARB_RW5_RA_MSB)
#define USBCOMM_ARB_RW5_WA_PTR     ( (reg8 *) USBCOMM_USB__ARB_RW5_WA)
#define USBCOMM_ARB_RW5_WA_MSB_PTR ( (reg8 *) USBCOMM_USB__ARB_RW5_WA_MSB)

#define USBCOMM_ARB_RW6_DR_PTR     ( (reg8 *) USBCOMM_USB__ARB_RW6_DR)
#define USBCOMM_ARB_RW6_RA_PTR     ( (reg8 *) USBCOMM_USB__ARB_RW6_RA)
#define USBCOMM_ARB_RW6_RA_MSB_PTR ( (reg8 *) USBCOMM_USB__ARB_RW6_RA_MSB)
#define USBCOMM_ARB_RW6_WA_PTR     ( (reg8 *) USBCOMM_USB__ARB_RW6_WA)
#define USBCOMM_ARB_RW6_WA_MSB_PTR ( (reg8 *) USBCOMM_USB__ARB_RW6_WA_MSB)

#define USBCOMM_ARB_RW7_DR_PTR     ( (reg8 *) USBCOMM_USB__ARB_RW7_DR)
#define USBCOMM_ARB_RW7_RA_PTR     ( (reg8 *) USBCOMM_USB__ARB_RW7_RA)
#define USBCOMM_ARB_RW7_RA_MSB_PTR ( (reg8 *) USBCOMM_USB__ARB_RW7_RA_MSB)
#define USBCOMM_ARB_RW7_WA_PTR     ( (reg8 *) USBCOMM_USB__ARB_RW7_WA)
#define USBCOMM_ARB_RW7_WA_MSB_PTR ( (reg8 *) USBCOMM_USB__ARB_RW7_WA_MSB)

#define USBCOMM_ARB_RW8_DR_PTR     ( (reg8 *) USBCOMM_USB__ARB_RW8_DR)
#define USBCOMM_ARB_RW8_RA_PTR     ( (reg8 *) USBCOMM_USB__ARB_RW8_RA)
#define USBCOMM_ARB_RW8_RA_MSB_PTR ( (reg8 *) USBCOMM_USB__ARB_RW8_RA_MSB)
#define USBCOMM_ARB_RW8_WA_PTR     ( (reg8 *) USBCOMM_USB__ARB_RW8_WA)
#define USBCOMM_ARB_RW8_WA_MSB_PTR ( (reg8 *) USBCOMM_USB__ARB_RW8_WA_MSB)

#define USBCOMM_BUF_SIZE_PTR       ( (reg8 *) USBCOMM_USB__BUF_SIZE)
#define USBCOMM_BUF_SIZE_REG       (*(reg8 *) USBCOMM_USB__BUF_SIZE)
#define USBCOMM_BUS_RST_CNT_PTR    ( (reg8 *) USBCOMM_USB__BUS_RST_CNT)
#define USBCOMM_BUS_RST_CNT_REG    (*(reg8 *) USBCOMM_USB__BUS_RST_CNT)
#define USBCOMM_CWA_PTR            ( (reg8 *) USBCOMM_USB__CWA)
#define USBCOMM_CWA_REG            (*(reg8 *) USBCOMM_USB__CWA)
#define USBCOMM_CWA_MSB_PTR        ( (reg8 *) USBCOMM_USB__CWA_MSB)
#define USBCOMM_CWA_MSB_REG        (*(reg8 *) USBCOMM_USB__CWA_MSB)
#define USBCOMM_CR0_PTR            ( (reg8 *) USBCOMM_USB__CR0)
#define USBCOMM_CR0_REG            (*(reg8 *) USBCOMM_USB__CR0)
#define USBCOMM_CR1_PTR            ( (reg8 *) USBCOMM_USB__CR1)
#define USBCOMM_CR1_REG            (*(reg8 *) USBCOMM_USB__CR1)

#define USBCOMM_DMA_THRES_PTR      ( (reg8 *) USBCOMM_USB__DMA_THRES)
#define USBCOMM_DMA_THRES_REG      (*(reg8 *) USBCOMM_USB__DMA_THRES)
#define USBCOMM_DMA_THRES_MSB_PTR  ( (reg8 *) USBCOMM_USB__DMA_THRES_MSB)
#define USBCOMM_DMA_THRES_MSB_REG  (*(reg8 *) USBCOMM_USB__DMA_THRES_MSB)

#define USBCOMM_EP_ACTIVE_PTR      ( (reg8 *) USBCOMM_USB__EP_ACTIVE)
#define USBCOMM_EP_ACTIVE_REG      (*(reg8 *) USBCOMM_USB__EP_ACTIVE)
#define USBCOMM_EP_TYPE_PTR        ( (reg8 *) USBCOMM_USB__EP_TYPE)
#define USBCOMM_EP_TYPE_REG        (*(reg8 *) USBCOMM_USB__EP_TYPE)

#define USBCOMM_EP0_CNT_PTR        ( (reg8 *) USBCOMM_USB__EP0_CNT)
#define USBCOMM_EP0_CNT_REG        (*(reg8 *) USBCOMM_USB__EP0_CNT)
#define USBCOMM_EP0_CR_PTR         ( (reg8 *) USBCOMM_USB__EP0_CR)
#define USBCOMM_EP0_CR_REG         (*(reg8 *) USBCOMM_USB__EP0_CR)
#define USBCOMM_EP0_DR0_PTR        ( (reg8 *) USBCOMM_USB__EP0_DR0)
#define USBCOMM_EP0_DR0_REG        (*(reg8 *) USBCOMM_USB__EP0_DR0)
#define USBCOMM_EP0_DR1_PTR        ( (reg8 *) USBCOMM_USB__EP0_DR1)
#define USBCOMM_EP0_DR1_REG        (*(reg8 *) USBCOMM_USB__EP0_DR1)
#define USBCOMM_EP0_DR2_PTR        ( (reg8 *) USBCOMM_USB__EP0_DR2)
#define USBCOMM_EP0_DR2_REG        (*(reg8 *) USBCOMM_USB__EP0_DR2)
#define USBCOMM_EP0_DR3_PTR        ( (reg8 *) USBCOMM_USB__EP0_DR3)
#define USBCOMM_EP0_DR3_REG        (*(reg8 *) USBCOMM_USB__EP0_DR3)
#define USBCOMM_EP0_DR4_PTR        ( (reg8 *) USBCOMM_USB__EP0_DR4)
#define USBCOMM_EP0_DR4_REG        (*(reg8 *) USBCOMM_USB__EP0_DR4)
#define USBCOMM_EP0_DR5_PTR        ( (reg8 *) USBCOMM_USB__EP0_DR5)
#define USBCOMM_EP0_DR5_REG        (*(reg8 *) USBCOMM_USB__EP0_DR5)
#define USBCOMM_EP0_DR6_PTR        ( (reg8 *) USBCOMM_USB__EP0_DR6)
#define USBCOMM_EP0_DR6_REG        (*(reg8 *) USBCOMM_USB__EP0_DR6)
#define USBCOMM_EP0_DR7_PTR        ( (reg8 *) USBCOMM_USB__EP0_DR7)
#define USBCOMM_EP0_DR7_REG        (*(reg8 *) USBCOMM_USB__EP0_DR7)
#define USBCOMM_EP0_DR0_IND        USBCOMM_USB__EP0_DR0
#define USBCOMM_EP0_DR_BASE        (*(volatile USBCOMM_ep0_data_struct CYXDATA *) USBCOMM_USB__EP0_DR0)

#define USBCOMM_OSCLK_DR0_PTR      ( (reg8 *) USBCOMM_USB__OSCLK_DR0)
#define USBCOMM_OSCLK_DR0_REG      (*(reg8 *) USBCOMM_USB__OSCLK_DR0)
#define USBCOMM_OSCLK_DR1_PTR      ( (reg8 *) USBCOMM_USB__OSCLK_DR1)
#define USBCOMM_OSCLK_DR1_REG      (*(reg8 *) USBCOMM_USB__OSCLK_DR1)

#define USBCOMM_SIE_EP_INT_EN_PTR  ( (reg8 *) USBCOMM_USB__SIE_EP_INT_EN)
#define USBCOMM_SIE_EP_INT_EN_REG  (*(reg8 *) USBCOMM_USB__SIE_EP_INT_EN)
#define USBCOMM_SIE_EP_INT_SR_PTR  ( (reg8 *) USBCOMM_USB__SIE_EP_INT_SR)
#define USBCOMM_SIE_EP_INT_SR_REG  (*(reg8 *) USBCOMM_USB__SIE_EP_INT_SR)

#define USBCOMM_SIE_EP1_CNT0_PTR   ( (reg8 *) USBCOMM_USB__SIE_EP1_CNT0)
#define USBCOMM_SIE_EP1_CNT0_REG   (*(reg8 *) USBCOMM_USB__SIE_EP1_CNT0)
#define USBCOMM_SIE_EP1_CNT1_PTR   ( (reg8 *) USBCOMM_USB__SIE_EP1_CNT1)
#define USBCOMM_SIE_EP1_CNT1_REG   (*(reg8 *) USBCOMM_USB__SIE_EP1_CNT1)
#define USBCOMM_SIE_EP1_CR0_PTR    ( (reg8 *) USBCOMM_USB__SIE_EP1_CR0)
#define USBCOMM_SIE_EP1_CR0_REG    (*(reg8 *) USBCOMM_USB__SIE_EP1_CR0)
#define USBCOMM_SIE_EP1_CNT1_IND   USBCOMM_USB__SIE_EP1_CNT1
#define USBCOMM_SIE_EP1_CNT0_IND   USBCOMM_USB__SIE_EP1_CNT0
#define USBCOMM_SIE_EP1_CR0_IND    USBCOMM_USB__SIE_EP1_CR0
#define USBCOMM_SIE_EP_BASE        (*(volatile USBCOMM_sie_eps_struct CYXDATA *) \
                                            (USBCOMM_USB__SIE_EP1_CNT0 - sizeof(USBCOMM_sie_ep_struct)))

#define USBCOMM_SIE_EP2_CNT0_PTR   ( (reg8 *) USBCOMM_USB__SIE_EP2_CNT0)
#define USBCOMM_SIE_EP2_CNT0_REG   (*(reg8 *) USBCOMM_USB__SIE_EP2_CNT0)
#define USBCOMM_SIE_EP2_CNT1_PTR   ( (reg8 *) USBCOMM_USB__SIE_EP2_CNT1)
#define USBCOMM_SIE_EP2_CNT1_REG   (*(reg8 *) USBCOMM_USB__SIE_EP2_CNT1)
#define USBCOMM_SIE_EP2_CR0_PTR    ( (reg8 *) USBCOMM_USB__SIE_EP2_CR0)
#define USBCOMM_SIE_EP2_CR0_REG    (*(reg8 *) USBCOMM_USB__SIE_EP2_CR0)

#define USBCOMM_SIE_EP3_CNT0_PTR   ( (reg8 *) USBCOMM_USB__SIE_EP3_CNT0)
#define USBCOMM_SIE_EP3_CNT0_REG   (*(reg8 *) USBCOMM_USB__SIE_EP3_CNT0)
#define USBCOMM_SIE_EP3_CNT1_PTR   ( (reg8 *) USBCOMM_USB__SIE_EP3_CNT1)
#define USBCOMM_SIE_EP3_CNT1_REG   (*(reg8 *) USBCOMM_USB__SIE_EP3_CNT1)
#define USBCOMM_SIE_EP3_CR0_PTR    ( (reg8 *) USBCOMM_USB__SIE_EP3_CR0)
#define USBCOMM_SIE_EP3_CR0_REG    (*(reg8 *) USBCOMM_USB__SIE_EP3_CR0)

#define USBCOMM_SIE_EP4_CNT0_PTR   ( (reg8 *) USBCOMM_USB__SIE_EP4_CNT0)
#define USBCOMM_SIE_EP4_CNT0_REG   (*(reg8 *) USBCOMM_USB__SIE_EP4_CNT0)
#define USBCOMM_SIE_EP4_CNT1_PTR   ( (reg8 *) USBCOMM_USB__SIE_EP4_CNT1)
#define USBCOMM_SIE_EP4_CNT1_REG   (*(reg8 *) USBCOMM_USB__SIE_EP4_CNT1)
#define USBCOMM_SIE_EP4_CR0_PTR    ( (reg8 *) USBCOMM_USB__SIE_EP4_CR0)
#define USBCOMM_SIE_EP4_CR0_REG    (*(reg8 *) USBCOMM_USB__SIE_EP4_CR0)

#define USBCOMM_SIE_EP5_CNT0_PTR   ( (reg8 *) USBCOMM_USB__SIE_EP5_CNT0)
#define USBCOMM_SIE_EP5_CNT0_REG   (*(reg8 *) USBCOMM_USB__SIE_EP5_CNT0)
#define USBCOMM_SIE_EP5_CNT1_PTR   ( (reg8 *) USBCOMM_USB__SIE_EP5_CNT1)
#define USBCOMM_SIE_EP5_CNT1_REG   (*(reg8 *) USBCOMM_USB__SIE_EP5_CNT1)
#define USBCOMM_SIE_EP5_CR0_PTR    ( (reg8 *) USBCOMM_USB__SIE_EP5_CR0)
#define USBCOMM_SIE_EP5_CR0_REG    (*(reg8 *) USBCOMM_USB__SIE_EP5_CR0)

#define USBCOMM_SIE_EP6_CNT0_PTR   ( (reg8 *) USBCOMM_USB__SIE_EP6_CNT0)
#define USBCOMM_SIE_EP6_CNT0_REG   (*(reg8 *) USBCOMM_USB__SIE_EP6_CNT0)
#define USBCOMM_SIE_EP6_CNT1_PTR   ( (reg8 *) USBCOMM_USB__SIE_EP6_CNT1)
#define USBCOMM_SIE_EP6_CNT1_REG   (*(reg8 *) USBCOMM_USB__SIE_EP6_CNT1)
#define USBCOMM_SIE_EP6_CR0_PTR    ( (reg8 *) USBCOMM_USB__SIE_EP6_CR0)
#define USBCOMM_SIE_EP6_CR0_REG    (*(reg8 *) USBCOMM_USB__SIE_EP6_CR0)

#define USBCOMM_SIE_EP7_CNT0_PTR   ( (reg8 *) USBCOMM_USB__SIE_EP7_CNT0)
#define USBCOMM_SIE_EP7_CNT0_REG   (*(reg8 *) USBCOMM_USB__SIE_EP7_CNT0)
#define USBCOMM_SIE_EP7_CNT1_PTR   ( (reg8 *) USBCOMM_USB__SIE_EP7_CNT1)
#define USBCOMM_SIE_EP7_CNT1_REG   (*(reg8 *) USBCOMM_USB__SIE_EP7_CNT1)
#define USBCOMM_SIE_EP7_CR0_PTR    ( (reg8 *) USBCOMM_USB__SIE_EP7_CR0)
#define USBCOMM_SIE_EP7_CR0_REG    (*(reg8 *) USBCOMM_USB__SIE_EP7_CR0)

#define USBCOMM_SIE_EP8_CNT0_PTR   ( (reg8 *) USBCOMM_USB__SIE_EP8_CNT0)
#define USBCOMM_SIE_EP8_CNT0_REG   (*(reg8 *) USBCOMM_USB__SIE_EP8_CNT0)
#define USBCOMM_SIE_EP8_CNT1_PTR   ( (reg8 *) USBCOMM_USB__SIE_EP8_CNT1)
#define USBCOMM_SIE_EP8_CNT1_REG   (*(reg8 *) USBCOMM_USB__SIE_EP8_CNT1)
#define USBCOMM_SIE_EP8_CR0_PTR    ( (reg8 *) USBCOMM_USB__SIE_EP8_CR0)
#define USBCOMM_SIE_EP8_CR0_REG    (*(reg8 *) USBCOMM_USB__SIE_EP8_CR0)

#define USBCOMM_SOF0_PTR           ( (reg8 *) USBCOMM_USB__SOF0)
#define USBCOMM_SOF0_REG           (*(reg8 *) USBCOMM_USB__SOF0)
#define USBCOMM_SOF1_PTR           ( (reg8 *) USBCOMM_USB__SOF1)
#define USBCOMM_SOF1_REG           (*(reg8 *) USBCOMM_USB__SOF1)

#define USBCOMM_USB_CLK_EN_PTR     ( (reg8 *) USBCOMM_USB__USB_CLK_EN)
#define USBCOMM_USB_CLK_EN_REG     (*(reg8 *) USBCOMM_USB__USB_CLK_EN)

#define USBCOMM_USBIO_CR0_PTR      ( (reg8 *) USBCOMM_USB__USBIO_CR0)
#define USBCOMM_USBIO_CR0_REG      (*(reg8 *) USBCOMM_USB__USBIO_CR0)
#define USBCOMM_USBIO_CR1_PTR      ( (reg8 *) USBCOMM_USB__USBIO_CR1)
#define USBCOMM_USBIO_CR1_REG      (*(reg8 *) USBCOMM_USB__USBIO_CR1)

#define USBCOMM_DYN_RECONFIG_PTR   ( (reg8 *) USBCOMM_USB__DYN_RECONFIG)
#define USBCOMM_DYN_RECONFIG_REG   (*(reg8 *) USBCOMM_USB__DYN_RECONFIG)

#if (CY_PSOC4)
    #define USBCOMM_ARB_RW1_RA16_PTR   ( (reg32 *) USBCOMM_cy_m0s8_usb__ARB_RW1_RA16)
    #define USBCOMM_ARB_RW1_RA16_REG   (*(reg32 *) USBCOMM_cy_m0s8_usb__ARB_RW1_RA16)
    #define USBCOMM_ARB_RW1_WA16_PTR   ( (reg32 *) USBCOMM_cy_m0s8_usb__ARB_RW1_WA16)
    #define USBCOMM_ARB_RW1_WA16_REG   (*(reg32 *) USBCOMM_cy_m0s8_usb__ARB_RW1_WA16)
    #define USBCOMM_ARB_RW1_DR16_PTR   ( (reg32 *) USBCOMM_cy_m0s8_usb__ARB_RW1_DR16)
    #define USBCOMM_ARB_RW1_DR16_PTR   ( (reg32 *) USBCOMM_cy_m0s8_usb__ARB_RW1_DR16)
    #define USBCOMM_ARB_EP16_BASE      (*(volatile USBCOMM_arb_eps_reg16_struct CYXDATA *) \
                                                (USBCOMM_USB__ARB_RW1_WA16 - sizeof(USBCOMM_arb_ep_reg16_struct)))

    #define USBCOMM_ARB_RW2_DR16_PTR   ( (reg32 *) USBCOMM_cy_m0s8_usb__ARB_RW2_DR16)
    #define USBCOMM_ARB_RW2_RA16_PTR   ( (reg32 *) USBCOMM_cy_m0s8_usb__ARB_RW2_RA16)
    #define USBCOMM_ARB_RW2_WA16_PTR   ( (reg32 *) USBCOMM_cy_m0s8_usb__ARB_RW2_WA16)

    #define USBCOMM_ARB_RW3_DR16_PTR   ( (reg32 *) USBCOMM_cy_m0s8_usb__ARB_RW3_DR16)
    #define USBCOMM_ARB_RW3_RA16_PTR   ( (reg32 *) USBCOMM_cy_m0s8_usb__ARB_RW3_RA16)
    #define USBCOMM_ARB_RW3_WA16_PTR   ( (reg32 *) USBCOMM_cy_m0s8_usb__ARB_RW3_WA16)

    #define USBCOMM_ARB_RW4_DR16_PTR   ( (reg32 *) USBCOMM_cy_m0s8_usb__ARB_RW4_DR16)
    #define USBCOMM_ARB_RW4_RA16_PTR   ( (reg32 *) USBCOMM_cy_m0s8_usb__ARB_RW4_RA16)
    #define USBCOMM_ARB_RW4_WA16_PTR   ( (reg32 *) USBCOMM_cy_m0s8_usb__ARB_RW4_WA16)

    #define USBCOMM_ARB_RW5_DR16_PTR   ( (reg32 *) USBCOMM_cy_m0s8_usb__ARB_RW5_DR16)
    #define USBCOMM_ARB_RW5_RA16_PTR   ( (reg32 *) USBCOMM_cy_m0s8_usb__ARB_RW5_RA16)
    #define USBCOMM_ARB_RW5_WA16_PTR   ( (reg32 *) USBCOMM_cy_m0s8_usb__ARB_RW5_WA16)

    #define USBCOMM_ARB_RW6_DR16_PTR   ( (reg32 *) USBCOMM_cy_m0s8_usb__ARB_RW6_DR16)
    #define USBCOMM_ARB_RW6_RA16_PTR   ( (reg32 *) USBCOMM_cy_m0s8_usb__ARB_RW6_RA16)
    #define USBCOMM_ARB_RW6_WA16_PTR   ( (reg32 *) USBCOMM_cy_m0s8_usb__ARB_RW6_WA16)

    #define USBCOMM_ARB_RW7_DR16_PTR   ( (reg32 *) USBCOMM_cy_m0s8_usb__ARB_RW7_DR16)
    #define USBCOMM_ARB_RW7_RA16_PTR   ( (reg32 *) USBCOMM_cy_m0s8_usb__ARB_RW7_RA16)
    #define USBCOMM_ARB_RW7_WA16_PTR   ( (reg32 *) USBCOMM_cy_m0s8_usb__ARB_RW7_WA16)

    #define USBCOMM_ARB_RW8_DR16_PTR   ( (reg32 *) USBCOMM_cy_m0s8_usb__ARB_RW8_DR16)
    #define USBCOMM_ARB_RW8_RA16_PTR   ( (reg32 *) USBCOMM_cy_m0s8_usb__ARB_RW8_RA16)
    #define USBCOMM_ARB_RW8_WA16_PTR   ( (reg32 *) USBCOMM_cy_m0s8_usb__ARB_RW8_WA16)

    #define USBCOMM_OSCLK_DR16_PTR     ( (reg32 *) USBCOMM_cy_m0s8_usb__OSCLK_DR16)
    #define USBCOMM_OSCLK_DR16_REG     (*(reg32 *) USBCOMM_cy_m0s8_usb__OSCLK_DR16)

    #define USBCOMM_SOF16_PTR          ( (reg32 *) USBCOMM_cy_m0s8_usb__SOF16)
    #define USBCOMM_SOF16_REG          (*(reg32 *) USBCOMM_cy_m0s8_usb__SOF16)
    
    #define USBCOMM_CWA16_PTR          ( (reg32 *) USBCOMM_cy_m0s8_usb__CWA16)
    #define USBCOMM_CWA16_REG          (*(reg32 *) USBCOMM_cy_m0s8_usb__CWA16)

    #define USBCOMM_DMA_THRES16_PTR    ( (reg32 *) USBCOMM_cy_m0s8_usb__DMA_THRES16)
    #define USBCOMM_DMA_THRES16_REG    (*(reg32 *) USBCOMM_cy_m0s8_usb__DMA_THRES16)

    #define USBCOMM_USB_CLK_EN_PTR     ( (reg32 *) USBCOMM_cy_m0s8_usb__USB_CLK_EN)
    #define USBCOMM_USB_CLK_EN_REG     (*(reg32 *) USBCOMM_cy_m0s8_usb__USB_CLK_EN)

    #define USBCOMM_USBIO_CR2_PTR      ( (reg32 *) USBCOMM_cy_m0s8_usb__USBIO_CR2)
    #define USBCOMM_USBIO_CR2_REG      (*(reg32 *) USBCOMM_cy_m0s8_usb__USBIO_CR2)

    #define USBCOMM_USB_MEM            ( (reg32 *) USBCOMM_cy_m0s8_usb__MEM_DATA0)

    #define USBCOMM_POWER_CTRL_REG      (*(reg32 *) USBCOMM_cy_m0s8_usb__USB_POWER_CTRL)
    #define USBCOMM_POWER_CTRL_PTR      ( (reg32 *) USBCOMM_cy_m0s8_usb__USB_POWER_CTRL)

    #define USBCOMM_CHGDET_CTRL_REG     (*(reg32 *) USBCOMM_cy_m0s8_usb__USB_CHGDET_CTRL)
    #define USBCOMM_CHGDET_CTRL_PTR     ( (reg32 *) USBCOMM_cy_m0s8_usb__USB_CHGDET_CTRL)

    #define USBCOMM_USBIO_CTRL_REG      (*(reg32 *) USBCOMM_cy_m0s8_usb__USB_USBIO_CTRL)
    #define USBCOMM_USBIO_CTRL_PTR      ( (reg32 *) USBCOMM_cy_m0s8_usb__USB_USBIO_CTRL)

    #define USBCOMM_FLOW_CTRL_REG       (*(reg32 *) USBCOMM_cy_m0s8_usb__USB_FLOW_CTRL)
    #define USBCOMM_FLOW_CTRL_PTR       ( (reg32 *) USBCOMM_cy_m0s8_usb__USB_FLOW_CTRL)

    #define USBCOMM_LPM_CTRL_REG        (*(reg32 *) USBCOMM_cy_m0s8_usb__USB_LPM_CTRL)
    #define USBCOMM_LPM_CTRL_PTR        ( (reg32 *) USBCOMM_cy_m0s8_usb__USB_LPM_CTRL)

    #define USBCOMM_LPM_STAT_REG        (*(reg32 *) USBCOMM_cy_m0s8_usb__USB_LPM_STAT)
    #define USBCOMM_LPM_STAT_PTR        ( (reg32 *) USBCOMM_cy_m0s8_usb__USB_LPM_STAT)

    #define USBCOMM_PHY_CONTROL_REG     (*(reg32 *) USBCOMM_cy_m0s8_usb__USB_PHY_CONTROL)
    #define USBCOMM_PHY_CONTROL_PTR     ( (reg32 *) USBCOMM_cy_m0s8_usb__USB_PHY_CONTROL)

    #define USBCOMM_INTR_SIE_REG        (*(reg32 *) USBCOMM_cy_m0s8_usb__USB_INTR_SIE)
    #define USBCOMM_INTR_SIE_PTR        ( (reg32 *) USBCOMM_cy_m0s8_usb__USB_INTR_SIE)

    #define USBCOMM_INTR_SIE_SET_REG    (*(reg32 *) USBCOMM_cy_m0s8_usb__USB_INTR_SIE_SET)
    #define USBCOMM_INTR_SIE_SET_PTR    ( (reg32 *) USBCOMM_cy_m0s8_usb__USB_INTR_SIE_SET)

    #define USBCOMM_INTR_SIE_MASK_REG   (*(reg32 *) USBCOMM_cy_m0s8_usb__USB_INTR_SIE_MASK)
    #define USBCOMM_INTR_SIE_MASK_PTR   ( (reg32 *) USBCOMM_cy_m0s8_usb__USB_INTR_SIE_MASK)

    #define USBCOMM_INTR_SIE_MASKED_REG (*(reg32 *) USBCOMM_cy_m0s8_usb__USB_INTR_SIE_MASKED)
    #define USBCOMM_INTR_SIE_MASKED_PTR ( (reg32 *) USBCOMM_cy_m0s8_usb__USB_INTR_SIE_MASKED)

    #define USBCOMM_INTR_LVL_SEL_REG    (*(reg32 *) USBCOMM_cy_m0s8_usb__USB_INTR_LVL_SEL)
    #define USBCOMM_INTR_LVL_SEL_PTR    ( (reg32 *) USBCOMM_cy_m0s8_usb__USB_INTR_LVL_SEL)

    #define USBCOMM_INTR_CAUSE_HI_REG   (*(reg32 *) USBCOMM_cy_m0s8_usb__USB_INTR_CAUSE_HI)
    #define USBCOMM_INTR_CAUSE_HI_PTR   ( (reg32 *) USBCOMM_cy_m0s8_usb__USB_INTR_CAUSE_HI)

    #define USBCOMM_INTR_CAUSE_LO_REG   (*(reg32 *) USBCOMM_cy_m0s8_usb__USB_INTR_CAUSE_LO)
    #define USBCOMM_INTR_CAUSE_LO_PTR   ( (reg32 *) USBCOMM_cy_m0s8_usb__USB_INTR_CAUSE_LO)

    #define USBCOMM_INTR_CAUSE_MED_REG  (*(reg32 *) USBCOMM_cy_m0s8_usb__USB_INTR_CAUSE_MED)
    #define USBCOMM_INTR_CAUSE_MED_PTR  ( (reg32 *) USBCOMM_cy_m0s8_usb__USB_INTR_CAUSE_MED)

    #define USBCOMM_DFT_CTRL_REG        (*(reg32 *) USBCOMM_cy_m0s8_usb__USB_DFT_CTRL)
    #define USBCOMM_DFT_CTRL_PTR        ( (reg32 *) USBCOMM_cy_m0s8_usb__USB_DFT_CTRL)

    #if (USBCOMM_VBUS_MONITORING_ENABLE)
        #if (USBCOMM_VBUS_POWER_PAD_ENABLE)
            /* Vbus power pad pin is hard wired to P13[2] */
            #define USBCOMM_VBUS_STATUS_REG    (*(reg32 *) CYREG_GPIO_PRT13_PS)
            #define USBCOMM_VBUS_STATUS_PTR    ( (reg32 *) CYREG_GPIO_PRT13_PS)
            #define USBCOMM_VBUS_VALID         (0x04u)
        #else
            /* Vbus valid pin is hard wired to P0[0] */
            #define USBCOMM_VBUS_STATUS_REG    (*(reg32 *) CYREG_GPIO_PRT0_PS)
            #define USBCOMM_VBUS_STATUS_PTR    ( (reg32 *) CYREG_GPIO_PRT0_PS)
            #define USBCOMM_VBUS_VALID         (0x01u)
        #endif
    #endif /*(USBCOMM_VBUS_MONITORING_ENABLE) */

    #define USBCOMM_BURSTEND_0_TR_OUTPUT    (USBCOMM_cy_m0s8_usb__BURSTEND0_TR_OUTPUT)
    #define USBCOMM_BURSTEND_1_TR_OUTPUT    (USBCOMM_cy_m0s8_usb__BURSTEND1_TR_OUTPUT)
    #define USBCOMM_BURSTEND_2_TR_OUTPUT    (USBCOMM_cy_m0s8_usb__BURSTEND2_TR_OUTPUT)
    #define USBCOMM_BURSTEND_3_TR_OUTPUT    (USBCOMM_cy_m0s8_usb__BURSTEND3_TR_OUTPUT)
    #define USBCOMM_BURSTEND_4_TR_OUTPUT    (USBCOMM_cy_m0s8_usb__BURSTEND4_TR_OUTPUT)
    #define USBCOMM_BURSTEND_5_TR_OUTPUT    (USBCOMM_cy_m0s8_usb__BURSTEND5_TR_OUTPUT)
    #define USBCOMM_BURSTEND_6_TR_OUTPUT    (USBCOMM_cy_m0s8_usb__BURSTEND6_TR_OUTPUT)
    #define USBCOMM_BURSTEND_7_TR_OUTPUT    (USBCOMM_cy_m0s8_usb__BURSTEND7_TR_OUTPUT)
    
#else /* (CY_PSOC3 || CY_PSOC5LP) */

    /* USBCOMM_PM_USB_CR0 */
    #define USBCOMM_PM_USB_CR0_PTR     ( (reg8 *) CYREG_PM_USB_CR0)
    #define USBCOMM_PM_USB_CR0_REG     (*(reg8 *) CYREG_PM_USB_CR0)

    /* USBCOMM_PM_ACT/STBY_CFG */
    #define USBCOMM_PM_ACT_CFG_PTR     ( (reg8 *) USBCOMM_USB__PM_ACT_CFG)
    #define USBCOMM_PM_ACT_CFG_REG     (*(reg8 *) USBCOMM_USB__PM_ACT_CFG)
    #define USBCOMM_PM_STBY_CFG_PTR    ( (reg8 *) USBCOMM_USB__PM_STBY_CFG)
    #define USBCOMM_PM_STBY_CFG_REG    (*(reg8 *) USBCOMM_USB__PM_STBY_CFG)

    #if (!CY_PSOC5LP)
        #define USBCOMM_USBIO_CR2_PTR  (  (reg8 *) USBCOMM_USB__USBIO_CR2)
        #define USBCOMM_USBIO_CR2_REG  (* (reg8 *) USBCOMM_USB__USBIO_CR2)
    #endif /* (!CY_PSOC5LP) */

    /* USBCOMM_USB_MEM - USB IP memory buffer */
    #define USBCOMM_USB_MEM            ((reg8 *) CYDEV_USB_MEM_BASE)

    #if (USBCOMM_VBUS_MONITORING_ENABLE)
        #if (USBCOMM_VBUS_MONITORING_INTERNAL)
            #define USBCOMM_VBUS_STATUS_REG    (*(reg8 *) USBCOMM_VBUS__PS)
            #define USBCOMM_VBUS_STATUS_PTR    ( (reg8 *) USBCOMM_VBUS__PS)
            #define USBCOMM_VBUS_VALID         (USBCOMM_VBUS__MASK)
        #else
            #define USBCOMM_VBUS_STATUS_REG    (*(reg8 *) USBCOMM_Vbus_ps_sts_sts_reg__STATUS_REG)
            #define USBCOMM_VBUS_STATUS_PTR    ( (reg8 *) USBCOMM_Vbus_ps_sts_sts_reg__STATUS_REG)
            #define USBCOMM_VBUS_VALID         (USBCOMM_Vbus_ps_sts_sts_reg__MASK)
        #endif /* (USBCOMM_VBUS_MONITORING_INTERNAL) */
    #endif /*(USBCOMM_VBUS_MONITORING_ENABLE) */
#endif /* (CY_PSOC4) */


/***************************************
*       Interrupt source constants
***************************************/

#define USBCOMM_DP_INTC_PRIORITY       USBCOMM_dp_int__INTC_PRIOR_NUM
#define USBCOMM_DP_INTC_VECT_NUM       USBCOMM_dp_int__INTC_NUMBER

#if (CY_PSOC4)
    #define USBCOMM_DMA_AUTO_INTR_PRIO (0u)
    
    #define USBCOMM_INTR_HI_PRIORITY   USBCOMM_high_int__INTC_PRIOR_NUM
    #define USBCOMM_INTR_HI_VECT_NUM   USBCOMM_high_int__INTC_NUMBER

    #define USBCOMM_INTR_MED_PRIORITY  USBCOMM_med_int__INTC_PRIOR_NUM
    #define USBCOMM_INTR_MED_VECT_NUM  USBCOMM_med_int__INTC_NUMBER

    #define USBCOMM_INTR_LO_PRIORITY   USBCOMM_lo_int__INTC_PRIOR_NUM
    #define USBCOMM_INTR_LO_VECT_NUM   USBCOMM_lo_int__INTC_NUMBER

    /* Interrupt sources in USBCOMM_isrCallbacks[] table */
    #define USBCOMM_SOF_INTR_NUM       (0u)
    #define USBCOMM_BUS_RESET_INT_NUM  (1u)
    #define USBCOMM_EP0_INTR_NUM       (2u)
    #define USBCOMM_LPM_INTR_NUM       (3u)
    #define USBCOMM_ARB_EP_INTR_NUM    (4u)
    #define USBCOMM_EP1_INTR_NUM       (5u)
    #define USBCOMM_EP2_INTR_NUM       (6u)
    #define USBCOMM_EP3_INTR_NUM       (7u)
    #define USBCOMM_EP4_INTR_NUM       (8u)
    #define USBCOMM_EP5_INTR_NUM       (9u)
    #define USBCOMM_EP6_INTR_NUM       (10u)
    #define USBCOMM_EP7_INTR_NUM       (11u)
    #define USBCOMM_EP8_INTR_NUM       (12u)

#else
    #define USBCOMM_BUS_RESET_PRIOR    USBCOMM_bus_reset__INTC_PRIOR_NUM
    #define USBCOMM_BUS_RESET_MASK     USBCOMM_bus_reset__INTC_MASK
    #define USBCOMM_BUS_RESET_VECT_NUM USBCOMM_bus_reset__INTC_NUMBER

    #define USBCOMM_SOF_PRIOR          USBCOMM_sof_int__INTC_PRIOR_NUM
    #define USBCOMM_SOF_MASK           USBCOMM_sof_int__INTC_MASK
    #define USBCOMM_SOF_VECT_NUM       USBCOMM_sof_int__INTC_NUMBER

    #define USBCOMM_EP_0_PRIOR         USBCOMM_ep_0__INTC_PRIOR_NUM
    #define USBCOMM_EP_0_MASK          USBCOMM_ep_0__INTC_MASK
    #define USBCOMM_EP_0_VECT_NUM      USBCOMM_ep_0__INTC_NUMBER

    #define USBCOMM_EP_1_PRIOR         USBCOMM_ep_1__INTC_PRIOR_NUM
    #define USBCOMM_EP_1_MASK          USBCOMM_ep_1__INTC_MASK
    #define USBCOMM_EP_1_VECT_NUM      USBCOMM_ep_1__INTC_NUMBER

    #define USBCOMM_EP_2_PRIOR         USBCOMM_ep_2__INTC_PRIOR_NUM
    #define USBCOMM_EP_2_MASK          USBCOMM_ep_2__INTC_MASK
    #define USBCOMM_EP_2_VECT_NUM      USBCOMM_ep_2__INTC_NUMBER

    #define USBCOMM_EP_3_PRIOR         USBCOMM_ep_3__INTC_PRIOR_NUM
    #define USBCOMM_EP_3_MASK          USBCOMM_ep_3__INTC_MASK
    #define USBCOMM_EP_3_VECT_NUM      USBCOMM_ep_3__INTC_NUMBER

    #define USBCOMM_EP_4_PRIOR         USBCOMM_ep_4__INTC_PRIOR_NUM
    #define USBCOMM_EP_4_MASK          USBCOMM_ep_4__INTC_MASK
    #define USBCOMM_EP_4_VECT_NUM      USBCOMM_ep_4__INTC_NUMBER

    #define USBCOMM_EP_5_PRIOR         USBCOMM_ep_5__INTC_PRIOR_NUM
    #define USBCOMM_EP_5_MASK          USBCOMM_ep_5__INTC_MASK
    #define USBCOMM_EP_5_VECT_NUM      USBCOMM_ep_5__INTC_NUMBER

    #define USBCOMM_EP_6_PRIOR         USBCOMM_ep_6__INTC_PRIOR_NUM
    #define USBCOMM_EP_6_MASK          USBCOMM_ep_6__INTC_MASK
    #define USBCOMM_EP_6_VECT_NUM      USBCOMM_ep_6__INTC_NUMBER

    #define USBCOMM_EP_7_PRIOR         USBCOMM_ep_7__INTC_PRIOR_NUM
    #define USBCOMM_EP_7_MASK          USBCOMM_ep_7__INTC_MASK
    #define USBCOMM_EP_7_VECT_NUM      USBCOMM_ep_7__INTC_NUMBER

    #define USBCOMM_EP_8_PRIOR         USBCOMM_ep_8__INTC_PRIOR_NUM
    #define USBCOMM_EP_8_MASK          USBCOMM_ep_8__INTC_MASK
    #define USBCOMM_EP_8_VECT_NUM      USBCOMM_ep_8__INTC_NUMBER

    /* Set ARB ISR priority 0 to be highest for all EPX ISRs. */
    #define USBCOMM_ARB_PRIOR          (0u)
    #define USBCOMM_ARB_MASK           USBCOMM_arb_int__INTC_MASK
    #define USBCOMM_ARB_VECT_NUM       USBCOMM_arb_int__INTC_NUMBER
#endif /* (CY_PSOC4) */


/***************************************
*       Endpoint 0 offsets (Table 9-2)
***************************************/
#define USBCOMM_bmRequestTypeReg      USBCOMM_EP0_DR_BASE.epData[0u]
#define USBCOMM_bRequestReg           USBCOMM_EP0_DR_BASE.epData[1u]
#define USBCOMM_wValueLoReg           USBCOMM_EP0_DR_BASE.epData[2u]
#define USBCOMM_wValueHiReg           USBCOMM_EP0_DR_BASE.epData[3u]
#define USBCOMM_wIndexLoReg           USBCOMM_EP0_DR_BASE.epData[4u]
#define USBCOMM_wIndexHiReg           USBCOMM_EP0_DR_BASE.epData[5u]
#define USBCOMM_wLengthLoReg          USBCOMM_EP0_DR_BASE.epData[6u]
#define USBCOMM_wLengthHiReg          USBCOMM_EP0_DR_BASE.epData[7u]

/* Compatibility defines */
#define USBCOMM_lengthLoReg           USBCOMM_EP0_DR_BASE.epData[6u]
#define USBCOMM_lengthHiReg           USBCOMM_EP0_DR_BASE.epData[7u]


/***************************************
*       Register Constants
***************************************/

#define USBCOMM_3500MV     (3500u)
#if (CY_PSOC4)
    #define USBCOMM_VDDD_MV    (CYDEV_VBUS_MV)
#else
    #define USBCOMM_VDDD_MV    (CYDEV_VDDD_MV)
#endif /* (CY_PSOC4) */


/* USBCOMM_USB_CLK */
#define USBCOMM_USB_CLK_CSR_CLK_EN_POS (0u)
#define USBCOMM_USB_CLK_CSR_CLK_EN     ((uint8) ((uint8) 0x1u << USBCOMM_USB_CLK_CSR_CLK_EN_POS))
#define USBCOMM_USB_CLK_ENABLE         (USBCOMM_USB_CLK_CSR_CLK_EN)

/* USBCOMM_CR0 */
#define USBCOMM_CR0_DEVICE_ADDRESS_POS     (0u)
#define USBCOMM_CR0_ENABLE_POS             (7u)
#define USBCOMM_CR0_DEVICE_ADDRESS_MASK    ((uint8) ((uint8) 0x7Fu << USBCOMM_CR0_DEVICE_ADDRESS_POS))
#define USBCOMM_CR0_ENABLE                 ((uint8) ((uint8) 0x01u << USBCOMM_CR0_ENABLE_POS))


/* USBCOMM_CR1 */
#define USBCOMM_CR1_REG_ENABLE_POS         (0u)
#define USBCOMM_CR1_ENABLE_LOCK_POS        (1u)
#define USBCOMM_CR1_BUS_ACTIVITY_POS       (2u)
#define USBCOMM_CR1_TRIM_OFFSET_MSB_POS    (3u)
#define USBCOMM_CR1_REG_ENABLE             ((uint8) ((uint8) 0x1u << USBCOMM_CR1_REG_ENABLE_POS))
#define USBCOMM_CR1_ENABLE_LOCK            ((uint8) ((uint8) 0x1u << USBCOMM_CR1_ENABLE_LOCK_POS))
#define USBCOMM_CR1_BUS_ACTIVITY           ((uint8) ((uint8) 0x1u << USBCOMM_CR1_BUS_ACTIVITY_POS))
#define USBCOMM_CR1_TRIM_OFFSET_MSB        ((uint8) ((uint8) 0x1u << USBCOMM_CR1_TRIM_OFFSET_MSB_POS))

/* USBCOMM_EPX_CNT */
#define USBCOMM_EP0_CNT_DATA_TOGGLE        (0x80u)
#define USBCOMM_EPX_CNT_DATA_TOGGLE        (0x80u)
#define USBCOMM_EPX_CNT0_MASK              (0x0Fu)
#define USBCOMM_EPX_CNTX_MSB_MASK          (0x07u)
#define USBCOMM_EPX_CNTX_ADDR_SHIFT        (0x04u)
#define USBCOMM_EPX_CNTX_ADDR_OFFSET       (0x10u)
#define USBCOMM_EPX_CNTX_CRC_COUNT         (0x02u)
#define USBCOMM_EPX_DATA_BUF_MAX           (512u)

/* USBCOMM_USBIO_CR0 */

#define USBCOMM_USBIO_CR0_TEN              (0x80u)
#define USBCOMM_USBIO_CR0_TSE0             (0x40u)
#define USBCOMM_USBIO_CR0_TD               (0x20u)
#define USBCOMM_USBIO_CR0_RD               (0x01u)

/* USBCOMM_USBIO_CR1 */
#define USBCOMM_USBIO_CR1_DM0_POS      (0u)
#define USBCOMM_USBIO_CR1_DP0_POS      (1u)
#define USBCOMM_USBIO_CR1_USBPUEN_POS  (2u)
#define USBCOMM_USBIO_CR1_IOMODE_POS   (5u)
#define USBCOMM_USBIO_CR1_DM0          ((uint8) ((uint8) 0x1u << USBCOMM_USBIO_CR1_DM0_POS))
#define USBCOMM_USBIO_CR1_DP0          ((uint8) ((uint8) 0x1u << USBCOMM_USBIO_CR1_DP0_POS))
#define USBCOMM_USBIO_CR1_USBPUEN      ((uint8) ((uint8) 0x1u << USBCOMM_USBIO_CR1_USBPUEN_POS))
#define USBCOMM_USBIO_CR1_IOMODE       ((uint8) ((uint8) 0x1u << USBCOMM_USBIO_CR1_IOMODE_POS))

/* USBCOMM_FASTCLK_IMO_CR */
#define USBCOMM_FASTCLK_IMO_CR_USBCLK_ON   (0x40u)
#define USBCOMM_FASTCLK_IMO_CR_XCLKEN      (0x20u)
#define USBCOMM_FASTCLK_IMO_CR_FX2ON       (0x10u)

/* USBCOMM_ARB_EPX_CFG */
#define USBCOMM_ARB_EPX_CFG_IN_DATA_RDY_POS    (0u)
#define USBCOMM_ARB_EPX_CFG_DMA_REQ_POS        (1u)
#define USBCOMM_ARB_EPX_CFG_CRC_BYPASS_POS     (2u)
#define USBCOMM_ARB_EPX_CFG_RESET_POS          (3u)
#define USBCOMM_ARB_EPX_CFG_IN_DATA_RDY        ((uint8) ((uint8) 0x1u << USBCOMM_ARB_EPX_CFG_IN_DATA_RDY_POS))
#define USBCOMM_ARB_EPX_CFG_DMA_REQ            ((uint8) ((uint8) 0x1u << USBCOMM_ARB_EPX_CFG_DMA_REQ_POS))
#define USBCOMM_ARB_EPX_CFG_CRC_BYPASS         ((uint8) ((uint8) 0x1u << USBCOMM_ARB_EPX_CFG_CRC_BYPASS_POS))
#define USBCOMM_ARB_EPX_CFG_RESET              ((uint8) ((uint8) 0x1u << USBCOMM_ARB_EPX_CFG_RESET_POS))

/* USBCOMM_ARB_EPX_INT / SR */
#define USBCOMM_ARB_EPX_INT_IN_BUF_FULL_POS    (0u)
#define USBCOMM_ARB_EPX_INT_DMA_GNT_POS        (1u)
#define USBCOMM_ARB_EPX_INT_BUF_OVER_POS       (2u)
#define USBCOMM_ARB_EPX_INT_BUF_UNDER_POS      (3u)
#define USBCOMM_ARB_EPX_INT_ERR_INT_POS        (4u)
#define USBCOMM_ARB_EPX_INT_IN_BUF_FULL        ((uint8) ((uint8) 0x1u << USBCOMM_ARB_EPX_INT_IN_BUF_FULL_POS))
#define USBCOMM_ARB_EPX_INT_DMA_GNT            ((uint8) ((uint8) 0x1u << USBCOMM_ARB_EPX_INT_DMA_GNT_POS))
#define USBCOMM_ARB_EPX_INT_BUF_OVER           ((uint8) ((uint8) 0x1u << USBCOMM_ARB_EPX_INT_BUF_OVER_POS))
#define USBCOMM_ARB_EPX_INT_BUF_UNDER          ((uint8) ((uint8) 0x1u << USBCOMM_ARB_EPX_INT_BUF_UNDER_POS))
#define USBCOMM_ARB_EPX_INT_ERR_INT            ((uint8) ((uint8) 0x1u << USBCOMM_ARB_EPX_INT_ERR_INT_POS))

#if (CY_PSOC4)
#define USBCOMM_ARB_EPX_INT_DMA_TERMIN_POS     (5u)
#define USBCOMM_ARB_EPX_INT_DMA_TERMIN         ((uint8) ((uint8) 0x1u << USBCOMM_ARB_EPX_INT_DMA_TERMIN_POS))
#endif /* (CY_PSOC4) */

/* Common arbiter interrupt sources for all PSoC devices. */
#define USBCOMM_ARB_EPX_INT_COMMON    (USBCOMM_ARB_EPX_INT_IN_BUF_FULL | \
                                                USBCOMM_ARB_EPX_INT_DMA_GNT     | \
                                                USBCOMM_ARB_EPX_INT_BUF_OVER    | \
                                                USBCOMM_ARB_EPX_INT_BUF_UNDER   | \
                                                USBCOMM_ARB_EPX_INT_ERR_INT)

#if (CY_PSOC4)
    #define USBCOMM_ARB_EPX_INT_ALL    (USBCOMM_ARB_EPX_INT_COMMON | USBCOMM_ARB_EPX_INT_DMA_TERMIN)
#else
    #define USBCOMM_ARB_EPX_INT_ALL    (USBCOMM_ARB_EPX_INT_COMMON)
#endif /* (CY_PSOC4) */

/* USBCOMM_ARB_CFG */
#define USBCOMM_ARB_CFG_AUTO_MEM_POS   (4u)
#define USBCOMM_ARB_CFG_DMA_CFG_POS    (5u)
#define USBCOMM_ARB_CFG_CFG_CMP_POS    (7u)
#define USBCOMM_ARB_CFG_AUTO_MEM       ((uint8) ((uint8) 0x1u << USBCOMM_ARB_CFG_AUTO_MEM_POS))
#define USBCOMM_ARB_CFG_DMA_CFG_MASK   ((uint8) ((uint8) 0x3u << USBCOMM_ARB_CFG_DMA_CFG_POS))
#define USBCOMM_ARB_CFG_DMA_CFG_NONE   ((uint8) ((uint8) 0x0u << USBCOMM_ARB_CFG_DMA_CFG_POS))
#define USBCOMM_ARB_CFG_DMA_CFG_MANUAL ((uint8) ((uint8) 0x1u << USBCOMM_ARB_CFG_DMA_CFG_POS))
#define USBCOMM_ARB_CFG_DMA_CFG_AUTO   ((uint8) ((uint8) 0x2u << USBCOMM_ARB_CFG_DMA_CFG_POS))
#define USBCOMM_ARB_CFG_CFG_CMP        ((uint8) ((uint8) 0x1u << USBCOMM_ARB_CFG_CFG_CMP_POS))

/* USBCOMM_DYN_RECONFIG */
#define USBCOMM_DYN_RECONFIG_EP_SHIFT      (1u)
#define USBCOMM_DYN_RECONFIG_ENABLE_POS    (0u)
#define USBCOMM_DYN_RECONFIG_EPNO_POS      (1u)
#define USBCOMM_DYN_RECONFIG_RDY_STS_POS   (4u)
#define USBCOMM_DYN_RECONFIG_ENABLE        ((uint8) ((uint8) 0x1u << USBCOMM_DYN_RECONFIG_ENABLE_POS))
#define USBCOMM_DYN_RECONFIG_EPNO_MASK     ((uint8) ((uint8) 0x7u << USBCOMM_DYN_RECONFIG_EPNO_POS))
#define USBCOMM_DYN_RECONFIG_RDY_STS       ((uint8) ((uint8) 0x1u << USBCOMM_DYN_RECONFIG_RDY_STS_POS))

/* USBCOMM_ARB_INT */
#define USBCOMM_ARB_INT_EP1_INTR_POS          (0u) /* [0] Interrupt for USB EP1 */
#define USBCOMM_ARB_INT_EP2_INTR_POS          (1u) /* [1] Interrupt for USB EP2 */
#define USBCOMM_ARB_INT_EP3_INTR_POS          (2u) /* [2] Interrupt for USB EP3 */
#define USBCOMM_ARB_INT_EP4_INTR_POS          (3u) /* [3] Interrupt for USB EP4 */
#define USBCOMM_ARB_INT_EP5_INTR_POS          (4u) /* [4] Interrupt for USB EP5 */
#define USBCOMM_ARB_INT_EP6_INTR_POS          (5u) /* [5] Interrupt for USB EP6 */
#define USBCOMM_ARB_INT_EP7_INTR_POS          (6u) /* [6] Interrupt for USB EP7 */
#define USBCOMM_ARB_INT_EP8_INTR_POS          (7u) /* [7] Interrupt for USB EP8 */
#define USBCOMM_ARB_INT_EP1_INTR              ((uint8) ((uint8) 0x1u << USBCOMM_ARB_INT_EP1_INTR_POS))
#define USBCOMM_ARB_INT_EP2_INTR              ((uint8) ((uint8) 0x1u << USBCOMM_ARB_INT_EP2_INTR_POS))
#define USBCOMM_ARB_INT_EP3_INTR              ((uint8) ((uint8) 0x1u << USBCOMM_ARB_INT_EP3_INTR_POS))
#define USBCOMM_ARB_INT_EP4_INTR              ((uint8) ((uint8) 0x1u << USBCOMM_ARB_INT_EP4_INTR_POS))
#define USBCOMM_ARB_INT_EP5_INTR              ((uint8) ((uint8) 0x1u << USBCOMM_ARB_INT_EP5_INTR_POS))
#define USBCOMM_ARB_INT_EP6_INTR              ((uint8) ((uint8) 0x1u << USBCOMM_ARB_INT_EP6_INTR_POS))
#define USBCOMM_ARB_INT_EP7_INTR              ((uint8) ((uint8) 0x1u << USBCOMM_ARB_INT_EP7_INTR_POS))
#define USBCOMM_ARB_INT_EP8_INTR              ((uint8) ((uint8) 0x1u << USBCOMM_ARB_INT_EP8_INTR_POS))

/* USBCOMM_SIE_INT */
#define USBCOMM_SIE_INT_EP1_INTR_POS          (0u) /* [0] Interrupt for USB EP1 */
#define USBCOMM_SIE_INT_EP2_INTR_POS          (1u) /* [1] Interrupt for USB EP2 */
#define USBCOMM_SIE_INT_EP3_INTR_POS          (2u) /* [2] Interrupt for USB EP3 */
#define USBCOMM_SIE_INT_EP4_INTR_POS          (3u) /* [3] Interrupt for USB EP4 */
#define USBCOMM_SIE_INT_EP5_INTR_POS          (4u) /* [4] Interrupt for USB EP5 */
#define USBCOMM_SIE_INT_EP6_INTR_POS          (5u) /* [5] Interrupt for USB EP6 */
#define USBCOMM_SIE_INT_EP7_INTR_POS          (6u) /* [6] Interrupt for USB EP7 */
#define USBCOMM_SIE_INT_EP8_INTR_POS          (7u) /* [7] Interrupt for USB EP8 */
#define USBCOMM_SIE_INT_EP1_INTR              ((uint8) ((uint8) 0x01u << USBCOMM_SIE_INT_EP1_INTR_POS))
#define USBCOMM_SIE_INT_EP2_INTR              ((uint8) ((uint8) 0x01u << USBCOMM_SIE_INT_EP2_INTR_POS))
#define USBCOMM_SIE_INT_EP3_INTR              ((uint8) ((uint8) 0x01u << USBCOMM_SIE_INT_EP3_INTR_POS))
#define USBCOMM_SIE_INT_EP4_INTR              ((uint8) ((uint8) 0x01u << USBCOMM_SIE_INT_EP4_INTR_POS))
#define USBCOMM_SIE_INT_EP5_INTR              ((uint8) ((uint8) 0x01u << USBCOMM_SIE_INT_EP5_INTR_POS))
#define USBCOMM_SIE_INT_EP6_INTR              ((uint8) ((uint8) 0x01u << USBCOMM_SIE_INT_EP6_INTR_POS))
#define USBCOMM_SIE_INT_EP7_INTR              ((uint8) ((uint8) 0x01u << USBCOMM_SIE_INT_EP7_INTR_POS))
#define USBCOMM_SIE_INT_EP8_INTR              ((uint8) ((uint8) 0x01u << USBCOMM_SIE_INT_EP8_INTR_POS))

#if (CY_PSOC4)
    /* USBCOMM_POWER_CTRL_REG */
    #define USBCOMM_POWER_CTRL_VBUS_VALID_OVR_POS       (0u)  /* [0] */
    #define USBCOMM_POWER_CTRL_SUSPEND_POS              (2u)  /* [1] */
    #define USBCOMM_POWER_CTRL_SUSPEND_DEL_POS          (3u)  /* [3] */
    #define USBCOMM_POWER_CTRL_ISOLATE_POS              (4u)  /* [4] */
    #define USBCOMM_POWER_CTRL_CHDET_PWR_CTL_POS        (5u)  /* [5] */
    #define USBCOMM_POWER_CTRL_ENABLE_DM_PULLDOWN_POS   (25u) /* [25] */
    #define USBCOMM_POWER_CTRL_ENABLE_VBUS_PULLDOWN_POS (26u) /* [26] */
    #define USBCOMM_POWER_CTRL_ENABLE_RCVR_POS          (27u) /* [27] */
    #define USBCOMM_POWER_CTRL_ENABLE_DPO_POS           (28u) /* [28] */
    #define USBCOMM_POWER_CTRL_ENABLE_DMO_POS           (29u) /* [29] */
    #define USBCOMM_POWER_CTRL_ENABLE_CHGDET_POS        (30u) /* [30] */
    #define USBCOMM_POWER_CTRL_ENABLE_POS               (31u) /* [31] */
    #define USBCOMM_POWER_CTRL_VBUS_VALID_OVR_MASK      ((uint32) 0x03u << USBCOMM_POWER_CTRL_VBUS_VALID_OVR_POS)
    #define USBCOMM_POWER_CTRL_VBUS_VALID_OVR_0         ((uint32) 0x00u << USBCOMM_POWER_CTRL_VBUS_VALID_OVR_POS)
    #define USBCOMM_POWER_CTRL_VBUS_VALID_OVR_1         ((uint32) 0x01u << USBCOMM_POWER_CTRL_VBUS_VALID_OVR_POS)
    #define USBCOMM_POWER_CTRL_VBUS_VALID_OVR_GPIO      ((uint32) 0x02u << USBCOMM_POWER_CTRL_VBUS_VALID_OVR_POS)
    #define USBCOMM_POWER_CTRL_VBUS_VALID_OVR_PHY       ((uint32) 0x03u << USBCOMM_POWER_CTRL_VBUS_VALID_OVR_POS)
    #define USBCOMM_POWER_CTRL_SUSPEND                  ((uint32) 0x01u << USBCOMM_POWER_CTRL_SUSPEND_POS)
    #define USBCOMM_POWER_CTRL_SUSPEND_DEL              ((uint32) 0x01u << USBCOMM_POWER_CTRL_SUSPEND_DEL_POS)
    #define USBCOMM_POWER_CTRL_ISOLATE                  ((uint32) 0x01u << USBCOMM_POWER_CTRL_ISOLATE_POS)
    #define USBCOMM_POWER_CTRL_CHDET_PWR_CTL_MASK       ((uint32) 0x03u << USBCOMM_POWER_CTRL_CHDET_PWR_CTL_POS)
    #define USBCOMM_POWER_CTRL_ENABLE_DM_PULLDOWN       ((uint32) 0x01u << USBCOMM_POWER_CTRL_ENABLE_DM_PULLDOWN_POS)
    #define USBCOMM_POWER_CTRL_ENABLE_VBUS_PULLDOWN     ((uint32) 0x01u << USBCOMM_POWER_CTRL_ENABLE_VBUS_PULLDOWN_POS)
    #define USBCOMM_POWER_CTRL_ENABLE_RCVR              ((uint32) 0x01u << USBCOMM_POWER_CTRL_ENABLE_RCVR_POS)
    #define USBCOMM_POWER_CTRL_ENABLE_DPO               ((uint32) 0x01u << USBCOMM_POWER_CTRL_ENABLE_DPO_POS)
    #define USBCOMM_POWER_CTRL_ENABLE_DMO               ((uint32) 0x01u << USBCOMM_POWER_CTRL_ENABLE_DMO_POS)
    #define USBCOMM_POWER_CTRL_ENABLE_CHGDET            ((uint32) 0x01u << USBCOMM_POWER_CTRL_ENABLE_CHGDET_POS)
    #define USBCOMM_POWER_CTRL_ENABLE                   ((uint32) 0x01u << USBCOMM_POWER_CTRL_ENABLE_POS)

    /* USBCOMM_CHGDET_CTRL_REG */
    #define USBCOMM_CHGDET_CTRL_COMP_DP_POS        (0u)  /* [0] */
    #define USBCOMM_CHGDET_CTRL_COMP_DM_POS        (1u)  /* [1] */
    #define USBCOMM_CHGDET_CTRL_COMP_EN_POS        (2u)  /* [2] */
    #define USBCOMM_CHGDET_CTRL_REF_DP_POS         (3u)  /* [3] */
    #define USBCOMM_CHGDET_CTRL_REF_DM_POS         (4u)  /* [4] */
    #define USBCOMM_CHGDET_CTRL_REF_EN_POS         (5u)  /* [5] */
    #define USBCOMM_CHGDET_CTRL_DCD_SRC_EN_POS     (6u)  /* [6] */
    #define USBCOMM_CHGDET_CTRL_ADFT_CTRL_POS      (12u) /* [12] */
    #define USBCOMM_CHGDET_CTRL_COMP_OUT_POS       (31u) /* [31] */
    #define USBCOMM_CHGDET_CTRL_COMP_DP            ((uint32) 0x01u << USBCOMM_CHGDET_CTRL_COMP_DP_POS)
    #define USBCOMM_CHGDET_CTRL_COMP_DM            ((uint32) 0x01u << USBCOMM_CHGDET_CTRL_COMP_DM_POS)
    #define USBCOMM_CHGDET_CTRL_COMP_EN            ((uint32) 0x01u << USBCOMM_CHGDET_CTRL_COMP_EN_POS)
    #define USBCOMM_CHGDET_CTRL_REF_DP             ((uint32) 0x01u << USBCOMM_CHGDET_CTRL_REF_DP_POS)
    #define USBCOMM_CHGDET_CTRL_REF_DM             ((uint32) 0x01u << USBCOMM_CHGDET_CTRL_REF_DM_POS)
    #define USBCOMM_CHGDET_CTRL_REF_EN             ((uint32) 0x01u << USBCOMM_CHGDET_CTRL_REF_EN_POS)
    #define USBCOMM_CHGDET_CTRL_DCD_SRC_EN         ((uint32) 0x01u << USBCOMM_CHGDET_CTRL_DCD_SRC_EN_POS)
    #define USBCOMM_CHGDET_CTRL_ADFT_CTRL_MASK     ((uint32) 0x03u << USBCOMM_CHGDET_CTRL_ADFT_CTRL_POS)
    #define USBCOMM_CHGDET_CTRL_ADFT_CTRL_NORMAL   ((uint32) 0x00u << USBCOMM_CHGDET_CTRL_ADFT_CTRL_POS)
    #define USBCOMM_CHGDET_CTRL_ADFT_CTRL_VBG      ((uint32) 0x01u << USBCOMM_CHGDET_CTRL_ADFT_CTRL_POS)
    #define USBCOMM_CHGDET_CTRL_ADFT_CTRL_DONTUSE  ((uint32) 0x02u << USBCOMM_CHGDET_CTRL_ADFT_CTRL_POS)
    #define USBCOMM_CHGDET_CTRL_ADFT_CTRL_ADFTIN   ((uint32) 0x03u << USBCOMM_CHGDET_CTRL_ADFT_CTRL_POS)
    #define USBCOMM_CHGDET_CTRL_COMP_OUT           ((uint32) 0x01u << USBCOMM_CHGDET_CTRL_COMP_OUT_POS)

    /* USBCOMM_LPM_CTRL */
    #define USBCOMM_LPM_CTRL_LPM_EN_POS        (0u)
    #define USBCOMM_LPM_CTRL_LPM_ACK_RESP_POS  (1u)
    #define USBCOMM_LPM_CTRL_NYET_EN_POS       (2u)
    #define USBCOMM_LPM_CTRL_SUB_RESP_POS      (4u)
    #define USBCOMM_LPM_CTRL_LPM_EN            ((uint32) 0x01u << USBCOMM_LPM_CTRL_LPM_EN_POS)
    #define USBCOMM_LPM_CTRL_LPM_ACK_RESP      ((uint32) 0x01u << USBCOMM_LPM_CTRL_LPM_ACK_RESP_POS)
    #define USBCOMM_LPM_CTRL_NYET_EN           ((uint32) 0x01u << USBCOMM_LPM_CTRL_NYET_EN_POS)
    #define USBCOMM_LPM_CTRL_ACK_NYET_MASK     ((uint32) 0x03u << USBCOMM_LPM_CTRL_LPM_ACK_RESP_POS)
    #define USBCOMM_LPM_CTRL_SUB_RESP          ((uint32) 0x01u << USBCOMM_LPM_CTRL_SUB_RESP_POS)

    #define USBCOMM_LPM_STAT_LPM_BESL_POS          (0u)
    #define USBCOMM_LPM_STAT_LPM_REMOTE_WAKE_POS   (4u)
    #define USBCOMM_LPM_STAT_LPM_BESL_MASK         ((uint32) 0x0Fu << USBCOMM_LPM_STAT_LPM_BESL_POS)
    #define USBCOMM_LPM_STAT_LPM_REMOTE_WAKE       ((uint32) 0x01u << USBCOMM_LPM_STAT_LPM_REMOTE_WAKE_POS)

    /* USBCOMM_INTR_SIE */
    #define USBCOMM_INTR_SIE_SOF_INTR_POS          (0u) /* [0] Interrupt for USB SOF   */
    #define USBCOMM_INTR_SIE_BUS_RESET_INTR_POS    (1u) /* [1] Interrupt for BUS RESET */
    #define USBCOMM_INTR_SIE_EP0_INTR_POS          (2u) /* [2] Interrupt for EP0       */
    #define USBCOMM_INTR_SIE_LPM_INTR_POS          (3u) /* [3] Interrupt for LPM       */
    #define USBCOMM_INTR_SIE_RESUME_INTR_POS       (4u) /* [4] Interrupt for RESUME (not used by component) */
    #define USBCOMM_INTR_SIE_SOF_INTR              ((uint32) 0x01u << USBCOMM_INTR_SIE_SOF_INTR_POS)
    #define USBCOMM_INTR_SIE_BUS_RESET_INTR        ((uint32) 0x01u << USBCOMM_INTR_SIE_BUS_RESET_INTR_POS)
    #define USBCOMM_INTR_SIE_EP0_INTR              ((uint32) 0x01u << USBCOMM_INTR_SIE_EP0_INTR_POS)
    #define USBCOMM_INTR_SIE_LPM_INTR              ((uint32) 0x01u << USBCOMM_INTR_SIE_LPM_INTR_POS)
    #define USBCOMM_INTR_SIE_RESUME_INTR           ((uint32) 0x01u << USBCOMM_INTR_SIE_RESUME_INTR_POS)

    /* USBCOMM_INTR_CAUSE_LO, MED and HI */
    #define USBCOMM_INTR_CAUSE_SOF_INTR_POS       (0u)  /* [0] Interrupt status for USB SOF    */
    #define USBCOMM_INTR_CAUSE_BUS_RESET_INTR_POS (1u)  /* [1] Interrupt status for USB BUS RSET */
    #define USBCOMM_INTR_CAUSE_EP0_INTR_POS       (2u)  /* [2] Interrupt status for USB EP0    */
    #define USBCOMM_INTR_CAUSE_LPM_INTR_POS       (3u)  /* [3] Interrupt status for USB LPM    */
    #define USBCOMM_INTR_CAUSE_RESUME_INTR_POS    (4u)  /* [4] Interrupt status for USB RESUME */
    #define USBCOMM_INTR_CAUSE_ARB_INTR_POS       (7u)  /* [7] Interrupt status for USB ARB    */
    #define USBCOMM_INTR_CAUSE_EP1_INTR_POS       (8u)  /* [8] Interrupt status for USB EP1    */
    #define USBCOMM_INTR_CAUSE_EP2_INTR_POS       (9u)  /* [9] Interrupt status for USB EP2    */
    #define USBCOMM_INTR_CAUSE_EP3_INTR_POS       (10u) /* [10] Interrupt status for USB EP3   */
    #define USBCOMM_INTR_CAUSE_EP4_INTR_POS       (11u) /* [11] Interrupt status for USB EP4   */
    #define USBCOMM_INTR_CAUSE_EP5_INTR_POS       (12u) /* [12] Interrupt status for USB EP5   */
    #define USBCOMM_INTR_CAUSE_EP6_INTR_POS       (13u) /* [13] Interrupt status for USB EP6   */
    #define USBCOMM_INTR_CAUSE_EP7_INTR_POS       (14u) /* [14] Interrupt status for USB EP7   */
    #define USBCOMM_INTR_CAUSE_EP8_INTR_POS       (15u) /* [15] Interrupt status for USB EP8   */
    #define USBCOMM_INTR_CAUSE_SOF_INTR           ((uint32) 0x01u << USBCOMM_INTR_CAUSE_SOF_INTR_POS)
    #define USBCOMM_INTR_CAUSE_BUS_RESET_INTR     ((uint32) 0x01u << USBCOMM_INTR_CAUSE_BUS_RESET_INTR_POS)
    #define USBCOMM_INTR_CAUSE_EP0_INTR           ((uint32) 0x01u << USBCOMM_INTR_CAUSE_EP0_INTR_POS)
    #define USBCOMM_INTR_CAUSE_LPM_INTR           ((uint32) 0x01u << USBCOMM_INTR_CAUSE_LPM_INTR_POS)
    #define USBCOMM_INTR_CAUSE_RESUME_INTR        ((uint32) 0x01u << USBCOMM_INTR_CAUSE_RESUME_INTR_POS)
    #define USBCOMM_INTR_CAUSE_ARB_INTR           ((uint32) 0x01u << USBCOMM_INTR_CAUSE_ARB_INTR_POS)
    #define USBCOMM_INTR_CAUSE_EP1_INTR           ((uint32) 0x01u << USBCOMM_INTR_CAUSE_EP1_INTR_POS)
    #define USBCOMM_INTR_CAUSE_EP2_INTR           ((uint32) 0x01u << USBCOMM_INTR_CAUSE_EP2_INTR_POS)
    #define USBCOMM_INTR_CAUSE_EP3_INTR           ((uint32) 0x01u << USBCOMM_INTR_CAUSE_EP3_INTR_POS)
    #define USBCOMM_INTR_CAUSE_EP4_INTR           ((uint32) 0x01u << USBCOMM_INTR_CAUSE_EP4_INTR_POS)
    #define USBCOMM_INTR_CAUSE_EP5_INTR           ((uint32) 0x01u << USBCOMM_INTR_CAUSE_EP5_INTR_POS)
    #define USBCOMM_INTR_CAUSE_EP6_INTR           ((uint32) 0x01u << USBCOMM_INTR_CAUSE_EP6_INTR_POS)
    #define USBCOMM_INTR_CAUSE_EP7_INTR           ((uint32) 0x01u << USBCOMM_INTR_CAUSE_EP7_INTR_POS)
    #define USBCOMM_INTR_CAUSE_EP8_INTR           ((uint32) 0x01u << USBCOMM_INTR_CAUSE_EP8_INTR_POS)

    #define USBCOMM_INTR_CAUSE_CTRL_INTR_MASK     (USBCOMM_INTR_CAUSE_SOF_INTR       | \
                                                            USBCOMM_INTR_CAUSE_BUS_RESET_INTR | \
                                                            USBCOMM_INTR_CAUSE_EP0_INTR       | \
                                                            USBCOMM_INTR_CAUSE_LPM_INTR)

    #define USBCOMM_INTR_CAUSE_EP1_8_INTR_MASK    (USBCOMM_INTR_CAUSE_EP1_INTR       | \
                                                            USBCOMM_INTR_CAUSE_EP2_INTR       | \
                                                            USBCOMM_INTR_CAUSE_EP3_INTR       | \
                                                            USBCOMM_INTR_CAUSE_EP4_INTR       | \
                                                            USBCOMM_INTR_CAUSE_EP5_INTR       | \
                                                            USBCOMM_INTR_CAUSE_EP6_INTR       | \
                                                            USBCOMM_INTR_CAUSE_EP7_INTR       | \
                                                            USBCOMM_INTR_CAUSE_EP8_INTR)

    #define USBCOMM_INTR_CAUSE_EP_INTR_SHIFT      (USBCOMM_INTR_CAUSE_ARB_INTR_POS - \
                                                           (USBCOMM_INTR_CAUSE_LPM_INTR_POS + 1u))
    #define USBCOMM_INTR_CAUSE_SRC_COUNT          (13u)

    #define USBCOMM_CHGDET_CTRL_PRIMARY    (USBCOMM_CHGDET_CTRL_COMP_EN | \
                                                     USBCOMM_CHGDET_CTRL_COMP_DM | \
                                                     USBCOMM_CHGDET_CTRL_REF_EN  | \
                                                     USBCOMM_CHGDET_CTRL_REF_DP)

    #define USBCOMM_CHGDET_CTRL_SECONDARY  (USBCOMM_CHGDET_CTRL_COMP_EN | \
                                                     USBCOMM_CHGDET_CTRL_COMP_DP | \
                                                     USBCOMM_CHGDET_CTRL_REF_EN  | \
                                                     USBCOMM_CHGDET_CTRL_REF_DM)

    #define USBCOMM_CHGDET_CTRL_DEFAULT    (0x00000900u)


#else /* (CY_PSOC3 || CY_PSOC5LP) */
    #define USBCOMM_PM_ACT_EN_FSUSB            USBCOMM_USB__PM_ACT_MSK
    #define USBCOMM_PM_STBY_EN_FSUSB           USBCOMM_USB__PM_STBY_MSK
    #define USBCOMM_PM_AVAIL_EN_FSUSBIO        (0x10u)

    #define USBCOMM_PM_USB_CR0_REF_EN          (0x01u)
    #define USBCOMM_PM_USB_CR0_PD_N            (0x02u)
    #define USBCOMM_PM_USB_CR0_PD_PULLUP_N     (0x04u)
#endif /* (CY_PSOC4) */


/***************************************
*       Macros Definitions
***************************************/

#if (CY_PSOC4)
    #define USBCOMM_ClearSieInterruptSource(intMask) \
                do{ \
                    USBCOMM_INTR_SIE_REG = (uint32) (intMask); \
                }while(0)
#else
    #define USBCOMM_ClearSieInterruptSource(intMask) \
                do{ /* Does nothing. */ }while(0)
#endif /* (CY_PSOC4) */

#define USBCOMM_ClearSieEpInterruptSource(intMask) \
            do{ \
                USBCOMM_SIE_EP_INT_SR_REG = (uint8) (intMask); \
            }while(0)

#define USBCOMM_GET_ACTIVE_IN_EP_CR0_MODE(epType)  (((epType) == USBCOMM_EP_TYPE_ISOC) ? \
                                                                (USBCOMM_MODE_ISO_IN) : (USBCOMM_MODE_ACK_IN))

#define USBCOMM_GET_ACTIVE_OUT_EP_CR0_MODE(epType) (((epType) == USBCOMM_EP_TYPE_ISOC) ? \
                                                                (USBCOMM_MODE_ISO_OUT) : (USBCOMM_MODE_ACK_OUT))

#define USBCOMM_GET_EP_TYPE(epNumber)  (USBCOMM_EP[epNumber].attrib & USBCOMM_EP_TYPE_MASK)

#define USBCOMM_GET_UINT16(hi, low)    (((uint16) ((uint16) (hi) << 8u)) | ((uint16) (low) & 0xFFu))


/***************************************
*    Initialization Register Settings
***************************************/

/* Clear device address and enable USB IP respond to USB traffic. */
#define USBCOMM_DEFUALT_CR0    (USBCOMM_CR0_ENABLE)

/* Arbiter configuration depends on memory management mode. */
#define USBCOMM_DEFAULT_ARB_CFG    ((USBCOMM_EP_MANAGEMENT_MANUAL) ? (USBCOMM_ARB_CFG_DMA_CFG_NONE) : \
                                                ((USBCOMM_EP_MANAGEMENT_DMA_MANUAL) ? \
                                                    (USBCOMM_ARB_CFG_DMA_CFG_MANUAL) : \
                                                        (USBCOMM_ARB_CFG_AUTO_MEM | USBCOMM_ARB_CFG_DMA_CFG_AUTO)))

/* Enable arbiter interrupt for active endpoints only */
#define USBCOMM_DEFAULT_ARB_INT_EN \
        ((uint8) ((uint8) USBCOMM_DMA1_ACTIVE << USBCOMM_ARB_INT_EP1_INTR_POS) | \
         (uint8) ((uint8) USBCOMM_DMA2_ACTIVE << USBCOMM_ARB_INT_EP2_INTR_POS) | \
         (uint8) ((uint8) USBCOMM_DMA3_ACTIVE << USBCOMM_ARB_INT_EP3_INTR_POS) | \
         (uint8) ((uint8) USBCOMM_DMA4_ACTIVE << USBCOMM_ARB_INT_EP4_INTR_POS) | \
         (uint8) ((uint8) USBCOMM_DMA5_ACTIVE << USBCOMM_ARB_INT_EP5_INTR_POS) | \
         (uint8) ((uint8) USBCOMM_DMA6_ACTIVE << USBCOMM_ARB_INT_EP6_INTR_POS) | \
         (uint8) ((uint8) USBCOMM_DMA7_ACTIVE << USBCOMM_ARB_INT_EP7_INTR_POS) | \
         (uint8) ((uint8) USBCOMM_DMA8_ACTIVE << USBCOMM_ARB_INT_EP8_INTR_POS))

/* Enable all SIE endpoints interrupts */
#define USBCOMM_DEFAULT_SIE_EP_INT_EN  (USBCOMM_SIE_INT_EP1_INTR | \
                                                 USBCOMM_SIE_INT_EP2_INTR | \
                                                 USBCOMM_SIE_INT_EP3_INTR | \
                                                 USBCOMM_SIE_INT_EP4_INTR | \
                                                 USBCOMM_SIE_INT_EP5_INTR | \
                                                 USBCOMM_SIE_INT_EP6_INTR | \
                                                 USBCOMM_SIE_INT_EP7_INTR | \
                                                 USBCOMM_SIE_INT_EP8_INTR)

#define USBCOMM_ARB_EPX_CFG_DEFAULT    (USBCOMM_ARB_EPX_CFG_RESET | \
                                                 USBCOMM_ARB_EPX_CFG_CRC_BYPASS)

/* Default EP arbiter interrupt source register */
#define USBCOMM_ARB_EPX_INT_COMMON_MASK   (USBCOMM_ARB_EPX_INT_IN_BUF_FULL | \
                                                    USBCOMM_ARB_EPX_INT_BUF_OVER    | \
                                                    USBCOMM_ARB_EPX_INT_BUF_UNDER   | \
                                                    USBCOMM_ARB_EPX_INT_ERR_INT     | \
                                                    (USBCOMM_EP_MANAGEMENT_DMA_MANUAL ? USBCOMM_ARB_EPX_INT_DMA_GNT : 0u))

#define USBCOMM_CLEAR_REG      (0u)

#if (CY_PSOC4)
    /* Set USB lock option when IMO is locked to USB traffic. */
    #define USBCOMM_DEFUALT_CR1    ((0u != CySysClkImoGetUsbLock()) ? (USBCOMM_CR1_ENABLE_LOCK) : (0u))

    /* Recommended value is increased from 3 to 10 due to suppress glitch on  
     * RSE0 with USB2.0 hubs (LF CLK = 32kHz equal to 350us). */
    #define USBCOMM_DEFUALT_BUS_RST_CNT  (10u)

    /* Select VBUS sources as: valid, PHY of GPIO, and clears isolate bit. */
    /* Application level must ensure that VBUS is valid valid to use. */
    #define USBCOMM_DEFAULT_POWER_CTRL_VBUS    (USBCOMM_POWER_CTRL_ENABLE_VBUS_PULLDOWN | \
                                                         ((!USBCOMM_VBUS_MONITORING_ENABLE) ? \
                                                            (USBCOMM_POWER_CTRL_VBUS_VALID_OVR_1) : \
                                                                (USBCOMM_VBUS_POWER_PAD_ENABLE ? \
                                                                    (USBCOMM_POWER_CTRL_VBUS_VALID_OVR_PHY) : \
                                                                    (USBCOMM_POWER_CTRL_VBUS_VALID_OVR_GPIO))))
    /* Enable USB IP. */
    #define USBCOMM_DEFAULT_POWER_CTRL_PHY (USBCOMM_POWER_CTRL_SUSPEND     | \
                                                     USBCOMM_POWER_CTRL_SUSPEND_DEL | \
                                                     USBCOMM_POWER_CTRL_ENABLE_RCVR | \
                                                     USBCOMM_POWER_CTRL_ENABLE_DPO  | \
                                                     USBCOMM_POWER_CTRL_ENABLE_DMO  | \
                                                     USBCOMM_POWER_CTRL_ENABLE)

    /* Assign interrupt between levels lo, med, hi. */
    #define USBCOMM_DEFAULT_INTR_LVL_SEL   ((uint32) (USBCOMM_INTR_LVL_SEL))

    /* Enable interrupt source in the INTR_SIE. The SOF is always disabled and EP0 is enabled. */
    #define USBCOMM_DEFAULT_INTR_SIE_MASK \
                ((uint32) ((uint32) USBCOMM_BUS_RESET_ISR_ACTIVE << USBCOMM_INTR_SIE_BUS_RESET_INTR_POS) | \
                 (uint32) ((uint32) USBCOMM_SOF_ISR_ACTIVE       << USBCOMM_INTR_SIE_SOF_INTR_POS)       | \
                 (uint32) ((uint32) USBCOMM_LPM_ACTIVE           << USBCOMM_INTR_SIE_LPM_INTR_POS)       | \
                 (uint32) ((uint32) USBCOMM_INTR_SIE_EP0_INTR))

    /* Arbiter interrupt sources */
    #define USBCOMM_ARB_EPX_INT_MASK   (USBCOMM_ARB_EPX_INT_COMMON_MASK | \
                                                (USBCOMM_EP_MANAGEMENT_DMA_AUTO ? USBCOMM_ARB_EPX_INT_DMA_TERMIN : 0u))

    /* Common DMA configuration */
    #define USBCOMM_DMA_COMMON_CFG     (CYDMA_PULSE | CYDMA_ENTIRE_DESCRIPTOR | \
                                                 CYDMA_NON_PREEMPTABLE)


#else
    #define USBCOMM_ARB_EPX_INT_MASK   (USBCOMM_ARB_EPX_INT_COMMON_MASK)

    #define USBCOMM_DEFUALT_CR1        (USBCOMM_CR1_ENABLE_LOCK)

    /* Recommended value is 3 for LF CLK = 100kHz equal to 100us. */
    #define USBCOMM_DEFUALT_BUS_RST_CNT    (10u)
#endif /* (CY_PSOC4) */

/*
* \addtogroup group_deprecated
* @{
*/

/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Renamed type definitions */
#define USBCOMM_CODE CYCODE
#define USBCOMM_FAR CYFAR
#if defined(__C51__) || defined(__CX51__)
    #define USBCOMM_DATA data
    #define USBCOMM_XDATA xdata
#else
    #define USBCOMM_DATA
    #define USBCOMM_XDATA
#endif /*  __C51__ */
#define USBCOMM_NULL       NULL
/** @} deprecated */
/* Renamed structure fields */
#define wBuffOffset         buffOffset
#define wBufferSize         bufferSize
#define bStatus             status
#define wLength             length
#define wCount              count

/* Renamed global variable */
#define CurrentTD           USBCOMM_currentTD
#define USBCOMM_interfaceSetting_last       USBCOMM_interfaceSettingLast

/* Renamed global constants */
#define USBCOMM_DWR_VDDD_OPERATION         (USBCOMM_DWR_POWER_OPERATION)

/* Renamed functions */
#define USBCOMM_bCheckActivity             USBCOMM_CheckActivity
#define USBCOMM_bGetConfiguration          USBCOMM_GetConfiguration
#define USBCOMM_bGetInterfaceSetting       USBCOMM_GetInterfaceSetting
#define USBCOMM_bGetEPState                USBCOMM_GetEPState
#define USBCOMM_wGetEPCount                USBCOMM_GetEPCount
#define USBCOMM_bGetEPAckState             USBCOMM_GetEPAckState
#define USBCOMM_bRWUEnabled                USBCOMM_RWUEnabled
#define USBCOMM_bVBusPresent               USBCOMM_VBusPresent

#define USBCOMM_bConfiguration             USBCOMM_configuration
#define USBCOMM_bInterfaceSetting          USBCOMM_interfaceSetting
#define USBCOMM_bDeviceAddress             USBCOMM_deviceAddress
#define USBCOMM_bDeviceStatus              USBCOMM_deviceStatus
#define USBCOMM_bDevice                    USBCOMM_device
#define USBCOMM_bTransferState             USBCOMM_transferState
#define USBCOMM_bLastPacketSize            USBCOMM_lastPacketSize

#define USBCOMM_LoadEP                     USBCOMM_LoadInEP
#define USBCOMM_LoadInISOCEP               USBCOMM_LoadInEP
#define USBCOMM_EnableOutISOCEP            USBCOMM_EnableOutEP

#define USBCOMM_SetVector                  CyIntSetVector
#define USBCOMM_SetPriority                CyIntSetPriority
#define USBCOMM_EnableInt                  CyIntEnable

/* Replace with register access. */
#define USBCOMM_bmRequestType      USBCOMM_EP0_DR0_PTR
#define USBCOMM_bRequest           USBCOMM_EP0_DR1_PTR
#define USBCOMM_wValue             USBCOMM_EP0_DR2_PTR
#define USBCOMM_wValueHi           USBCOMM_EP0_DR3_PTR
#define USBCOMM_wValueLo           USBCOMM_EP0_DR2_PTR
#define USBCOMM_wIndex             USBCOMM_EP0_DR4_PTR
#define USBCOMM_wIndexHi           USBCOMM_EP0_DR5_PTR
#define USBCOMM_wIndexLo           USBCOMM_EP0_DR4_PTR
#define USBCOMM_length             USBCOMM_EP0_DR6_PTR
#define USBCOMM_lengthHi           USBCOMM_EP0_DR7_PTR
#define USBCOMM_lengthLo           USBCOMM_EP0_DR6_PTR

/* Rename VBUS monitoring registers. */
#if (CY_PSOC3 || CY_PSOC5LP)
    #if (USBCOMM_VBUS_MONITORING_ENABLE)
        #if (USBCOMM_VBUS_MONITORING_INTERNAL)
            #define USBCOMM_VBUS_DR_PTR    ( (reg8 *) USBCOMM_VBUS__DR)
            #define USBCOMM_VBUS_DR_REG    (*(reg8 *) USBCOMM_VBUS__DR)
            #define USBCOMM_VBUS_PS_PTR    ( (reg8 *) USBCOMM_VBUS__PS)
            #define USBCOMM_VBUS_PS_REG    (*(reg8 *) USBCOMM_VBUS__PS)
            #define USBCOMM_VBUS_MASK          USBCOMM_VBUS__MASK
        #else
            #define USBCOMM_VBUS_PS_PTR    ( (reg8 *) USBCOMM_Vbus_ps_sts_sts_reg__STATUS_REG)
            #define USBCOMM_VBUS_MASK      (0x01u)
        #endif /* (USBCOMM_VBUS_MONITORING_INTERNAL) */
    #endif /*(USBCOMM_VBUS_MONITORING_ENABLE) */
        
    /* Pointer DIE structure in flash (8 bytes): Y and X location, wafer, lot msb, lot lsb, 
    *  work week, fab/year, minor. */
    #define USBCOMM_DIE_ID             CYDEV_FLSHID_CUST_TABLES_BASE

     #if (USBCOMM_EP_MANAGEMENT_DMA_AUTO)
        #if (USBCOMM_DMA1_ACTIVE)
            #define USBCOMM_ep1_TD_TERMOUT_EN  (USBCOMM_ep1__TD_TERMOUT_EN)
        #else
            #define USBCOMM_ep1_TD_TERMOUT_EN  (0u)
        #endif /* (USBCOMM_DMA1_ACTIVE) */

        #if (USBCOMM_DMA2_ACTIVE)
            #define USBCOMM_ep2_TD_TERMOUT_EN  (USBCOMM_ep2__TD_TERMOUT_EN)
        #else
            #define USBCOMM_ep2_TD_TERMOUT_EN  (0u)
        #endif /* (USBCOMM_DMA2_ACTIVE) */

        #if (USBCOMM_DMA3_ACTIVE)
            #define USBCOMM_ep3_TD_TERMOUT_EN  (USBCOMM_ep3__TD_TERMOUT_EN)
        #else
            #define USBCOMM_ep3_TD_TERMOUT_EN  (0u)
        #endif /* (USBCOMM_DMA3_ACTIVE) */

        #if (USBCOMM_DMA4_ACTIVE)
            #define USBCOMM_ep4_TD_TERMOUT_EN  (USBCOMM_ep4__TD_TERMOUT_EN)
        #else
            #define USBCOMM_ep4_TD_TERMOUT_EN  (0u)
        #endif /* (USBCOMM_DMA4_ACTIVE) */

        #if (USBCOMM_DMA5_ACTIVE)
            #define USBCOMM_ep5_TD_TERMOUT_EN  (USBCOMM_ep5__TD_TERMOUT_EN)
        #else
            #define USBCOMM_ep5_TD_TERMOUT_EN  (0u)
        #endif /* (USBCOMM_DMA5_ACTIVE) */

        #if (USBCOMM_DMA6_ACTIVE)
            #define USBCOMM_ep6_TD_TERMOUT_EN  (USBCOMM_ep6__TD_TERMOUT_EN)
        #else
            #define USBCOMM_ep6_TD_TERMOUT_EN  (0u)
        #endif /* (USBCOMM_DMA6_ACTIVE) */

        #if (USBCOMM_DMA7_ACTIVE)
            #define USBCOMM_ep7_TD_TERMOUT_EN  (USBCOMM_ep7__TD_TERMOUT_EN)
        #else
            #define USBCOMM_ep7_TD_TERMOUT_EN  (0u)
        #endif /* (USBCOMM_DMA7_ACTIVE) */

        #if (USBCOMM_DMA8_ACTIVE)
            #define USBCOMM_ep8_TD_TERMOUT_EN  (USBCOMM_ep8__TD_TERMOUT_EN)
        #else
            #define USBCOMM_ep8_TD_TERMOUT_EN  (0u)
        #endif /* (USBCOMM_DMA8_ACTIVE) */
    #endif /* (USBCOMM_EP_MANAGEMENT_DMA_AUTO) */   
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

/* Rename USB IP registers. */
#define USBCOMM_ARB_CFG        USBCOMM_ARB_CFG_PTR

#define USBCOMM_ARB_EP1_CFG    USBCOMM_ARB_EP1_CFG_PTR
#define USBCOMM_ARB_EP1_INT_EN USBCOMM_ARB_EP1_INT_EN_PTR
#define USBCOMM_ARB_EP1_SR     USBCOMM_ARB_EP1_SR_PTR

#define USBCOMM_ARB_EP2_CFG    USBCOMM_ARB_EP2_CFG_PTR
#define USBCOMM_ARB_EP2_INT_EN USBCOMM_ARB_EP2_INT_EN_PTR
#define USBCOMM_ARB_EP2_SR     USBCOMM_ARB_EP2_SR_PTR

#define USBCOMM_ARB_EP3_CFG    USBCOMM_ARB_EP3_CFG_PTR
#define USBCOMM_ARB_EP3_INT_EN USBCOMM_ARB_EP3_INT_EN_PTR
#define USBCOMM_ARB_EP3_SR     USBCOMM_ARB_EP3_SR_PTR

#define USBCOMM_ARB_EP4_CFG    USBCOMM_ARB_EP4_CFG_PTR
#define USBCOMM_ARB_EP4_INT_EN USBCOMM_ARB_EP4_INT_EN_PTR
#define USBCOMM_ARB_EP4_SR     USBCOMM_ARB_EP4_SR_PTR

#define USBCOMM_ARB_EP5_CFG    USBCOMM_ARB_EP5_CFG_PTR
#define USBCOMM_ARB_EP5_INT_EN USBCOMM_ARB_EP5_INT_EN_PTR
#define USBCOMM_ARB_EP5_SR     USBCOMM_ARB_EP5_SR_PTR

#define USBCOMM_ARB_EP6_CFG    USBCOMM_ARB_EP6_CFG_PTR
#define USBCOMM_ARB_EP6_INT_EN USBCOMM_ARB_EP6_INT_EN_PTR
#define USBCOMM_ARB_EP6_SR     USBCOMM_ARB_EP6_SR_PTR

#define USBCOMM_ARB_EP7_CFG    USBCOMM_ARB_EP7_CFG_PTR
#define USBCOMM_ARB_EP7_INT_EN USBCOMM_ARB_EP7_INT_EN_PTR
#define USBCOMM_ARB_EP7_SR     USBCOMM_ARB_EP7_SR_PTR

#define USBCOMM_ARB_EP8_CFG    USBCOMM_ARB_EP8_CFG_PTR
#define USBCOMM_ARB_EP8_INT_EN USBCOMM_ARB_EP8_INT_EN_PTR
#define USBCOMM_ARB_EP8_SR     USBCOMM_ARB_EP8_SR_PTR

#define USBCOMM_ARB_INT_EN     USBCOMM_ARB_INT_EN_PTR
#define USBCOMM_ARB_INT_SR     USBCOMM_ARB_INT_SR_PTR

#define USBCOMM_ARB_RW1_DR     USBCOMM_ARB_RW1_DR_PTR
#define USBCOMM_ARB_RW1_RA     USBCOMM_ARB_RW1_RA_PTR
#define USBCOMM_ARB_RW1_RA_MSB USBCOMM_ARB_RW1_RA_MSB_PTR
#define USBCOMM_ARB_RW1_WA     USBCOMM_ARB_RW1_WA_PTR
#define USBCOMM_ARB_RW1_WA_MSB USBCOMM_ARB_RW1_WA_MSB_PTR

#define USBCOMM_ARB_RW2_DR     USBCOMM_ARB_RW2_DR_PTR
#define USBCOMM_ARB_RW2_RA     USBCOMM_ARB_RW2_RA_PTR
#define USBCOMM_ARB_RW2_RA_MSB USBCOMM_ARB_RW2_RA_MSB_PTR
#define USBCOMM_ARB_RW2_WA     USBCOMM_ARB_RW2_WA_PTR
#define USBCOMM_ARB_RW2_WA_MSB USBCOMM_ARB_RW2_WA_MSB_PTR

#define USBCOMM_ARB_RW3_DR     USBCOMM_ARB_RW3_DR_PTR
#define USBCOMM_ARB_RW3_RA     USBCOMM_ARB_RW3_RA_PTR
#define USBCOMM_ARB_RW3_RA_MSB USBCOMM_ARB_RW3_RA_MSB_PTR
#define USBCOMM_ARB_RW3_WA     USBCOMM_ARB_RW3_WA_PTR
#define USBCOMM_ARB_RW3_WA_MSB USBCOMM_ARB_RW3_WA_MSB_PTR

#define USBCOMM_ARB_RW4_DR     USBCOMM_ARB_RW4_DR_PTR
#define USBCOMM_ARB_RW4_RA     USBCOMM_ARB_RW4_RA_PTR
#define USBCOMM_ARB_RW4_RA_MSB USBCOMM_ARB_RW4_RA_MSB_PTR
#define USBCOMM_ARB_RW4_WA     USBCOMM_ARB_RW4_WA_PTR
#define USBCOMM_ARB_RW4_WA_MSB USBCOMM_ARB_RW4_WA_MSB_PTR

#define USBCOMM_ARB_RW5_DR     USBCOMM_ARB_RW5_DR_PTR
#define USBCOMM_ARB_RW5_RA     USBCOMM_ARB_RW5_RA_PTR
#define USBCOMM_ARB_RW5_RA_MSB USBCOMM_ARB_RW5_RA_MSB_PTR
#define USBCOMM_ARB_RW5_WA     USBCOMM_ARB_RW5_WA_PTR
#define USBCOMM_ARB_RW5_WA_MSB USBCOMM_ARB_RW5_WA_MSB_PTR

#define USBCOMM_ARB_RW6_DR     USBCOMM_ARB_RW6_DR_PTR
#define USBCOMM_ARB_RW6_RA     USBCOMM_ARB_RW6_RA_PTR
#define USBCOMM_ARB_RW6_RA_MSB USBCOMM_ARB_RW6_RA_MSB_PTR
#define USBCOMM_ARB_RW6_WA     USBCOMM_ARB_RW6_WA_PTR
#define USBCOMM_ARB_RW6_WA_MSB USBCOMM_ARB_RW6_WA_MSB_PTR

#define USBCOMM_ARB_RW7_DR     USBCOMM_ARB_RW7_DR_PTR
#define USBCOMM_ARB_RW7_RA     USBCOMM_ARB_RW7_RA_PTR
#define USBCOMM_ARB_RW7_RA_MSB USBCOMM_ARB_RW7_RA_MSB_PTR
#define USBCOMM_ARB_RW7_WA     USBCOMM_ARB_RW7_WA_PTR
#define USBCOMM_ARB_RW7_WA_MSB USBCOMM_ARB_RW7_WA_MSB_PTR

#define USBCOMM_ARB_RW8_DR     USBCOMM_ARB_RW8_DR_PTR
#define USBCOMM_ARB_RW8_RA     USBCOMM_ARB_RW8_RA_PTR
#define USBCOMM_ARB_RW8_RA_MSB USBCOMM_ARB_RW8_RA_MSB_PTR
#define USBCOMM_ARB_RW8_WA     USBCOMM_ARB_RW8_WA_PTR
#define USBCOMM_ARB_RW8_WA_MSB USBCOMM_ARB_RW8_WA_MSB_PTR

#define USBCOMM_BUF_SIZE       USBCOMM_BUF_SIZE_PTR
#define USBCOMM_BUS_RST_CNT    USBCOMM_BUS_RST_CNT_PTR
#define USBCOMM_CR0            USBCOMM_CR0_PTR
#define USBCOMM_CR1            USBCOMM_CR1_PTR
#define USBCOMM_CWA            USBCOMM_CWA_PTR
#define USBCOMM_CWA_MSB        USBCOMM_CWA_MSB_PTR

#define USBCOMM_DMA_THRES      USBCOMM_DMA_THRES_PTR
#define USBCOMM_DMA_THRES_MSB  USBCOMM_DMA_THRES_MSB_PTR

#define USBCOMM_EP_ACTIVE      USBCOMM_EP_ACTIVE_PTR
#define USBCOMM_EP_TYPE        USBCOMM_EP_TYPE_PTR

#define USBCOMM_EP0_CNT        USBCOMM_EP0_CNT_PTR
#define USBCOMM_EP0_CR         USBCOMM_EP0_CR_PTR
#define USBCOMM_EP0_DR0        USBCOMM_EP0_DR0_PTR
#define USBCOMM_EP0_DR1        USBCOMM_EP0_DR1_PTR
#define USBCOMM_EP0_DR2        USBCOMM_EP0_DR2_PTR
#define USBCOMM_EP0_DR3        USBCOMM_EP0_DR3_PTR
#define USBCOMM_EP0_DR4        USBCOMM_EP0_DR4_PTR
#define USBCOMM_EP0_DR5        USBCOMM_EP0_DR5_PTR
#define USBCOMM_EP0_DR6        USBCOMM_EP0_DR6_PTR
#define USBCOMM_EP0_DR7        USBCOMM_EP0_DR7_PTR

#define USBCOMM_OSCLK_DR0      USBCOMM_OSCLK_DR0_PTR
#define USBCOMM_OSCLK_DR1      USBCOMM_OSCLK_DR1_PTR

#define USBCOMM_PM_ACT_CFG     USBCOMM_PM_ACT_CFG_PTR
#define USBCOMM_PM_STBY_CFG    USBCOMM_PM_STBY_CFG_PTR

#define USBCOMM_SIE_EP_INT_EN  USBCOMM_SIE_EP_INT_EN_PTR
#define USBCOMM_SIE_EP_INT_SR  USBCOMM_SIE_EP_INT_SR_PTR

#define USBCOMM_SIE_EP1_CNT0   USBCOMM_SIE_EP1_CNT0_PTR
#define USBCOMM_SIE_EP1_CNT1   USBCOMM_SIE_EP1_CNT1_PTR
#define USBCOMM_SIE_EP1_CR0    USBCOMM_SIE_EP1_CR0_PTR

#define USBCOMM_SIE_EP2_CNT0   USBCOMM_SIE_EP2_CNT0_PTR
#define USBCOMM_SIE_EP2_CNT1   USBCOMM_SIE_EP2_CNT1_PTR
#define USBCOMM_SIE_EP2_CR0    USBCOMM_SIE_EP2_CR0_PTR

#define USBCOMM_SIE_EP3_CNT0   USBCOMM_SIE_EP3_CNT0_PTR
#define USBCOMM_SIE_EP3_CNT1   USBCOMM_SIE_EP3_CNT1_PTR
#define USBCOMM_SIE_EP3_CR0    USBCOMM_SIE_EP3_CR0_PTR

#define USBCOMM_SIE_EP4_CNT0   USBCOMM_SIE_EP4_CNT0_PTR
#define USBCOMM_SIE_EP4_CNT1   USBCOMM_SIE_EP4_CNT1_PTR
#define USBCOMM_SIE_EP4_CR0    USBCOMM_SIE_EP4_CR0_PTR

#define USBCOMM_SIE_EP5_CNT0   USBCOMM_SIE_EP5_CNT0_PTR
#define USBCOMM_SIE_EP5_CNT1   USBCOMM_SIE_EP5_CNT1_PTR
#define USBCOMM_SIE_EP5_CR0    USBCOMM_SIE_EP5_CR0_PTR

#define USBCOMM_SIE_EP6_CNT0   USBCOMM_SIE_EP6_CNT0_PTR
#define USBCOMM_SIE_EP6_CNT1   USBCOMM_SIE_EP6_CNT1_PTR
#define USBCOMM_SIE_EP6_CR0    USBCOMM_SIE_EP6_CR0_PTR

#define USBCOMM_SIE_EP7_CNT0   USBCOMM_SIE_EP7_CNT0_PTR
#define USBCOMM_SIE_EP7_CNT1   USBCOMM_SIE_EP7_CNT1_PTR
#define USBCOMM_SIE_EP7_CR0    USBCOMM_SIE_EP7_CR0_PTR

#define USBCOMM_SIE_EP8_CNT0   USBCOMM_SIE_EP8_CNT0_PTR
#define USBCOMM_SIE_EP8_CNT1   USBCOMM_SIE_EP8_CNT1_PTR
#define USBCOMM_SIE_EP8_CR0    USBCOMM_SIE_EP8_CR0_PTR

#define USBCOMM_SOF0           USBCOMM_SOF0_PTR
#define USBCOMM_SOF1           USBCOMM_SOF1_PTR

#define USBCOMM_USB_CLK_EN     USBCOMM_USB_CLK_EN_PTR

#define USBCOMM_USBIO_CR0      USBCOMM_USBIO_CR0_PTR
#define USBCOMM_USBIO_CR1      USBCOMM_USBIO_CR1_PTR
#define USBCOMM_USBIO_CR2      USBCOMM_USBIO_CR2_PTR

#define USBCOMM_DM_INP_DIS_PTR     ( (reg8 *) USBCOMM_Dm__INP_DIS)
#define USBCOMM_DM_INP_DIS_REG     (*(reg8 *) USBCOMM_Dm__INP_DIS)
#define USBCOMM_DP_INP_DIS_PTR     ( (reg8 *) USBCOMM_Dp__INP_DIS)
#define USBCOMM_DP_INP_DIS_REG     (*(reg8 *) USBCOMM_Dp__INP_DIS)
#define USBCOMM_DP_INTSTAT_PTR     ( (reg8 *) USBCOMM_Dp__INTSTAT)
#define USBCOMM_DP_INTSTAT_REG     (*(reg8 *) USBCOMM_Dp__INTSTAT)
#define USBCOMM_DM_MASK            USBCOMM_Dm__0__MASK
#define USBCOMM_DP_MASK            USBCOMM_Dp__0__MASK

#define USBFS_SIE_EP_INT_EP1_MASK        (0x01u)
#define USBFS_SIE_EP_INT_EP2_MASK        (0x02u)
#define USBFS_SIE_EP_INT_EP3_MASK        (0x04u)
#define USBFS_SIE_EP_INT_EP4_MASK        (0x08u)
#define USBFS_SIE_EP_INT_EP5_MASK        (0x10u)
#define USBFS_SIE_EP_INT_EP6_MASK        (0x20u)
#define USBFS_SIE_EP_INT_EP7_MASK        (0x40u)
#define USBFS_SIE_EP_INT_EP8_MASK        (0x80u)

#define USBCOMM_ARB_EPX_SR_IN_BUF_FULL     (0x01u)
#define USBCOMM_ARB_EPX_SR_DMA_GNT         (0x02u)
#define USBCOMM_ARB_EPX_SR_BUF_OVER        (0x04u)
#define USBCOMM_ARB_EPX_SR_BUF_UNDER       (0x08u)

#define USBCOMM_ARB_EPX_INT_EN_ALL USBCOMM_ARB_EPX_INT_ALL

#define USBCOMM_CR1_BUS_ACTIVITY_SHIFT     (0x02u)

#define USBCOMM_BUS_RST_COUNT      USBCOMM_DEFUALT_BUS_RST_CNT

#define USBCOMM_ARB_INT_MASK       USBCOMM_DEFAULT_ARB_INT_EN

#if (CYDEV_CHIP_DIE_EXPECT == CYDEV_CHIP_DIE_LEOPARD)
    /* CY_PSOC3 interrupt registers */
    #define USBCOMM_USB_ISR_PRIOR  ((reg8 *) CYDEV_INTC_PRIOR0)
    #define USBCOMM_USB_ISR_SET_EN ((reg8 *) CYDEV_INTC_SET_EN0)
    #define USBCOMM_USB_ISR_CLR_EN ((reg8 *) CYDEV_INTC_CLR_EN0)
    #define USBCOMM_USB_ISR_VECT   ((cyisraddress *) CYDEV_INTC_VECT_MBASE)
#elif (CYDEV_CHIP_DIE_EXPECT == CYDEV_CHIP_DIE_PANTHER)
    /* CY_PSOC5LP interrupt registers */
    #define USBCOMM_USB_ISR_PRIOR  ((reg8 *) CYDEV_NVIC_PRI_0)
    #define USBCOMM_USB_ISR_SET_EN ((reg8 *) CYDEV_NVIC_SETENA0)
    #define USBCOMM_USB_ISR_CLR_EN ((reg8 *) CYDEV_NVIC_CLRENA0)
    #define USBCOMM_USB_ISR_VECT   ((cyisraddress *) CYDEV_NVIC_VECT_OFFSET)
#endif /*  CYDEV_CHIP_DIE_EXPECT */


#endif /* (CY_USBFS_USBCOMM_H) */


/* [] END OF FILE */

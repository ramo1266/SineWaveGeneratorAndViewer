/***************************************************************************//**
* \file USBCOMM_audio.h
* \version 3.20
*
* \brief
*  This file provides function prototypes and constants for the USBFS component 
*  Audio class.
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

#if !defined(CY_USBFS_USBCOMM_audio_H)
#define CY_USBFS_USBCOMM_audio_H

#include "USBCOMM.h"


/***************************************
* Custom Declarations
***************************************/

/* `#START CUSTOM_CONSTANTS` Place your declaration here */

/* `#END` */


/***************************************
*  Constants for USBCOMM_audio API.
***************************************/

/* Audio Class-Specific Request Codes (AUDIO Table A-9) */
#define USBCOMM_REQUEST_CODE_UNDEFINED     (0x00u)
#define USBCOMM_SET_CUR                    (0x01u)
#define USBCOMM_GET_CUR                    (0x81u)
#define USBCOMM_SET_MIN                    (0x02u)
#define USBCOMM_GET_MIN                    (0x82u)
#define USBCOMM_SET_MAX                    (0x03u)
#define USBCOMM_GET_MAX                    (0x83u)
#define USBCOMM_SET_RES                    (0x04u)
#define USBCOMM_GET_RES                    (0x84u)
#define USBCOMM_SET_MEM                    (0x05u)
#define USBCOMM_GET_MEM                    (0x85u)
#define USBCOMM_GET_STAT                   (0xFFu)

/* point Control Selectors (AUDIO Table A-19) */
#define USBCOMM_EP_CONTROL_UNDEFINED       (0x00u)
#define USBCOMM_SAMPLING_FREQ_CONTROL      (0x01u)
#define USBCOMM_PITCH_CONTROL              (0x02u)

/* Feature Unit Control Selectors (AUDIO Table A-11) */
#define USBCOMM_FU_CONTROL_UNDEFINED       (0x00u)
#define USBCOMM_MUTE_CONTROL               (0x01u)
#define USBCOMM_VOLUME_CONTROL             (0x02u)
#define USBCOMM_BASS_CONTROL               (0x03u)
#define USBCOMM_MID_CONTROL                (0x04u)
#define USBCOMM_TREBLE_CONTROL             (0x05u)
#define USBCOMM_GRAPHIC_EQUALIZER_CONTROL  (0x06u)
#define USBCOMM_AUTOMATIC_GAIN_CONTROL     (0x07u)
#define USBCOMM_DELAY_CONTROL              (0x08u)
#define USBCOMM_BASS_BOOST_CONTROL         (0x09u)
#define USBCOMM_LOUDNESS_CONTROL           (0x0Au)

#define USBCOMM_SAMPLE_FREQ_LEN            (3u)
#define USBCOMM_VOLUME_LEN                 (2u)

#if !defined(USER_SUPPLIED_DEFAULT_VOLUME_VALUE)
    #define USBCOMM_VOL_MIN_MSB            (0x80u)
    #define USBCOMM_VOL_MIN_LSB            (0x01u)
    #define USBCOMM_VOL_MAX_MSB            (0x7Fu)
    #define USBCOMM_VOL_MAX_LSB            (0xFFu)
    #define USBCOMM_VOL_RES_MSB            (0x00u)
    #define USBCOMM_VOL_RES_LSB            (0x01u)
#endif /* USER_SUPPLIED_DEFAULT_VOLUME_VALUE */


/***************************************
* External data references
***************************************/
/**
* \addtogroup group_audio
* @{
*/
extern volatile uint8 USBCOMM_currentSampleFrequency[USBCOMM_MAX_EP][USBCOMM_SAMPLE_FREQ_LEN];
extern volatile uint8 USBCOMM_frequencyChanged;
extern volatile uint8 USBCOMM_currentMute;
extern volatile uint8 USBCOMM_currentVolume[USBCOMM_VOLUME_LEN];
/** @} audio */

extern volatile uint8 USBCOMM_minimumVolume[USBCOMM_VOLUME_LEN];
extern volatile uint8 USBCOMM_maximumVolume[USBCOMM_VOLUME_LEN];
extern volatile uint8 USBCOMM_resolutionVolume[USBCOMM_VOLUME_LEN];

#endif /*  CY_USBFS_USBCOMM_audio_H */


/* [] END OF FILE */

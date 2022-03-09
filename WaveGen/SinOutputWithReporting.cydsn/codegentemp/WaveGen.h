/*******************************************************************************
* File Name: WaveGen.h  
* Version 2.10
*
* Description:
*  This file contains the function prototypes and constants used in
*  the 8-bit Waveform DAC (WaveDAC8) Component.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_WaveDAC8_WaveGen_H) 
#define CY_WaveDAC8_WaveGen_H

#include "cytypes.h"
#include "cyfitter.h"
#include <WaveGen_Wave1_DMA_dma.h>
#include <WaveGen_Wave2_DMA_dma.h>
#include <WaveGen_VDAC8.h>


/***************************************
*  Initial Parameter Constants
***************************************/

#define WaveGen_WAVE1_TYPE     (0u)     /* Waveform for wave1 */
#define WaveGen_WAVE2_TYPE     (0u)     /* Waveform for wave2 */
#define WaveGen_SINE_WAVE      (0u)
#define WaveGen_SQUARE_WAVE    (1u)
#define WaveGen_TRIANGLE_WAVE  (2u)
#define WaveGen_SAWTOOTH_WAVE  (3u)
#define WaveGen_ARB_DRAW_WAVE  (10u) /* Arbitrary (draw) */
#define WaveGen_ARB_FILE_WAVE  (11u) /* Arbitrary (from file) */

#define WaveGen_WAVE1_LENGTH   (1000u)   /* Length for wave1 */
#define WaveGen_WAVE2_LENGTH   (1000u)   /* Length for wave2 */
	
#define WaveGen_DEFAULT_RANGE    (1u) /* Default DAC range */
#define WaveGen_DAC_RANGE_1V     (0u)
#define WaveGen_DAC_RANGE_1V_BUF (16u)
#define WaveGen_DAC_RANGE_4V     (1u)
#define WaveGen_DAC_RANGE_4V_BUF (17u)
#define WaveGen_VOLT_MODE        (0u)
#define WaveGen_CURRENT_MODE     (1u)
#define WaveGen_DAC_MODE         (((WaveGen_DEFAULT_RANGE == WaveGen_DAC_RANGE_1V) || \
									  (WaveGen_DEFAULT_RANGE == WaveGen_DAC_RANGE_4V) || \
							  		  (WaveGen_DEFAULT_RANGE == WaveGen_DAC_RANGE_1V_BUF) || \
									  (WaveGen_DEFAULT_RANGE == WaveGen_DAC_RANGE_4V_BUF)) ? \
									   WaveGen_VOLT_MODE : WaveGen_CURRENT_MODE)

#define WaveGen_DACMODE WaveGen_DAC_MODE /* legacy definition for backward compatibility */

#define WaveGen_DIRECT_MODE (0u)
#define WaveGen_BUFFER_MODE (1u)
#define WaveGen_OUT_MODE    (((WaveGen_DEFAULT_RANGE == WaveGen_DAC_RANGE_1V_BUF) || \
								 (WaveGen_DEFAULT_RANGE == WaveGen_DAC_RANGE_4V_BUF)) ? \
								  WaveGen_BUFFER_MODE : WaveGen_DIRECT_MODE)

#if(WaveGen_OUT_MODE == WaveGen_BUFFER_MODE)
    #include <WaveGen_BuffAmp.h>
#endif /* WaveGen_OUT_MODE == WaveGen_BUFFER_MODE */

#define WaveGen_CLOCK_INT      (1u)
#define WaveGen_CLOCK_EXT      (0u)
#define WaveGen_CLOCK_SRC      (0u)

#if(WaveGen_CLOCK_SRC == WaveGen_CLOCK_INT)  
	#include <WaveGen_DacClk.h>
	#if defined(WaveGen_DacClk_PHASE)
		#define WaveGen_CLK_PHASE_0nS (1u)
	#endif /* defined(WaveGen_DacClk_PHASE) */
#endif /* WaveGen_CLOCK_SRC == WaveGen_CLOCK_INT */

#if (CY_PSOC3)
	#define WaveGen_HI16FLASHPTR   (0xFFu)
#endif /* CY_PSOC3 */

#define WaveGen_Wave1_DMA_BYTES_PER_BURST      (1u)
#define WaveGen_Wave1_DMA_REQUEST_PER_BURST    (1u)
#define WaveGen_Wave2_DMA_BYTES_PER_BURST      (1u)
#define WaveGen_Wave2_DMA_REQUEST_PER_BURST    (1u)


/***************************************
*   Data Struct Definition
***************************************/

/* Low power Mode API Support */
typedef struct
{
	uint8   enableState;
}WaveGen_BACKUP_STRUCT;


/***************************************
*        Function Prototypes 
***************************************/

void WaveGen_Start(void)             ;
void WaveGen_StartEx(const uint8 * wavePtr1, uint16 sampleSize1, const uint8 * wavePtr2, uint16 sampleSize2)
                                        ;
void WaveGen_Init(void)              ;
void WaveGen_Enable(void)            ;
void WaveGen_Stop(void)              ;

void WaveGen_Wave1Setup(const uint8 * wavePtr, uint16 sampleSize)
                                        ;
void WaveGen_Wave2Setup(const uint8 * wavePtr, uint16 sampleSize)
                                        ;

void WaveGen_Sleep(void)             ;
void WaveGen_Wakeup(void)            ;

#define WaveGen_SetSpeed       WaveGen_VDAC8_SetSpeed
#define WaveGen_SetRange       WaveGen_VDAC8_SetRange
#define WaveGen_SetValue       WaveGen_VDAC8_SetValue
#define WaveGen_DacTrim        WaveGen_VDAC8_DacTrim
#define WaveGen_SaveConfig     WaveGen_VDAC8_SaveConfig
#define WaveGen_RestoreConfig  WaveGen_VDAC8_RestoreConfig


/***************************************
*    Variable with external linkage 
***************************************/

extern uint8 WaveGen_initVar;

extern const uint8 CYCODE WaveGen_wave1[WaveGen_WAVE1_LENGTH];
extern const uint8 CYCODE WaveGen_wave2[WaveGen_WAVE2_LENGTH];


/***************************************
*            API Constants
***************************************/

/* SetRange constants */
#if(WaveGen_DAC_MODE == WaveGen_VOLT_MODE)
    #define WaveGen_RANGE_1V       (0x00u)
    #define WaveGen_RANGE_4V       (0x04u)
#else /* current mode */
    #define WaveGen_RANGE_32uA     (0x00u)
    #define WaveGen_RANGE_255uA    (0x04u)
    #define WaveGen_RANGE_2mA      (0x08u)
    #define WaveGen_RANGE_2048uA   WaveGen_RANGE_2mA
#endif /* WaveGen_DAC_MODE == WaveGen_VOLT_MODE */

/* Power setting for SetSpeed API */
#define WaveGen_LOWSPEED       (0x00u)
#define WaveGen_HIGHSPEED      (0x02u)


/***************************************
*              Registers        
***************************************/

#define WaveGen_DAC8__D WaveGen_VDAC8_viDAC8__D


/***************************************
*         Register Constants       
***************************************/

/* CR0 vDac Control Register 0 definitions */

/* Bit Field  DAC_HS_MODE */
#define WaveGen_HS_MASK        (0x02u)
#define WaveGen_HS_LOWPOWER    (0x00u)
#define WaveGen_HS_HIGHSPEED   (0x02u)

/* Bit Field  DAC_MODE */
#define WaveGen_MODE_MASK      (0x10u)
#define WaveGen_MODE_V         (0x00u)
#define WaveGen_MODE_I         (0x10u)

/* Bit Field  DAC_RANGE */
#define WaveGen_RANGE_MASK     (0x0Cu)
#define WaveGen_RANGE_0        (0x00u)
#define WaveGen_RANGE_1        (0x04u)
#define WaveGen_RANGE_2        (0x08u)
#define WaveGen_RANGE_3        (0x0Cu)
#define WaveGen_IDIR_MASK      (0x04u)

#define WaveGen_DAC_RANGE      ((uint8)(1u << 2u) & WaveGen_RANGE_MASK)
#define WaveGen_DAC_POL        ((uint8)(1u >> 1u) & WaveGen_IDIR_MASK)


#endif /* CY_WaveDAC8_WaveGen_H  */

/* [] END OF FILE */

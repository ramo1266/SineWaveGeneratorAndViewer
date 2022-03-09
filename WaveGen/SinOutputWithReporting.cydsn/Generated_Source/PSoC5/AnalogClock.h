/*******************************************************************************
* File Name: AnalogClock.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_AnalogClock_H)
#define CY_CLOCK_AnalogClock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void AnalogClock_Start(void) ;
void AnalogClock_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void AnalogClock_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void AnalogClock_StandbyPower(uint8 state) ;
void AnalogClock_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 AnalogClock_GetDividerRegister(void) ;
void AnalogClock_SetModeRegister(uint8 modeBitMask) ;
void AnalogClock_ClearModeRegister(uint8 modeBitMask) ;
uint8 AnalogClock_GetModeRegister(void) ;
void AnalogClock_SetSourceRegister(uint8 clkSource) ;
uint8 AnalogClock_GetSourceRegister(void) ;
#if defined(AnalogClock__CFG3)
void AnalogClock_SetPhaseRegister(uint8 clkPhase) ;
uint8 AnalogClock_GetPhaseRegister(void) ;
#endif /* defined(AnalogClock__CFG3) */

#define AnalogClock_Enable()                       AnalogClock_Start()
#define AnalogClock_Disable()                      AnalogClock_Stop()
#define AnalogClock_SetDivider(clkDivider)         AnalogClock_SetDividerRegister(clkDivider, 1u)
#define AnalogClock_SetDividerValue(clkDivider)    AnalogClock_SetDividerRegister((clkDivider) - 1u, 1u)
#define AnalogClock_SetMode(clkMode)               AnalogClock_SetModeRegister(clkMode)
#define AnalogClock_SetSource(clkSource)           AnalogClock_SetSourceRegister(clkSource)
#if defined(AnalogClock__CFG3)
#define AnalogClock_SetPhase(clkPhase)             AnalogClock_SetPhaseRegister(clkPhase)
#define AnalogClock_SetPhaseValue(clkPhase)        AnalogClock_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(AnalogClock__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define AnalogClock_CLKEN              (* (reg8 *) AnalogClock__PM_ACT_CFG)
#define AnalogClock_CLKEN_PTR          ((reg8 *) AnalogClock__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define AnalogClock_CLKSTBY            (* (reg8 *) AnalogClock__PM_STBY_CFG)
#define AnalogClock_CLKSTBY_PTR        ((reg8 *) AnalogClock__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define AnalogClock_DIV_LSB            (* (reg8 *) AnalogClock__CFG0)
#define AnalogClock_DIV_LSB_PTR        ((reg8 *) AnalogClock__CFG0)
#define AnalogClock_DIV_PTR            ((reg16 *) AnalogClock__CFG0)

/* Clock MSB divider configuration register. */
#define AnalogClock_DIV_MSB            (* (reg8 *) AnalogClock__CFG1)
#define AnalogClock_DIV_MSB_PTR        ((reg8 *) AnalogClock__CFG1)

/* Mode and source configuration register */
#define AnalogClock_MOD_SRC            (* (reg8 *) AnalogClock__CFG2)
#define AnalogClock_MOD_SRC_PTR        ((reg8 *) AnalogClock__CFG2)

#if defined(AnalogClock__CFG3)
/* Analog clock phase configuration register */
#define AnalogClock_PHASE              (* (reg8 *) AnalogClock__CFG3)
#define AnalogClock_PHASE_PTR          ((reg8 *) AnalogClock__CFG3)
#endif /* defined(AnalogClock__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define AnalogClock_CLKEN_MASK         AnalogClock__PM_ACT_MSK
#define AnalogClock_CLKSTBY_MASK       AnalogClock__PM_STBY_MSK

/* CFG2 field masks */
#define AnalogClock_SRC_SEL_MSK        AnalogClock__CFG2_SRC_SEL_MASK
#define AnalogClock_MODE_MASK          (~(AnalogClock_SRC_SEL_MSK))

#if defined(AnalogClock__CFG3)
/* CFG3 phase mask */
#define AnalogClock_PHASE_MASK         AnalogClock__CFG3_PHASE_DLY_MASK
#endif /* defined(AnalogClock__CFG3) */

#endif /* CY_CLOCK_AnalogClock_H */


/* [] END OF FILE */

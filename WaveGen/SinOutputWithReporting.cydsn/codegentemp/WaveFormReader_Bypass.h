/*******************************************************************************
* File Name: WaveFormReader_Bypass.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_WaveFormReader_Bypass_H) /* Pins WaveFormReader_Bypass_H */
#define CY_PINS_WaveFormReader_Bypass_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "WaveFormReader_Bypass_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 WaveFormReader_Bypass__PORT == 15 && ((WaveFormReader_Bypass__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    WaveFormReader_Bypass_Write(uint8 value);
void    WaveFormReader_Bypass_SetDriveMode(uint8 mode);
uint8   WaveFormReader_Bypass_ReadDataReg(void);
uint8   WaveFormReader_Bypass_Read(void);
void    WaveFormReader_Bypass_SetInterruptMode(uint16 position, uint16 mode);
uint8   WaveFormReader_Bypass_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the WaveFormReader_Bypass_SetDriveMode() function.
     *  @{
     */
        #define WaveFormReader_Bypass_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define WaveFormReader_Bypass_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define WaveFormReader_Bypass_DM_RES_UP          PIN_DM_RES_UP
        #define WaveFormReader_Bypass_DM_RES_DWN         PIN_DM_RES_DWN
        #define WaveFormReader_Bypass_DM_OD_LO           PIN_DM_OD_LO
        #define WaveFormReader_Bypass_DM_OD_HI           PIN_DM_OD_HI
        #define WaveFormReader_Bypass_DM_STRONG          PIN_DM_STRONG
        #define WaveFormReader_Bypass_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define WaveFormReader_Bypass_MASK               WaveFormReader_Bypass__MASK
#define WaveFormReader_Bypass_SHIFT              WaveFormReader_Bypass__SHIFT
#define WaveFormReader_Bypass_WIDTH              1u

/* Interrupt constants */
#if defined(WaveFormReader_Bypass__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in WaveFormReader_Bypass_SetInterruptMode() function.
     *  @{
     */
        #define WaveFormReader_Bypass_INTR_NONE      (uint16)(0x0000u)
        #define WaveFormReader_Bypass_INTR_RISING    (uint16)(0x0001u)
        #define WaveFormReader_Bypass_INTR_FALLING   (uint16)(0x0002u)
        #define WaveFormReader_Bypass_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define WaveFormReader_Bypass_INTR_MASK      (0x01u) 
#endif /* (WaveFormReader_Bypass__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define WaveFormReader_Bypass_PS                     (* (reg8 *) WaveFormReader_Bypass__PS)
/* Data Register */
#define WaveFormReader_Bypass_DR                     (* (reg8 *) WaveFormReader_Bypass__DR)
/* Port Number */
#define WaveFormReader_Bypass_PRT_NUM                (* (reg8 *) WaveFormReader_Bypass__PRT) 
/* Connect to Analog Globals */                                                  
#define WaveFormReader_Bypass_AG                     (* (reg8 *) WaveFormReader_Bypass__AG)                       
/* Analog MUX bux enable */
#define WaveFormReader_Bypass_AMUX                   (* (reg8 *) WaveFormReader_Bypass__AMUX) 
/* Bidirectional Enable */                                                        
#define WaveFormReader_Bypass_BIE                    (* (reg8 *) WaveFormReader_Bypass__BIE)
/* Bit-mask for Aliased Register Access */
#define WaveFormReader_Bypass_BIT_MASK               (* (reg8 *) WaveFormReader_Bypass__BIT_MASK)
/* Bypass Enable */
#define WaveFormReader_Bypass_BYP                    (* (reg8 *) WaveFormReader_Bypass__BYP)
/* Port wide control signals */                                                   
#define WaveFormReader_Bypass_CTL                    (* (reg8 *) WaveFormReader_Bypass__CTL)
/* Drive Modes */
#define WaveFormReader_Bypass_DM0                    (* (reg8 *) WaveFormReader_Bypass__DM0) 
#define WaveFormReader_Bypass_DM1                    (* (reg8 *) WaveFormReader_Bypass__DM1)
#define WaveFormReader_Bypass_DM2                    (* (reg8 *) WaveFormReader_Bypass__DM2) 
/* Input Buffer Disable Override */
#define WaveFormReader_Bypass_INP_DIS                (* (reg8 *) WaveFormReader_Bypass__INP_DIS)
/* LCD Common or Segment Drive */
#define WaveFormReader_Bypass_LCD_COM_SEG            (* (reg8 *) WaveFormReader_Bypass__LCD_COM_SEG)
/* Enable Segment LCD */
#define WaveFormReader_Bypass_LCD_EN                 (* (reg8 *) WaveFormReader_Bypass__LCD_EN)
/* Slew Rate Control */
#define WaveFormReader_Bypass_SLW                    (* (reg8 *) WaveFormReader_Bypass__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define WaveFormReader_Bypass_PRTDSI__CAPS_SEL       (* (reg8 *) WaveFormReader_Bypass__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define WaveFormReader_Bypass_PRTDSI__DBL_SYNC_IN    (* (reg8 *) WaveFormReader_Bypass__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define WaveFormReader_Bypass_PRTDSI__OE_SEL0        (* (reg8 *) WaveFormReader_Bypass__PRTDSI__OE_SEL0) 
#define WaveFormReader_Bypass_PRTDSI__OE_SEL1        (* (reg8 *) WaveFormReader_Bypass__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define WaveFormReader_Bypass_PRTDSI__OUT_SEL0       (* (reg8 *) WaveFormReader_Bypass__PRTDSI__OUT_SEL0) 
#define WaveFormReader_Bypass_PRTDSI__OUT_SEL1       (* (reg8 *) WaveFormReader_Bypass__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define WaveFormReader_Bypass_PRTDSI__SYNC_OUT       (* (reg8 *) WaveFormReader_Bypass__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(WaveFormReader_Bypass__SIO_CFG)
    #define WaveFormReader_Bypass_SIO_HYST_EN        (* (reg8 *) WaveFormReader_Bypass__SIO_HYST_EN)
    #define WaveFormReader_Bypass_SIO_REG_HIFREQ     (* (reg8 *) WaveFormReader_Bypass__SIO_REG_HIFREQ)
    #define WaveFormReader_Bypass_SIO_CFG            (* (reg8 *) WaveFormReader_Bypass__SIO_CFG)
    #define WaveFormReader_Bypass_SIO_DIFF           (* (reg8 *) WaveFormReader_Bypass__SIO_DIFF)
#endif /* (WaveFormReader_Bypass__SIO_CFG) */

/* Interrupt Registers */
#if defined(WaveFormReader_Bypass__INTSTAT)
    #define WaveFormReader_Bypass_INTSTAT            (* (reg8 *) WaveFormReader_Bypass__INTSTAT)
    #define WaveFormReader_Bypass_SNAP               (* (reg8 *) WaveFormReader_Bypass__SNAP)
    
	#define WaveFormReader_Bypass_0_INTTYPE_REG 		(* (reg8 *) WaveFormReader_Bypass__0__INTTYPE)
#endif /* (WaveFormReader_Bypass__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_WaveFormReader_Bypass_H */


/* [] END OF FILE */

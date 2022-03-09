/*******************************************************************************
* File Name: WaveFormSelect.h  
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

#if !defined(CY_PINS_WaveFormSelect_H) /* Pins WaveFormSelect_H */
#define CY_PINS_WaveFormSelect_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "WaveFormSelect_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 WaveFormSelect__PORT == 15 && ((WaveFormSelect__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    WaveFormSelect_Write(uint8 value);
void    WaveFormSelect_SetDriveMode(uint8 mode);
uint8   WaveFormSelect_ReadDataReg(void);
uint8   WaveFormSelect_Read(void);
void    WaveFormSelect_SetInterruptMode(uint16 position, uint16 mode);
uint8   WaveFormSelect_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the WaveFormSelect_SetDriveMode() function.
     *  @{
     */
        #define WaveFormSelect_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define WaveFormSelect_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define WaveFormSelect_DM_RES_UP          PIN_DM_RES_UP
        #define WaveFormSelect_DM_RES_DWN         PIN_DM_RES_DWN
        #define WaveFormSelect_DM_OD_LO           PIN_DM_OD_LO
        #define WaveFormSelect_DM_OD_HI           PIN_DM_OD_HI
        #define WaveFormSelect_DM_STRONG          PIN_DM_STRONG
        #define WaveFormSelect_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define WaveFormSelect_MASK               WaveFormSelect__MASK
#define WaveFormSelect_SHIFT              WaveFormSelect__SHIFT
#define WaveFormSelect_WIDTH              1u

/* Interrupt constants */
#if defined(WaveFormSelect__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in WaveFormSelect_SetInterruptMode() function.
     *  @{
     */
        #define WaveFormSelect_INTR_NONE      (uint16)(0x0000u)
        #define WaveFormSelect_INTR_RISING    (uint16)(0x0001u)
        #define WaveFormSelect_INTR_FALLING   (uint16)(0x0002u)
        #define WaveFormSelect_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define WaveFormSelect_INTR_MASK      (0x01u) 
#endif /* (WaveFormSelect__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define WaveFormSelect_PS                     (* (reg8 *) WaveFormSelect__PS)
/* Data Register */
#define WaveFormSelect_DR                     (* (reg8 *) WaveFormSelect__DR)
/* Port Number */
#define WaveFormSelect_PRT_NUM                (* (reg8 *) WaveFormSelect__PRT) 
/* Connect to Analog Globals */                                                  
#define WaveFormSelect_AG                     (* (reg8 *) WaveFormSelect__AG)                       
/* Analog MUX bux enable */
#define WaveFormSelect_AMUX                   (* (reg8 *) WaveFormSelect__AMUX) 
/* Bidirectional Enable */                                                        
#define WaveFormSelect_BIE                    (* (reg8 *) WaveFormSelect__BIE)
/* Bit-mask for Aliased Register Access */
#define WaveFormSelect_BIT_MASK               (* (reg8 *) WaveFormSelect__BIT_MASK)
/* Bypass Enable */
#define WaveFormSelect_BYP                    (* (reg8 *) WaveFormSelect__BYP)
/* Port wide control signals */                                                   
#define WaveFormSelect_CTL                    (* (reg8 *) WaveFormSelect__CTL)
/* Drive Modes */
#define WaveFormSelect_DM0                    (* (reg8 *) WaveFormSelect__DM0) 
#define WaveFormSelect_DM1                    (* (reg8 *) WaveFormSelect__DM1)
#define WaveFormSelect_DM2                    (* (reg8 *) WaveFormSelect__DM2) 
/* Input Buffer Disable Override */
#define WaveFormSelect_INP_DIS                (* (reg8 *) WaveFormSelect__INP_DIS)
/* LCD Common or Segment Drive */
#define WaveFormSelect_LCD_COM_SEG            (* (reg8 *) WaveFormSelect__LCD_COM_SEG)
/* Enable Segment LCD */
#define WaveFormSelect_LCD_EN                 (* (reg8 *) WaveFormSelect__LCD_EN)
/* Slew Rate Control */
#define WaveFormSelect_SLW                    (* (reg8 *) WaveFormSelect__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define WaveFormSelect_PRTDSI__CAPS_SEL       (* (reg8 *) WaveFormSelect__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define WaveFormSelect_PRTDSI__DBL_SYNC_IN    (* (reg8 *) WaveFormSelect__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define WaveFormSelect_PRTDSI__OE_SEL0        (* (reg8 *) WaveFormSelect__PRTDSI__OE_SEL0) 
#define WaveFormSelect_PRTDSI__OE_SEL1        (* (reg8 *) WaveFormSelect__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define WaveFormSelect_PRTDSI__OUT_SEL0       (* (reg8 *) WaveFormSelect__PRTDSI__OUT_SEL0) 
#define WaveFormSelect_PRTDSI__OUT_SEL1       (* (reg8 *) WaveFormSelect__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define WaveFormSelect_PRTDSI__SYNC_OUT       (* (reg8 *) WaveFormSelect__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(WaveFormSelect__SIO_CFG)
    #define WaveFormSelect_SIO_HYST_EN        (* (reg8 *) WaveFormSelect__SIO_HYST_EN)
    #define WaveFormSelect_SIO_REG_HIFREQ     (* (reg8 *) WaveFormSelect__SIO_REG_HIFREQ)
    #define WaveFormSelect_SIO_CFG            (* (reg8 *) WaveFormSelect__SIO_CFG)
    #define WaveFormSelect_SIO_DIFF           (* (reg8 *) WaveFormSelect__SIO_DIFF)
#endif /* (WaveFormSelect__SIO_CFG) */

/* Interrupt Registers */
#if defined(WaveFormSelect__INTSTAT)
    #define WaveFormSelect_INTSTAT            (* (reg8 *) WaveFormSelect__INTSTAT)
    #define WaveFormSelect_SNAP               (* (reg8 *) WaveFormSelect__SNAP)
    
	#define WaveFormSelect_0_INTTYPE_REG 		(* (reg8 *) WaveFormSelect__0__INTTYPE)
#endif /* (WaveFormSelect__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_WaveFormSelect_H */


/* [] END OF FILE */

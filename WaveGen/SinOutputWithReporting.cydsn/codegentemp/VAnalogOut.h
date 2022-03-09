/*******************************************************************************
* File Name: VAnalogOut.h  
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

#if !defined(CY_PINS_VAnalogOut_H) /* Pins VAnalogOut_H */
#define CY_PINS_VAnalogOut_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "VAnalogOut_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 VAnalogOut__PORT == 15 && ((VAnalogOut__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    VAnalogOut_Write(uint8 value);
void    VAnalogOut_SetDriveMode(uint8 mode);
uint8   VAnalogOut_ReadDataReg(void);
uint8   VAnalogOut_Read(void);
void    VAnalogOut_SetInterruptMode(uint16 position, uint16 mode);
uint8   VAnalogOut_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the VAnalogOut_SetDriveMode() function.
     *  @{
     */
        #define VAnalogOut_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define VAnalogOut_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define VAnalogOut_DM_RES_UP          PIN_DM_RES_UP
        #define VAnalogOut_DM_RES_DWN         PIN_DM_RES_DWN
        #define VAnalogOut_DM_OD_LO           PIN_DM_OD_LO
        #define VAnalogOut_DM_OD_HI           PIN_DM_OD_HI
        #define VAnalogOut_DM_STRONG          PIN_DM_STRONG
        #define VAnalogOut_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define VAnalogOut_MASK               VAnalogOut__MASK
#define VAnalogOut_SHIFT              VAnalogOut__SHIFT
#define VAnalogOut_WIDTH              1u

/* Interrupt constants */
#if defined(VAnalogOut__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in VAnalogOut_SetInterruptMode() function.
     *  @{
     */
        #define VAnalogOut_INTR_NONE      (uint16)(0x0000u)
        #define VAnalogOut_INTR_RISING    (uint16)(0x0001u)
        #define VAnalogOut_INTR_FALLING   (uint16)(0x0002u)
        #define VAnalogOut_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define VAnalogOut_INTR_MASK      (0x01u) 
#endif /* (VAnalogOut__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define VAnalogOut_PS                     (* (reg8 *) VAnalogOut__PS)
/* Data Register */
#define VAnalogOut_DR                     (* (reg8 *) VAnalogOut__DR)
/* Port Number */
#define VAnalogOut_PRT_NUM                (* (reg8 *) VAnalogOut__PRT) 
/* Connect to Analog Globals */                                                  
#define VAnalogOut_AG                     (* (reg8 *) VAnalogOut__AG)                       
/* Analog MUX bux enable */
#define VAnalogOut_AMUX                   (* (reg8 *) VAnalogOut__AMUX) 
/* Bidirectional Enable */                                                        
#define VAnalogOut_BIE                    (* (reg8 *) VAnalogOut__BIE)
/* Bit-mask for Aliased Register Access */
#define VAnalogOut_BIT_MASK               (* (reg8 *) VAnalogOut__BIT_MASK)
/* Bypass Enable */
#define VAnalogOut_BYP                    (* (reg8 *) VAnalogOut__BYP)
/* Port wide control signals */                                                   
#define VAnalogOut_CTL                    (* (reg8 *) VAnalogOut__CTL)
/* Drive Modes */
#define VAnalogOut_DM0                    (* (reg8 *) VAnalogOut__DM0) 
#define VAnalogOut_DM1                    (* (reg8 *) VAnalogOut__DM1)
#define VAnalogOut_DM2                    (* (reg8 *) VAnalogOut__DM2) 
/* Input Buffer Disable Override */
#define VAnalogOut_INP_DIS                (* (reg8 *) VAnalogOut__INP_DIS)
/* LCD Common or Segment Drive */
#define VAnalogOut_LCD_COM_SEG            (* (reg8 *) VAnalogOut__LCD_COM_SEG)
/* Enable Segment LCD */
#define VAnalogOut_LCD_EN                 (* (reg8 *) VAnalogOut__LCD_EN)
/* Slew Rate Control */
#define VAnalogOut_SLW                    (* (reg8 *) VAnalogOut__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define VAnalogOut_PRTDSI__CAPS_SEL       (* (reg8 *) VAnalogOut__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define VAnalogOut_PRTDSI__DBL_SYNC_IN    (* (reg8 *) VAnalogOut__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define VAnalogOut_PRTDSI__OE_SEL0        (* (reg8 *) VAnalogOut__PRTDSI__OE_SEL0) 
#define VAnalogOut_PRTDSI__OE_SEL1        (* (reg8 *) VAnalogOut__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define VAnalogOut_PRTDSI__OUT_SEL0       (* (reg8 *) VAnalogOut__PRTDSI__OUT_SEL0) 
#define VAnalogOut_PRTDSI__OUT_SEL1       (* (reg8 *) VAnalogOut__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define VAnalogOut_PRTDSI__SYNC_OUT       (* (reg8 *) VAnalogOut__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(VAnalogOut__SIO_CFG)
    #define VAnalogOut_SIO_HYST_EN        (* (reg8 *) VAnalogOut__SIO_HYST_EN)
    #define VAnalogOut_SIO_REG_HIFREQ     (* (reg8 *) VAnalogOut__SIO_REG_HIFREQ)
    #define VAnalogOut_SIO_CFG            (* (reg8 *) VAnalogOut__SIO_CFG)
    #define VAnalogOut_SIO_DIFF           (* (reg8 *) VAnalogOut__SIO_DIFF)
#endif /* (VAnalogOut__SIO_CFG) */

/* Interrupt Registers */
#if defined(VAnalogOut__INTSTAT)
    #define VAnalogOut_INTSTAT            (* (reg8 *) VAnalogOut__INTSTAT)
    #define VAnalogOut_SNAP               (* (reg8 *) VAnalogOut__SNAP)
    
	#define VAnalogOut_0_INTTYPE_REG 		(* (reg8 *) VAnalogOut__0__INTTYPE)
#endif /* (VAnalogOut__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_VAnalogOut_H */


/* [] END OF FILE */

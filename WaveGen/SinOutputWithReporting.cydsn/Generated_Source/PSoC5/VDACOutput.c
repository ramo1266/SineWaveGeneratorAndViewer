/*******************************************************************************
* File Name: VDACOutput.c  
* Version 1.90
*
* Description:
*  This file provides the source code to the API for the 8-bit Voltage DAC 
*  (VDAC8) User Module.
*
* Note:
*  Any unusual or non-standard behavior should be noted here. Other-
*  wise, this section should remain blank.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "VDACOutput.h"

#if (CY_PSOC5A)
#include <CyLib.h>
#endif /* CY_PSOC5A */

uint8 VDACOutput_initVar = 0u;

#if (CY_PSOC5A)
    static uint8 VDACOutput_restoreVal = 0u;
#endif /* CY_PSOC5A */

#if (CY_PSOC5A)
    static VDACOutput_backupStruct VDACOutput_backup;
#endif /* CY_PSOC5A */


/*******************************************************************************
* Function Name: VDACOutput_Init
********************************************************************************
* Summary:
*  Initialize to the schematic state.
* 
* Parameters:
*  void:
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void VDACOutput_Init(void) 
{
    VDACOutput_CR0 = (VDACOutput_MODE_V );

    /* Set default data source */
    #if(VDACOutput_DEFAULT_DATA_SRC != 0 )
        VDACOutput_CR1 = (VDACOutput_DEFAULT_CNTL | VDACOutput_DACBUS_ENABLE) ;
    #else
        VDACOutput_CR1 = (VDACOutput_DEFAULT_CNTL | VDACOutput_DACBUS_DISABLE) ;
    #endif /* (VDACOutput_DEFAULT_DATA_SRC != 0 ) */

    /* Set default strobe mode */
    #if(VDACOutput_DEFAULT_STRB != 0)
        VDACOutput_Strobe |= VDACOutput_STRB_EN ;
    #endif/* (VDACOutput_DEFAULT_STRB != 0) */

    /* Set default range */
    VDACOutput_SetRange(VDACOutput_DEFAULT_RANGE); 

    /* Set default speed */
    VDACOutput_SetSpeed(VDACOutput_DEFAULT_SPEED);
}


/*******************************************************************************
* Function Name: VDACOutput_Enable
********************************************************************************
* Summary:
*  Enable the VDAC8
* 
* Parameters:
*  void
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void VDACOutput_Enable(void) 
{
    VDACOutput_PWRMGR |= VDACOutput_ACT_PWR_EN;
    VDACOutput_STBY_PWRMGR |= VDACOutput_STBY_PWR_EN;

    /*This is to restore the value of register CR0 ,
    which is modified  in Stop API , this prevents misbehaviour of VDAC */
    #if (CY_PSOC5A)
        if(VDACOutput_restoreVal == 1u) 
        {
             VDACOutput_CR0 = VDACOutput_backup.data_value;
             VDACOutput_restoreVal = 0u;
        }
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: VDACOutput_Start
********************************************************************************
*
* Summary:
*  The start function initializes the voltage DAC with the default values, 
*  and sets the power to the given level.  A power level of 0, is the same as
*  executing the stop function.
*
* Parameters:
*  Power: Sets power level between off (0) and (3) high power
*
* Return:
*  void 
*
* Global variables:
*  VDACOutput_initVar: Is modified when this function is called for the 
*  first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void VDACOutput_Start(void)  
{
    /* Hardware initiazation only needs to occure the first time */
    if(VDACOutput_initVar == 0u)
    { 
        VDACOutput_Init();
        VDACOutput_initVar = 1u;
    }

    /* Enable power to DAC */
    VDACOutput_Enable();

    /* Set default value */
    VDACOutput_SetValue(VDACOutput_DEFAULT_DATA); 
}


/*******************************************************************************
* Function Name: VDACOutput_Stop
********************************************************************************
*
* Summary:
*  Powers down DAC to lowest power state.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void VDACOutput_Stop(void) 
{
    /* Disble power to DAC */
    VDACOutput_PWRMGR &= (uint8)(~VDACOutput_ACT_PWR_EN);
    VDACOutput_STBY_PWRMGR &= (uint8)(~VDACOutput_STBY_PWR_EN);

    /* This is a work around for PSoC5A  ,
    this sets VDAC to current mode with output off */
    #if (CY_PSOC5A)
        VDACOutput_backup.data_value = VDACOutput_CR0;
        VDACOutput_CR0 = VDACOutput_CUR_MODE_OUT_OFF;
        VDACOutput_restoreVal = 1u;
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: VDACOutput_SetSpeed
********************************************************************************
*
* Summary:
*  Set DAC speed
*
* Parameters:
*  power: Sets speed value
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void VDACOutput_SetSpeed(uint8 speed) 
{
    /* Clear power mask then write in new value */
    VDACOutput_CR0 &= (uint8)(~VDACOutput_HS_MASK);
    VDACOutput_CR0 |=  (speed & VDACOutput_HS_MASK);
}


/*******************************************************************************
* Function Name: VDACOutput_SetRange
********************************************************************************
*
* Summary:
*  Set one of three current ranges.
*
* Parameters:
*  Range: Sets one of Three valid ranges.
*
* Return:
*  void 
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void VDACOutput_SetRange(uint8 range) 
{
    VDACOutput_CR0 &= (uint8)(~VDACOutput_RANGE_MASK);      /* Clear existing mode */
    VDACOutput_CR0 |= (range & VDACOutput_RANGE_MASK);      /*  Set Range  */
    VDACOutput_DacTrim();
}


/*******************************************************************************
* Function Name: VDACOutput_SetValue
********************************************************************************
*
* Summary:
*  Set 8-bit DAC value
*
* Parameters:  
*  value:  Sets DAC value between 0 and 255.
*
* Return: 
*  void 
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void VDACOutput_SetValue(uint8 value) 
{
    #if (CY_PSOC5A)
        uint8 VDACOutput_intrStatus = CyEnterCriticalSection();
    #endif /* CY_PSOC5A */

    VDACOutput_Data = value;                /*  Set Value  */

    /* PSOC5A requires a double write */
    /* Exit Critical Section */
    #if (CY_PSOC5A)
        VDACOutput_Data = value;
        CyExitCriticalSection(VDACOutput_intrStatus);
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: VDACOutput_DacTrim
********************************************************************************
*
* Summary:
*  Set the trim value for the given range.
*
* Parameters:
*  range:  1V or 4V range.  See constants.
*
* Return:
*  void
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void VDACOutput_DacTrim(void) 
{
    uint8 mode;

    mode = (uint8)((VDACOutput_CR0 & VDACOutput_RANGE_MASK) >> 2) + VDACOutput_TRIM_M7_1V_RNG_OFFSET;
    VDACOutput_TR = CY_GET_XTND_REG8((uint8 *)(VDACOutput_DAC_TRIM_BASE + mode));
}


/* [] END OF FILE */

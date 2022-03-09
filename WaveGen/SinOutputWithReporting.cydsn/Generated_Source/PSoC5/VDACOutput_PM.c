/*******************************************************************************
* File Name: VDACOutput_PM.c  
* Version 1.90
*
* Description:
*  This file provides the power management source code to API for the
*  VDAC8.  
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "VDACOutput.h"

static VDACOutput_backupStruct VDACOutput_backup;


/*******************************************************************************
* Function Name: VDACOutput_SaveConfig
********************************************************************************
* Summary:
*  Save the current user configuration
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void VDACOutput_SaveConfig(void) 
{
    if (!((VDACOutput_CR1 & VDACOutput_SRC_MASK) == VDACOutput_SRC_UDB))
    {
        VDACOutput_backup.data_value = VDACOutput_Data;
    }
}


/*******************************************************************************
* Function Name: VDACOutput_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
*******************************************************************************/
void VDACOutput_RestoreConfig(void) 
{
    if (!((VDACOutput_CR1 & VDACOutput_SRC_MASK) == VDACOutput_SRC_UDB))
    {
        if((VDACOutput_Strobe & VDACOutput_STRB_MASK) == VDACOutput_STRB_EN)
        {
            VDACOutput_Strobe &= (uint8)(~VDACOutput_STRB_MASK);
            VDACOutput_Data = VDACOutput_backup.data_value;
            VDACOutput_Strobe |= VDACOutput_STRB_EN;
        }
        else
        {
            VDACOutput_Data = VDACOutput_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: VDACOutput_Sleep
********************************************************************************
* Summary:
*  Stop and Save the user configuration
*
* Parameters:  
*  void:  
*
* Return: 
*  void
*
* Global variables:
*  VDACOutput_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void VDACOutput_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(VDACOutput_ACT_PWR_EN == (VDACOutput_PWRMGR & VDACOutput_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        VDACOutput_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        VDACOutput_backup.enableState = 0u;
    }
    
    VDACOutput_Stop();
    VDACOutput_SaveConfig();
}


/*******************************************************************************
* Function Name: VDACOutput_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  VDACOutput_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void VDACOutput_Wakeup(void) 
{
    VDACOutput_RestoreConfig();
    
    if(VDACOutput_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        VDACOutput_Enable();

        /* Restore the data register */
        VDACOutput_SetValue(VDACOutput_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */

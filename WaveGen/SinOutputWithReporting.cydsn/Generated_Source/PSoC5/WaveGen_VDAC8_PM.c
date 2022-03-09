/*******************************************************************************
* File Name: WaveGen_VDAC8_PM.c  
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

#include "WaveGen_VDAC8.h"

static WaveGen_VDAC8_backupStruct WaveGen_VDAC8_backup;


/*******************************************************************************
* Function Name: WaveGen_VDAC8_SaveConfig
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
void WaveGen_VDAC8_SaveConfig(void) 
{
    if (!((WaveGen_VDAC8_CR1 & WaveGen_VDAC8_SRC_MASK) == WaveGen_VDAC8_SRC_UDB))
    {
        WaveGen_VDAC8_backup.data_value = WaveGen_VDAC8_Data;
    }
}


/*******************************************************************************
* Function Name: WaveGen_VDAC8_RestoreConfig
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
void WaveGen_VDAC8_RestoreConfig(void) 
{
    if (!((WaveGen_VDAC8_CR1 & WaveGen_VDAC8_SRC_MASK) == WaveGen_VDAC8_SRC_UDB))
    {
        if((WaveGen_VDAC8_Strobe & WaveGen_VDAC8_STRB_MASK) == WaveGen_VDAC8_STRB_EN)
        {
            WaveGen_VDAC8_Strobe &= (uint8)(~WaveGen_VDAC8_STRB_MASK);
            WaveGen_VDAC8_Data = WaveGen_VDAC8_backup.data_value;
            WaveGen_VDAC8_Strobe |= WaveGen_VDAC8_STRB_EN;
        }
        else
        {
            WaveGen_VDAC8_Data = WaveGen_VDAC8_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: WaveGen_VDAC8_Sleep
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
*  WaveGen_VDAC8_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void WaveGen_VDAC8_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(WaveGen_VDAC8_ACT_PWR_EN == (WaveGen_VDAC8_PWRMGR & WaveGen_VDAC8_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        WaveGen_VDAC8_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        WaveGen_VDAC8_backup.enableState = 0u;
    }
    
    WaveGen_VDAC8_Stop();
    WaveGen_VDAC8_SaveConfig();
}


/*******************************************************************************
* Function Name: WaveGen_VDAC8_Wakeup
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
*  WaveGen_VDAC8_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void WaveGen_VDAC8_Wakeup(void) 
{
    WaveGen_VDAC8_RestoreConfig();
    
    if(WaveGen_VDAC8_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        WaveGen_VDAC8_Enable();

        /* Restore the data register */
        WaveGen_VDAC8_SetValue(WaveGen_VDAC8_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */

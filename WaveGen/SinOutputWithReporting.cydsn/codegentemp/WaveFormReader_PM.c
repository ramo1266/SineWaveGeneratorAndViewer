/*******************************************************************************
* File Name: WaveFormReader_PM.c
* Version 3.10
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "WaveFormReader.h"


/***************************************
* Local data allocation
***************************************/

static WaveFormReader_BACKUP_STRUCT  WaveFormReader_backup =
{
    WaveFormReader_DISABLED
};


/*******************************************************************************
* Function Name: WaveFormReader_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void WaveFormReader_SaveConfig(void)
{
    /* All configuration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: WaveFormReader_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void WaveFormReader_RestoreConfig(void)
{
    /* All congiguration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: WaveFormReader_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred routine to prepare the component for sleep.
*  The WaveFormReader_Sleep() routine saves the current component state,
*  then it calls the ADC_Stop() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  WaveFormReader_backup - The structure field 'enableState' is modified
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void WaveFormReader_Sleep(void)
{
    if((WaveFormReader_PWRMGR_SAR_REG  & WaveFormReader_ACT_PWR_SAR_EN) != 0u)
    {
        if((WaveFormReader_SAR_CSR0_REG & WaveFormReader_SAR_SOF_START_CONV) != 0u)
        {
            WaveFormReader_backup.enableState = WaveFormReader_ENABLED | WaveFormReader_STARTED;
        }
        else
        {
            WaveFormReader_backup.enableState = WaveFormReader_ENABLED;
        }
        WaveFormReader_Stop();
    }
    else
    {
        WaveFormReader_backup.enableState = WaveFormReader_DISABLED;
    }
}


/*******************************************************************************
* Function Name: WaveFormReader_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred routine to restore the component to the state when
*  WaveFormReader_Sleep() was called. If the component was enabled before the
*  WaveFormReader_Sleep() function was called, the
*  WaveFormReader_Wakeup() function also re-enables the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  WaveFormReader_backup - The structure field 'enableState' is used to
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void WaveFormReader_Wakeup(void)
{
    if(WaveFormReader_backup.enableState != WaveFormReader_DISABLED)
    {
        WaveFormReader_Enable();
        #if(WaveFormReader_DEFAULT_CONV_MODE != WaveFormReader__HARDWARE_TRIGGER)
            if((WaveFormReader_backup.enableState & WaveFormReader_STARTED) != 0u)
            {
                WaveFormReader_StartConvert();
            }
        #endif /* End WaveFormReader_DEFAULT_CONV_MODE != WaveFormReader__HARDWARE_TRIGGER */
    }
}


/* [] END OF FILE */

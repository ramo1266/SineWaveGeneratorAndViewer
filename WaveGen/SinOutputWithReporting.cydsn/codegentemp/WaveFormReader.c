/*******************************************************************************
* File Name: WaveFormReader.c
* Version 3.10
*
* Description:
*  This file provides the source code to the API for the Successive
*  approximation ADC Component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "CyLib.h"
#include "WaveFormReader.h"

#if(WaveFormReader_DEFAULT_INTERNAL_CLK)
    #include "WaveFormReader_theACLK.h"
#endif /* End WaveFormReader_DEFAULT_INTERNAL_CLK */


/***************************************
* Forward function references
***************************************/
static void WaveFormReader_CalcGain(uint8 resolution);


/***************************************
* Global data allocation
***************************************/
uint8 WaveFormReader_initVar = 0u;
volatile int16 WaveFormReader_offset;
volatile int16 WaveFormReader_countsPerVolt;     /* Obsolete Gain compensation */
volatile int32 WaveFormReader_countsPer10Volt;   /* Gain compensation */
volatile int16 WaveFormReader_shift;


/*******************************************************************************
* Function Name: WaveFormReader_Start
********************************************************************************
*
* Summary:
*  This is the preferred method to begin component operation.
*  WaveFormReader_Start() sets the initVar variable, calls the
*  WaveFormReader_Init() function, and then calls the
*  WaveFormReader_Enable() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  The WaveFormReader_initVar variable is used to indicate when/if initial
*  configuration of this component has happened. The variable is initialized to
*  zero and set to 1 the first time ADC_Start() is called. This allows for
*  component Re-Start without re-initialization in all subsequent calls to the
*  WaveFormReader_Start() routine.
*  If re-initialization of the component is required the variable should be set
*  to zero before call of WaveFormReader_Start() routine, or the user may call
*  WaveFormReader_Init() and WaveFormReader_Enable() as done in the
*  WaveFormReader_Start() routine.
*
* Side Effect:
*  If the initVar variable is already set, this function only calls the
*  WaveFormReader_Enable() function.
*
*******************************************************************************/
void WaveFormReader_Start(void)
{

    /* If not Initialized then initialize all required hardware and software */
    if(WaveFormReader_initVar == 0u)
    {
        WaveFormReader_Init();
        WaveFormReader_initVar = 1u;
    }
    WaveFormReader_Enable();
}


/*******************************************************************************
* Function Name: WaveFormReader_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  WaveFormReader_Start().
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  The WaveFormReader_offset variable is initialized to 0.
*
*******************************************************************************/
void WaveFormReader_Init(void)
{

    /* This is only valid if there is an internal clock */
    #if(WaveFormReader_DEFAULT_INTERNAL_CLK)
        WaveFormReader_theACLK_SetMode(CYCLK_DUTY);
    #endif /* End WaveFormReader_DEFAULT_INTERNAL_CLK */

    #if(WaveFormReader_IRQ_REMOVE == 0u)
        /* Start and set interrupt vector */
        CyIntSetPriority(WaveFormReader_INTC_NUMBER, WaveFormReader_INTC_PRIOR_NUMBER);
        (void)CyIntSetVector(WaveFormReader_INTC_NUMBER, &WaveFormReader_ISR);
    #endif   /* End WaveFormReader_IRQ_REMOVE */

    /* Enable IRQ mode*/
    WaveFormReader_SAR_CSR1_REG |= WaveFormReader_SAR_IRQ_MASK_EN | WaveFormReader_SAR_IRQ_MODE_EDGE;

    /*Set SAR ADC resolution ADC */
    WaveFormReader_SetResolution(WaveFormReader_DEFAULT_RESOLUTION);
    WaveFormReader_offset = 0;
}


/*******************************************************************************
* Function Name: WaveFormReader_Enable
********************************************************************************
*
* Summary:
*  Enables the reference, clock and power for SAR ADC.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void WaveFormReader_Enable(void)
{
    uint8 tmpReg;
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    /* Enable the SAR ADC block in Active Power Mode */
    WaveFormReader_PWRMGR_SAR_REG |= WaveFormReader_ACT_PWR_SAR_EN;

     /* Enable the SAR ADC in Standby Power Mode*/
    WaveFormReader_STBY_PWRMGR_SAR_REG |= WaveFormReader_STBY_PWR_SAR_EN;

    /* This is only valid if there is an internal clock */
    #if(WaveFormReader_DEFAULT_INTERNAL_CLK)
        WaveFormReader_PWRMGR_CLK_REG |= WaveFormReader_ACT_PWR_CLK_EN;
        WaveFormReader_STBY_PWRMGR_CLK_REG |= WaveFormReader_STBY_PWR_CLK_EN;
    #endif /* End WaveFormReader_DEFAULT_INTERNAL_CLK */

    /* Enable VCM buffer and Enable Int Ref Amp */
    tmpReg = WaveFormReader_SAR_CSR3_REG;
    tmpReg |= WaveFormReader_SAR_EN_BUF_VCM_EN;
    /* PD_BUF_VREF is OFF in External reference or Vdda reference mode */
    #if((WaveFormReader_DEFAULT_REFERENCE == WaveFormReader__EXT_REF) || \
        (WaveFormReader_DEFAULT_RANGE == WaveFormReader__VNEG_VDDA_DIFF))
        tmpReg &= (uint8)~WaveFormReader_SAR_EN_BUF_VREF_EN;
    #else /* In INTREF or INTREF Bypassed this buffer is ON */
        tmpReg |= WaveFormReader_SAR_EN_BUF_VREF_EN;
    #endif /* WaveFormReader_DEFAULT_REFERENCE == WaveFormReader__EXT_REF */
    WaveFormReader_SAR_CSR3_REG = tmpReg;

    /* Set reference for ADC */
    #if(WaveFormReader_DEFAULT_RANGE == WaveFormReader__VNEG_VDDA_DIFF)
        #if(WaveFormReader_DEFAULT_REFERENCE == WaveFormReader__EXT_REF)
            WaveFormReader_SAR_CSR6_REG = WaveFormReader_INT_BYPASS_EXT_VREF; /* S2 */
        #else /* Internal Vdda reference or obsolete bypass mode */
            WaveFormReader_SAR_CSR6_REG = WaveFormReader_VDDA_VREF;           /* S7 */
        #endif /* WaveFormReader_DEFAULT_REFERENCE == WaveFormReader__EXT_REF */
    #else  /* Reference goes through internal buffer */
        #if(WaveFormReader_DEFAULT_REFERENCE == WaveFormReader__INT_REF_NOT_BYPASSED)
            WaveFormReader_SAR_CSR6_REG = WaveFormReader_INT_VREF;            /* S3 + S4 */
        #else /* INTREF Bypassed of External */
            WaveFormReader_SAR_CSR6_REG = WaveFormReader_INT_BYPASS_EXT_VREF; /* S2 */
        #endif /* WaveFormReader_DEFAULT_REFERENCE == WaveFormReader__INT_REF_NOT_BYPASSED */
    #endif /* VNEG_VDDA_DIFF */

    /* Low non-overlap delay for sampling clock signals (for 1MSPS) */
    #if(WaveFormReader_HIGH_POWER_PULSE == 0u) /* MinPulseWidth <= 50 ns */
        WaveFormReader_SAR_CSR5_REG &= (uint8)~WaveFormReader_SAR_DLY_INC;
    #else /* Set High non-overlap delay for sampling clock signals (for <500KSPS)*/
        WaveFormReader_SAR_CSR5_REG |= WaveFormReader_SAR_DLY_INC;
    #endif /* WaveFormReader_HIGH_POWER_PULSE == 0u */

    /* Increase comparator latch enable delay by 20%, 
    *  Increase comparator bias current by 30% without impacting delaysDelay 
    *  Default for 1MSPS) 
    */
    #if(WaveFormReader_HIGH_POWER_PULSE == 0u)    /* MinPulseWidth <= 50 ns */
        WaveFormReader_SAR_CSR5_REG |= WaveFormReader_SAR_SEL_CSEL_DFT_CHAR;
    #else /* for <500ksps */
        WaveFormReader_SAR_CSR5_REG &= (uint8)~WaveFormReader_SAR_SEL_CSEL_DFT_CHAR;
    #endif /* WaveFormReader_HIGH_POWER_PULSE == 0u */

    /* Set default power and other configurations for control register 0 in multiple lines */
    WaveFormReader_SAR_CSR0_REG = (uint8)((uint8)WaveFormReader_DEFAULT_POWER << WaveFormReader_SAR_POWER_SHIFT)
    /* SAR_HIZ_CLEAR:   Should not be used for LP */
    #if ((CY_PSOC5LP) || (WaveFormReader_DEFAULT_REFERENCE != WaveFormReader__EXT_REF))
        | WaveFormReader_SAR_HIZ_CLEAR
    #endif /* SAR_HIZ_CLEAR */
    /*Set Convertion mode */
    #if(WaveFormReader_DEFAULT_CONV_MODE != WaveFormReader__FREE_RUNNING)      /* If triggered mode */
        | WaveFormReader_SAR_MX_SOF_UDB           /* source: UDB */
        | WaveFormReader_SAR_SOF_MODE_EDGE        /* Set edge-sensitive sof source */
    #endif /* WaveFormReader_DEFAULT_CONV_MODE */
    ; /* end of multiple line initialization */

    WaveFormReader_SAR_TR0_REG = WaveFormReader_SAR_CAP_TRIM_2;

    /* Enable clock for SAR ADC*/
    WaveFormReader_SAR_CLK_REG |= WaveFormReader_SAR_MX_CLK_EN;

    CyDelayUs(10u); /* The block is ready to use 10 us after the enable signal is set high. */

    #if(WaveFormReader_IRQ_REMOVE == 0u)
        /* Clear a pending interrupt */
        CyIntClearPending(WaveFormReader_INTC_NUMBER);
    #endif   /* End WaveFormReader_IRQ_REMOVE */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: WaveFormReader_Stop
********************************************************************************
*
* Summary:
*  Stops ADC conversions and puts the ADC into its lowest power mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void WaveFormReader_Stop(void)
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    /* Stop all conversions */
    WaveFormReader_SAR_CSR0_REG &= (uint8)~WaveFormReader_SAR_SOF_START_CONV;
    /* Disable the SAR ADC block in Active Power Mode */
    WaveFormReader_PWRMGR_SAR_REG &= (uint8)~WaveFormReader_ACT_PWR_SAR_EN;
    /* Disable the SAR ADC in Standby Power Mode */
    WaveFormReader_STBY_PWRMGR_SAR_REG &= (uint8)~WaveFormReader_STBY_PWR_SAR_EN;

    /* This is only valid if there is an internal clock */
    #if(WaveFormReader_DEFAULT_INTERNAL_CLK)
        WaveFormReader_PWRMGR_CLK_REG &= (uint8)~WaveFormReader_ACT_PWR_CLK_EN;
        WaveFormReader_STBY_PWRMGR_CLK_REG &= (uint8)~WaveFormReader_STBY_PWR_CLK_EN;
    #endif /* End WaveFormReader_DEFAULT_INTERNAL_CLK */

    CyExitCriticalSection(enableInterrupts);

}


/*******************************************************************************
* Function Name: WaveFormReader_SetPower
********************************************************************************
*
* Summary:
*  Sets the operational power of the ADC. You should use the higher power
*  settings with faster clock speeds.
*
* Parameters:
*  power:  Power setting for ADC
*  0 ->    Normal
*  1 ->    Medium power
*  2 ->    1.25 power
*  3 ->    Minimum power.
*
* Return:
*  None.
*
*******************************************************************************/
void WaveFormReader_SetPower(uint8 power)
{
    uint8 tmpReg;

    /* mask off invalid power settings */
    power &= WaveFormReader_SAR_API_POWER_MASK;

    /* Set Power parameter  */
    tmpReg = WaveFormReader_SAR_CSR0_REG & (uint8)~WaveFormReader_SAR_POWER_MASK;
    tmpReg |= (uint8)(power << WaveFormReader_SAR_POWER_SHIFT);
    WaveFormReader_SAR_CSR0_REG = tmpReg;
}


/*******************************************************************************
* Function Name: WaveFormReader_SetResolution
********************************************************************************
*
* Summary:
*  Sets the Relution of the SAR.
*
* Parameters:
*  resolution:
*  12 ->    RES12
*  10 ->    RES10
*  8  ->    RES8
*
* Return:
*  None.
*
* Side Effects:
*  The ADC resolution cannot be changed during a conversion cycle. The
*  recommended best practice is to stop conversions with
*  ADC_StopConvert(), change the resolution, then restart the
*  conversions with ADC_StartConvert().
*  If you decide not to stop conversions before calling this API, you
*  should use ADC_IsEndConversion() to wait until conversion is complete
*  before changing the resolution.
*  If you call ADC_SetResolution() during a conversion, the resolution will
*  not be changed until the current conversion is complete. Data will not be
*  available in the new resolution for another 6 + "New Resolution(in bits)"
*  clock cycles.
*  You may need add a delay of this number of clock cycles after
*  ADC_SetResolution() is called before data is valid again.
*  Affects ADC_CountsTo_Volts(), ADC_CountsTo_mVolts(), and
*  ADC_CountsTo_uVolts() by calculating the correct conversion between ADC
*  counts and the applied input voltage. Calculation depends on resolution,
*  input range, and voltage reference.
*
*******************************************************************************/
void WaveFormReader_SetResolution(uint8 resolution)
{
    uint8 tmpReg;

    /* Set SAR ADC resolution and sample width: 18 conversion cycles at 12bits + 1 gap */
    switch (resolution)
    {
        case (uint8)WaveFormReader__BITS_12:
            tmpReg = WaveFormReader_SAR_RESOLUTION_12BIT | WaveFormReader_SAR_SAMPLE_WIDTH;
            break;
        case (uint8)WaveFormReader__BITS_10:
            tmpReg = WaveFormReader_SAR_RESOLUTION_10BIT | WaveFormReader_SAR_SAMPLE_WIDTH;
            break;
        case (uint8)WaveFormReader__BITS_8:
            tmpReg = WaveFormReader_SAR_RESOLUTION_8BIT | WaveFormReader_SAR_SAMPLE_WIDTH;
            break;
        default:
            tmpReg = WaveFormReader_SAR_RESOLUTION_12BIT | WaveFormReader_SAR_SAMPLE_WIDTH;
            /* Halt CPU in debug mode if resolution is out of valid range */
            CYASSERT(0u != 0u);
            break;
    }
    WaveFormReader_SAR_CSR2_REG = tmpReg;

     /* Calculate gain for convert counts to volts */
    WaveFormReader_CalcGain(resolution);
}


#if(WaveFormReader_DEFAULT_CONV_MODE != WaveFormReader__HARDWARE_TRIGGER)


    /*******************************************************************************
    * Function Name: WaveFormReader_StartConvert
    ********************************************************************************
    *
    * Summary:
    *  Forces the ADC to initiate a conversion. In free-running mode, the ADC runs
    *  continuously. In software trigger mode, the function also acts as a software
    *  version of the SOC and every conversion must be triggered by
    *  WaveFormReader_StartConvert(). This function is not available when the
    *  Hardware Trigger sample mode is selected.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Forces the ADC to initiate a conversion. In Free Running mode, the ADC will
    *  run continuously. In a software trigger mode the function also acts as a
    *  software version of the SOC. Here every conversion has to be triggered by
    *  the routine. This writes into the SOC bit in SAR_CTRL reg.
    *
    * Side Effects:
    *  In a software trigger mode the function switches source for SOF from the
    *  external pin to the internal SOF generation. Application should not call
    *  StartConvert if external source used for SOF.
    *
    *******************************************************************************/
    void WaveFormReader_StartConvert(void)
    {
        #if(WaveFormReader_DEFAULT_CONV_MODE != WaveFormReader__FREE_RUNNING)  /* If software triggered mode */
            WaveFormReader_SAR_CSR0_REG &= (uint8)~WaveFormReader_SAR_MX_SOF_UDB;   /* source: SOF bit */
        #endif /* End WaveFormReader_DEFAULT_CONV_MODE */

        /* Start the conversion */
        WaveFormReader_SAR_CSR0_REG |= WaveFormReader_SAR_SOF_START_CONV;
    }


    /*******************************************************************************
    * Function Name: WaveFormReader_StopConvert
    ********************************************************************************
    *
    * Summary:
    *  Forces the ADC to stop conversions. If a conversion is currently executing,
    *  that conversion will complete, but no further conversions will occur. This
    *  function is not available when the Hardware Trigger sample mode is selected.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Stops ADC conversion in Free Running mode.
    *
    * Side Effects:
    *  In Software Trigger sample mode, this function sets a software version of the
    *  SOC to low level and switches the SOC source to hardware SOC input.
    *
    *******************************************************************************/
    void WaveFormReader_StopConvert(void)
    {
        /* Stop all conversions */
        WaveFormReader_SAR_CSR0_REG &= (uint8)~WaveFormReader_SAR_SOF_START_CONV;

        #if(WaveFormReader_DEFAULT_CONV_MODE != WaveFormReader__FREE_RUNNING)  /* If software triggered mode */
            /* Return source to UDB for hardware SOF signal */
            WaveFormReader_SAR_CSR0_REG |= WaveFormReader_SAR_MX_SOF_UDB;    /* source: UDB */
        #endif /* End WaveFormReader_DEFAULT_CONV_MODE */

    }

#endif /* End WaveFormReader_DEFAULT_CONV_MODE != WaveFormReader__HARDWARE_TRIGGER */


/*******************************************************************************
* Function Name: WaveFormReader_IsEndConversion
********************************************************************************
*
* Summary:
*  Immediately returns the status of the conversion or does not return
*  (blocking) until the conversion completes, depending on the retMode
*  parameter.
*
* Parameters:
*  retMode:  Check conversion return mode.
*   WaveFormReader_RETURN_STATUS: Immediately returns the status. If the
*     value returned is zero, the conversion is not complete, and this function
*     should be retried until a nonzero result is returned.
*   WaveFormReader_WAIT_FOR_RESULT: Does not return a result until the ADC
*     conversion is complete.
*
* Return:
*  (uint8)  0 =>  The ADC is still calculating the last result.
*           1 =>  The last conversion is complete.
*
* Side Effects:
*  This function reads the end of conversion status, which is cleared on read.
*
*******************************************************************************/
uint8 WaveFormReader_IsEndConversion(uint8 retMode)
{
    uint8 status;

    do
    {
        status = WaveFormReader_SAR_CSR1_REG & WaveFormReader_SAR_EOF_1;
    } while ((status != WaveFormReader_SAR_EOF_1) && (retMode == WaveFormReader_WAIT_FOR_RESULT));
    /* If convertion complete, wait until EOF bit released */
    if(status == WaveFormReader_SAR_EOF_1)
    {
        /* wait one ADC clock to let the EOC status bit release */
        CyDelayUs(1u);
        /* Do the unconditional read operation of the CSR1 register to make sure the EOC bit has been cleared */
        CY_GET_REG8(WaveFormReader_SAR_CSR1_PTR);
    }

    return(status);
}


/*******************************************************************************
* Function Name: WaveFormReader_GetResult8
********************************************************************************
*
* Summary:
*  Returns the result of an 8-bit conversion. If the resolution is set greater
*  than 8 bits, the function returns the LSB of the result.
*  WaveFormReader_IsEndConversion() should be called to verify that the data
*   sample is ready.
*
* Parameters:
*  None.
*
* Return:
*  The LSB of the last ADC conversion.
*
* Global Variables:
*  WaveFormReader_shift - used to convert the ADC counts to the 2s
*  compliment form.
*
* Side Effects:
*  Converts the ADC counts to the 2s complement form.
*
*******************************************************************************/
int8 WaveFormReader_GetResult8( void )
{
    return( (int8)WaveFormReader_SAR_WRK0_REG - (int8)WaveFormReader_shift);
}


/*******************************************************************************
* Function Name: WaveFormReader_GetResult16
********************************************************************************
*
* Summary:
*  Returns a 16-bit result for a conversion with a result that has a resolution
*  of 8 to 12 bits.
*  WaveFormReader_IsEndConversion() should be called to verify that the data
*   sample is ready
*
* Parameters:
*  None.
*
* Return:
*  The 16-bit result of the last ADC conversion
*
* Global Variables:
*  WaveFormReader_shift - used to convert the ADC counts to the 2s
*  compliment form.
*
* Side Effects:
*  Converts the ADC counts to the 2s complement form.
*
*******************************************************************************/
int16 WaveFormReader_GetResult16( void )
{
    uint16 res;

    res = CY_GET_REG16(WaveFormReader_SAR_WRK_PTR);

    return( (int16)res - WaveFormReader_shift );
}


/*******************************************************************************
* Function Name: WaveFormReader_SetOffset
********************************************************************************
*
* Summary:
*  Sets the ADC offset, which is used by WaveFormReader_CountsTo_Volts(),
*  WaveFormReader_CountsTo_mVolts(), and WaveFormReader_CountsTo_uVolts()
*  to subtract the offset from the given reading before calculating the voltage
*  conversion.
*
* Parameters:
*  int16: This value is measured when the inputs are shorted or connected to
   the same input voltage.
*
* Return:
*  None.
*
* Global Variables:
*  The WaveFormReader_offset variable modified. This variable is used for
*  offset calibration purpose.
*  Affects the WaveFormReader_CountsTo_Volts,
*  WaveFormReader_CountsTo_mVolts, WaveFormReader_CountsTo_uVolts functions
*  by subtracting the given offset.
*
*******************************************************************************/
void WaveFormReader_SetOffset(int16 offset)
{
    WaveFormReader_offset = offset;
}


/*******************************************************************************
* Function Name: WaveFormReader_CalcGain
********************************************************************************
*
* Summary:
*  This function calculates the ADC gain in counts per 10 volt.
*
* Parameters:
*  uint8: resolution
*
* Return:
*  None.
*
* Global Variables:
*  WaveFormReader_shift variable initialized. This variable is used to
*  convert the ADC counts to the 2s compliment form.
*  WaveFormReader_countsPer10Volt variable initialized. This variable is used
*  for gain calibration purpose.
*
*******************************************************************************/
static void WaveFormReader_CalcGain( uint8 resolution )
{
    int32 counts;
    #if(!((WaveFormReader_DEFAULT_RANGE == WaveFormReader__VSS_TO_VREF) || \
         (WaveFormReader_DEFAULT_RANGE == WaveFormReader__VSSA_TO_VDDA) || \
         (WaveFormReader_DEFAULT_RANGE == WaveFormReader__VSSA_TO_VDAC)) )
        uint16 diff_zero;
    #endif /* End WaveFormReader_DEFAULT_RANGE */

    switch (resolution)
    {
        case (uint8)WaveFormReader__BITS_12:
            counts = (int32)WaveFormReader_SAR_WRK_MAX_12BIT;
            #if(!((WaveFormReader_DEFAULT_RANGE == WaveFormReader__VSS_TO_VREF) || \
                 (WaveFormReader_DEFAULT_RANGE == WaveFormReader__VSSA_TO_VDDA) || \
                 (WaveFormReader_DEFAULT_RANGE == WaveFormReader__VSSA_TO_VDAC)) )
                diff_zero = WaveFormReader_SAR_DIFF_SHIFT;
            #endif /* End WaveFormReader_DEFAULT_RANGE */
            break;
        case (uint8)WaveFormReader__BITS_10:
            counts = (int32)WaveFormReader_SAR_WRK_MAX_10BIT;
            #if(!((WaveFormReader_DEFAULT_RANGE == WaveFormReader__VSS_TO_VREF) || \
                 (WaveFormReader_DEFAULT_RANGE == WaveFormReader__VSSA_TO_VDDA) || \
                 (WaveFormReader_DEFAULT_RANGE == WaveFormReader__VSSA_TO_VDAC)) )
                diff_zero = WaveFormReader_SAR_DIFF_SHIFT >> 2u;
            #endif /* End WaveFormReader_DEFAULT_RANGE */
            break;
        case (uint8)WaveFormReader__BITS_8:
            counts = (int32)WaveFormReader_SAR_WRK_MAX_8BIT;
            #if(!((WaveFormReader_DEFAULT_RANGE == WaveFormReader__VSS_TO_VREF) || \
                 (WaveFormReader_DEFAULT_RANGE == WaveFormReader__VSSA_TO_VDDA) || \
                 (WaveFormReader_DEFAULT_RANGE == WaveFormReader__VSSA_TO_VDAC)) )
                diff_zero = WaveFormReader_SAR_DIFF_SHIFT >> 4u;
            #endif /* End WaveFormReader_DEFAULT_RANGE */
            break;
        default: /* Halt CPU in debug mode if resolution is out of valid range */
            counts = 0;
            #if(!((WaveFormReader_DEFAULT_RANGE == WaveFormReader__VSS_TO_VREF) || \
                 (WaveFormReader_DEFAULT_RANGE == WaveFormReader__VSSA_TO_VDDA) || \
                 (WaveFormReader_DEFAULT_RANGE == WaveFormReader__VSSA_TO_VDAC)) )
                diff_zero = 0u;
            #endif /* End WaveFormReader_DEFAULT_RANGE */
            CYASSERT(0u != 0u);
            break;
    }
    WaveFormReader_countsPerVolt = 0; /* Clear obsolete variable */
    /* Calculate gain in counts per 10 volts with rounding */
    WaveFormReader_countsPer10Volt = (((counts * WaveFormReader_10MV_COUNTS) +
                        WaveFormReader_DEFAULT_REF_VOLTAGE_MV) / (WaveFormReader_DEFAULT_REF_VOLTAGE_MV * 2));

    #if( (WaveFormReader_DEFAULT_RANGE == WaveFormReader__VSS_TO_VREF) || \
         (WaveFormReader_DEFAULT_RANGE == WaveFormReader__VSSA_TO_VDDA) || \
         (WaveFormReader_DEFAULT_RANGE == WaveFormReader__VSSA_TO_VDAC) )
        WaveFormReader_shift = 0;
    #else
        WaveFormReader_shift = diff_zero;
    #endif /* End WaveFormReader_DEFAULT_RANGE */
}


/*******************************************************************************
* Function Name: WaveFormReader_SetGain
********************************************************************************
*
* Summary:
*  Sets the ADC gain in counts per volt for the voltage conversion functions
*  that follow. This value is set by default by the reference and input range
*  settings. It should only be used to further calibrate the ADC with a known
*  input or if the ADC is using an external reference.
*
* Parameters:
*  int16 adcGain counts per volt
*
* Return:
*  None.
*
* Global Variables:
*  WaveFormReader_countsPer10Volt variable modified. This variable is used
*  for gain calibration purpose.
*
*******************************************************************************/
void WaveFormReader_SetGain(int16 adcGain)
{
    WaveFormReader_countsPer10Volt = (int32)adcGain * 10;
}


/*******************************************************************************
* Function Name: WaveFormReader_SetScaledGain
********************************************************************************
*
* Summary:
*  Sets the ADC gain in counts per 10 volt for the voltage conversion functions
*  that follow. This value is set by default by the reference and input range
*  settings. It should only be used to further calibrate the ADC with a known
*  input or if the ADC is using an external reference.
*
* Parameters:
*  int32 adcGain  counts per 10 volt
*
* Return:
*  None.
*
* Global Variables:
*  WaveFormReader_countsPer10Volt variable modified. This variable is used
*  for gain calibration purpose.
*
*******************************************************************************/
void WaveFormReader_SetScaledGain(int32 adcGain)
{
    WaveFormReader_countsPer10Volt = adcGain;
}


/*******************************************************************************
* Function Name: WaveFormReader_CountsTo_mVolts
********************************************************************************
*
* Summary:
*  Converts the ADC output to millivolts as a 16-bit integer.
*
* Parameters:
*  int16 adcCounts:  Result from the ADC conversion
*
* Return:
*  int16 Result in mVolts
*
* Global Variables:
*  WaveFormReader_offset variable used.
*  WaveFormReader_countsPer10Volt variable used.
*
*******************************************************************************/
int16 WaveFormReader_CountsTo_mVolts(int16 adcCounts)
{
    int16 mVolts;
    int32 countsPer10Volt;

    if(WaveFormReader_countsPerVolt != 0)
    {   /* Support obsolete method */
        countsPer10Volt = (int32)WaveFormReader_countsPerVolt * 10;
    }
    else
    {
        countsPer10Volt = WaveFormReader_countsPer10Volt;
    }

    /* Subtract ADC offset */
    adcCounts -= WaveFormReader_offset;
    /* Convert to millivolts with rounding */
    mVolts = (int16)( (( (int32)adcCounts * WaveFormReader_10MV_COUNTS ) + ( (adcCounts > 0) ?
                       (countsPer10Volt / 2) : (-(countsPer10Volt / 2)) )) / countsPer10Volt);

    return( mVolts );
}


/*******************************************************************************
* Function Name: WaveFormReader_CountsTo_uVolts
********************************************************************************
*
* Summary:
*  Converts the ADC output to microvolts as a 32-bit integer.
*
* Parameters:
*  int16 adcCounts: Result from the ADC conversion
*
* Return:
*  int32 Result in micro Volts
*
* Global Variables:
*  WaveFormReader_offset variable used.
*  WaveFormReader_countsPer10Volt used to convert ADC counts to uVolts.
*
*******************************************************************************/
int32 WaveFormReader_CountsTo_uVolts(int16 adcCounts)
{

    int64 uVolts;
    int32 countsPer10Volt;

    if(WaveFormReader_countsPerVolt != 0)
    {   /* Support obsolete method */
        countsPer10Volt = (int32)WaveFormReader_countsPerVolt * 10;
    }
    else
    {
        countsPer10Volt = WaveFormReader_countsPer10Volt;
    }

    /* Subtract ADC offset */
    adcCounts -= WaveFormReader_offset;
    /* To convert adcCounts to microVolts it is required to be multiplied
    *  on 10 million and later divide on gain in counts per 10V.
    */
    uVolts = (( (int64)adcCounts * WaveFormReader_10UV_COUNTS ) / countsPer10Volt);

    return((int32) uVolts );
}


/*******************************************************************************
* Function Name: WaveFormReader_CountsTo_Volts
********************************************************************************
*
* Summary:
*  Converts the ADC output to volts as a floating-point number.
*
* Parameters:
*  int16 adcCounts: Result from the ADC conversion
*
* Return:
*  float Result in Volts
*
* Global Variables:
*  WaveFormReader_offset variable used.
*  WaveFormReader_countsPer10Volt used to convert ADC counts to Volts.
*
*******************************************************************************/
float32 WaveFormReader_CountsTo_Volts(int16 adcCounts)
{
    float32 volts;
    int32 countsPer10Volt;

    if(WaveFormReader_countsPerVolt != 0)
    {   /* Support obsolete method */
        countsPer10Volt = (int32)WaveFormReader_countsPerVolt * 10;
    }
    else
    {
        countsPer10Volt = WaveFormReader_countsPer10Volt;
    }

    /* Subtract ADC offset */
    adcCounts -= WaveFormReader_offset;

    volts = ((float32)adcCounts * WaveFormReader_10V_COUNTS) / (float32)countsPer10Volt;

    return( volts );
}


/* [] END OF FILE */

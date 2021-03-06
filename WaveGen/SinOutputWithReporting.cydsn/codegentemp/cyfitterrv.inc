;
; File Name: cyfitterrv.inc
; 
; PSoC Creator  4.2
;
; Description:
; 
;
;-------------------------------------------------------------------------------
; Copyright (c) 2007-2018 Cypress Semiconductor.  All rights reserved.
; You may use this file only in accordance with the license, terms, conditions, 
; disclaimers, and limitations in the end user license agreement accompanying 
; the software package with which this file was provided.
;-------------------------------------------------------------------------------

    IF :LNOT::DEF:INCLUDED_CYFITTERRV_INC
INCLUDED_CYFITTERRV_INC EQU 1
    GET cydevicerv.inc
    GET cydevicerv_trm.inc

; USBCOMM
USBCOMM_arb_int__INTC_CLR_EN_REG EQU CYREG_NVIC_CLRENA0
USBCOMM_arb_int__INTC_CLR_PD_REG EQU CYREG_NVIC_CLRPEND0
USBCOMM_arb_int__INTC_MASK EQU 0x400000
USBCOMM_arb_int__INTC_NUMBER EQU 22
USBCOMM_arb_int__INTC_PRIOR_NUM EQU 7
USBCOMM_arb_int__INTC_PRIOR_REG EQU CYREG_NVIC_PRI_22
USBCOMM_arb_int__INTC_SET_EN_REG EQU CYREG_NVIC_SETENA0
USBCOMM_arb_int__INTC_SET_PD_REG EQU CYREG_NVIC_SETPEND0
USBCOMM_bus_reset__INTC_CLR_EN_REG EQU CYREG_NVIC_CLRENA0
USBCOMM_bus_reset__INTC_CLR_PD_REG EQU CYREG_NVIC_CLRPEND0
USBCOMM_bus_reset__INTC_MASK EQU 0x800000
USBCOMM_bus_reset__INTC_NUMBER EQU 23
USBCOMM_bus_reset__INTC_PRIOR_NUM EQU 7
USBCOMM_bus_reset__INTC_PRIOR_REG EQU CYREG_NVIC_PRI_23
USBCOMM_bus_reset__INTC_SET_EN_REG EQU CYREG_NVIC_SETENA0
USBCOMM_bus_reset__INTC_SET_PD_REG EQU CYREG_NVIC_SETPEND0
USBCOMM_Dm__0__INTTYPE EQU CYREG_PICU15_INTTYPE7
USBCOMM_Dm__0__MASK EQU 0x80
USBCOMM_Dm__0__PC EQU CYREG_IO_PC_PRT15_7_6_PC1
USBCOMM_Dm__0__PORT EQU 15
USBCOMM_Dm__0__SHIFT EQU 7
USBCOMM_Dm__AG EQU CYREG_PRT15_AG
USBCOMM_Dm__AMUX EQU CYREG_PRT15_AMUX
USBCOMM_Dm__BIE EQU CYREG_PRT15_BIE
USBCOMM_Dm__BIT_MASK EQU CYREG_PRT15_BIT_MASK
USBCOMM_Dm__BYP EQU CYREG_PRT15_BYP
USBCOMM_Dm__CTL EQU CYREG_PRT15_CTL
USBCOMM_Dm__DM0 EQU CYREG_PRT15_DM0
USBCOMM_Dm__DM1 EQU CYREG_PRT15_DM1
USBCOMM_Dm__DM2 EQU CYREG_PRT15_DM2
USBCOMM_Dm__DR EQU CYREG_PRT15_DR
USBCOMM_Dm__INP_DIS EQU CYREG_PRT15_INP_DIS
USBCOMM_Dm__INTTYPE_BASE EQU CYDEV_PICU_INTTYPE_PICU15_BASE
USBCOMM_Dm__LCD_COM_SEG EQU CYREG_PRT15_LCD_COM_SEG
USBCOMM_Dm__LCD_EN EQU CYREG_PRT15_LCD_EN
USBCOMM_Dm__MASK EQU 0x80
USBCOMM_Dm__PORT EQU 15
USBCOMM_Dm__PRT EQU CYREG_PRT15_PRT
USBCOMM_Dm__PRTDSI__CAPS_SEL EQU CYREG_PRT15_CAPS_SEL
USBCOMM_Dm__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT15_DBL_SYNC_IN
USBCOMM_Dm__PRTDSI__OE_SEL0 EQU CYREG_PRT15_OE_SEL0
USBCOMM_Dm__PRTDSI__OE_SEL1 EQU CYREG_PRT15_OE_SEL1
USBCOMM_Dm__PRTDSI__OUT_SEL0 EQU CYREG_PRT15_OUT_SEL0
USBCOMM_Dm__PRTDSI__OUT_SEL1 EQU CYREG_PRT15_OUT_SEL1
USBCOMM_Dm__PRTDSI__SYNC_OUT EQU CYREG_PRT15_SYNC_OUT
USBCOMM_Dm__PS EQU CYREG_PRT15_PS
USBCOMM_Dm__SHIFT EQU 7
USBCOMM_Dm__SLW EQU CYREG_PRT15_SLW
USBCOMM_Dp__0__INTTYPE EQU CYREG_PICU15_INTTYPE6
USBCOMM_Dp__0__MASK EQU 0x40
USBCOMM_Dp__0__PC EQU CYREG_IO_PC_PRT15_7_6_PC0
USBCOMM_Dp__0__PORT EQU 15
USBCOMM_Dp__0__SHIFT EQU 6
USBCOMM_Dp__AG EQU CYREG_PRT15_AG
USBCOMM_Dp__AMUX EQU CYREG_PRT15_AMUX
USBCOMM_Dp__BIE EQU CYREG_PRT15_BIE
USBCOMM_Dp__BIT_MASK EQU CYREG_PRT15_BIT_MASK
USBCOMM_Dp__BYP EQU CYREG_PRT15_BYP
USBCOMM_Dp__CTL EQU CYREG_PRT15_CTL
USBCOMM_Dp__DM0 EQU CYREG_PRT15_DM0
USBCOMM_Dp__DM1 EQU CYREG_PRT15_DM1
USBCOMM_Dp__DM2 EQU CYREG_PRT15_DM2
USBCOMM_Dp__DR EQU CYREG_PRT15_DR
USBCOMM_Dp__INP_DIS EQU CYREG_PRT15_INP_DIS
USBCOMM_Dp__INTSTAT EQU CYREG_PICU15_INTSTAT
USBCOMM_Dp__INTTYPE_BASE EQU CYDEV_PICU_INTTYPE_PICU15_BASE
USBCOMM_Dp__LCD_COM_SEG EQU CYREG_PRT15_LCD_COM_SEG
USBCOMM_Dp__LCD_EN EQU CYREG_PRT15_LCD_EN
USBCOMM_Dp__MASK EQU 0x40
USBCOMM_Dp__PORT EQU 15
USBCOMM_Dp__PRT EQU CYREG_PRT15_PRT
USBCOMM_Dp__PRTDSI__CAPS_SEL EQU CYREG_PRT15_CAPS_SEL
USBCOMM_Dp__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT15_DBL_SYNC_IN
USBCOMM_Dp__PRTDSI__OE_SEL0 EQU CYREG_PRT15_OE_SEL0
USBCOMM_Dp__PRTDSI__OE_SEL1 EQU CYREG_PRT15_OE_SEL1
USBCOMM_Dp__PRTDSI__OUT_SEL0 EQU CYREG_PRT15_OUT_SEL0
USBCOMM_Dp__PRTDSI__OUT_SEL1 EQU CYREG_PRT15_OUT_SEL1
USBCOMM_Dp__PRTDSI__SYNC_OUT EQU CYREG_PRT15_SYNC_OUT
USBCOMM_Dp__PS EQU CYREG_PRT15_PS
USBCOMM_Dp__SHIFT EQU 6
USBCOMM_Dp__SLW EQU CYREG_PRT15_SLW
USBCOMM_Dp__SNAP EQU CYREG_PICU_15_SNAP_15
USBCOMM_dp_int__INTC_CLR_EN_REG EQU CYREG_NVIC_CLRENA0
USBCOMM_dp_int__INTC_CLR_PD_REG EQU CYREG_NVIC_CLRPEND0
USBCOMM_dp_int__INTC_MASK EQU 0x1000
USBCOMM_dp_int__INTC_NUMBER EQU 12
USBCOMM_dp_int__INTC_PRIOR_NUM EQU 7
USBCOMM_dp_int__INTC_PRIOR_REG EQU CYREG_NVIC_PRI_12
USBCOMM_dp_int__INTC_SET_EN_REG EQU CYREG_NVIC_SETENA0
USBCOMM_dp_int__INTC_SET_PD_REG EQU CYREG_NVIC_SETPEND0
USBCOMM_ep_0__INTC_CLR_EN_REG EQU CYREG_NVIC_CLRENA0
USBCOMM_ep_0__INTC_CLR_PD_REG EQU CYREG_NVIC_CLRPEND0
USBCOMM_ep_0__INTC_MASK EQU 0x1000000
USBCOMM_ep_0__INTC_NUMBER EQU 24
USBCOMM_ep_0__INTC_PRIOR_NUM EQU 7
USBCOMM_ep_0__INTC_PRIOR_REG EQU CYREG_NVIC_PRI_24
USBCOMM_ep_0__INTC_SET_EN_REG EQU CYREG_NVIC_SETENA0
USBCOMM_ep_0__INTC_SET_PD_REG EQU CYREG_NVIC_SETPEND0
USBCOMM_ep_1__INTC_CLR_EN_REG EQU CYREG_NVIC_CLRENA0
USBCOMM_ep_1__INTC_CLR_PD_REG EQU CYREG_NVIC_CLRPEND0
USBCOMM_ep_1__INTC_MASK EQU 0x01
USBCOMM_ep_1__INTC_NUMBER EQU 0
USBCOMM_ep_1__INTC_PRIOR_NUM EQU 7
USBCOMM_ep_1__INTC_PRIOR_REG EQU CYREG_NVIC_PRI_0
USBCOMM_ep_1__INTC_SET_EN_REG EQU CYREG_NVIC_SETENA0
USBCOMM_ep_1__INTC_SET_PD_REG EQU CYREG_NVIC_SETPEND0
USBCOMM_ep_2__INTC_CLR_EN_REG EQU CYREG_NVIC_CLRENA0
USBCOMM_ep_2__INTC_CLR_PD_REG EQU CYREG_NVIC_CLRPEND0
USBCOMM_ep_2__INTC_MASK EQU 0x02
USBCOMM_ep_2__INTC_NUMBER EQU 1
USBCOMM_ep_2__INTC_PRIOR_NUM EQU 7
USBCOMM_ep_2__INTC_PRIOR_REG EQU CYREG_NVIC_PRI_1
USBCOMM_ep_2__INTC_SET_EN_REG EQU CYREG_NVIC_SETENA0
USBCOMM_ep_2__INTC_SET_PD_REG EQU CYREG_NVIC_SETPEND0
USBCOMM_sof_int__INTC_CLR_EN_REG EQU CYREG_NVIC_CLRENA0
USBCOMM_sof_int__INTC_CLR_PD_REG EQU CYREG_NVIC_CLRPEND0
USBCOMM_sof_int__INTC_MASK EQU 0x200000
USBCOMM_sof_int__INTC_NUMBER EQU 21
USBCOMM_sof_int__INTC_PRIOR_NUM EQU 7
USBCOMM_sof_int__INTC_PRIOR_REG EQU CYREG_NVIC_PRI_21
USBCOMM_sof_int__INTC_SET_EN_REG EQU CYREG_NVIC_SETENA0
USBCOMM_sof_int__INTC_SET_PD_REG EQU CYREG_NVIC_SETPEND0
USBCOMM_USB__ARB_CFG EQU CYREG_USB_ARB_CFG
USBCOMM_USB__ARB_EP1_CFG EQU CYREG_USB_ARB_EP1_CFG
USBCOMM_USB__ARB_EP1_INT_EN EQU CYREG_USB_ARB_EP1_INT_EN
USBCOMM_USB__ARB_EP1_SR EQU CYREG_USB_ARB_EP1_SR
USBCOMM_USB__ARB_EP2_CFG EQU CYREG_USB_ARB_EP2_CFG
USBCOMM_USB__ARB_EP2_INT_EN EQU CYREG_USB_ARB_EP2_INT_EN
USBCOMM_USB__ARB_EP2_SR EQU CYREG_USB_ARB_EP2_SR
USBCOMM_USB__ARB_EP3_CFG EQU CYREG_USB_ARB_EP3_CFG
USBCOMM_USB__ARB_EP3_INT_EN EQU CYREG_USB_ARB_EP3_INT_EN
USBCOMM_USB__ARB_EP3_SR EQU CYREG_USB_ARB_EP3_SR
USBCOMM_USB__ARB_EP4_CFG EQU CYREG_USB_ARB_EP4_CFG
USBCOMM_USB__ARB_EP4_INT_EN EQU CYREG_USB_ARB_EP4_INT_EN
USBCOMM_USB__ARB_EP4_SR EQU CYREG_USB_ARB_EP4_SR
USBCOMM_USB__ARB_EP5_CFG EQU CYREG_USB_ARB_EP5_CFG
USBCOMM_USB__ARB_EP5_INT_EN EQU CYREG_USB_ARB_EP5_INT_EN
USBCOMM_USB__ARB_EP5_SR EQU CYREG_USB_ARB_EP5_SR
USBCOMM_USB__ARB_EP6_CFG EQU CYREG_USB_ARB_EP6_CFG
USBCOMM_USB__ARB_EP6_INT_EN EQU CYREG_USB_ARB_EP6_INT_EN
USBCOMM_USB__ARB_EP6_SR EQU CYREG_USB_ARB_EP6_SR
USBCOMM_USB__ARB_EP7_CFG EQU CYREG_USB_ARB_EP7_CFG
USBCOMM_USB__ARB_EP7_INT_EN EQU CYREG_USB_ARB_EP7_INT_EN
USBCOMM_USB__ARB_EP7_SR EQU CYREG_USB_ARB_EP7_SR
USBCOMM_USB__ARB_EP8_CFG EQU CYREG_USB_ARB_EP8_CFG
USBCOMM_USB__ARB_EP8_INT_EN EQU CYREG_USB_ARB_EP8_INT_EN
USBCOMM_USB__ARB_EP8_SR EQU CYREG_USB_ARB_EP8_SR
USBCOMM_USB__ARB_INT_EN EQU CYREG_USB_ARB_INT_EN
USBCOMM_USB__ARB_INT_SR EQU CYREG_USB_ARB_INT_SR
USBCOMM_USB__ARB_RW1_DR EQU CYREG_USB_ARB_RW1_DR
USBCOMM_USB__ARB_RW1_RA EQU CYREG_USB_ARB_RW1_RA
USBCOMM_USB__ARB_RW1_RA_MSB EQU CYREG_USB_ARB_RW1_RA_MSB
USBCOMM_USB__ARB_RW1_WA EQU CYREG_USB_ARB_RW1_WA
USBCOMM_USB__ARB_RW1_WA_MSB EQU CYREG_USB_ARB_RW1_WA_MSB
USBCOMM_USB__ARB_RW2_DR EQU CYREG_USB_ARB_RW2_DR
USBCOMM_USB__ARB_RW2_RA EQU CYREG_USB_ARB_RW2_RA
USBCOMM_USB__ARB_RW2_RA_MSB EQU CYREG_USB_ARB_RW2_RA_MSB
USBCOMM_USB__ARB_RW2_WA EQU CYREG_USB_ARB_RW2_WA
USBCOMM_USB__ARB_RW2_WA_MSB EQU CYREG_USB_ARB_RW2_WA_MSB
USBCOMM_USB__ARB_RW3_DR EQU CYREG_USB_ARB_RW3_DR
USBCOMM_USB__ARB_RW3_RA EQU CYREG_USB_ARB_RW3_RA
USBCOMM_USB__ARB_RW3_RA_MSB EQU CYREG_USB_ARB_RW3_RA_MSB
USBCOMM_USB__ARB_RW3_WA EQU CYREG_USB_ARB_RW3_WA
USBCOMM_USB__ARB_RW3_WA_MSB EQU CYREG_USB_ARB_RW3_WA_MSB
USBCOMM_USB__ARB_RW4_DR EQU CYREG_USB_ARB_RW4_DR
USBCOMM_USB__ARB_RW4_RA EQU CYREG_USB_ARB_RW4_RA
USBCOMM_USB__ARB_RW4_RA_MSB EQU CYREG_USB_ARB_RW4_RA_MSB
USBCOMM_USB__ARB_RW4_WA EQU CYREG_USB_ARB_RW4_WA
USBCOMM_USB__ARB_RW4_WA_MSB EQU CYREG_USB_ARB_RW4_WA_MSB
USBCOMM_USB__ARB_RW5_DR EQU CYREG_USB_ARB_RW5_DR
USBCOMM_USB__ARB_RW5_RA EQU CYREG_USB_ARB_RW5_RA
USBCOMM_USB__ARB_RW5_RA_MSB EQU CYREG_USB_ARB_RW5_RA_MSB
USBCOMM_USB__ARB_RW5_WA EQU CYREG_USB_ARB_RW5_WA
USBCOMM_USB__ARB_RW5_WA_MSB EQU CYREG_USB_ARB_RW5_WA_MSB
USBCOMM_USB__ARB_RW6_DR EQU CYREG_USB_ARB_RW6_DR
USBCOMM_USB__ARB_RW6_RA EQU CYREG_USB_ARB_RW6_RA
USBCOMM_USB__ARB_RW6_RA_MSB EQU CYREG_USB_ARB_RW6_RA_MSB
USBCOMM_USB__ARB_RW6_WA EQU CYREG_USB_ARB_RW6_WA
USBCOMM_USB__ARB_RW6_WA_MSB EQU CYREG_USB_ARB_RW6_WA_MSB
USBCOMM_USB__ARB_RW7_DR EQU CYREG_USB_ARB_RW7_DR
USBCOMM_USB__ARB_RW7_RA EQU CYREG_USB_ARB_RW7_RA
USBCOMM_USB__ARB_RW7_RA_MSB EQU CYREG_USB_ARB_RW7_RA_MSB
USBCOMM_USB__ARB_RW7_WA EQU CYREG_USB_ARB_RW7_WA
USBCOMM_USB__ARB_RW7_WA_MSB EQU CYREG_USB_ARB_RW7_WA_MSB
USBCOMM_USB__ARB_RW8_DR EQU CYREG_USB_ARB_RW8_DR
USBCOMM_USB__ARB_RW8_RA EQU CYREG_USB_ARB_RW8_RA
USBCOMM_USB__ARB_RW8_RA_MSB EQU CYREG_USB_ARB_RW8_RA_MSB
USBCOMM_USB__ARB_RW8_WA EQU CYREG_USB_ARB_RW8_WA
USBCOMM_USB__ARB_RW8_WA_MSB EQU CYREG_USB_ARB_RW8_WA_MSB
USBCOMM_USB__BUF_SIZE EQU CYREG_USB_BUF_SIZE
USBCOMM_USB__BUS_RST_CNT EQU CYREG_USB_BUS_RST_CNT
USBCOMM_USB__CR0 EQU CYREG_USB_CR0
USBCOMM_USB__CR1 EQU CYREG_USB_CR1
USBCOMM_USB__CWA EQU CYREG_USB_CWA
USBCOMM_USB__CWA_MSB EQU CYREG_USB_CWA_MSB
USBCOMM_USB__DMA_THRES EQU CYREG_USB_DMA_THRES
USBCOMM_USB__DMA_THRES_MSB EQU CYREG_USB_DMA_THRES_MSB
USBCOMM_USB__DYN_RECONFIG EQU CYREG_USB_DYN_RECONFIG
USBCOMM_USB__EP_ACTIVE EQU CYREG_USB_EP_ACTIVE
USBCOMM_USB__EP_TYPE EQU CYREG_USB_EP_TYPE
USBCOMM_USB__EP0_CNT EQU CYREG_USB_EP0_CNT
USBCOMM_USB__EP0_CR EQU CYREG_USB_EP0_CR
USBCOMM_USB__EP0_DR0 EQU CYREG_USB_EP0_DR0
USBCOMM_USB__EP0_DR1 EQU CYREG_USB_EP0_DR1
USBCOMM_USB__EP0_DR2 EQU CYREG_USB_EP0_DR2
USBCOMM_USB__EP0_DR3 EQU CYREG_USB_EP0_DR3
USBCOMM_USB__EP0_DR4 EQU CYREG_USB_EP0_DR4
USBCOMM_USB__EP0_DR5 EQU CYREG_USB_EP0_DR5
USBCOMM_USB__EP0_DR6 EQU CYREG_USB_EP0_DR6
USBCOMM_USB__EP0_DR7 EQU CYREG_USB_EP0_DR7
USBCOMM_USB__MEM_DATA EQU CYREG_USB_MEM_DATA_MBASE
USBCOMM_USB__PM_ACT_CFG EQU CYREG_PM_ACT_CFG5
USBCOMM_USB__PM_ACT_MSK EQU 0x01
USBCOMM_USB__PM_STBY_CFG EQU CYREG_PM_STBY_CFG5
USBCOMM_USB__PM_STBY_MSK EQU 0x01
USBCOMM_USB__SIE_EP_INT_EN EQU CYREG_USB_SIE_EP_INT_EN
USBCOMM_USB__SIE_EP_INT_SR EQU CYREG_USB_SIE_EP_INT_SR
USBCOMM_USB__SIE_EP1_CNT0 EQU CYREG_USB_SIE_EP1_CNT0
USBCOMM_USB__SIE_EP1_CNT1 EQU CYREG_USB_SIE_EP1_CNT1
USBCOMM_USB__SIE_EP1_CR0 EQU CYREG_USB_SIE_EP1_CR0
USBCOMM_USB__SIE_EP2_CNT0 EQU CYREG_USB_SIE_EP2_CNT0
USBCOMM_USB__SIE_EP2_CNT1 EQU CYREG_USB_SIE_EP2_CNT1
USBCOMM_USB__SIE_EP2_CR0 EQU CYREG_USB_SIE_EP2_CR0
USBCOMM_USB__SIE_EP3_CNT0 EQU CYREG_USB_SIE_EP3_CNT0
USBCOMM_USB__SIE_EP3_CNT1 EQU CYREG_USB_SIE_EP3_CNT1
USBCOMM_USB__SIE_EP3_CR0 EQU CYREG_USB_SIE_EP3_CR0
USBCOMM_USB__SIE_EP4_CNT0 EQU CYREG_USB_SIE_EP4_CNT0
USBCOMM_USB__SIE_EP4_CNT1 EQU CYREG_USB_SIE_EP4_CNT1
USBCOMM_USB__SIE_EP4_CR0 EQU CYREG_USB_SIE_EP4_CR0
USBCOMM_USB__SIE_EP5_CNT0 EQU CYREG_USB_SIE_EP5_CNT0
USBCOMM_USB__SIE_EP5_CNT1 EQU CYREG_USB_SIE_EP5_CNT1
USBCOMM_USB__SIE_EP5_CR0 EQU CYREG_USB_SIE_EP5_CR0
USBCOMM_USB__SIE_EP6_CNT0 EQU CYREG_USB_SIE_EP6_CNT0
USBCOMM_USB__SIE_EP6_CNT1 EQU CYREG_USB_SIE_EP6_CNT1
USBCOMM_USB__SIE_EP6_CR0 EQU CYREG_USB_SIE_EP6_CR0
USBCOMM_USB__SIE_EP7_CNT0 EQU CYREG_USB_SIE_EP7_CNT0
USBCOMM_USB__SIE_EP7_CNT1 EQU CYREG_USB_SIE_EP7_CNT1
USBCOMM_USB__SIE_EP7_CR0 EQU CYREG_USB_SIE_EP7_CR0
USBCOMM_USB__SIE_EP8_CNT0 EQU CYREG_USB_SIE_EP8_CNT0
USBCOMM_USB__SIE_EP8_CNT1 EQU CYREG_USB_SIE_EP8_CNT1
USBCOMM_USB__SIE_EP8_CR0 EQU CYREG_USB_SIE_EP8_CR0
USBCOMM_USB__SOF0 EQU CYREG_USB_SOF0
USBCOMM_USB__SOF1 EQU CYREG_USB_SOF1
USBCOMM_USB__USB_CLK_EN EQU CYREG_USB_USB_CLK_EN
USBCOMM_USB__USBIO_CR0 EQU CYREG_USB_USBIO_CR0
USBCOMM_USB__USBIO_CR1 EQU CYREG_USB_USBIO_CR1

; WaveGen
WaveGen_VDAC8_viDAC8__CR0 EQU CYREG_DAC3_CR0
WaveGen_VDAC8_viDAC8__CR1 EQU CYREG_DAC3_CR1
WaveGen_VDAC8_viDAC8__D EQU CYREG_DAC3_D
WaveGen_VDAC8_viDAC8__PM_ACT_CFG EQU CYREG_PM_ACT_CFG8
WaveGen_VDAC8_viDAC8__PM_ACT_MSK EQU 0x08
WaveGen_VDAC8_viDAC8__PM_STBY_CFG EQU CYREG_PM_STBY_CFG8
WaveGen_VDAC8_viDAC8__PM_STBY_MSK EQU 0x08
WaveGen_VDAC8_viDAC8__STROBE EQU CYREG_DAC3_STROBE
WaveGen_VDAC8_viDAC8__SW0 EQU CYREG_DAC3_SW0
WaveGen_VDAC8_viDAC8__SW2 EQU CYREG_DAC3_SW2
WaveGen_VDAC8_viDAC8__SW3 EQU CYREG_DAC3_SW3
WaveGen_VDAC8_viDAC8__SW4 EQU CYREG_DAC3_SW4
WaveGen_VDAC8_viDAC8__TR EQU CYREG_DAC3_TR
WaveGen_VDAC8_viDAC8__TRIM__M1 EQU CYREG_FLSHID_CUST_TABLES_DAC3_M1
WaveGen_VDAC8_viDAC8__TRIM__M2 EQU CYREG_FLSHID_CUST_TABLES_DAC3_M2
WaveGen_VDAC8_viDAC8__TRIM__M3 EQU CYREG_FLSHID_CUST_TABLES_DAC3_M3
WaveGen_VDAC8_viDAC8__TRIM__M4 EQU CYREG_FLSHID_CUST_TABLES_DAC3_M4
WaveGen_VDAC8_viDAC8__TRIM__M5 EQU CYREG_FLSHID_CUST_TABLES_DAC3_M5
WaveGen_VDAC8_viDAC8__TRIM__M6 EQU CYREG_FLSHID_CUST_TABLES_DAC3_M6
WaveGen_VDAC8_viDAC8__TRIM__M7 EQU CYREG_FLSHID_CUST_TABLES_DAC3_M7
WaveGen_VDAC8_viDAC8__TRIM__M8 EQU CYREG_FLSHID_CUST_TABLES_DAC3_M8
WaveGen_VDAC8_viDAC8__TST EQU CYREG_DAC3_TST
WaveGen_Wave1_DMA__DRQ_CTL EQU CYREG_IDMUX_DRQ_CTL0
WaveGen_Wave1_DMA__DRQ_NUMBER EQU 0
WaveGen_Wave1_DMA__NUMBEROF_TDS EQU 0
WaveGen_Wave1_DMA__PRIORITY EQU 2
WaveGen_Wave1_DMA__TERMIN_EN EQU 0
WaveGen_Wave1_DMA__TERMIN_SEL EQU 0
WaveGen_Wave1_DMA__TERMOUT0_EN EQU 0
WaveGen_Wave1_DMA__TERMOUT0_SEL EQU 0
WaveGen_Wave1_DMA__TERMOUT1_EN EQU 0
WaveGen_Wave1_DMA__TERMOUT1_SEL EQU 0
WaveGen_Wave2_DMA__DRQ_CTL EQU CYREG_IDMUX_DRQ_CTL0
WaveGen_Wave2_DMA__DRQ_NUMBER EQU 1
WaveGen_Wave2_DMA__NUMBEROF_TDS EQU 0
WaveGen_Wave2_DMA__PRIORITY EQU 2
WaveGen_Wave2_DMA__TERMIN_EN EQU 0
WaveGen_Wave2_DMA__TERMIN_SEL EQU 0
WaveGen_Wave2_DMA__TERMOUT0_EN EQU 0
WaveGen_Wave2_DMA__TERMOUT0_SEL EQU 0
WaveGen_Wave2_DMA__TERMOUT1_EN EQU 0
WaveGen_Wave2_DMA__TERMOUT1_SEL EQU 0

; VAnalogOut
VAnalogOut__0__INTTYPE EQU CYREG_PICU0_INTTYPE0
VAnalogOut__0__MASK EQU 0x01
VAnalogOut__0__PC EQU CYREG_PRT0_PC0
VAnalogOut__0__PORT EQU 0
VAnalogOut__0__SHIFT EQU 0
VAnalogOut__AG EQU CYREG_PRT0_AG
VAnalogOut__AMUX EQU CYREG_PRT0_AMUX
VAnalogOut__BIE EQU CYREG_PRT0_BIE
VAnalogOut__BIT_MASK EQU CYREG_PRT0_BIT_MASK
VAnalogOut__BYP EQU CYREG_PRT0_BYP
VAnalogOut__CTL EQU CYREG_PRT0_CTL
VAnalogOut__DM0 EQU CYREG_PRT0_DM0
VAnalogOut__DM1 EQU CYREG_PRT0_DM1
VAnalogOut__DM2 EQU CYREG_PRT0_DM2
VAnalogOut__DR EQU CYREG_PRT0_DR
VAnalogOut__INP_DIS EQU CYREG_PRT0_INP_DIS
VAnalogOut__INTTYPE_BASE EQU CYDEV_PICU_INTTYPE_PICU0_BASE
VAnalogOut__LCD_COM_SEG EQU CYREG_PRT0_LCD_COM_SEG
VAnalogOut__LCD_EN EQU CYREG_PRT0_LCD_EN
VAnalogOut__MASK EQU 0x01
VAnalogOut__PORT EQU 0
VAnalogOut__PRT EQU CYREG_PRT0_PRT
VAnalogOut__PRTDSI__CAPS_SEL EQU CYREG_PRT0_CAPS_SEL
VAnalogOut__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT0_DBL_SYNC_IN
VAnalogOut__PRTDSI__OE_SEL0 EQU CYREG_PRT0_OE_SEL0
VAnalogOut__PRTDSI__OE_SEL1 EQU CYREG_PRT0_OE_SEL1
VAnalogOut__PRTDSI__OUT_SEL0 EQU CYREG_PRT0_OUT_SEL0
VAnalogOut__PRTDSI__OUT_SEL1 EQU CYREG_PRT0_OUT_SEL1
VAnalogOut__PRTDSI__SYNC_OUT EQU CYREG_PRT0_SYNC_OUT
VAnalogOut__PS EQU CYREG_PRT0_PS
VAnalogOut__SHIFT EQU 0
VAnalogOut__SLW EQU CYREG_PRT0_SLW

; AnalogClock
AnalogClock__CFG0 EQU CYREG_CLKDIST_DCFG0_CFG0
AnalogClock__CFG1 EQU CYREG_CLKDIST_DCFG0_CFG1
AnalogClock__CFG2 EQU CYREG_CLKDIST_DCFG0_CFG2
AnalogClock__CFG2_SRC_SEL_MASK EQU 0x07
AnalogClock__INDEX EQU 0x00
AnalogClock__PM_ACT_CFG EQU CYREG_PM_ACT_CFG2
AnalogClock__PM_ACT_MSK EQU 0x01
AnalogClock__PM_STBY_CFG EQU CYREG_PM_STBY_CFG2
AnalogClock__PM_STBY_MSK EQU 0x01

; WaveFormReader
WaveFormReader_ADC_SAR__CLK EQU CYREG_SAR1_CLK
WaveFormReader_ADC_SAR__CSR0 EQU CYREG_SAR1_CSR0
WaveFormReader_ADC_SAR__CSR1 EQU CYREG_SAR1_CSR1
WaveFormReader_ADC_SAR__CSR2 EQU CYREG_SAR1_CSR2
WaveFormReader_ADC_SAR__CSR3 EQU CYREG_SAR1_CSR3
WaveFormReader_ADC_SAR__CSR4 EQU CYREG_SAR1_CSR4
WaveFormReader_ADC_SAR__CSR5 EQU CYREG_SAR1_CSR5
WaveFormReader_ADC_SAR__CSR6 EQU CYREG_SAR1_CSR6
WaveFormReader_ADC_SAR__PM_ACT_CFG EQU CYREG_PM_ACT_CFG11
WaveFormReader_ADC_SAR__PM_ACT_MSK EQU 0x02
WaveFormReader_ADC_SAR__PM_STBY_CFG EQU CYREG_PM_STBY_CFG11
WaveFormReader_ADC_SAR__PM_STBY_MSK EQU 0x02
WaveFormReader_ADC_SAR__SW0 EQU CYREG_SAR1_SW0
WaveFormReader_ADC_SAR__SW2 EQU CYREG_SAR1_SW2
WaveFormReader_ADC_SAR__SW3 EQU CYREG_SAR1_SW3
WaveFormReader_ADC_SAR__SW4 EQU CYREG_SAR1_SW4
WaveFormReader_ADC_SAR__SW6 EQU CYREG_SAR1_SW6
WaveFormReader_ADC_SAR__TR0 EQU CYREG_SAR1_TR0
WaveFormReader_ADC_SAR__WRK0 EQU CYREG_SAR1_WRK0
WaveFormReader_ADC_SAR__WRK1 EQU CYREG_SAR1_WRK1
WaveFormReader_Bypass__0__INTTYPE EQU CYREG_PICU0_INTTYPE2
WaveFormReader_Bypass__0__MASK EQU 0x04
WaveFormReader_Bypass__0__PC EQU CYREG_PRT0_PC2
WaveFormReader_Bypass__0__PORT EQU 0
WaveFormReader_Bypass__0__SHIFT EQU 2
WaveFormReader_Bypass__AG EQU CYREG_PRT0_AG
WaveFormReader_Bypass__AMUX EQU CYREG_PRT0_AMUX
WaveFormReader_Bypass__BIE EQU CYREG_PRT0_BIE
WaveFormReader_Bypass__BIT_MASK EQU CYREG_PRT0_BIT_MASK
WaveFormReader_Bypass__BYP EQU CYREG_PRT0_BYP
WaveFormReader_Bypass__CTL EQU CYREG_PRT0_CTL
WaveFormReader_Bypass__DM0 EQU CYREG_PRT0_DM0
WaveFormReader_Bypass__DM1 EQU CYREG_PRT0_DM1
WaveFormReader_Bypass__DM2 EQU CYREG_PRT0_DM2
WaveFormReader_Bypass__DR EQU CYREG_PRT0_DR
WaveFormReader_Bypass__INP_DIS EQU CYREG_PRT0_INP_DIS
WaveFormReader_Bypass__INTTYPE_BASE EQU CYDEV_PICU_INTTYPE_PICU0_BASE
WaveFormReader_Bypass__LCD_COM_SEG EQU CYREG_PRT0_LCD_COM_SEG
WaveFormReader_Bypass__LCD_EN EQU CYREG_PRT0_LCD_EN
WaveFormReader_Bypass__MASK EQU 0x04
WaveFormReader_Bypass__PORT EQU 0
WaveFormReader_Bypass__PRT EQU CYREG_PRT0_PRT
WaveFormReader_Bypass__PRTDSI__CAPS_SEL EQU CYREG_PRT0_CAPS_SEL
WaveFormReader_Bypass__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT0_DBL_SYNC_IN
WaveFormReader_Bypass__PRTDSI__OE_SEL0 EQU CYREG_PRT0_OE_SEL0
WaveFormReader_Bypass__PRTDSI__OE_SEL1 EQU CYREG_PRT0_OE_SEL1
WaveFormReader_Bypass__PRTDSI__OUT_SEL0 EQU CYREG_PRT0_OUT_SEL0
WaveFormReader_Bypass__PRTDSI__OUT_SEL1 EQU CYREG_PRT0_OUT_SEL1
WaveFormReader_Bypass__PRTDSI__SYNC_OUT EQU CYREG_PRT0_SYNC_OUT
WaveFormReader_Bypass__PS EQU CYREG_PRT0_PS
WaveFormReader_Bypass__SHIFT EQU 2
WaveFormReader_Bypass__SLW EQU CYREG_PRT0_SLW
WaveFormReader_IRQ__INTC_CLR_EN_REG EQU CYREG_NVIC_CLRENA0
WaveFormReader_IRQ__INTC_CLR_PD_REG EQU CYREG_NVIC_CLRPEND0
WaveFormReader_IRQ__INTC_MASK EQU 0x04
WaveFormReader_IRQ__INTC_NUMBER EQU 2
WaveFormReader_IRQ__INTC_PRIOR_NUM EQU 7
WaveFormReader_IRQ__INTC_PRIOR_REG EQU CYREG_NVIC_PRI_2
WaveFormReader_IRQ__INTC_SET_EN_REG EQU CYREG_NVIC_SETENA0
WaveFormReader_IRQ__INTC_SET_PD_REG EQU CYREG_NVIC_SETPEND0
WaveFormReader_theACLK__CFG0 EQU CYREG_CLKDIST_ACFG0_CFG0
WaveFormReader_theACLK__CFG1 EQU CYREG_CLKDIST_ACFG0_CFG1
WaveFormReader_theACLK__CFG2 EQU CYREG_CLKDIST_ACFG0_CFG2
WaveFormReader_theACLK__CFG2_SRC_SEL_MASK EQU 0x07
WaveFormReader_theACLK__CFG3 EQU CYREG_CLKDIST_ACFG0_CFG3
WaveFormReader_theACLK__CFG3_PHASE_DLY_MASK EQU 0x0F
WaveFormReader_theACLK__INDEX EQU 0x00
WaveFormReader_theACLK__PM_ACT_CFG EQU CYREG_PM_ACT_CFG1
WaveFormReader_theACLK__PM_ACT_MSK EQU 0x01
WaveFormReader_theACLK__PM_STBY_CFG EQU CYREG_PM_STBY_CFG1
WaveFormReader_theACLK__PM_STBY_MSK EQU 0x01

; WaveFormSelect
WaveFormSelect__0__INTTYPE EQU CYREG_PICU0_INTTYPE1
WaveFormSelect__0__MASK EQU 0x02
WaveFormSelect__0__PC EQU CYREG_PRT0_PC1
WaveFormSelect__0__PORT EQU 0
WaveFormSelect__0__SHIFT EQU 1
WaveFormSelect__AG EQU CYREG_PRT0_AG
WaveFormSelect__AMUX EQU CYREG_PRT0_AMUX
WaveFormSelect__BIE EQU CYREG_PRT0_BIE
WaveFormSelect__BIT_MASK EQU CYREG_PRT0_BIT_MASK
WaveFormSelect__BYP EQU CYREG_PRT0_BYP
WaveFormSelect__CTL EQU CYREG_PRT0_CTL
WaveFormSelect__DM0 EQU CYREG_PRT0_DM0
WaveFormSelect__DM1 EQU CYREG_PRT0_DM1
WaveFormSelect__DM2 EQU CYREG_PRT0_DM2
WaveFormSelect__DR EQU CYREG_PRT0_DR
WaveFormSelect__INP_DIS EQU CYREG_PRT0_INP_DIS
WaveFormSelect__INTTYPE_BASE EQU CYDEV_PICU_INTTYPE_PICU0_BASE
WaveFormSelect__LCD_COM_SEG EQU CYREG_PRT0_LCD_COM_SEG
WaveFormSelect__LCD_EN EQU CYREG_PRT0_LCD_EN
WaveFormSelect__MASK EQU 0x02
WaveFormSelect__PORT EQU 0
WaveFormSelect__PRT EQU CYREG_PRT0_PRT
WaveFormSelect__PRTDSI__CAPS_SEL EQU CYREG_PRT0_CAPS_SEL
WaveFormSelect__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT0_DBL_SYNC_IN
WaveFormSelect__PRTDSI__OE_SEL0 EQU CYREG_PRT0_OE_SEL0
WaveFormSelect__PRTDSI__OE_SEL1 EQU CYREG_PRT0_OE_SEL1
WaveFormSelect__PRTDSI__OUT_SEL0 EQU CYREG_PRT0_OUT_SEL0
WaveFormSelect__PRTDSI__OUT_SEL1 EQU CYREG_PRT0_OUT_SEL1
WaveFormSelect__PRTDSI__SYNC_OUT EQU CYREG_PRT0_SYNC_OUT
WaveFormSelect__PS EQU CYREG_PRT0_PS
WaveFormSelect__SHIFT EQU 1
WaveFormSelect__SLW EQU CYREG_PRT0_SLW

; Miscellaneous
BCLK__BUS_CLK__HZ EQU 24000000
BCLK__BUS_CLK__KHZ EQU 24000
BCLK__BUS_CLK__MHZ EQU 24
CYDEV_CHIP_DIE_LEOPARD EQU 1
CYDEV_CHIP_DIE_PSOC4A EQU 18
CYDEV_CHIP_DIE_PSOC5LP EQU 2
CYDEV_CHIP_DIE_PSOC5TM EQU 3
CYDEV_CHIP_DIE_TMA4 EQU 4
CYDEV_CHIP_DIE_UNKNOWN EQU 0
CYDEV_CHIP_FAMILY_FM0P EQU 5
CYDEV_CHIP_FAMILY_FM3 EQU 6
CYDEV_CHIP_FAMILY_FM4 EQU 7
CYDEV_CHIP_FAMILY_PSOC3 EQU 1
CYDEV_CHIP_FAMILY_PSOC4 EQU 2
CYDEV_CHIP_FAMILY_PSOC5 EQU 3
CYDEV_CHIP_FAMILY_PSOC6 EQU 4
CYDEV_CHIP_FAMILY_UNKNOWN EQU 0
CYDEV_CHIP_FAMILY_USED EQU CYDEV_CHIP_FAMILY_PSOC5
CYDEV_CHIP_JTAG_ID EQU 0x2E161069
CYDEV_CHIP_MEMBER_3A EQU 1
CYDEV_CHIP_MEMBER_4A EQU 18
CYDEV_CHIP_MEMBER_4D EQU 13
CYDEV_CHIP_MEMBER_4E EQU 6
CYDEV_CHIP_MEMBER_4F EQU 19
CYDEV_CHIP_MEMBER_4G EQU 4
CYDEV_CHIP_MEMBER_4H EQU 17
CYDEV_CHIP_MEMBER_4I EQU 23
CYDEV_CHIP_MEMBER_4J EQU 14
CYDEV_CHIP_MEMBER_4K EQU 15
CYDEV_CHIP_MEMBER_4L EQU 22
CYDEV_CHIP_MEMBER_4M EQU 21
CYDEV_CHIP_MEMBER_4N EQU 10
CYDEV_CHIP_MEMBER_4O EQU 7
CYDEV_CHIP_MEMBER_4P EQU 20
CYDEV_CHIP_MEMBER_4Q EQU 12
CYDEV_CHIP_MEMBER_4R EQU 8
CYDEV_CHIP_MEMBER_4S EQU 11
CYDEV_CHIP_MEMBER_4T EQU 9
CYDEV_CHIP_MEMBER_4U EQU 5
CYDEV_CHIP_MEMBER_4V EQU 16
CYDEV_CHIP_MEMBER_5A EQU 3
CYDEV_CHIP_MEMBER_5B EQU 2
CYDEV_CHIP_MEMBER_6A EQU 24
CYDEV_CHIP_MEMBER_FM3 EQU 28
CYDEV_CHIP_MEMBER_FM4 EQU 29
CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE1 EQU 25
CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE2 EQU 26
CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE3 EQU 27
CYDEV_CHIP_MEMBER_UNKNOWN EQU 0
CYDEV_CHIP_MEMBER_USED EQU CYDEV_CHIP_MEMBER_5B
CYDEV_CHIP_DIE_EXPECT EQU CYDEV_CHIP_MEMBER_USED
CYDEV_CHIP_DIE_ACTUAL EQU CYDEV_CHIP_DIE_EXPECT
CYDEV_CHIP_REV_LEOPARD_ES1 EQU 0
CYDEV_CHIP_REV_LEOPARD_ES2 EQU 1
CYDEV_CHIP_REV_LEOPARD_ES3 EQU 3
CYDEV_CHIP_REV_LEOPARD_PRODUCTION EQU 3
CYDEV_CHIP_REV_PSOC4A_ES0 EQU 17
CYDEV_CHIP_REV_PSOC4A_PRODUCTION EQU 17
CYDEV_CHIP_REV_PSOC5LP_ES0 EQU 0
CYDEV_CHIP_REV_PSOC5LP_PRODUCTION EQU 0
CYDEV_CHIP_REV_PSOC5TM_ES0 EQU 0
CYDEV_CHIP_REV_PSOC5TM_ES1 EQU 1
CYDEV_CHIP_REV_PSOC5TM_PRODUCTION EQU 1
CYDEV_CHIP_REV_TMA4_ES EQU 17
CYDEV_CHIP_REV_TMA4_ES2 EQU 33
CYDEV_CHIP_REV_TMA4_PRODUCTION EQU 17
CYDEV_CHIP_REVISION_3A_ES1 EQU 0
CYDEV_CHIP_REVISION_3A_ES2 EQU 1
CYDEV_CHIP_REVISION_3A_ES3 EQU 3
CYDEV_CHIP_REVISION_3A_PRODUCTION EQU 3
CYDEV_CHIP_REVISION_4A_ES0 EQU 17
CYDEV_CHIP_REVISION_4A_PRODUCTION EQU 17
CYDEV_CHIP_REVISION_4D_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4E_CCG2_NO_USBPD EQU 0
CYDEV_CHIP_REVISION_4E_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4F_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4F_PRODUCTION_256DMA EQU 0
CYDEV_CHIP_REVISION_4F_PRODUCTION_256K EQU 0
CYDEV_CHIP_REVISION_4G_ES EQU 17
CYDEV_CHIP_REVISION_4G_ES2 EQU 33
CYDEV_CHIP_REVISION_4G_PRODUCTION EQU 17
CYDEV_CHIP_REVISION_4H_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4I_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4J_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4K_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4L_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4M_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4N_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4O_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4P_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4Q_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4R_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4S_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4T_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4U_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4V_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_5A_ES0 EQU 0
CYDEV_CHIP_REVISION_5A_ES1 EQU 1
CYDEV_CHIP_REVISION_5A_PRODUCTION EQU 1
CYDEV_CHIP_REVISION_5B_ES0 EQU 0
CYDEV_CHIP_REVISION_5B_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_6A_ES EQU 17
CYDEV_CHIP_REVISION_6A_NO_UDB EQU 33
CYDEV_CHIP_REVISION_6A_PRODUCTION EQU 33
CYDEV_CHIP_REVISION_FM3_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_FM4_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_PDL_FM0P_TYPE1_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_PDL_FM0P_TYPE2_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_PDL_FM0P_TYPE3_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_USED EQU CYDEV_CHIP_REVISION_5B_PRODUCTION
CYDEV_CHIP_REV_EXPECT EQU CYDEV_CHIP_REVISION_USED
CYDEV_CONFIG_FASTBOOT_ENABLED EQU 1
CYDEV_CONFIG_UNUSED_IO_AllowButWarn EQU 0
CYDEV_CONFIG_UNUSED_IO EQU CYDEV_CONFIG_UNUSED_IO_AllowButWarn
CYDEV_CONFIG_UNUSED_IO_AllowWithInfo EQU 1
CYDEV_CONFIG_UNUSED_IO_Disallowed EQU 2
CYDEV_CONFIGURATION_COMPRESSED EQU 1
CYDEV_CONFIGURATION_DMA EQU 0
CYDEV_CONFIGURATION_ECC EQU 1
CYDEV_CONFIGURATION_IMOENABLED EQU CYDEV_CONFIG_FASTBOOT_ENABLED
CYDEV_CONFIGURATION_MODE_COMPRESSED EQU 0
CYDEV_CONFIGURATION_MODE EQU CYDEV_CONFIGURATION_MODE_COMPRESSED
CYDEV_CONFIGURATION_MODE_DMA EQU 2
CYDEV_CONFIGURATION_MODE_UNCOMPRESSED EQU 1
CYDEV_DEBUG_ENABLE_MASK EQU 0x20
CYDEV_DEBUG_ENABLE_REGISTER EQU CYREG_MLOGIC_DEBUG
CYDEV_DEBUGGING_DPS_Disable EQU 3
CYDEV_DEBUGGING_DPS_JTAG_4 EQU 1
CYDEV_DEBUGGING_DPS_JTAG_5 EQU 0
CYDEV_DEBUGGING_DPS_SWD EQU 2
CYDEV_DEBUGGING_DPS_SWD_SWV EQU 6
CYDEV_DEBUGGING_DPS EQU CYDEV_DEBUGGING_DPS_SWD_SWV
CYDEV_DEBUGGING_ENABLE EQU 1
CYDEV_DEBUGGING_XRES EQU 0
CYDEV_DMA_CHANNELS_AVAILABLE EQU 24
CYDEV_ECC_ENABLE EQU 0
CYDEV_HEAP_SIZE EQU 0x80
CYDEV_INSTRUCT_CACHE_ENABLED EQU 1
CYDEV_INTR_RISING EQU 0x00000004
CYDEV_IS_EXPORTING_CODE EQU 0
CYDEV_IS_IMPORTING_CODE EQU 0
CYDEV_PROJ_TYPE EQU 0
CYDEV_PROJ_TYPE_BOOTLOADER EQU 1
CYDEV_PROJ_TYPE_LAUNCHER EQU 5
CYDEV_PROJ_TYPE_LOADABLE EQU 2
CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER EQU 4
CYDEV_PROJ_TYPE_MULTIAPPBOOTLOADER EQU 3
CYDEV_PROJ_TYPE_STANDARD EQU 0
CYDEV_PROTECTION_ENABLE EQU 0
CYDEV_STACK_SIZE EQU 0x0800
CYDEV_USB_CLK_OSC_LOCKING_ENABLED_AT_PWR_UP EQU 1
CYDEV_USE_BUNDLED_CMSIS EQU 1
CYDEV_VARIABLE_VDDA EQU 0
CYDEV_VDDA_MV EQU 5000
CYDEV_VDDD_MV EQU 5000
CYDEV_VDDIO0_MV EQU 5000
CYDEV_VDDIO1_MV EQU 5000
CYDEV_VDDIO2_MV EQU 5000
CYDEV_VDDIO3_MV EQU 5000
CYDEV_VIO0_MV EQU 5000
CYDEV_VIO1_MV EQU 5000
CYDEV_VIO2_MV EQU 5000
CYDEV_VIO3_MV EQU 5000
CYIPBLOCK_ARM_CM3_VERSION EQU 0
CYIPBLOCK_P3_ANAIF_VERSION EQU 0
CYIPBLOCK_P3_CAN_VERSION EQU 0
CYIPBLOCK_P3_CAPSENSE_VERSION EQU 0
CYIPBLOCK_P3_COMP_VERSION EQU 0
CYIPBLOCK_P3_DECIMATOR_VERSION EQU 0
CYIPBLOCK_P3_DFB_VERSION EQU 0
CYIPBLOCK_P3_DMA_VERSION EQU 0
CYIPBLOCK_P3_DRQ_VERSION EQU 0
CYIPBLOCK_P3_DSM_VERSION EQU 0
CYIPBLOCK_P3_EMIF_VERSION EQU 0
CYIPBLOCK_P3_I2C_VERSION EQU 0
CYIPBLOCK_P3_LCD_VERSION EQU 0
CYIPBLOCK_P3_LPF_VERSION EQU 0
CYIPBLOCK_P3_OPAMP_VERSION EQU 0
CYIPBLOCK_P3_PM_VERSION EQU 0
CYIPBLOCK_P3_SCCT_VERSION EQU 0
CYIPBLOCK_P3_TIMER_VERSION EQU 0
CYIPBLOCK_P3_USB_VERSION EQU 0
CYIPBLOCK_P3_VIDAC_VERSION EQU 0
CYIPBLOCK_P3_VREF_VERSION EQU 0
CYIPBLOCK_S8_GPIO_VERSION EQU 0
CYIPBLOCK_S8_IRQ_VERSION EQU 0
CYIPBLOCK_S8_SAR_VERSION EQU 0
CYIPBLOCK_S8_SIO_VERSION EQU 0
CYIPBLOCK_S8_UDB_VERSION EQU 0
DMA_CHANNELS_USED__MASK0 EQU 0x00000003
CYDEV_BOOTLOADER_ENABLE EQU 0
    ENDIF
    END

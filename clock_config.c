/*
 *clock_config.c
 * \brief
 *      	This source file helps with the CLOCK CONFIGURATION device driver for Kinetis K64.
 *      	It currently configures the k64 to 100MHz
 *  Created on: 16 nov 2022
 *      Author: Laura García
 */

#include <stdio.h>
#include "MK64F12.h"
#include "fsl_clock.h"
#include "clock_config.h"


// formula: PLL_input_freq = 50MHz / 20MHz = 2.5MHz
// 			PLL_output_freq = 2.5MHz * 40MHz = 100MHz
void clock_config(void) {

	 mcg_pll_config_t 	 pll0Config =
		 	        {
		 	            .enableMode = MCG_PLL_DISABLE, /* MCGPLLCLK disabled */
		 	            .prdiv      = 0x13U,            /* PLL Reference divider: divided by 20 */
		 	            .vdiv       = 0x10U,            /* VCO divider: multiplied by 40 */
		 	        };

	const osc_config_t osc_config = {
	    .freq        = 50000000U,    /* Oscillator frequency: 50000000Hz */
	    .capLoad     = (OSC_CAP0P),  /* Oscillator capacity load: 0pF */
	    .workMode    = kOSC_ModeExt, /* Use external clock */
	    .oscerConfig = {
	        .enableMode =
	            kOSC_ErClkEnable, /* Enable external reference clock, disable external reference clock in STOP mode */
	    }};


	CLOCK_SetSimSafeDivs();

	CLOCK_InitOsc0(&osc_config);
	CLOCK_SetXtal0Freq(osc_config.freq);


	CLOCK_BootToPeeMode(kMCG_OscselOsc, kMCG_PllClkSelPll0, &pll0Config);


	SystemCoreClock = CLOCK_GetFreq(kCLOCK_CoreSysClk);

	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
	PORTC->PCR[1]   = PORT_PCR_MUX(0x4);


}

/*
 * clock_config.h
 * \brief
 *      	This source file helps with the CLOCK CONFIGURATION device driver for Kinetis K64.
 *      	It currently configures the k64 to 100MHz
 *
 *  Created on: Nov 12, 2022
 *      Author: armando
 */

#ifndef CLOCK_CONFIG_H_
#define CLOCK_CONFIG_H_

#define MCG_IRCLK_DISABLE 0U                   /*!< MCGIRCLK disabled */
#define MCG_PLL_DISABLE 0U                     /*!< MCGPLLCLK disabled */
#define OSC_CAP0P 0U                           /*!< Oscillator 0pF capacitor load */
#define OSC_ER_CLK_DISABLE 0U                  /*!< Disable external reference clock */
#define SIM_CLKOUT_SEL_FLEXBUS_CLK 0U          /*!< CLKOUT pin clock select: FlexBus clock */
#define SIM_ENET_1588T_CLK_SEL_OSCERCLK_CLK 2U /*!< SDHC clock select: OSCERCLK clock */
#define SIM_ENET_RMII_CLK_SEL_EXTAL_CLK 0U     /*!< SDHC clock select: Core/system clock */
#define SIM_OSC32KSEL_RTC32KCLK_CLK 2U         /*!< OSC32KSEL select: RTC32KCLK clock (32.768kHz) */
#define SIM_PLLFLLSEL_IRC48MCLK_CLK 3U         /*!< PLLFLL select: IRC48MCLK clock */
#define SIM_PLLFLLSEL_MCGPLLCLK_CLK 1U         /*!< PLLFLL select: MCGPLLCLK clock */
#define SIM_SDHC_CLK_SEL_OSCERCLK_CLK 2U       /*!< SDHC clock select: OSCERCLK clock */
#define SIM_TRACE_CLK_SEL_CORE_SYSTEM_CLK 1U   /*!< Trace clock select: Core/system clock */
#define SIM_USB_CLK_120000000HZ 120000000U     /*!< Input SIM frequency for USB: 120000000Hz */

// setups the k64 to a frequency of 100MHz
void clock_config(void);

#endif /* CLOCK_CONFIG_H_ */

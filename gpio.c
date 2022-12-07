/*
 * gpio.c
 *
 *  Created on: Nov 8, 2022
 *      Author: armando
 */

#include "config.h"
#include <gpio.h>
#include "fsl_gpio.h"
#include "fsl_port.h"

volatile static gpio_interrupt_flags_t g_intr_status_flag = {0};

static void (*gpio_A_callback)(uint32_t flags) = 0;
static void (*gpio_B_callback)(uint32_t flags) = 0;
static void (*gpio_C_callback)(uint32_t flags) = 0;
static void (*gpio_D_callback)(uint32_t flags) = 0;
static void (*gpio_E_callback)(uint32_t flags) = 0;


void GPIO_callback_init(gpio_name_t gpio, void (*handler)(uint32_t flags))
{
	switch(gpio){
		case GPIO_A:
			gpio_A_callback = handler;
			break;

		case GPIO_B:
			gpio_B_callback = handler;
			break;

		case GPIO_C:
			gpio_C_callback = handler;
			break;

		case GPIO_D:
			gpio_D_callback = handler;
			break;

		default: // gpio == GPIO_E
			gpio_E_callback = handler;
	}
}

void PORTC_IRQHandler(void){
	uint32_t irq_status = 0;

	irq_status = GPIO_PortGetInterruptFlags(GPIOC);

	if(gpio_C_callback)
	{
		gpio_C_callback(irq_status);
	}

	GPIO_PortClearInterruptFlags(GPIOC, irq_status);


}

void PORTB_IRQHandler(void){
	uint32_t irq_status = 0;

	irq_status = GPIO_PortGetInterruptFlags(GPIOB);

	if(gpio_B_callback)
	{
		gpio_B_callback(irq_status);
	}

	GPIO_PortClearInterruptFlags(GPIOB, irq_status);
}

void GPIO_init(void)
{
	gpio_pin_config_t gpio_input_config = {
			        kGPIO_DigitalInput,
			        0,
			    };

//	gpio_pin_config_t gpio_output_config = {
//			        kGPIO_DigitalOutput,
//			        1,
//			    };

	const port_pin_config_t spi_config = {
		.pullSelect = kPORT_PullDisable,
		.slewRate = kPORT_FastSlewRate,
		.passiveFilterEnable = kPORT_PassiveFilterEnable,
		.openDrainEnable = kPORT_OpenDrainDisable,
		.driveStrength = kPORT_HighDriveStrength,
		.mux = kPORT_MuxAlt2,
		.lockRegister = kPORT_UnlockRegister,
	};

    const port_pin_config_t i2c_config = {
    		kPORT_PullUp,
			kPORT_FastSlewRate,
			kPORT_PassiveFilterDisable,
			kPORT_OpenDrainEnable,
			kPORT_LowDriveStrength,
			kPORT_MuxAlt2,
			kPORT_UnlockRegister
    };


	const port_pin_config_t button_config = {
			kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
			kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
			kPORT_PassiveFilterEnable,                              /* Passive filter is disabled */
			kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
			kPORT_HighDriveStrength,                                 /* High drive strength is configured */
			kPORT_MuxAsGpio,                                         /* Pin is configured as PTA4 */
			kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
		  };


	CLOCK_EnableClock(kCLOCK_PortD);
	CLOCK_EnableClock(kCLOCK_PortC);
	CLOCK_EnableClock(kCLOCK_PortB);
//	CLOCK_EnableClock(kCLOCK_PortA);

	// DC AND RST
	gpio_pin_config_t gpio_pin_config;

	gpio_pin_config.outputLogic = 0;
	gpio_pin_config.pinDirection = kGPIO_DigitalOutput;

	GPIO_PinInit(LCD_DC_GPIO, LCD_DC_PIN, &gpio_pin_config);

	gpio_pin_config.outputLogic = 1;

	GPIO_PinInit(LCD_RST_GPIO, LCD_RST_PIN, &gpio_pin_config);

	PORT_SetPinMux(LCD_DC_PORT, LCD_DC_PIN, kPORT_MuxAsGpio);
	PORT_SetPinMux(LCD_RST_PORT, LCD_RST_PIN, kPORT_MuxAsGpio);


	// DISPLAY
	PORT_SetPinConfig(LCD_CE_PORT, LCD_CE_PIN, &spi_config);
	PORT_SetPinConfig(CLK_PORT, CLK_PIN, &spi_config);
	PORT_SetPinConfig(LCD_SDA_PORT, LCD_SDA_PIN, &spi_config);

	//BUTTONS
	PORT_SetPinConfig(RED_BUTTON_PORT, RED_BUTTON_PIN, &button_config);
	GPIO_PinInit(RED_BUTTON_GPIO, RED_BUTTON_PIN, &gpio_input_config);
	PORT_SetPinInterruptConfig(RED_BUTTON_PORT, RED_BUTTON_PIN, kPORT_InterruptFallingEdge);

	PORT_SetPinConfig(BLUE_BUTTON_PORT, BLUE_BUTTON_PIN, &button_config);
	GPIO_PinInit(BLUE_BUTTON_GPIO, BLUE_BUTTON_PIN, &gpio_input_config);
	PORT_SetPinInterruptConfig(BLUE_BUTTON_PORT, BLUE_BUTTON_PIN, kPORT_InterruptFallingEdge);

	PORT_SetPinConfig(GREEN_BUTTON_PORT, GREEN_BUTTON_PIN, &button_config);
	GPIO_PinInit(GREEN_BUTTON_GPIO, GREEN_BUTTON_PIN, &gpio_input_config);
	PORT_SetPinInterruptConfig(GREEN_BUTTON_PORT, GREEN_BUTTON_PIN, kPORT_InterruptFallingEdge);

	PORT_SetPinConfig(WHITE_BUTTON_PORT, WHITE_BUTTON_PIN, &button_config);
	GPIO_PinInit(WHITE_BUTTON_GPIO, WHITE_BUTTON_PIN, &gpio_input_config);
	PORT_SetPinInterruptConfig(WHITE_BUTTON_PORT, WHITE_BUTTON_PIN, kPORT_InterruptFallingEdge);

    // I2C1 PINS
    PORT_SetPinConfig(SCL_PORT, SCL_PIN, &i2c_config);
    PORT_SetPinConfig(SDA_PORT, SDA_PIN, &i2c_config);

    GPIO_PinInit(GPIOD, SQW_PIN, &gpio_input_config);
    PORT_SetPinConfig(PORTD, SQW_PIN, &button_config);
    PORT_SetPinInterruptConfig(PORTD, SQW_PIN, kPORT_InterruptFallingEdge);
}

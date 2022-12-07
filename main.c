
#include <st7789.h>
#include "spi.h"
#include "gpio.h"
#include "st7789.h"
#include "cards.h"
#include "random.h"
#include "clock_config.h"
#include "state_machine.h"
#include "nvic.h"
#include "pit.h"
#include "i2c.h"
#include "dac.h"
#include "dma.h"

void main(void) {
	clock_config();
	GPIO_init();
	SPI_config();
	i2c_config();
	RNG_Init();
	PIT_init();
	DAC_init();
	dma_init();

	NVIC_set_basepri_threshold(PRIORITY_5);
	NVIC_enable_interrupt_and_priority(PORTB_IRQ,PRIORITY_2);
	NVIC_global_enable_interrupts;

	GPIO_callback_init(GPIO_B, button_pressed);

	st7789_init();
	st7789_set_rotation(ROTATION_180);
	st7789_fill_screen(ST7789_COLOR_GREEN);

	setup_deck();

    while(TRUE) {
    	state_machine();
    }
}

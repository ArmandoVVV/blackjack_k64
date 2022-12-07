/*
 * pit.c
 *
 * 		\brief
 * 		This is the PIT source file for the device driver for Kinetis K64.
 * 		It contains all PIT´s configuration functions and runtime functions.
 *      Created on: Sep 20, 2022
 *      Author: Armando Cabrales
 */

#include "pin_mux.h"
#include "clock_config.h"
#include "pit.h"
#include "config.h"

#define PIT_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_BusClk)
#define	HALF_SECOND		500000U

volatile boolean_t g_pit0_flag = FALSE;
volatile boolean_t g_pit1_flag = FALSE;
volatile boolean_t g_pit2_flag = FALSE;

static void (*PIT_0_callback)(uint32_t flags) = 0;
static void (*PIT_1_callback)(uint32_t flags) = 0;
static void (*PIT_2_callback)(uint32_t flags) = 0;

boolean_t get_pit0_flag(void){
	return g_pit0_flag;
}

void set_pit0_flag(boolean_t value){
	g_pit0_flag = value;
}

boolean_t get_pit1_flag(void){
	return g_pit1_flag;
}

void set_pit1_flag(boolean_t value){
	g_pit1_flag = value;
}

boolean_t get_pit2_flag(void){
	return g_pit2_flag;
}

void set_pit2_flag(boolean_t value){
	g_pit2_flag = value;
}


void PIT0_IRQHandler(void)
{
	uint32_t irq_status = false;
	set_pit0_flag(TRUE);

	irq_status = PIT_GetStatusFlags(PIT, kPIT_Chnl_0);

	if(PIT_0_callback)
	{
		PIT_0_callback(irq_status);
	}
	PIT_ClearStatusFlags(PIT, kPIT_Chnl_0, kPIT_TimerFlag);
	__DSB(); //Used to enter the interrupt

}

void PIT1_IRQHandler(void)
{
	uint32_t irq_status = false;
	set_pit1_flag(FALSE);

	irq_status = PIT_GetStatusFlags(PIT, kPIT_Chnl_1);

	if(PIT_1_callback)
	{
		PIT_1_callback(irq_status);
	}
	PIT_ClearStatusFlags(PIT, kPIT_Chnl_1, kPIT_TimerFlag);
	__DSB(); //Used to enter the interrupt

	PIT_stop(kPIT_Chnl_1);
}

void PIT2_IRQHandler(void)
{
	uint32_t irq_status = false;
	set_pit2_flag(FALSE);

	irq_status = PIT_GetStatusFlags(PIT, kPIT_Chnl_2);

	if(PIT_2_callback)
	{
		PIT_2_callback(irq_status);
	}
	PIT_ClearStatusFlags(PIT, kPIT_Chnl_2, kPIT_TimerFlag);
	__DSB(); //Used to enter the interrupt

	PIT_stop(kPIT_Chnl_2);
}

void PIT_callback_init(pit_chnl_t channel, void (*handler)(uint32_t flags))
{
	if(kPIT_Chnl_0 == channel){
		PIT_0_callback = handler;
	}
	else if(kPIT_Chnl_1 == channel){
		PIT_1_callback = handler;
	}
}

void PIT_stop(pit_chnl_t channel){
	PIT_StopTimer(PIT, channel);
}

void PIT_start(pit_chnl_t channel){
	PIT_StartTimer(PIT, channel);
}

void PIT_init(void){
	pit_config_t pitConfig;

	CLOCK_SetSimSafeDivs();
	PIT_GetDefaultConfig(&pitConfig);
	PIT_Init(PIT, &pitConfig);

	PIT_SetTimerPeriod(PIT, kPIT_Chnl_0, USEC_TO_COUNT(62U, PIT_SOURCE_CLOCK));
	PIT_EnableInterrupts(PIT, kPIT_Chnl_0, kPIT_TimerInterruptEnable);
	EnableIRQ(PIT0_IRQn);

	PIT_SetTimerPeriod(PIT, kPIT_Chnl_1, USEC_TO_COUNT(HALF_SECOND * 3, PIT_SOURCE_CLOCK));
	PIT_EnableInterrupts(PIT, kPIT_Chnl_1, kPIT_TimerInterruptEnable);
	EnableIRQ(PIT1_IRQn);

	PIT_SetTimerPeriod(PIT, kPIT_Chnl_2, USEC_TO_COUNT(HALF_SECOND, PIT_SOURCE_CLOCK));
	PIT_EnableInterrupts(PIT, kPIT_Chnl_2, kPIT_TimerInterruptEnable);
	EnableIRQ(PIT2_IRQn);

}



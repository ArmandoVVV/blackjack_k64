/*
 * pit.h
 *
 * 		\brief
 * 		This is the PIT source file for the device driver for Kinetis K64.
 * 		It contains all PITÂ´s configuration functions and runtime functions.
 *      Created on: Sep 20, 2022
 *      Author: Armando Cabrales
 */

#include "fsl_pit.h"
#include "config.h"

#ifndef PIT_H_
#define PIT_H_

// initialize the pit
void PIT_init(void);
// stops the PIT
void PIT_stop(pit_chnl_t channel);
// starts the PIT
void PIT_start(pit_chnl_t channel);
void PIT0_IRQHandler(void);
void PIT1_IRQHandler(void);
void PIT_callback_init(pit_chnl_t channel, void (*handler)(uint32_t flags));

boolean_t get_pit0_flag(void);
void set_pit0_flag(boolean_t value);

boolean_t get_pit1_flag(void);
void set_pit1_flag(boolean_t value);

boolean_t get_pit2_flag(void);
void set_pit2_flag(boolean_t value);


#endif /* PIT_H_ */

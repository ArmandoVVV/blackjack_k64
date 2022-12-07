/*
 * dac.h
 *
 * 		\brief
 *				This source file helps us to set the DAC values to create
 *				different signals, and start the DAC.
 *  	Created on: Sep 20, 2022
 *		Author: Laura García
 */

#ifndef DAC_H_
#define DAC_H_

#include "stdint.h"

// initialize the DAC
void DAC_init(void);
// sends a 0 to the DAC
void DAC_noSignal(void);
// sends a specific value to the DAC
void DAC_setValue (uint16_t value);

#endif /* DAC_H_ */

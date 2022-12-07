/*
 * dma.h
 *
 * This source file helps us to configure the DMA to transfer from an array
 * to the DAC, the DMA is currently always enable by PIT channel 0.
 *  Created on: Nov 15, 2022
 *      Author: armando
 */

#ifndef DMA_H_
#define DMA_H_

//#include "sounds.h"
#include "config.h"

// initialize the dma, sets the mux channel
void dma_init(void);
// configures the dma to transfer and specific sound in an array
void setup_dma_transfer_config(uint32_t bytes, const uint16_t* sound_array);

boolean_t get_transfer_done(void);
void set_transfer_done(boolean_t value);


#endif /* DMA_H_ */

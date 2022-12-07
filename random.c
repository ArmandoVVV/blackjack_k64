/*
 * random.c
 *
 *  Created on: 30 nov 2022
 *      Author: Laura García
 */

#include "random.h"
#include "fsl_rnga.h"


uint32_t get_random_number(void){
	static uint32_t random_numbers[1];
	static uint8_t random_number;

	RNGA_GetRandomData(RNG, random_numbers, sizeof(random_numbers));
	random_number = random_numbers[0];

	return random_number;
}



void RNG_Init(void){
	static rnga_mode_t rng_config = kRNGA_ModeNormal;

	RNGA_Init(RNG);
	RNGA_SetMode(RNG, rng_config);
}

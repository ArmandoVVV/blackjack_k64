/*
 * AT24C32D.h
 *
 *  Created on: Nov 1, 2022
 *      Author: Laura García
 *      brief: this module has the functions to write and read all the required
 *      values on the memory device.
 */

#ifndef AT24C32D_H_
#define AT24C32D_H_

#include "i2c.h"
#include "stdint.h"

#define TOTAL_VALUES_TO_STORE	 1
#define ROM_DATASIZE	1
#define ROM_SUBADDRESS_SIZE 2

//typedef struct{
//	clock_values_t time;
//	date_values_t date;
//	uint8_t temperature;
//	uint8_t humidity;
//}rom_values_t;


//void set_ROM_uart0(void);
//rom_values_t get_ROM_uart0(void);
//void set_ROM_uart4(void);
//rom_values_t get_ROM_uart4(void);

uint8_t get_value_at_address(uint16_t address);
void write_value_at_address(uint8_t value, uint16_t address);


#endif /* AT24C32D_H_ */

/*
 * AT24C32D.c
 *
 *  Created on: Nov 1, 2022
 *      Author: Laura García
 *      brief: this module has the functions to write and read all the required
 *      values on the memory device.
 *
 */

#include "AT24C32D.h"


void write_value_at_address(uint8_t value, uint16_t address){
	static i2c_device_config_t rom_config = {
			.address        = ROM_ADDRESS,
			.dataSize       = ROM_DATASIZE,
			.subaddressSize = ROM_SUBADDRESS_SIZE
	};

	rom_config.regAddress = address;

	i2c_write_indv(rom_config, value);
}

uint8_t get_value_at_address(uint16_t address){
	static i2c_device_config_t rom_config = {
			.address        = ROM_ADDRESS,
			.dataSize       = ROM_DATASIZE,
			.subaddressSize = ROM_SUBADDRESS_SIZE,
	};
	rom_config.regAddress = address;

	i2c_read(rom_config);

	return get_master_rxBuff()[0];
}






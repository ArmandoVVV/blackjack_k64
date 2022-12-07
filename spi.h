/*
 * spi.h
 *
 *  Created on: Nov 8, 2022
 *      Author: armando
 */
#ifndef SPI_H_
#define SPI_H_

#define TRANSFER_SIZE     64U     /*! Transfer dataSize */
#define TRANSFER_BAUDRATE 5000000U /*! Transfer baudrate - 500k */

void SPI_config(void);

#endif /* SPI_H_ */

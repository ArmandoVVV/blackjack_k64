/*
 * spi.c
 *
 *  Created on: Nov 8, 2022
 *      Author: armando
 */


#include "spi.h"
#include "fsl_dspi.h"
#include "fsl_clock.h"

void SPI_config(void)
{
	dspi_master_config_t masterConfig;

	CLOCK_EnableClock(kCLOCK_Spi0);

	masterConfig.whichCtar = kDSPI_Ctar0;

	masterConfig.ctarConfig.baudRate = TRANSFER_BAUDRATE;
	masterConfig.ctarConfig.bitsPerFrame = 8u;
	masterConfig.ctarConfig.cpol = kDSPI_ClockPolarityActiveLow;
	masterConfig.ctarConfig.cpha = kDSPI_ClockPhaseSecondEdge;
	masterConfig.ctarConfig.direction = kDSPI_MsbFirst;

	masterConfig.ctarConfig.pcsToSckDelayInNanoSec = 10000 / TRANSFER_BAUDRATE;
	masterConfig.ctarConfig.lastSckToPcsDelayInNanoSec = 10000 / TRANSFER_BAUDRATE;
	masterConfig.ctarConfig.betweenTransferDelayInNanoSec = 10000 / TRANSFER_BAUDRATE;

	masterConfig.whichPcs = kDSPI_Pcs0;
	masterConfig.pcsActiveHighOrLow = kDSPI_PcsActiveLow;
	masterConfig.enableContinuousSCK = false;
	masterConfig.enableRxFifoOverWrite = false;
	masterConfig.enableModifiedTimingFormat = false;
	masterConfig.samplePoint = kDSPI_SckToSin0Clock;

	DSPI_MasterInit(SPI0, &masterConfig, CLOCK_GetFreq(kDSPI_SckToSin0Clock));
}


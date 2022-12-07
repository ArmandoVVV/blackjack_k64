/*
 * dma.c
 *
 * This source file helps us to configure the DMA to transfer from an array
 * to the DAC, the DMA is currently always enable by PIT channel 0.
 *
 *
 *  Created on: Nov 15, 2022
 *      Author: armando Cabrales
 */

#include "fsl_edma.h"
#include "fsl_dmamux.h"
#include "fsl_gpio.h"
#include "pit.h"
#include "dma.h"
#include "dac.h"

#define DMA_SOURCE_ALWAYS_ENABLE (58u)
#define TCD_QUEUE_SIZE      1U

volatile boolean_t g_Transfer_Done = TRUE;

boolean_t get_transfer_done(void){
	return g_Transfer_Done;
}

void set_transfer_done(boolean_t value){
	g_Transfer_Done = value;
}

edma_handle_t g_EDMA_Handle;
AT_QUICKACCESS_SECTION_DATA_ALIGN(edma_tcd_t tcdMemoryPoolPtr[TCD_QUEUE_SIZE + 1], sizeof(edma_tcd_t));


void EDMA_Callback(edma_handle_t *handle, void *param, bool transferDone, uint32_t tcds)
{
    if (transferDone)
    {
    	PIT_stop(kPIT_Chnl_0);
        g_Transfer_Done = TRUE;
    }
}
//
void setup_dma_transfer_config(uint32_t bytes, const uint16_t* sound_array){
	edma_transfer_config_t transferConfig;

    EDMA_PrepareTransferConfig(
    		&transferConfig,
    		&sound_array[0],	/* origin, SARD reg */
			2,				/* source width, how big it is in bytes */
			2, /* source offset, space between each source value*/
			&DAC0->DAT[0],	/* destiny address where data will be located */
			2,				/* N bytes to transfer */
			0,              /* dest offset */
			2,            /* minor loop bytes CITER reg*/
			( (bytes & 1) == 1 ? bytes-1 : bytes)   /* major loop counts NBYTES reg*/
	);

    EDMA_TcdSetMajorOffsetConfig(
    		tcdMemoryPoolPtr, //param tcd A point to the TCD structure.
			0, //* param sourceOffset source address offset. SLAST reg
			0	//destOffset destination address offset. DLAST reg
	);

    EDMA_TcdSetTransferConfig(tcdMemoryPoolPtr, &transferConfig, NULL); // configures the tcd
	EDMA_TcdEnableInterrupts(&tcdMemoryPoolPtr[0], kEDMA_MajorInterruptEnable);
	EDMA_TcdEnableAutoStopRequest(&tcdMemoryPoolPtr[0], false);	// stops after completing the major loop
	EDMA_InstallTCD(DMA0, 0, &tcdMemoryPoolPtr[0]);
	EDMA_EnableChannelRequest(DMA0, 0);	// enables callback
}



void dma_init(void){
	edma_config_t userConfig;

	DMAMUX_Init(DMAMUX0);
	DMAMUX_SetSource(DMAMUX0, 0, DMA_SOURCE_ALWAYS_ENABLE); // always enable for PIT use
	DMAMUX_EnablePeriodTrigger(DMAMUX0, 0); // sets channel 0 where pit0 calls the transfer
	DMAMUX_EnableChannel(DMAMUX0, 0); // enables dma with channel 0

	EDMA_GetDefaultConfig(&userConfig);
	EDMA_Init(DMA0, &userConfig);

	EDMA_CreateHandle(&g_EDMA_Handle, DMA0, 0); // initialize the transfer structure
	EDMA_SetCallback(&g_EDMA_Handle, EDMA_Callback, NULL);
	EDMA_ResetChannel(g_EDMA_Handle.base, g_EDMA_Handle.channel); // resets channel


}


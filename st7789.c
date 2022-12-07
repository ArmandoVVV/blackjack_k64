/*
 * st7789.c
 *
 *  Created on: 30 nov 2022
 *      Author: Armando Cabrales
 */
#include "st7789.h"

#include "gpio.h"
#include "spi.h"

#include <fsl_dspi.h>
#include <fsl_clock.h>
#include <fsl_port.h>
#include "config.h"
#include "fsl_gpio.h"

void st7789_init(void){
    SDK_DelayAtLeastUs(DELAY_25_MS, CLOCK_GetFreq(kCLOCK_CoreSysClk));
    GPIO_PortClear(LCD_RST_GPIO, LCD_RST_MASK);
    SDK_DelayAtLeastUs(DELAY_25_MS, CLOCK_GetFreq(kCLOCK_CoreSysClk));
    GPIO_PortSet(LCD_RST_GPIO, LCD_RST_MASK);
    SDK_DelayAtLeastUs(DELAY_150_MS, CLOCK_GetFreq(kCLOCK_CoreSysClk));

    st7789_write_command(SWRESET);
    SDK_DelayAtLeastUs(DELAY_150_MS, CLOCK_GetFreq(kCLOCK_CoreSysClk));

    st7789_write_command(SLPOUT);
    SDK_DelayAtLeastUs(DELAY_10_MS, CLOCK_GetFreq(kCLOCK_CoreSysClk));

    st7789_write_command(COLMOD);
    st7789_write_data(0x55);
    SDK_DelayAtLeastUs(DELAY_10_MS, CLOCK_GetFreq(kCLOCK_CoreSysClk));

    st7789_write_command(RDDMADCTL);
    st7789_write_data(0x01);

    st7789_write_command(CASET);
    st7789_write_data(0x00);
    st7789_write_data(0x00);
    st7789_write_data(0x00);
    st7789_write_data(0xF0);

    st7789_write_command(RASET);

    st7789_write_data(0x00);
    st7789_write_data(0x00);
    st7789_write_data(320 >> 8);
    st7789_write_data(320 & 0xFF);

    st7789_write_command(INVON);

    st7789_write_command(NORON);
    SDK_DelayAtLeastUs(DELAY_10_MS, CLOCK_GetFreq(kCLOCK_CoreSysClk));

    st7789_write_command(DISPON);
    SDK_DelayAtLeastUs(DELAY_10_MS, CLOCK_GetFreq(kCLOCK_CoreSysClk));
}

void st7789_set_rotation(st7789_rotation_t rotation){
    uint8_t madctl = 0;

    switch (rotation){
    	case ROTATION_0:
    		madctl = 0x40 | 0x80 | 0x00;
    		break;

    	case ROTATION_90:
    		madctl = 0x80 | 0x20 | 0x00;
    		break;

    	case ROTATION_180:
    		madctl = 0x00;
    		break;

    	case ROTATION_270:
    		madctl = 0x40 | 0x20 | 0x00;
    		break;

    	default:
    		break;
    }

    st7789_write_command(MADCTL);
    st7789_write_data(madctl);
}


void st7789_write_command(uint8_t command){
    GPIO_PortClear(LCD_DC_GPIO, LCD_DC_MASK);

    dspi_transfer_t masterXfer = {0};
    masterXfer.txData = &command;
    masterXfer.dataSize = 1; // bytes
    masterXfer.configFlags = kDSPI_MasterPcs0  |  kDSPI_MasterCtar0 | kDSPI_MasterPcsContinuous;

    DSPI_MasterTransferBlocking(SPI0, &masterXfer);

    GPIO_PortSet(LCD_DC_GPIO, LCD_DC_MASK);
}


void st7789_write_data(uint8_t data){
    GPIO_PortSet(LCD_DC_GPIO, LCD_DC_MASK);

    dspi_transfer_t masterXfer = {0};
    masterXfer.txData = &data;
    masterXfer.dataSize = 1; // bytes
    masterXfer.configFlags = kDSPI_MasterPcs0  |  kDSPI_MasterCtar0 | kDSPI_MasterPcsContinuous;

    DSPI_MasterTransferBlocking(SPI0, &masterXfer);

    GPIO_PortClear(LCD_DC_GPIO, LCD_DC_MASK);
}

static void set_addr_window(vector_t start, vector_t size){
    st7789_write_command(CASET);
    st7789_write_data(start.x >> 8);
    st7789_write_data(start.x & 0xFF);
    st7789_write_data(size.x >> 8);
    st7789_write_data(size.x & 0xFF);

    st7789_write_command(RASET);
    st7789_write_data(start.y >> 8);
    st7789_write_data(start.y & 0xFF);
    st7789_write_data(size.y >> 8);
    st7789_write_data(size.y & 0xFF);
}


void st7789_draw_rectangle(vector_t origin, vector_t size, uint16_t color){
    set_addr_window(origin, (vector_t){origin.x + size.x, origin.y + size.y});

    st7789_write_command(RAMWR);

    color = (color >> 8) | (color << 8);

    dspi_transfer_t masterXfer = {0};
    masterXfer.txData = (uint8_t*)&color;
    masterXfer.dataSize = sizeof(color);
    masterXfer.configFlags = kDSPI_MasterPcs0  |  kDSPI_MasterCtar0 | kDSPI_MasterPcsContinuous;

    GPIO_PortSet(LCD_DC_GPIO, LCD_DC_MASK);

    for (uint32_t i = 0; i < (size.x * size.y) + 10; i++)
    {
    	DSPI_MasterTransferBlocking(SPI0, &masterXfer);
    }

    GPIO_PortClear(LCD_DC_GPIO, LCD_DC_MASK);
}



void st7789_draw_image(vector_t origin, vector_t end, const uint8_t * image){
    set_addr_window(origin, end);

    st7789_write_command(RAMWR);

    dspi_transfer_t masterXfer = {0};
    masterXfer.txData = (uint8_t*)image;
    masterXfer.dataSize = (end.x - origin.x) * (end.y - origin.y) * 2;
    masterXfer.configFlags = kDSPI_MasterPcs0  |  kDSPI_MasterCtar0 | kDSPI_MasterPcsContinuous;

    DSPI_MasterTransferBlocking(SPI0, &masterXfer);

    GPIO_PortClear(LCD_DC_GPIO, LCD_DC_MASK);
}

void st7789_fill_screen(uint16_t color){
    st7789_draw_rectangle((vector_t){0, 0}, (vector_t){SCREEN_WIDTH, SCREEN_HEIGHT}, color);
}

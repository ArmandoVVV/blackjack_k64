/*
 * st7789.h
 *
 *  Created on: 30 nov 2022
 *      Author: Armando Cabrales
 */

#ifndef ST7789_H
#define ST7789_H

#include <stdint.h>

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 240
#define DELAY_150_MS 150000
#define DELAY_25_MS 25000
#define DELAY_10_MS 10000

typedef enum{
    ROTATION_0,
    ROTATION_90,
    ROTATION_180,
    ROTATION_270
} st7789_rotation_t;

typedef struct{
    uint8_t x;
    uint8_t y;
} vector_t;

typedef enum{
	NOP = 0x00,
	SWRESET = 0x01,
	RDDID = 0x04,
	RDDST = 0x09,
	RDDPM = 0x0A,
	RDDMADCTL = 0x0B,
	RDDCOLMOD = 0x0C,
	RDDIM = 0x0D,
	RDDSM = 0x0E,
	RDDSDR = 0x0F,
	SLPIN = 0x10,
	SLPOUT = 0x11,
	PTLON = 0x12,
	NORON = 0x13,
	INVOFF = 0x20,
	INVON = 0x21,
	GAMSET = 0x26,
	DISPOFF = 0x28,
	DISPON = 0x29,
	CASET = 0x2A,
	RASET = 0x2B,
	RAMWR = 0x2C,
	RAMRD = 0x2D,
	PTLAR = 0x30,
	VSCRDEF = 0x33,
	TEOFF = 0x34,
	TEON = 0x35,
	MADCTL = 0x36,
	VSCSAD = 0x37,
	IDMOFF = 0x38,
	IDMON = 0x39,
	COLMOD = 0x3A,
	WRMEMC = 0x3C,
	RDMEMC = 0x3E,
	STE = 0x44,
	GSCAN = 0x45,
	WRDISBV = 0x51,
	RDDISBV = 0x52,
	WRCTRLD = 0x53,
	RDCTRLD = 0x54,
	WRCACE = 0x55,
	RDCABC = 0x56,
	WRCABCMB = 0x5E,
	RDCABCMB = 0x5F,
	RDABCSDR = 0x68,
	RDID1 = 0xDA,
	RDID2 = 0xDB,
	RDID3 = 0xDC,
	RAMCTRL = 0xB0,
	RGBCTRL = 0xB1,
	PORTCTRL = 0xB2,
	FRCTRL1 = 0xB3,
	PARCTRL = 0xB5,
	GCTRL = 0xB7,
	GTADJ = 0xB8,
	DGMEN = 0xBA,
	VCOMS = 0xBB,
	POWSAVE = 0xBC,
	DLPOFFSAVE = 0xBD,
	LCMCTRL = 0xC0,
	IDSET = 0xC1,
	VDVVRHEN = 0xC2,
	VRHS = 0xC3,
	VDVS = 0xC4,
	VCMOFSET = 0xC5,
	FRCTRL2 = 0xC6,
	CABCCTRL = 0xC7,
	REGSEL1 = 0xC8,
	RESGSEL2 = 0xCA,
	PWMFRSEL = 0xCC,
	PWCTRL1 = 0xD0,
	VAPVANEN = 0xD2,
	CMD2EN = 0xDF,
	PVGAMCTRL = 0xE0,
	NVGAMCTRL = 0xE1,
	DGMLUTR = 0xE2,
	DGMLUTB = 0xE3,
	GATECTRL = 0xE4,
	SPI2EN = 0xE7,
	PWCTRL2 = 0xE8,
	EQCTRL = 0xE9,
	PROMCTRL = 0xEC,
	PROMEN = 0xFA,
	NVMSET = 0xFC,
	PROMACT = 0xF2
}st7789_command_t;

void st7789_init(void);
void st7789_set_rotation(st7789_rotation_t rotation);

void st7789_draw_rectangle(vector_t origin, vector_t size, uint16_t color);
void st7789_draw_image(vector_t origin, vector_t end, const uint8_t * image);
void st7789_fill_screen(uint16_t color);

void st7789_write_data(uint8_t data);
void st7789_write_command(uint8_t command);

static const uint16_t ST7789_COLOR_BLACK      = 0x0000;
static const uint16_t ST7789_COLOR_WHITE      = 0xFFFF;
static const uint16_t ST7789_COLOR_RED        = 0xF800;
static const uint16_t ST7789_COLOR_GREEN      = 0x07E0;
static const uint16_t ST7789_COLOR_BLUE       = 0x001F;
static const uint16_t ST7789_COLOR_CYAN       = 0x07FF;
static const uint16_t ST7789_COLOR_MAGENTA	  = 0xF81F;
static const uint16_t ST7789_COLOR_YELLOW     = 0xFFE0;
static const uint16_t ST7789_COLOR_ORANGE     = 0xFC00;

#endif



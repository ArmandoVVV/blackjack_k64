/*
 * config.h
 *
 * 		\brief
 * 		This is a source file for the configuration for the practice 3.
 * 		Device driver for Kinetis K64.
 * 		it contains all the definitions of the macros.
 *
 *  	Created on: Nov 10, 2022
 *		Author: Laura García
 */

#ifndef CONFIG_H_
#define CONFIG_H_

typedef enum{
	FALSE,
	TRUE
} boolean_t;

typedef enum{
	DISABLE,
	ENABLE
}device_status_t;

//GPIO
#define LCD_CE_GPIO			(GPIOD)	// DISPLAY AND MEMORY
#define CLK_GPIO			(GPIOD)
#define LCD_SDA_GPIO		(GPIOD)
#define LCD_DC_GPIO			(GPIOC)
#define LCD_RST_GPIO		(GPIOC)

#define WHITE_BUTTON_GPIO	(GPIOB)
#define GREEN_BUTTON_GPIO	(GPIOB)
#define BLUE_BUTTON_GPIO	(GPIOB)
#define RED_BUTTON_GPIO		(GPIOB)

#define SDA_GPIO			(GPIOC)
#define SCL_GPIO			(GPIOC)
#define SQW_GPIO			(GPIOD)


//PORTS
#define LCD_CE_PORT			(PORTD)	// DISPLAY AND MEMORY
#define CLK_PORT			(PORTD)
#define LCD_SDA_PORT 		(PORTD)
#define LCD_DC_PORT			(PORTC)
#define LCD_RST_PORT		(PORTC)

#define WHITE_BUTTON_PORT	(PORTB)
#define GREEN_BUTTON_PORT	(PORTB)
#define BLUE_BUTTON_PORT	(PORTB)
#define RED_BUTTON_PORT		(PORTB)

#define SDA_PORT        	(PORTC)
#define SCL_PORT       		(PORTC)
#define SQW_PORT        	(PORTD)


//PIN
#define LCD_CE_PIN			(0u)	// DISPLAY AND MEMORY
#define CLK_PIN				(1u)
#define LCD_SDA_PIN 		(2u)
#define LCD_DC_PIN			(5u)
#define LCD_RST_PIN			(7u)

#define WHITE_BUTTON_PIN	(11u)
#define GREEN_BUTTON_PIN	(10u)
#define BLUE_BUTTON_PIN		(3u)
#define RED_BUTTON_PIN		(2u)

#define SDA_PIN         	(11u)
#define SCL_PIN         	(10u)
#define SQW_PIN         	(0u)


// MASKS
#define LCD_CE_MASK			(1 << LCD_CE_PIN)	// DISPLAY AND MEMORY
#define CLK_MASK			(1 << CLK_PIN)
#define LCD_SDA_MASK 		(1 << DIN_SI_PIN)
#define LCD_DC_MASK			(1 << LCD_DC_PIN)
#define LCD_RST_MASK		(1 << LCD_RST_PIN)

#define WHITE_BUTTON_MASK	(1 << WHITE_BUTTON_PIN)
#define GREEN_BUTTON_MASK	(1 << GREEN_BUTTON_PIN)
#define BLUE_BUTTON_MASK	(1 << BLUE_BUTTON_PIN)
#define RED_BUTTON_MASK		(1 << RED_BUTTON_PIN)

#define SDA_MASK			(1 << SDA_PIN)
#define SCL_MASK			(1 << SCL_PIN)
#define SQW_MASK			(1 << SQW_PIN)

#endif /* CONFIG_H_ */

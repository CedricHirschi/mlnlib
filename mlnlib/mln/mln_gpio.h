/* 
* mln_gpio.h
*
* Created: 03.04.2023 11:41:24
* Author: cedr0
*/


#ifndef __MLN_GPIO_H__
#define __MLN_GPIO_H__

#include <avr/io.h>

typedef enum mln_gpio_pins_e
{
	PA0, PA1, PA2, PA3, PA4, PA5, PA6, PA7,		// PORT A > 0 - 7
	PB0, PB1, PB2, PB3, PB4, PB5, PB6, PB7,		// PORT B > 8 - 15
	PC0, PC1, PC2, PC3, PC4, PC5, PC6, PC7,		// PORT C > 16 - 23
	PD0, PD1, PD2, PD3, PD4, PD5, PD6, PD7,		// PORT D > 24 - 31
	PE0, PE1, PE2, PE3, PE4, PE5, PE6, PE7,		// PORT E > 32 - 39
	PF0, PF1, PF2, PF3, PF4, PF5, PF6, PF7,		// PORT F > 40 - 47
	PG0, PG1, PG2, PG3, PG4, PG5, PG6, PG7		// PORT G > 48 - 55
} PIN_t;

typedef enum mln_gpio_pin_dirs_e
{
	OUTPUT,
	INPUT,
	INPUT_PULLUP
} PIN_DIR_t;

class mln_gpio
{
public:
	PIN_t pin;
	PIN_DIR_t dir;
	PORT_t port;
	uint8_t pin_num;
	
	mln_gpio(PIN_t new_pin, PIN_DIR_t new_dir);
	
	void set_dir(PIN_DIR_t new_di);
private:

}; //mln_gpio

#endif //__MLN_GPIO_H__

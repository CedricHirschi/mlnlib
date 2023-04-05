/* 
* mln_gpio.h
*
* Created: 03.04.2023 11:41:24
* Author: cedr0
*/


#ifndef __MLN_GPIO_H__
#define __MLN_GPIO_H__

#include <avr/io.h>


// define all pins of the MCU (PA0 - PA7, ... , PG0 - PG7) as PIN_t define each port only if PORT is defined in the device header file
#ifdef PORTA
#define PA0 (PIN_t){&PORTA, 0}
#define PA1 (PIN_t){&PORTA, 1}
#define PA2 (PIN_t){&PORTA, 2}
#define PA3 (PIN_t){&PORTA, 3}
#define PA4 (PIN_t){&PORTA, 4}
#define PA5 (PIN_t){&PORTA, 5}
#define PA6 (PIN_t){&PORTA, 6}
#define PA7 (PIN_t){&PORTA, 7}
#endif

#ifdef PORTB
#define PB0 (PIN_t){&PORTB, 0}
#define PB1 (PIN_t){&PORTB, 1}
#define PB2 (PIN_t){&PORTB, 2}
#define PB3 (PIN_t){&PORTB, 3}
#define PB4 (PIN_t){&PORTB, 4}
#define PB5 (PIN_t){&PORTB, 5}
#define PB6 (PIN_t){&PORTB, 6}
#define PB7 (PIN_t){&PORTB, 7}
#endif

#ifdef PORTC
#define PC0 (PIN_t){&PORTC, 0}
#define PC1 (PIN_t){&PORTC, 1}
#define PC2 (PIN_t){&PORTC, 2}
#define PC3 (PIN_t){&PORTC, 3}
#define PC4 (PIN_t){&PORTC, 4}
#define PC5 (PIN_t){&PORTC, 5}
#define PC6 (PIN_t){&PORTC, 6}
#define PC7 (PIN_t){&PORTC, 7}
#endif

#ifdef PORTD
#define PD0 (PIN_t){&PORTD, 0}
#define PD1 (PIN_t){&PORTD, 1}
#define PD2 (PIN_t){&PORTD, 2}
#define PD3 (PIN_t){&PORTD, 3}
#define PD4 (PIN_t){&PORTD, 4}
#define PD5 (PIN_t){&PORTD, 5}
#define PD6 (PIN_t){&PORTD, 6}
#define PD7 (PIN_t){&PORTD, 7}
#endif

#ifdef PORTE
#define PE0 (PIN_t){&PORTE, 0}
#define PE1 (PIN_t){&PORTE, 1}
#define PE2 (PIN_t){&PORTE, 2}
#define PE3 (PIN_t){&PORTE, 3}
#define PE4 (PIN_t){&PORTE, 4}
#define PE5 (PIN_t){&PORTE, 5}
#define PE6 (PIN_t){&PORTE, 6}
#define PE7 (PIN_t){&PORTE, 7}
#endif

#ifdef PORTF
#define PF0 (PIN_t){&PORTF, 0}
#define PF1 (PIN_t){&PORTF, 1}
#define PF2 (PIN_t){&PORTF, 2}
#define PF3 (PIN_t){&PORTF, 3}
#define PF4 (PIN_t){&PORTF, 4}
#define PF5 (PIN_t){&PORTF, 5}
#define PF6 (PIN_t){&PORTF, 6}
#define PF7 (PIN_t){&PORTF, 7}
#endif

#ifdef PORTG
#define PG0 (PIN_t){&PORTG, 0}
#define PG1 (PIN_t){&PORTG, 1}
#define PG2 (PIN_t){&PORTG, 2}
#define PG3 (PIN_t){&PORTG, 3}
#define PG4 (PIN_t){&PORTG, 4}
#define PG5 (PIN_t){&PORTG, 5}
#define PG6 (PIN_t){&PORTG, 6}
#define PG7 (PIN_t){&PORTG, 7}
#endif

typedef struct mln_gpio_pin_s
{
	PORT_t *port;
	uint8_t pin_num;
} PIN_t;

typedef enum mln_gpio_pin_dirs_e
{
	OUTPUT,
	INPUT,
	INPUT_PULLUP
} PIN_DIR_t;

typedef enum mln_gpio_pin_pull_e
{
	NOPULL,
	PULLUP
} PIN_PULL_t;

class mln_gpio
{
	PIN_t pin;
	PIN_DIR_t dir;
	uint8_t inverted;
	
public:
	mln_gpio();
	mln_gpio(PIN_t new_pin, PIN_DIR_t new_dir, uint8_t new_inverted = 0);
	
	void set(void);
	void clear(void);
	void toggle(void);
	void put(bool val);
	void invert(bool val);
	
	uint8_t get(void);
	
	void conf_dir(PIN_DIR_t new_dir);
	void conf_pull(PIN_DIR_t new_pull);
}; //mln_gpio

#endif //__MLN_GPIO_H__

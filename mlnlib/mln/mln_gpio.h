/* 
* mln_gpio.h
*
* Created: 03.04.2023 11:41:24
* Author: cedr0
*/


#ifndef __MLN_GPIO_H__
#define __MLN_GPIO_H__

#include <avr/io.h>


// define all pins of the MCU (PA0 - PA7, ... , PG0 - PG7) as PIN_t define each port only if PORT is definded in the device header file
#ifdef PORTA
#define PA0 {&PORTA, 0}
#define PA1 {&PORTA, 1}
#define PA2 {&PORTA, 2}
#define PA3 {&PORTA, 3}
#define PA4 {&PORTA, 4}
#define PA5 {&PORTA, 5}
#define PA6 {&PORTA, 6}
#define PA7 {&PORTA, 7}
#endif

#ifdef PORTB
#define PB0 {&PORTB, 0}
#define PB1 {&PORTB, 1}
#define PB2 {&PORTB, 2}
#define PB3 {&PORTB, 3}
#define PB4 {&PORTB, 4}
#define PB5 {&PORTB, 5}
#define PB6 {&PORTB, 6}
#define PB7 {&PORTB, 7}
#endif

#ifdef PORTC
#define PC0 {&PORTC, 0}
#define PC1 {&PORTC, 1}
#define PC2 {&PORTC, 2}
#define PC3 {&PORTC, 3}
#define PC4 {&PORTC, 4}
#define PC5 {&PORTC, 5}
#define PC6 {&PORTC, 6}
#define PC7 {&PORTC, 7}
#endif

#ifdef PORTD
#define PD0 {&PORTD, 0}
#define PD1 {&PORTD, 1}
#define PD2 {&PORTD, 2}
#define PD3 {&PORTD, 3}
#define PD4 {&PORTD, 4}
#define PD5 {&PORTD, 5}
#define PD6 {&PORTD, 6}
#define PD7 {&PORTD, 7}
#endif

#ifdef PORTE
#define PE0 {&PORTE, 0}
#define PE1 {&PORTE, 1}
#define PE2 {&PORTE, 2}
#define PE3 {&PORTE, 3}
#define PE4 {&PORTE, 4}
#define PE5 {&PORTE, 5}
#define PE6 {&PORTE, 6}
#define PE7 {&PORTE, 7}
#endif

#ifdef PORTF
#define PF0 {&PORTF, 0}
#define PF1 {&PORTF, 1}
#define PF2 {&PORTF, 2}
#define PF3 {&PORTF, 3}
#define PF4 {&PORTF, 4}
#define PF5 {&PORTF, 5}
#define PF6 {&PORTF, 6}
#define PF7 {&PORTF, 7}
#endif

#ifdef PORTG
#define PG0 {&PORTG, 0}
#define PG1 {&PORTG, 1}
#define PG2 {&PORTG, 2}
#define PG3 {&PORTG, 3}
#define PG4 {&PORTG, 4}
#define PG5 {&PORTG, 5}
#define PG6 {&PORTG, 6}
#define PG7 {&PORTG, 7}
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
public:
	PIN_t pin;
	PIN_DIR_t dir;
	uint8_t inverted;
	
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

	// assignment operator
private:

}; //mln_gpio

#endif //__MLN_GPIO_H__

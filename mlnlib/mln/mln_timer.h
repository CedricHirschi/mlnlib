/* 
* mln_timer.h
*
* Created: 04.04.2023 10:57:42
* Author: cedr0
*/


#ifndef __MLN_TIMER_H__
#define __MLN_TIMER_H__

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#ifndef F_CPU
#define F_CPU 4000000UL
#endif

#define MLN_TIMER_MAX_PERIOD(divs)	(65535 * divs * 1000 / F_CPU)

#ifdef TCA1
typedef enum mln_timer_inst_e
{
	TIMER0,
	TIMER1
} TIMER_t;
#endif

uint8_t TIMER_GET_DIV(uint16_t period);

class mln_timer
{
	TCA_t *tim;

	float actual_period;
	
public:
	void(*isr)(void);
	
#ifdef TCA1
	mln_timer(TIMER_t new_tim, uint16_t period);
#else
	mln_timer(uint16_t period);
#endif

	void set_isr(void(*f)(void));

	void start(void);
	void stop(void);
	
	bool is_running(void);
	float get_period(void);
}; //mln_timer

#endif //__MLN_TIMER_H__

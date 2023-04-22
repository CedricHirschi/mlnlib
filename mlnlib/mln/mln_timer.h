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

class mln_timer;

mln_timer *timer0_isr;

#ifdef TCA1
mln_timer *timer1_isr;
#endif

const uint16_t mln_timer_divs[] = {1, 2, 4, 8, 16, 64, 256, 1024};
const TCA_SINGLE_CLKSEL_t mln_timer_divs_bm[] = {
	TCA_SINGLE_CLKSEL_DIV1_gc,
	TCA_SINGLE_CLKSEL_DIV2_gc,
	TCA_SINGLE_CLKSEL_DIV4_gc,
	TCA_SINGLE_CLKSEL_DIV8_gc,
	TCA_SINGLE_CLKSEL_DIV16_gc,
	TCA_SINGLE_CLKSEL_DIV64_gc,
	TCA_SINGLE_CLKSEL_DIV256_gc,
	TCA_SINGLE_CLKSEL_DIV1024_gc
};

uint8_t MLN_TIMER_GET_DIV(uint16_t T)
{
	uint8_t index = 0;
	
	while(T > MLN_TIMER_MAX_PERIOD(mln_timer_divs[index]))
	{
		index++;
		if(index == sizeof(mln_timer_divs) / sizeof(uint16_t))
		return -1;
	}
	
	return index;
}

class mln_timer
{
	TCA_t *tim;

	float actual_period;
	
public:
	void(*isr)(void);
	
#ifdef TCA1
	mln_timer(TIMER_t new_tim, uint16_t period)
	{
	(new_tim == TIMER0) ? (tim = &TCA0) : (tim = &TCA1);
#else
	mln_timer(uint16_t period)
	{
		tim = &TCA0;
#endif
		
		uint8_t div_index = MLN_TIMER_GET_DIV(period);
		TCA_SINGLE_CLKSEL_t TCA_SINGLE_CLKSEL_DIV_bm = mln_timer_divs_bm[div_index];
		uint16_t max_period = (uint16_t)((float)period / (float)MLN_TIMER_MAX_PERIOD(mln_timer_divs[div_index]) * 65535.0f);
		
		tim->SINGLE.INTCTRL = TCA_SINGLE_OVF_bm;
		tim->SINGLE.PER = max_period;
		tim->SINGLE.CTRLA = TCA_SINGLE_RUNSTDBY_bm;
		tim->SINGLE.CTRLA |= TCA_SINGLE_CLKSEL_DIV_bm;
		
		actual_period = (float)max_period / 65535.0f * (float)MLN_TIMER_MAX_PERIOD(mln_timer_divs[div_index]);
	}
	
	/*
	* @brief Set ISR function of TCA peripheral
	*/
	inline void set_isr(void(*f)(void))
	{
		isr = f;
		
#ifdef TCA1
		(tim == &TCA0) ? (timer0_isr = this) : (timer1_isr = this);
#else
		timer0_isr = this;
#endif
	}
	
	/*
	* @brief Start TCA peripheral
	*/
	inline const void start(void) { tim->SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm; }
	/*
	* @brief Stop TCA peripheral
	*/
	inline const void stop(void) { tim->SINGLE.CTRLA &= ~TCA_SINGLE_ENABLE_bm; }
	
	/*
	* @brief Check if TCA peripheral is running
	*
	* @returns Whether TCA peripheral is running
	*/
	inline const bool is_running(void) { return tim->SINGLE.CTRLA & TCA_SINGLE_ENABLE_bm; }
	/*
	* @brief Check the actual ISR period of the TCA timer
	*
	* @returns Actual period of TCA timer
	*/
	inline const float get_period(void) { return actual_period; }
}; //mln_timer

ISR(TCA0_OVF_vect)
{
	if(timer0_isr->isr) timer0_isr->isr();
	
	TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
}

#ifdef TCA1
ISR(TCA1_OVF_vect)
{
	if(timer1_isr->isr) timer1_isr->isr();
	
	TCA1.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
}
#endif

#endif //__MLN_TIMER_H__

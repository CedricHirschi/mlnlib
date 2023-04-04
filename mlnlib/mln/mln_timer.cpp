/* 
* mln_timer.cpp
*
* Created: 04.04.2023 10:57:41
* Author: cedr0
*/


#include "mln_timer.h"

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

#ifdef TCA1
mln_timer::mln_timer(TIMER_t new_tim, uint16_t period)
{
	(new_tim == TIMER0) ? (tim = &TCA0) : (tim = &TCA1);
#else
mln_timer::mln_timer(uint16_t period)
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

void mln_timer::set_isr(void(*f)(void))
{
	isr = f;
	
#ifdef TCA1
	(tim == &TCA0) ? (timer0_isr = this) : (timer1_isr = this);
#else
	timer0_isr = this;
#endif
}

void mln_timer::start(void)
{
	tim->SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm;
}

void mln_timer::stop(void)
{
	tim->SINGLE.CTRLA &= ~TCA_SINGLE_ENABLE_bm;
}

bool mln_timer::is_running(void)
{
	return tim->SINGLE.CTRLA & TCA_SINGLE_ENABLE_bm;
}

float mln_timer::get_period(void)
{
	return actual_period;
}

ISR(TCA0_OVF_vect)
{
	if(timer0_isr->isr)
		timer0_isr->isr();
	TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
}

#ifdef TCA1
ISR(TCA1_OVF_vect)
{
	if(timer1_isr->isr)
		timer1_isr->isr();
		
	TCA1.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
}
#endif

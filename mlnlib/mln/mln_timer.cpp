/* 
* mln_timer.cpp
*
* Created: 04.04.2023 10:57:41
* Author: cedr0
*/


#include "mln_timer.h"





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



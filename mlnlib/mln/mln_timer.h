/**
 * @file mln_timer.h
 * @author C�dric Hirschi (cedr02@live.com)
 * @brief This peripheral is used to generate periodic interrupts
 * @version 0.1
 * @date 2023-04-27
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __MLN_TIMER_H__
#define __MLN_TIMER_H__

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#ifndef F_CPU
#error "F_CPU not defined"
#endif

#define MLN_TIMER_DIV (F_CPU / 1000000UL)

#ifdef TCA1
typedef enum mln_timer_inst_e
{
	MLN_TIMER_0 = 0,
	MLN_TIMER_1
} mln_timer_t;
#endif

class mln_timer;

mln_timer *timer0_isr;

#ifdef TCA1
mln_timer *timer1_isr;
#endif

/**
 * @brief Available clock dividers in the TCA peripheral in numerical form
 *
 */
const uint16_t mln_timer_divs[] = {1, 2, 4, 8, 16, 64, 256, 1024};
/**
 * @brief The maximum periods achievable by clock division, in ms at 1MHz
 *
 */
uint32_t mln_timer_max_periods[] = {65, 131, 262, 524, 1048, 4194, 16776, 67107};
/**
 * @brief Available clock dividers in the TCA peripheral as bitmasks
 *
 */
const TCA_SINGLE_CLKSEL_t mln_timer_divs_bm[] = {
	TCA_SINGLE_CLKSEL_DIV1_gc,
	TCA_SINGLE_CLKSEL_DIV2_gc,
	TCA_SINGLE_CLKSEL_DIV4_gc,
	TCA_SINGLE_CLKSEL_DIV8_gc,
	TCA_SINGLE_CLKSEL_DIV16_gc,
	TCA_SINGLE_CLKSEL_DIV64_gc,
	TCA_SINGLE_CLKSEL_DIV256_gc,
	TCA_SINGLE_CLKSEL_DIV1024_gc};

/**
 * @brief Helper function to get the lowest possible clock division to get certain period
 *
 * @param period Required period
 *
 * @returns Index for `mln_timer_...` arrays
 *
 */
uint8_t MLN_TIMER_GET_DIV(uint32_t period)
{
	uint8_t index = 0;

	uint32_t max_period = mln_timer_max_periods[index] / MLN_TIMER_DIV;

	while (period > max_period)
	{
		index++;

		if (index == sizeof(mln_timer_divs) / sizeof(uint16_t))
			return -1;

		max_period = mln_timer_max_periods[index] / MLN_TIMER_DIV;
	}

	return index;
}

/**
 * @brief TCA peripheral class
 *
 */
class mln_timer
{
	TCA_t *tim;

	float actual_period;

public:
	/**
	 * @brief ISR function currently stored in the class
	 *
	 */
	void (*isr)(void);

#ifdef TCA1
	/**
	 * @brief mln_timer class initializer
	 *
	 * @param new_tim Timer to control
	 * @param period Desired period
	 *
	 */
	inline mln_timer(mln_timer_t new_tim, uint16_t period)
	{
		(new_tim == MLN_TIMER_0) ? (tim = &TCA0) : (tim = &TCA1);
#else
	/**
	 * @brief mln_timer class initializer
	 *
	 * @param period Desired period
	 *
	 */
	inline mln_timer(uint16_t period)
	{
		tim = &TCA0;
#endif
		// Is currently done inside MLN_TIMER_GET_DIV function to not divide multiple times
		// TODO: Check if this is working properly
		// for(uint8_t i = 0; i < sizeof(mln_timer_divs) / sizeof(uint16_t); i++)
		//	mln_timer_max_periods[i] /= F_CPU / 1000000UL;

		uint8_t div_index = MLN_TIMER_GET_DIV(period);
		TCA_SINGLE_CLKSEL_t TCA_SINGLE_CLKSEL_DIV_bm = mln_timer_divs_bm[div_index];
		uint16_t max_period = (uint16_t)((float)period / (float)mln_timer_max_periods[div_index] * (float)MLN_TIMER_DIV * 65535.0f);

		tim->SINGLE.INTCTRL = TCA_SINGLE_OVF_bm;
		tim->SINGLE.PER = max_period;
		tim->SINGLE.CTRLA = TCA_SINGLE_RUNSTDBY_bm;
		tim->SINGLE.CTRLA |= TCA_SINGLE_CLKSEL_DIV_bm;

		actual_period = (float)max_period * (float)mln_timer_max_periods[div_index] / 65535.0f / MLN_TIMER_DIV;
	}

	/**
	 * @brief Set ISR function of TCA peripheral
	 */
	inline void set_isr(void (*f)(void))
	{
		isr = f;

#ifdef TCA1
		(tim == &TCA0) ? (timer0_isr = this) : (timer1_isr = this);
#else
		timer0_isr = this;
#endif
	}

	/**
	 * @brief Start TCA peripheral
	 *
	 */
	inline const void start(void) { tim->SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm; }
	/**
	 * @brief Stop TCA peripheral
	 *
	 */
	inline const void stop(void) { tim->SINGLE.CTRLA &= ~TCA_SINGLE_ENABLE_bm; }

	/**
	 * @brief Check if TCA peripheral is running
	 *
	 * @returns Whether TCA peripheral is running
	 * @retval true Peripheral is running
	 * @retval false Peripheral is not running
	 *
	 */
	inline const bool is_running(void) { return tim->SINGLE.CTRLA & TCA_SINGLE_ENABLE_bm; }
	/*
	 * @brief Check the actual ISR period of the TCA timer
	 *
	 * @returns Actual period of TCA timer
	 *
	 */
	inline const float get_period(void) { return actual_period; }
}; // mln_timer

/**
 * @brief Standard ISR for TCA0
 *
 * @note Does nothing but reset the corresponding flag
 *
 */
ISR(TCA0_OVF_vect)
{
	if (timer0_isr->isr)
		timer0_isr->isr();

	TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
}

#ifdef TCA1
/**
 * @brief Standard ISR for TCA1
 *
 * @note Does nothing but reset the corresponding flag
 *
 */
ISR(TCA1_OVF_vect)
{
	if (timer1_isr->isr)
		timer1_isr->isr();

	TCA1.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
}
#endif

#endif //__MLN_TIMER_H__

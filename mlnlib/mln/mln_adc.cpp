/*
* mln_adc.cpp
*
* Created: 05.04.2023 14:29:00
* Author: cedr0
*/


#include "mln_adc.h"

#define MLN_ADC_PIN_TO_IN(pin)		((pin.port - &PORTD) * 8 + pin.pin_num)
#define MLN_ADC_SHIFT(samples)		(samples >= 4 ? 4 : samples)

bool mln_adc::enabled(void)
{
	return (adc->CTRLA & ADC_ENABLE_bm) ? true : false;
}

bool mln_adc::has_result(void)
{
	return (adc->INTFLAGS & ADC_RESRDY_bm) ? true : false;
}

uint16_t mln_adc::result(void)
{
	return adc->RES >> MLN_ADC_SHIFT(adc->CTRLB);
}

mln_adc::mln_adc(PIN_t new_pin)
{
	adc = &ADC0;

#ifdef PORTE
	if(new_pin.port == &PORTD || new_pin.port == &PORTE || new_pin.port == &PORTF)
	{
#else
	if(new_pin.port == &PORTD || new_pin.port == &PORTF)
	{
#endif
		pin = mln_gpio(new_pin, INPUT);
		adc->MUXPOS = MLN_ADC_PIN_TO_IN(new_pin);
	}
}

mln_adc::mln_adc(ADC_IN_t in)
{
	adc = &ADC0;

	adc->MUXPOS = in;
}

mln_adc::mln_adc()
{
	adc = &ADC0;

	adc->MUXPOS = GND;
}

void mln_adc::enable(bool standby)
{
	adc->CTRLA |= ADC_ENABLE_bm | (ADC_RUNSTBY_bm * standby);
}

void mln_adc::disable(void)
{
	adc->CTRLA &= ~ADC_ENABLE_bm;
}

void mln_adc::config(ADC_RES_t res, ADC_SAMP_t samp, ADC_PRE_t presc)
{
	if((res == HIRES) && (adc->CTRLA & ADC_RESSEL_10BIT_gc))
		adc->CTRLA &= ~ADC_RESSEL_10BIT_gc;
	else
		adc->CTRLA |= ADC_RESSEL_10BIT_gc;

	adc->CTRLB = samp;

	adc->CTRLC = presc;
}

void mln_adc::set_in(PIN_t new_pin)
{
#ifdef PORTE
	if(new_pin.port == &PORTD || new_pin.port == &PORTE || new_pin.port == &PORTF)
	{
#else
	if(new_pin.port == &PORTD || new_pin.port == &PORTF)
	{
		#endif
		pin = mln_gpio(new_pin, INPUT);
		adc->MUXPOS = MLN_ADC_PIN_TO_IN(new_pin);
	}
}

void mln_adc::set_in(ADC_IN_t in)
{
	adc->MUXPOS = in;
}

void mln_adc::start(void)
{
	// if conversion already running, dont start
	if(adc->COMMAND & ADC_STCONV_bm)
		return;

	// else, start conversion
	adc->COMMAND = ADC_STCONV_bm;
}

uint16_t mln_adc::read(void)
{
	if(!enabled())
		return -1;

	if(has_result())
		return result();

	start();
	while(!has_result());

	return result();
}

uint16_t mln_adc::read(PIN_t pin)
{
	set_in(pin);

	if(!enabled())
		return -1;

	start();
	while(!has_result());

	return result();
}

uint16_t mln_adc::read(ADC_IN_t in)
{
	set_in(in);

	if(!enabled())
		return -1;

	start();
	while(!has_result());

	return result();
}
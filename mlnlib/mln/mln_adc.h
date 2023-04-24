/*
* mln_adc.h
*
* Created: 05.04.2023 14:29:00
* Author: cedr0
*/


#ifndef __MLN_ADC_H__
#define __MLN_ADC_H__

#include <avr/io.h>

#include "mln_gpio.h"

#define MLN_ADC_PIN_TO_IN(pin)		((pin.port - &PORTD) * 8 + pin.pin_num)
#define MLN_ADC_SHIFT(samples)		(samples >= 4 ? 4 : samples)

typedef enum mln_adc_alt_in_e
{
	GND = 0x40,
	TEMPSENSE = 0x42,
	VDDDIV10 = 0x44,
	VDDIO2DIV10 = 0x45,
	DAC = 0x48,
	DACREF0 = 0x49,
	DACREF1 = 0x4A,
	DACREF2 = 0x4B
} ADC_IN_t;

typedef enum mln_adc_res_e
{
	HIRES,
	LORES
} ADC_RES_t;

typedef enum mln_adc_presc_e
{
	DIV2,
	DIV4,
	DIV8,
	DIV12,
	DIV16,
	DIV20,
	DIV24,
	DIV28,
	DIV32,
	DIV48,
	DIV64,
	DIV96,
	DIV128,
	DIV256
} ADC_PRE_t;

typedef enum mln_adc_samp_e
{
	NONE,
	ACC2,
	ACC4,
	ACC8,
	ACC16,
	ACC32,
	ACC64,
	ACC128
} ADC_SAMP_t;

class mln_adc
{
	ADC_t *adc;

	inline const bool enabled(void) { return (adc->CTRLA & ADC_ENABLE_bm) ? true : false; }
	inline const bool has_result(void) { return (adc->INTFLAGS & ADC_RESRDY_bm) ? true : false; }

	inline const uint16_t result(void) { return adc->RES >> MLN_ADC_SHIFT(adc->CTRLB); }

public:
	inline mln_adc()
	{
		adc = &ADC0;

		adc->MUXPOS = GND;
	}
	inline mln_adc(PIN_t pin)
	{
		adc = &ADC0;

		set_in(pin);
	}
	inline mln_adc(ADC_IN_t in)
	{
		adc = &ADC0;

		set_in(in);
	}
	
	/*
	* @brief Configure the ADC peripheral
	* 
	* @param standby Whether peripheral is active when device is in standby
	* @param res Resolution to be used
	* @param samp Number of samples to be acquired per reading
	* @param presc The frequency prescaler to be used
	*/
	inline const void config(bool standby = false, ADC_RES_t res = HIRES, ADC_SAMP_t samp = NONE, ADC_PRE_t presc = DIV2)
	{
		if((res == HIRES) && (adc->CTRLA & ADC_RESSEL_10BIT_gc)) adc->CTRLA &= ~ADC_RESSEL_10BIT_gc;
		else adc->CTRLA |= ADC_RESSEL_10BIT_gc;
		
		adc->CTRLA |= (uint8_t)(ADC_RUNSTBY_bm * standby);
		
		adc->CTRLB = samp;

		adc->CTRLC = presc;
	}
	
	/*
	* @brief Enable the ADC peripheral
	*/
	inline const void enable() { adc->CTRLA |= ADC_ENABLE_bm; }
	/*
	* @brief Disable the ADC peripheral
	*/
	inline const void disable(void) { adc->CTRLA &= ~ADC_ENABLE_bm; }
	
	/*
	* @brief Configure the input pin of the ADC peripheral
	*
	* @param new_pin Pin to read from
	*/
	inline void set_in(PIN_t new_pin)
	{
#ifdef PORTE
		if(new_pin.port == &PORTD || new_pin.port == &PORTE || new_pin.port == &PORTF)
		{
#else
		if(new_pin.port == &PORTD || new_pin.port == &PORTF)
		{
#endif
			adc->MUXPOS = MLN_ADC_PIN_TO_IN(new_pin);
		}
	}
	/*
	* @brief Configure the input of the ADC peripheral
	*
	* @param new_pin Input to read from
	*/
	inline const void set_in(ADC_IN_t in) { adc->MUXPOS = in; }
	
	/*
	* @brief Start reading of ADC peripheral
	*/
	inline const void start(void)
	{
		// if conversion already running, dont start
		if(adc->COMMAND & ADC_STCONV_bm) return;

		// else, start conversion
		adc->COMMAND = ADC_STCONV_bm;
	}
	
	/*
	* @brief Read current result from ADC peripheral
	*
	* @returns Current reading of ADC peripheral, -1 if peripheral is disabled
	*
	* @warning If no reading is available, a new reading is started and waited until result is available
	*/
	inline const uint16_t read(void)
	{
		if(!enabled()) return -1;

		if(has_result()) return result();

		start();
		while(!has_result());

		return result();
	}
	/*
	* @brief Change input pin and read result from ADC peripheral
	*
	* @param pin Pin to change to
	*
	* @returns Current reading of ADC peripheral, -1 if peripheral is disabled
	*/
	inline uint16_t read(PIN_t pin)
	{
		set_in(pin);

		if(!enabled()) return -1;

		start();
		while(!has_result());

		return result();
	}
	/*
	* @brief Change input and read result from ADC peripheral
	*
	* @param pin Input to change to
	*
	* @returns Current reading of ADC peripheral, -1 if peripheral is disabled
	*/
	inline const uint16_t read(ADC_IN_t in)
	{
		set_in(in);

		if(!enabled()) return -1;

		start();
		while(!has_result());

		return result();
	}

}; //mln_adc

#endif //__MLN_ADC_H__

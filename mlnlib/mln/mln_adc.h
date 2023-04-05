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
	mln_gpio pin;

	bool enabled(void);
	bool has_result(void);

	uint16_t result(void);

public:
	mln_adc(PIN_t new_pin);
	mln_adc(ADC_IN_t in);
	mln_adc();

	void config(ADC_RES_t res, ADC_SAMP_t samp, ADC_PRE_t presc);

	void enable(bool standby);
	void disable(void);

	void set_in(PIN_t new_pin);
	void set_in(ADC_IN_t in);

	void start(void);

	uint16_t read(void);
	uint16_t read(PIN_t pin);
	uint16_t read(ADC_IN_t pin);

}; //mln_adc

#endif //__MLN_ADC_H__

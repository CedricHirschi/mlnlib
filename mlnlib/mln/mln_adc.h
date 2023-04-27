/**
 * @file mln_adc.h
 * @author Cédric Hirschi (cedr02@live.com)
 * @brief This peripheral is used to measure analog voltages.
 * @version 0.1
 * @date 2023-04-27
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __MLN_ADC_H__
#define __MLN_ADC_H__

#include <avr/io.h>

#include "mln_gpio.h"

/**
 * @brief Macro to convert mln_gpio pin to adc input
 *
 */
#define MLN_ADC_PIN_TO_IN(pin)		((pin.port - &PORTD) * 8 + pin.pin_num)
/**
 * @brief Macro to get the required shift of an ADC reading according to samples taken
 *
 */
#define MLN_ADC_SHIFT(samples)		(samples >= 4 ? 4 : samples)

/**
 * @brief ADC input selection enum
 *
 */
typedef enum
{
	MLN_ADC_IN_GND = 0x40,
	MLN_ADC_IN_TEMPSENSE = 0x42,
	MLN_ADC_IN_VDDDIV10 = 0x44,
	MLN_ADC_IN_VDDIO2DIV10 = 0x45,
	MLN_ADC_IN_DAC = 0x48,
	MLN_ADC_IN_DACREF0 = 0x49,
	MLN_ADC_IN_DACREF1 = 0x4A,
	MLN_ADC_IN_DACREF2 = 0x4B
} mln_adc_in_t;

/**
 * @brief ADC resolution selection enum
 *
 */
typedef enum
{
	MLN_ADC_RESOLUTION_HIGH = 0,
	MLN_ADC_RESOLUTION_LOW
} mln_adc_resolution_t;

/**
 * @brief ADC prescaler selection enum
 *
 */
typedef enum
{
	MLN_ADC_DIV2 = 0,
	MLN_ADC_DIV4,
	MLN_ADC_DIV8,
	MLN_ADC_DIV12,
	MLN_ADC_DIV16,
	MLN_ADC_DIV20,
	MLN_ADC_DIV24,
	MLN_ADC_DIV28,
	MLN_ADC_DIV32,
	MLN_ADC_DIV48,
	MLN_ADC_DIV64,
	MLN_ADC_DIV96,
	MLN_ADC_DIV128,
	MLN_ADC_DIV256
} mln_adc_prescaler_t;

/**
 * @brief ADC prescaler accumulation enum
 *
 */
typedef enum
{
	MLN_ADC_ACCNONE = 0,
	MLN_ADC_ACC2,
	MLN_ADC_ACC4,
	MLN_ADC_ACC8,
	MLN_ADC_ACC16,
	MLN_ADC_ACC32,
	MLN_ADC_ACC64,
	MLN_ADC_ACC128
} mln_adc_accumulation_t;

/**
 * @brief ADC peripheral class
 *
 */
class mln_adc
{
	/**
	 * @brief Standard ADC struct
	 *
	 */
	ADC_t *adc;

	/**
	 * @brief Check if ADC peripheral is enabled
	 *
	 * @returns Whether ADC peripheral is enabled
	 * @retval true Peripheral is enabled
	 * @retval false Peripheral is disabled
	 *
	 */
	inline const bool enabled(void) { return (adc->CTRLA & ADC_ENABLE_bm) ? true : false; }

	inline const uint16_t result(void) { return adc->RES >> MLN_ADC_SHIFT(adc->CTRLB); }

public:
	/**
	 * @brief Default `mln_adc` class initializer
	 *
	 * @note Selects ADC0 as peripheral and GND as input
	 *
	 */
	inline mln_adc()
	{
		adc = &ADC0;

		adc->MUXPOS = MLN_ADC_IN_GND;
	}
	/**
	 * @brief Initialize `mln_adc` class from pin
	 *
	 * @param pin Pin to set adc to
	 *
	 * @note Set the pin as input before this
	 */
	inline mln_adc(const mln_pin_t& pin)
	{
		adc = &ADC0;

		set_in(pin);
	}
	/**
	 * @brief Initialize `mln_adc` class from adc input
	 *
	 * @param pin Pin to set adc to
	 *
	 */
	inline mln_adc(const mln_adc_in_t in)
	{
		adc = &ADC0;

		set_in(in);
	}
	
	/**
	 * @brief Configure the ADC peripheral
	 * 
	 * @param standby If true, the peripheral is also running in device standby
	 * @param res Resolution to be utilized
	 * @param samp Number of samples to be acquired per reading
	 * @param presc The frequency prescaler to be used
	 */
	inline const void config(const bool standby = false,
							const mln_adc_resolution_t res = MLN_ADC_RESOLUTION_HIGH,
							const mln_adc_accumulation_t samp = MLN_ADC_ACCNONE,
							const mln_adc_prescaler_t presc = MLN_ADC_DIV2)
	{
		if((res == MLN_ADC_RESOLUTION_HIGH) && (adc->CTRLA & ADC_RESSEL_10BIT_gc)) adc->CTRLA &= ~ADC_RESSEL_10BIT_gc;
		else adc->CTRLA |= ADC_RESSEL_10BIT_gc;
		
		adc->CTRLA |= (uint8_t)(ADC_RUNSTBY_bm * standby);
		
		adc->CTRLB = samp;

		adc->CTRLC = presc;
	}
	
	/**
	 * @brief Enable the ADC peripheral
	 *
	 */
	inline const void enable(void) { adc->CTRLA |= ADC_ENABLE_bm; }
	/**
	 * @brief Disable the ADC peripheral
	 *
	 */
	inline const void disable(void) { adc->CTRLA &= ~ADC_ENABLE_bm; }
	
	/**
	 * @brief Configure the input pin of the ADC peripheral
	 *
	 * @param pin Pin to read from
	 *
	 */
	inline void set_in(const mln_pin_t& pin)
	{
#ifdef PORTE
		if(pin.port == &PORTD || pin.port == &PORTE || pin.port == &PORTF)
		{
#else
		if(pin.port == &PORTD || pin.port == &PORTF)
		{
#endif
			adc->MUXPOS = MLN_ADC_PIN_TO_IN(pin);
		}
	}
	/**
	 * @brief Configure the input of the ADC peripheral
	 *
	 * @param in Input to read from
	 *
	 */
	inline const void set_in(const mln_adc_in_t in) { adc->MUXPOS = in; }
	
	/**
	 * @brief Start reading of ADC peripheral
	 *
	 */
	inline const void start(void)
	{
		// if conversion already running, dont start
		if(adc->COMMAND & ADC_STCONV_bm) return;

		// else, start conversion
		adc->COMMAND = ADC_STCONV_bm;
	}

	/**
	 * @brief Check whether ADC peripheral has a result ready
	 *
	 * @returns Whether ADC peripheral has a result ready 
	 * @retval true Result is ready
	 * @retval false Result not ready
	 *
	 */
	inline const bool has_result(void) { return (adc->INTFLAGS & ADC_RESRDY_bm) ? true : false; }
	
	/**
	 * @brief Read current result from ADC peripheral
	 *
	 * @retval -1 If peripheral is disabled
	 * @retval result else
	 *
	 * @warning If no reading is available, a new reading is started and waited until result is available
	 * @note Previous reading will be returned, if available and not already read out
	 *
	 */
	inline const uint16_t read(void)
	{
		if(!enabled()) return -1;

		if(has_result()) return result();

		start();
		while(!has_result());

		return result();
	}
	/**
	 * @brief Change input pin and read result from ADC peripheral
	 *
	 * @param pin Pin to change to
	 *
	 * @retval -1 If peripheral is disabled
	 * @retval result else
	 *
	 * @warning If no reading is available, a new reading is started and waited until result is available
	 * @note Previous reading will be discarded, if available and not already read out
	 *
	 */
	inline const uint16_t read(const mln_pin_t& pin)
	{
		set_in(pin);

		if(!enabled()) return -1;

		start();
		while(!has_result());

		return result();
	}
	/**
	 * @brief Change input and read result from ADC peripheral
	 *
	 * @param pin Pin to change to
	 *
	 * @retval -1 If peripheral is disabled
	 * @retval result else
	 *
	 * @warning If no reading is available, a new reading is started and waited until result is available
	 * @note Previous reading will be discarded, if available and not already read out
	 *
	 */
	inline const uint16_t read(const mln_adc_in_t in)
	{
		set_in(in);

		if(!enabled()) return -1;

		start();
		while(!has_result());

		return result();
	}

}; //mln_adc

#endif //__MLN_ADC_H__

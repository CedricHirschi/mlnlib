/**
 * @file mln_vref.h
 * @author Cédric Hirschi (cedr02@live.com)
 * @brief This peripheral is used to generate reference voltages for use in other peripherals or on pins.
 * @version 0.1
 * @date 2023-04-27
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef MLN_VREF_H_
#define MLN_VREF_H_

#include <avr/io.h>

/**
 * @brief Reference voltage selection for DAC and ADC
 *
 */
typedef enum
{
	MLN_VREF_1V024,
	MLN_VREF_2V048,
	MLN_VREF_4V096,
	MLN_VREF_2V500,
	MLN_VREF_VDD = 0x5,
	MLN_VREF_VREFA
} MLN_VREF_SEL_t;

/**
 * @brief Voltage reference peripheral namespace
 *
 */
namespace mln_vref
{
	/**
	 * @brief Configure and set voltages of the VREF peripheral
	 *
	 * @param dac Reference voltage of DAC peripheral to set
	 * @param adc Reference voltage of ADC peripheral to set
	 * @param ac Reference voltage of AC peripheral to set
	 * @param standby If true, the peripheral is also running in device standby
	 *
	 */
	inline const void set(MLN_VREF_SEL_t adc = MLN_VREF_2V048, MLN_VREF_SEL_t dac = MLN_VREF_2V048, MLN_VREF_SEL_t ac = MLN_VREF_2V048, bool standby = false)
	{
		VREF.DAC0REF = (standby << 7) | dac;
		VREF.ADC0REF = (standby << 7) | adc;
		VREF.ACREF = (standby << 7) | dac;
	}
};

#endif /* MLN_VREF_H_ */
/**
 * @file mln_dac.h
 * @author Cédric Hirschi (cedr02@live.com)
 * @brief This peripheral is used to generate variable analog voltages for use in other peripherals or on pins.
 * @version 0.1
 * @date 2023-04-27
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef MLN_DAC_H_
#define MLN_DAC_H_

#include <avr/io.h>

/**
 * @brief DAC peripheral namespace
 *
 */
namespace mln_dac
{
	/**
	 * @brief Configure the DAC peripheral
	 *
	 * @param standby If true, the peripheral is also running in device standby
	 * @param buffer If true, the dac output is buffered and output to the pin
	 *
	 */
	inline const void config(bool standby, bool buffer)
	{
		buffer ? (DAC0.CTRLA |= 0x40) : (DAC0.CTRLA &= ~0x40);
		standby ? (DAC0.CTRLA |= 0x80) : (DAC0.CTRLA &= ~0x80);
	}

	/**
	 * @brief Enable the DAC peripheral
	 *
	 */
	inline const void enable(void) { DAC0.CTRLA |= DAC_ENABLE_bm; }
	/**
	 * @brief Disable the DAC peripheral
	 *
	 */
	inline const void disable(void) { DAC0.CTRLA &= ~DAC_ENABLE_bm; }

	/**
	 * @brief Set the output of the DAC peripheral
	 *
	 * @param value The output of the DAC peripheral
	 *
	 * @note Remember to call `enable` to enable the peripheral
	 */
	inline const void set(uint16_t value) { DAC0.DATA = value << 6; }
};

#endif /* MLN_DAC_H_ */
/*
 * mcp4822.h
 *
 * Created: 05.04.2023 00:39:27
 * Author: cedr0
 */

#ifndef __MCP4822_H__
#define __MCP4822_H__

#include "../mln/mln_spi.h"

#define MLN_MCP4822_ENABLE_bm (1 << 4)

/**
 * @brief MCP4822 gain enum
 *
 */
typedef enum
{
	MLN_MCP4822_GAIN2 = 0,
	MLN_MCP4822_GAIN1
} mln_mcp4822_gain_t;

/**
 * @brief MCP4822 channel enum
 *
 */
typedef enum
{
	// channel A
	CHANNELA,
	// channel B
	CHANNELB
} mln_mcp4822_channel_t;

/**
 * @brief MCP4822 DAC driver
 *
 * @note Utilizes the mln_spi and mln_gpio libraries
 */
class mcp4822
{
	// SPI interface
	mln_spi spi;
	// LDAC pin
	mln_gpio ldac;

	// current gain
	mln_mcp4822_gain_t gain;

	// buffer for SPI transfer
	uint8_t buffer[2];

public:
	/**
	 * @brief Construct a new mcp4822 object
	 *
	 * @param new_spi SPI interface to use
	 * @param cs Chip select pin
	 * @param new_ldac LDAC pin
	 */
	mcp4822(SPI_t *new_spi, mln_pin_t cs, mln_pin_t new_ldac)
	{
		spi = mln_spi(new_spi, cs);
		ldac = mln_gpio(new_ldac, MLN_GPIO_DIR_OUTPUT);

		ldac.set();
	}

	/**
	 * @brief Set the gain of the DAC
	 *
	 * @param new_gain The new gain
	 *
	 * @note The gain is set for both channels, only applies from the next write
	 */
	void set_gain(mln_mcp4822_gain_t new_gain) { gain = new_gain; }

	/**
	 * @brief Write a value to the DAC
	 *
	 * @param channel The channel to write to
	 * @param value The value to write
	 */
	void write(const mln_mcp4822_channel_t channel, const uint16_t value)
	{
		buffer[0] = (channel << 7) | (gain << 5) | MLN_MCP4822_ENABLE_bm | (uint8_t)(value >> 8);
		buffer[1] = (uint8_t)(value & 0xFF);

		spi.write(buffer, 2);
		ldac.clear();
		ldac.set();
	}
}; // mcp4822

#endif //__MCP4822_H__

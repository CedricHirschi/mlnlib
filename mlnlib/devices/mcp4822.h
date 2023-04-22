/*
 * mcp4822.h
 *
 * Created: 05.04.2023 00:39:27
 * Author: cedr0
 */

#ifndef __MCP4822_H__
#define __MCP4822_H__

#include "../mln/mln_spi.h"

#define MCP4822_ENABLE_bm (1 << 4)

// defines available gains of the MCP4822
typedef enum mln_spi_gain_s
{
	// 2x gain
	GAIN2,
	// 1x gain
	GAIN1
} MCP4822_GAIN_t;

// defines available channels of the MCP4822
typedef enum mln_spi_channel_s
{
	// channel A
	CHANNELA,
	// channel B
	CHANNELB
} MCP4822_CHANNEL_t;

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
	MCP4822_GAIN_t gain;

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
	mcp4822(SPI_t *new_spi, PIN_t cs, PIN_t new_ldac)
	{
		spi = mln_spi(new_spi, cs);
		ldac = mln_gpio(new_ldac, OUTPUT);

		ldac.set();
	}

	/**
	 * @brief Set the gain of the DAC
	 *
	 * @param new_gain The new gain
	 *
	 * @note The gain is set for both channels, only applies from the next write
	 */
	void set_gain(MCP4822_GAIN_t new_gain) { gain = new_gain; }

	/**
	 * @brief Write a value to the DAC
	 *
	 * @param channel The channel to write to
	 * @param value The value to write
	 */
	void write(MCP4822_CHANNEL_t channel, uint16_t value)
	{
		buffer[0] = (channel << 7) | (gain << 5) | MCP4822_ENABLE_bm | (uint8_t)(value >> 8);
		buffer[1] = (uint8_t)(value & 0xFF);

		spi.write(buffer, 2);
		ldac.clear();
		ldac.set();
	}
}; // mcp4822

#endif //__MCP4822_H__

/*
* mcp4822.cpp
*
* Created: 05.04.2023 00:39:27
* Author: cedr0
*/


#include "mcp4822.h"

mcp4822::mcp4822(SPI_t *new_spi, PIN_t cs, PIN_t new_ldac)
{
	spi = mln_spi(new_spi, cs);
	ldac = mln_gpio(new_ldac, OUTPUT);

	ldac.set();
} //mcp4822

void mcp4822::set_gain(MCP4822_GAIN_t new_gain)
{
	gain = new_gain;
}

void mcp4822::write(MCP4822_CHANNEL_t channel, uint16_t	value)
{
	buffer[0] = (channel << 7) | (gain << 5) | MCP4822_ENABLE_bm | (uint8_t)(value >> 8);
	buffer[1] = (uint8_t)(value & 0xFF);

	spi.write(buffer, 2);
	ldac.clear();
	ldac.set();
}
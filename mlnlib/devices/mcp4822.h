/*
* mcp4822.h
*
* Created: 05.04.2023 00:39:27
* Author: cedr0
*/


#ifndef __MCP4822_H__
#define __MCP4822_H__

#include "../mln/mln_spi.h"

#define MCP4822_ENABLE_bm	(1 << 4)

typedef enum mln_spi_gain_s
{
	GAIN2,
	GAIN1
} MCP4822_GAIN_t;

typedef enum mln_spi_channel_s
{
	CHANNELA,
	CHANNELB
} MCP4822_CHANNEL_t;

class mcp4822
{
public:
	mln_spi spi;
	mln_gpio ldac;
	MCP4822_GAIN_t gain;

	uint8_t buffer[2];

	mcp4822(SPI_t *new_spi, PIN_t cs, PIN_t new_ldac);

	void set_gain(MCP4822_GAIN_t new_gain);

	void write(MCP4822_CHANNEL_t channel, uint16_t value);

private:

}; //mcp4822

#endif //__MCP4822_H__

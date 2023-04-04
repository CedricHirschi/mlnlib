/*
 * mlnlib.cpp
 *
 * Created: 03.04.2023 11:13:26
 * Author : cedr0
 */

#include "mln/mln_common.h"
#include "mln/mln_gpio.h"
#include "mln/mln_uart.h"
#include "mln/mln_timer.h"
// #include "mln/mln_spi.h"
#include "devices/mcp4822.h"

mln_uart uart = mln_uart(UART3, 115200);

// mln_spi spi = mln_spi(&SPI0, PC7);

// mln_gpio ldac = mln_gpio(PC3, OUTPUT);
mln_gpio led_builtin = mln_gpio(PB3, OUTPUT);

mln_timer led_timer = mln_timer(TIMER0, 500);

mcp4822 dac = mcp4822(&SPI0, PC7, PC3);

uint16_t dac_value = 0;

MCP4822_GAIN_t gain = GAIN1;

int main(void)
{
	led_timer.set_isr([](void){led_builtin.toggle();});

	sei();

	led_timer.start();

	while (1)
	{
		dac.write(CHANNELA, dac_value);
		dac.write(CHANNELB, 4095 - dac_value);

		dac_value += 8;

		if(dac_value > 4095)
		{
			dac_value = 0;

			(gain == GAIN1) ? (gain = GAIN2) : (gain = GAIN1);

			dac.set_gain(gain);
		}
    }
}

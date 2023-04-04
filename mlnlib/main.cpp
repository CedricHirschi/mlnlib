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
#include "mln/mln_spi.h"

mln_uart uart = mln_uart(UART3, 115200);

mln_spi spi = mln_spi(&SPI0, PC7);

mln_gpio ldac = mln_gpio(PC3, OUTPUT);
mln_gpio led_builtin = mln_gpio(PB3, OUTPUT);

mln_timer led_timer = mln_timer(TIMER0, 500);

uint16_t dac_value = 0;
uint8_t buffer[2] = {0};

int main(void)
{
	led_timer.set_isr([](void){led_builtin.toggle();});

	sei();

	led_timer.start();

	while (1)
	{
		buffer[0] = 0b00110000 | (uint8_t)(dac_value >> 8); buffer[1] = (uint8_t)(dac_value & 0xFF);
		dac_value = (dac_value + 4) % 4096;
		spi.write(buffer, 2);
		ldac.clear();
		ldac.set();
    }
}




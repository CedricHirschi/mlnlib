/*
 * mlnlib.cpp
 *
 * Created: 03.04.2023 11:13:26
 * Author : cedr0
 */

#include "mln/mln_common.h"

mln_uart uart = mln_uart(UART3, 115200);

mln_gpio led_builtin = mln_gpio(PB3, OUTPUT);

mln_timer led_timer = mln_timer(TIMER0, 250);

mln_vref vref;
mcp4822 dac = mcp4822(&SPI0, PC7, PC3);
mln_dac dac_intern = mln_dac();
mln_adc adc = mln_adc();

uint16_t dac_value = 0;
uint8_t direction = 0;

void led_task(void)
{
	led_builtin.toggle();

	printf("A = %u\tB = %u\tdac = %u\n", adc.read(PD0), adc.read(PD1), adc.read(DAC));

	dac_value = (dac_value + 16) % 4096;

	dac_intern.set(dac_value / 4);

	if(uart.data_available())
	{
		uint8_t buffer[MLN_UART_BUF_SIZE];
		uart.pull(buffer);
		printf("Received '%s'\n", buffer);
	}
}

int main(void)
{
	vref.config(true);
	dac_intern.config(true, false);

	led_timer.set_isr(led_task);
	vref.set(_2V048, _2V048);
	dac.set_gain(GAIN1);

	adc.enable(true);
	dac_intern.start();
	led_timer.start();

	sei();

	while (1)
	{
		dac.write(CHANNELA, dac_value);
		dac.write(CHANNELB, 4095 - dac_value);
    }
}

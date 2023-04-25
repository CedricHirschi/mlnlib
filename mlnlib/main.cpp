/*
 * mlnlib.cpp
 *
 * Created: 03.04.2023 11:13:26
 * Author : cedr0
 */

#include "mln/mln_common.h"

mln_uart uart(UART3, 115200);

mln_gpio btn_builtin(PB2, INPUT_PULLUP, true);
mln_gpio led_builtin(PB3, OUTPUT, true);

mln_vref vref;
mln_adc adc;
mln_dac dac_intern;
mcp4822 dac(&SPI0, PC7, PC3);

mln_timer led_timer(TIMER0, 1000);

uint16_t dac_value = 0;

void led_task(void);

int main(void)
{
	mln_init();

	vref.config(true);
	vref.set(_2V048, _2V048);

	dac_intern.config(true, true);
	dac.set_gain(GAIN1);
	adc.enable();
	dac_intern.enable();

	led_timer.set_isr(led_task);
	led_timer.start();

	btn_builtin.attach_interrupt(RISING);

	sei();

	while (1)
	{
		dac_value = (dac_value + 16) % 4096;

		dac_intern.set(dac_value >> 2);
		dac.write(CHANNELA, dac_value);
		dac.write(CHANNELB, 4095 - dac_value);
    }
}

void led_task(void)
{
	printf(led_builtin.get() ? "LED is on\t" : "LED is off\t");
	printf(btn_builtin.get() ? "BTN is pressed\n" : "BTN is released\n");

	printf("%u\t%u\t%u\t%u\n", dac_value, adc.read(PD0), adc.read(PD1), adc.read(DAC));

	if(uart.data_available())
	{
		uint8_t n = uart.data_available();
		uint8_t buffer[n];
		uart.pull(buffer);
		printf("Received '%s' of size %u\n", buffer, n);
	}
}

ISR(PORTB_PORT_vect)
{
	led_builtin.toggle();

	PORTB.INTFLAGS = PIN2_bm;
}
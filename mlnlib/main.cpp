/*
 * mlnlib.cpp
 *
 * Created: 03.04.2023 11:13:26
 * Author : cedr0
 */

#include "mln/mln_common.h"

#include "mln/mln_opamp.h"

mln_uart uart(&USART3, 115200);

mln_gpio btn_builtin(PB2, MLN_GPIO_DIR_INPUT_PULLUP, true);
mln_gpio led_builtin(PB3, MLN_GPIO_DIR_OUTPUT, true);

mln_adc adc;
mcp4822 dac(&SPI0, PC7, PC3);

mln_timer led_timer(MLN_TIMER_0, 1000);

uint16_t dac_value = 0;

void led_task(void);

mln_opamp_inverting_init_t opamp_init = {
	.opamp = MLN_OPAMP_DEVICE_0,
	.runstdby = false,
	.output = true,
	.lowpower = false,
	.gain = MLN_OPAMP_GAIN_INVERTING_1,
	.in_pos = MLN_OPAMP_INVERTING_IN_POS_VDDDIV2,
	.in_neg = MLN_OPAMP_INVERTING_IN_NEG_INN
};

/**
 * @brief Main function
 *
 * @return int Should never return
 */
int main(void)
{
	mln_init();

	mln_opamp::init(opamp_init);

	adc.config(false, MLN_ADC_RESOLUTION_LOW, MLN_ADC_ACCNONE, MLN_ADC_DIV256);
	adc.enable();

	mln_vref::set(MLN_VREF_4V096, MLN_VREF_4V096);

	mln_dac::config(false, false);
	dac.set_gain(MLN_MCP4822_GAIN1);
	adc.enable();
	mln_dac::enable();

	led_timer.set_isr(led_task);
	led_timer.start();

	btn_builtin.attach_interrupt(MLN_GPIO_ISC_RISING);

	sei();

	while (1)
	{
		dac_value = (dac_value + 16) % 4096;

		mln_dac::set(dac_value >> 2);
		dac.write(CHANNELA, dac_value);
		dac.write(CHANNELB, 4095 - dac_value);
	}
}

void led_task(void)
{
	printf(led_builtin.get() ? "LED is on\t" : "LED is off\t");
	printf(btn_builtin.get() ? "BTN is pressed\n" : "BTN is released\n");

	printf("%u\t%u\t%u\t%u\n", dac_value, adc.read(PD0), adc.read(PD1), adc.read(MLN_ADC_IN_DAC));

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
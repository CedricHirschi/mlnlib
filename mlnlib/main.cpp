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

mln_opamp_follower_init_t opamp_init = {
	.opamp = MLN_OPAMP_DEVICE_0,
	
	.runstdby = true,
	.output = true,
	.lowpower = true,

	.in = MLN_OPAMP_FOLLOWER_IN_DAC
};

mln_opamp_noninverting_init_t opamp1_init = {
	.opamp = MLN_OPAMP_DEVICE_1,

	.runstdby = true,
	.output = true,
	.lowpower = true,

	.gain = MLN_OPAMP_GAIN_NONINVERTING_2,

	.in = MLN_OPAMP_NONINVERTING_IN_LINKOUT
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
	mln_opamp::init(opamp1_init);

	// adc.config(false, MLN_ADC_RESOLUTION_HIGH, MLN_ADC_ACCNONE, MLN_ADC_DIV2);
	adc.enable();

	mln_vref::set(MLN_VREF_2V048, MLN_VREF_1V024);

	mln_dac::config(false, true);
	dac.set_gain(MLN_MCP4822_GAIN1);
	adc.enable();
	mln_dac::enable();

	led_timer.set_isr(led_task);
	led_timer.start();

	btn_builtin.attach_interrupt(MLN_GPIO_ISC_RISING);

	printf("\n\nHello, world!\n");
	int actual_period = led_timer.get_period();
	printf("LED task will be executed every %d ms", actual_period);

	sei();

	while (1)
	{
		dac_value = (dac_value + 1) % 4096;

		mln_dac::set(dac_value >> 2);
		dac.write(CHANNELA, dac_value);
		dac.write(CHANNELB, 4095 - dac_value);
	}
}

void led_task(void)
{
	// printf(led_builtin.get() ? "LED is on\t" : "LED is off\t");
	// printf(btn_builtin.get() ? "BTN is pressed\n" : "BTN is released\n");

	printf("%u\t%u\t%u\t%u\t%u\n", dac_value, adc.read(PD1), adc.read(PD3), adc.read(PD6), adc.read(PD2), adc.read(PD5));

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
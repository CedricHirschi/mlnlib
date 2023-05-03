/*
 * mlnlib.cpp
 *
 * Created: 03.04.2023 11:13:26
 * Author : cedr0
 */

#include "mln/mln_common.h"

#include "devices/mcp4725.h"

mln_uart uart(&USART3, 115200);
// mln_twi i2c(&TWI0, 700000UL);

mln_gpio btn_builtin(PB2, MLN_GPIO_DIR_INPUT_PULLUP, true);
mln_gpio led_builtin(PB3, MLN_GPIO_DIR_OUTPUT, true);

mln_timer led_timer(MLN_TIMER_0, 1000);

#define TWO_BYTE_BUFFER(data) {(uint8_t)(data >> 8), (uint8_t)(data & 0xFF)}

mln_adc adc;
mcp4822 dac(&SPI0, PC7, PC3);

/* uint16_t dac_value = 0;



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
}; */

uint16_t dac_value = 0;

void periodic_task0(void);

bool status = true;
bool last_status = true;

/**
 * @brief Main function
 *
 * @return int Should never return
 */
int main(void)
{
	mln_init();

// 	mln_opamp::init(opamp_init);
// 	mln_opamp::init(opamp1_init);

	// adc.config(false, MLN_ADC_RESOLUTION_HIGH, MLN_ADC_ACCNONE, MLN_ADC_DIV2);
	adc.enable();
	mln_vref::set(MLN_VREF_VDD, MLN_VREF_VDD);
	mln_dac::config(false, true);
	mln_dac::enable();

	btn_builtin.attach_interrupt(MLN_GPIO_ISC_RISING);

	led_timer.set_isr(periodic_task0);
	led_timer.start();

	printf("\n\nHello, world!\n");
	int actual_period = led_timer.get_period();
	printf("LED task will be executed every %d ms\n", actual_period);

	mcp4725 dac;
	dac.power(MLN_MCP4725_PD_NORMAL);

	sei();

	while (1)
	{
 		// mln_dac::set(dac_value >> 2);
		// dac.write(CHANNELA, dac_value);
		// dac.write(CHANNELB, 4095 - dac_value);

		// uint8_t buffer[] = TWO_BYTE_BUFFER(dac_value);

		// status = i2c.write(0x60, buffer, 2);

 		dac.write(dac_value);

 		dac_value += 1;

 		if(dac_value > 4095) dac_value = 0;
		// led_builtin.toggle();

		// mln_gpio::toggle(PB3);
		// led_builtin.toggle();
	}
}

void periodic_task0(void)
{
	// printf(led_builtin.get() ? "LED is on\t" : "LED is off\t");
	// printf(btn_builtin.get() ? "BTN is pressed\n" : "BTN is released\n");

	// printf("%u\t%u\t%u\t%u\t%u\n", dac_value, adc.read(PD1), adc.read(PD3), adc.read(PD6), adc.read(PD2), adc.read(PD5));

	led_builtin.toggle();

	if(uart.data_available())
	{
		uint8_t n = uart.data_available();
		uint8_t buffer[n];
		uart.pull(buffer);
		printf("Received '%s' of size %u\n", buffer, n);
	}

	uint16_t internal = adc.read(MLN_ADC_IN_DAC);
	uint16_t external = adc.read(PD0);
	int16_t diff = (int16_t)internal - (int16_t)external;

	printf("Internal:  %u\tMCP4725:  %u\tdiff:  %d\n", internal, external, diff);

	if(!status && last_status) printf("\nSPI transfer returned an error\n");
	if(!last_status && status) printf("Problem is resolved\n");
	last_status = status;
}

ISR(PORTB_PORT_vect)
{
	if(status) printf("Everything is still ok.\n");

	PORTB.INTFLAGS = PIN2_bm;
}
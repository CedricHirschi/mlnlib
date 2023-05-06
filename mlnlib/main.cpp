/*
 * mlnlib.cpp
 *
 * Created: 03.04.2023 11:13:26
 * Author : cedr0
 */

#include "mln/mln_common.h"

// #include "devices/mcp4725.h"
#include "devices/mcp3421.h"

mln_uart uart(&USART3, 115200);
// mln_twi i2c(&TWI0, 700000UL);

mln_gpio btn_builtin(PB2, MLN_GPIO_DIR_INPUT_PULLUP, true);
mln_gpio led_builtin(PB3, MLN_GPIO_DIR_OUTPUT, true);

mln_timer led_timer(MLN_TIMER_0, 500);

mln_adc adc;
// mcp4822 dac(&SPI0, PC7, PC3);
mcp3421 mcp(&TWI0);

mln_opamp_follower_init_t opamp_init = {
	.opamp = MLN_OPAMP_DEVICE_0,

	.runstdby = true,
	.output = true,
	.lowpower = true,

	.in = MLN_OPAMP_FOLLOWER_IN_DAC
};

/* mln_opamp_noninverting_init_t opamp1_init = {
	.opamp = MLN_OPAMP_DEVICE_1,

	.runstdby = true,
	.output = true,
	.lowpower = true,

	.gain = MLN_OPAMP_GAIN_NONINVERTING_2,

	.in = MLN_OPAMP_NONINVERTING_IN_LINKOUT
}; */

uint16_t dac_value = 100;
int32_t value;

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

    mln_opamp::init(opamp_init);
// 	mln_opamp::init(opamp1_init);

	// adc.config(false, MLN_ADC_RESOLUTION_HIGH, MLN_ADC_ACCNONE, MLN_ADC_DIV2);
	adc.enable();
	mln_vref::set(MLN_VREF_2V048, MLN_VREF_2V048);
	mln_dac::config(false, true);
	mln_dac::enable();

	btn_builtin.attach_interrupt(MLN_GPIO_ISC_RISING);

	led_timer.set_isr(periodic_task0);
	led_timer.start();

	printf("\n\nHello, world!\n");
	int actual_period = led_timer.get_period();
	printf("LED task will be executed every %d ms\n", actual_period);

	sei();
	
	printf("Hello, world!\n");

	while (1)
	{
 		
	}
}

void periodic_task0(void)
{
	led_builtin.toggle();

	if(uart.data_available())
	{
		uint8_t n = uart.data_available();
		uint8_t buffer[n];
		uart.pull(buffer);
		printf("Received '%s' of size %u\n", buffer, n);
	}
	
	status = mcp.read(value);
	
	if(!status)
	{
		if(last_status) printf("mcp3421 reading failed\n");
	}
	else
	{
		float value_float = value * 2.048f / 131072.0f;
		
		printf("%u\t%li\t%.4f\n", dac_value, value, (double)value_float);
	}
	
	last_status = status;
	
	dac_value += 10;
	if(dac_value > 1000) dac_value = 0;
	
	mln_dac::set(dac_value);
}

ISR(PORTB_PORT_vect)
{
	if(status) printf(" > Everything is still ok.\n");
	else printf(" > Last reading not successcul.\n");
	
	dac_value = 0;

	PORTB.INTFLAGS = PIN2_bm;
}
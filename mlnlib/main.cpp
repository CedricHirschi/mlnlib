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

mln_gpio led_builtin = mln_gpio(PB3, OUTPUT);
mln_gpio btn_builtin = mln_gpio(PB2, INPUT_PULLUP);

mln_uart uart3 = mln_uart(UART3, 115200);

mln_timer timer0 = mln_timer(TIMER0, 250);
mln_timer timer1 = mln_timer(TIMER1, 1000);

void led_task(void)
{
	led_builtin.toggle();
}

void print_task(void)
{
	int16_t offset0 = (int16_t)((timer0.get_period() - 250.0f) * 10000);
	int16_t offset1 = (int16_t)((timer1.get_period() - 1000.0f) * 10000);
	
	printf("Errors (0.1us):\t%d (led task)\t%d (print task)\n", offset0, offset1);
	btn_builtin.get() ? printf("Button pressed\n") : printf("button released\n");
}

int main(void)
{
	led_builtin.invert(true);
	btn_builtin.invert(true);
	
	timer0.set_isr(led_task);
	timer1.set_isr(print_task);
	
	sei();
	
	timer0.start();
	timer1.start();
	
	SLPCTRL.CTRLA = SLPCTRL_SMODE_IDLE_gc;
	
    while (1) 
	{
		SLPCTRL.CTRLA |= SLPCTRL_SEN_bm;
    }
}




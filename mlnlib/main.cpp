/*
 * mlnlib.cpp
 *
 * Created: 03.04.2023 11:13:26
 * Author : cedr0
 */ 

#include "mln/mln_common.h"
#include "mln/mln_gpio.h"
#include "mln/mln_uart.h"

mln_gpio led_builtin = mln_gpio(PB3, OUTPUT);
mln_gpio btn_builtin = mln_gpio(PB2, INPUT_PULLUP);

mln_uart uart3 = mln_uart(UART3, 115200);

int main(void)
{
	led_builtin.invert(1);
	btn_builtin.invert(1);
	
	sei();
	
	uint8_t i = 0;
	
    while (1) 
	{
		led_builtin.toggle();
		
		printf("number:\t%u\n", i);
		i++;
		
		if(uart3.data_available())
		{
			uint8_t string[MLN_UART_BUF_SIZE];
			uart3.pull(string);
			printf("Got string '%s'\n", string);
		}
		
		_delay_ms(500);
    }
}

ISR(USART3_RXC_vect)
{
	uart3.push();
}




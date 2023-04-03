/* 
* mln_uart.cpp
*
* Created: 03.04.2023 16:16:30
* Author: cedr0
*/


#include "mln_uart.h"

// default constructor
mln_uart::mln_uart(UART_t new_inst, uint32_t baud)
{
	if(new_inst > MLN_UART_NUM_INSTS)
		return;
		
	inst = MLN_UART_GET_INST(new_inst);
	
	switch(new_inst)
	{
		case 0:
			pin_tx = mln_gpio(MLN_UART0_PIN_TX, OUTPUT);
			pin_rx = mln_gpio(MLN_UART0_PIN_RX, INPUT);
			break;
		case 1:
			pin_tx = mln_gpio(MLN_UART1_PIN_TX, OUTPUT);
			pin_rx = mln_gpio(MLN_UART1_PIN_RX, INPUT);
			break;
		case 2:
			pin_tx = mln_gpio(MLN_UART2_PIN_TX, OUTPUT);
			pin_rx = mln_gpio(MLN_UART2_PIN_RX, INPUT);
			break;
		#ifdef USART3
		case 3:
			pin_tx = mln_gpio(MLN_UART3_PIN_TX, OUTPUT);
			pin_rx = mln_gpio(MLN_UART3_PIN_RX, INPUT);
			break;
		#endif
		#ifdef USART4
		case 4:
			pin_tx = mln_gpio(MLN_UART4_PIN_TX, OUTPUT);
			pin_rx = mln_gpio(MLN_UART4_PIN_RX, INPUT);
			break;
		#endif
		#ifdef USART5
		case 5:
			pin_tx = mln_gpio(MLN_UART5_PIN_TX, OUTPUT);
			pin_rx = mln_gpio(MLN_UART5_PIN_RX, INPUT);
			break;
		#endif
	}
	
	inst.BAUD = MLN_UART_BAUD_NUM(baud);
	
	inst.CTRLA = USART_RXCIE_bm;
	
	inst.CTRLB = USART_RXEN_bm | USART_RXMODE_NORMAL_gc | USART_TXEN_bm;
} //mln_uart

// default destructor
mln_uart::~mln_uart()
{
} //~mln_uart

void mln_uart::set_stdout(void)
{
	// stdout = &stream;
}

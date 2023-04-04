/* 
* mln_uart.cpp
*
* Created: 03.04.2023 16:16:30
* Author: cedr0
*/


#include "mln_uart.h"

//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//////////////////////////////////////////////////////////////////////////

mln_uart *mln_uart_stream_uart;

USART_t* MLN_UART_TO_USART(UART_t uart)
{
	switch(uart)
	{
		case UART0:
			return &USART0;
		break;
		case UART1:
			return &USART1;
		break;
		case UART2:
			return &USART2;
		break;
		#ifdef USART3
		case UART3:
			return &USART3;
		break;
		#endif
		#ifdef USART4
		case UART4:
			return &USART4;
		break;
		#endif
		#ifdef USART5
		case UART5:
			return &USART5;
		break;
		#endif
	}
	
	return &USART0;
}

int mln_uart_stream_write(char character, FILE *f)
{
	mln_uart_stream_uart->write(character);
	return 0;
}

int mln_uart_stream_read(FILE *f)
{
	return mln_uart_stream_uart->read();
}

/* void mln_uart_init_stream(mln_uart* uart)
{
	mln_uart_stream_uart = uart;
	
	uart->f.get = mln_uart_stream_read;
	uart->f.put = mln_uart_stream_write;
	uart->f.flags = _FDEV_SETUP_RW;

	stdout = &uart->f;
	stdin = &uart->f;
} */

//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//////////////////////////////////////////////////////////////////////////

mln_uart::mln_uart(UART_t new_inst, uint32_t baud)
{
	if(new_inst > MLN_UART_NUM_INSTS)
		return;
		
	memset(buffer, 0, sizeof(buffer));
	index = 0;
		
	inst = MLN_UART_TO_USART(new_inst);
	
	init_pins(new_inst);
	
	inst->BAUD = (uint16_t)MLN_UART_BAUD_NUM(baud);
	
	inst->CTRLA = USART_RXCIE_bm;
	
	inst->CTRLB = USART_RXEN_bm | USART_RXMODE_NORMAL_gc | USART_TXEN_bm;
	
	init_stream();
}

//////////////////////////////////////////////////////////////////////////

void mln_uart::init_pins(UART_t new_inst)
{
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
}

void mln_uart::init_stream(void)
{
	mln_uart_stream_uart = this;
	
	mln_uart_stream_uart->f.get = mln_uart_stream_read;
	mln_uart_stream_uart->f.put = mln_uart_stream_write;
	mln_uart_stream_uart->f.flags = _FDEV_SETUP_RW;

	stdout = &mln_uart_stream_uart->f;
	stdin = &mln_uart_stream_uart->f;
}

//////////////////////////////////////////////////////////////////////////

void mln_uart::set_isr(void (*new_isr)(void))
{
	isr = new_isr;
}

//////////////////////////////////////////////////////////////////////////

void mln_uart::write(const uint8_t data)
{
	while(is_busy_tx());
	
	inst->TXDATAL = data;
}

uint8_t mln_uart::read(void)
{
	while (is_busy_rx());
	
	return ((inst->RXDATAH & 0x1) << 8) | inst->RXDATAL;
}

void mln_uart::push(void)
{
	buffer[index] = read();
	index = (index + 1) % MLN_UART_BUF_SIZE;
}

void mln_uart::pull(uint8_t* new_buffer)
{
	memccpy(new_buffer, buffer, 0, MLN_UART_BUF_SIZE);
	index = 0;
	memset(buffer, 0, sizeof(buffer));
}

//////////////////////////////////////////////////////////////////////////

bool mln_uart::is_busy_tx(void)
{
	return !(inst->STATUS & USART_DREIF_bm);
}

bool mln_uart::is_busy_rx(void)
{
	return !(inst->STATUS & USART_RXCIF_bm);
}
bool mln_uart::data_available(void)
{
	return index;
}



ISR(USART3_RXC_vect)
{
	mln_uart_stream_uart->push();
	if(!mln_uart_stream_uart->is_busy_rx())
		mln_uart_stream_uart->isr();
}
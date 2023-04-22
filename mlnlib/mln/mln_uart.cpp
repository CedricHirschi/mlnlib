/* 
* mln_uart.cpp
*
* Created: 03.04.2023 16:16:30
* Author: cedr0
*/


#include "mln_uart.h"

//////////////////////////////////////////////////////////////////////////





/* void mln_uart_init_stream(mln_uart* uart)
{
	mln_uart_stream_uart = uart;
	
	uart->f.get = mln_uart_stream_read;
	uart->f.put = mln_uart_stream_write;
	uart->f.flags = _FDEV_SETUP_RW;

	stdout = &uart->f;
	stdin = &uart->f;
} */

//////////////////////////////////////////////////////////////////////////

mln_uart::mln_uart(UART_t new_inst, uint32_t baud)


//////////////////////////////////////////////////////////////////////////

void mln_uart::init_pins(UART_t new_inst)


void mln_uart::init_stream(void)


//////////////////////////////////////////////////////////////////////////

void mln_uart::set_isr(void (*new_isr)(void))


//////////////////////////////////////////////////////////////////////////

void mln_uart::write(const uint8_t data)


uint8_t mln_uart::read(void)


void mln_uart::push(void)

void mln_uart::pull(uint8_t* new_buffer)


void mln_uart::run_isr(void)


//////////////////////////////////////////////////////////////////////////

bool mln_uart::is_busy_tx(void)


bool mln_uart::is_busy_rx(void)

bool mln_uart::data_available(void)





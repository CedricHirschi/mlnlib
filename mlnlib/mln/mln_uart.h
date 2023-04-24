/*
* mln_uart.h
*
* Created: 03.04.2023 16:16:30
* Author: cedr0
*/


#ifndef __MLN_UART_H__
#define __MLN_UART_H__

#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <avr/interrupt.h>

#include "mln_gpio.h"

#ifndef F_CPU
#define F_CPU					24000000UL
#endif

#define MLN_UART_BAUD			115200
#define MLN_UART_BUF_SIZE		32

#define MLN_UART0_PIN_TX		PA0
#define MLN_UART0_PIN_RX		PA1
#define MLN_UART1_PIN_TX		PC0
#define MLN_UART1_PIN_RX		PC1
#define MLN_UART2_PIN_TX		PF0
#define MLN_UART2_PIN_RX		PF1
#ifdef USART5
#ifndef MLN_UART_NUM_INSTS
#define MLN_UART_NUM_INSTS 6
#endif
#define MLN_UART5_PIN_TX		PG0
#define MLN_UART5_PIN_RX		PG1
#endif
#ifdef USART4
#ifndef MLN_UART_NUM_INSTS
#define MLN_UART_NUM_INSTS 5
#endif
#define MLN_UART4_PIN_TX		PE0
#define MLN_UART4_PIN_RX		PE1
#endif
#ifdef USART3
#ifndef MLN_UART_NUM_INSTS
#define MLN_UART_NUM_INSTS 4
#endif
#define MLN_UART3_PIN_TX		PB0
#define MLN_UART3_PIN_RX		PB1
#endif
#ifndef MLN_UART_NUM_INSTS
#define MLN_UART_NUM_INSTS 3
#endif

#define MLN_UART_BAUD_NUM(BAUD)		((float)(F_CPU * 64 / (16 * (float)BAUD)) + 0.5)
#define IS_INT(CHAR)				((CHAR >= 48) && (CHAR <= 57))

typedef enum mln_uart_inst_e
{
	UART0,
	UART1,
	UART2,
	#ifdef USART3
	UART3,
	#endif
	#ifdef USART4
	UART4,
	#endif
	#ifdef USART5
	UART5,
	#endif
} UART_t;

class mln_uart;

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

int mln_uart_stream_write(char character, FILE *f);

int mln_uart_stream_read(FILE *f);

class mln_uart
{
	USART_t* inst;

	mln_gpio pin_tx;
	mln_gpio pin_rx;

	uint8_t buffer[MLN_UART_BUF_SIZE];
	uint8_t index;

	FILE f;

	void (*isr)(void);

	void init_pins(UART_t new_inst)
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
	void init_stream(void)
	{
		mln_uart_stream_uart = this;

		mln_uart_stream_uart->f.get = mln_uart_stream_read;
		mln_uart_stream_uart->f.put = mln_uart_stream_write;
		mln_uart_stream_uart->f.flags = _FDEV_SETUP_RW;

		stdout = &mln_uart_stream_uart->f;
		stdin = &mln_uart_stream_uart->f;
	}

public:
	mln_uart(UART_t new_inst, uint32_t baud)
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

	/*
	* @brief Set ISR function of USART peripheral
	*/
	inline void set_isr(void (*new_isr)(void)) { isr = new_isr; }

	/*
	* @brief Write one byte to USART peripheral
	*/
	inline const void write(const uint8_t data)
	{
		while(is_busy_tx());

		inst->TXDATAL = data;
	}
	/*
	* @brief Read one byte from USART peripheral
	*/
	inline const uint8_t read(void)
	{
		while (is_busy_rx());

		return ((inst->RXDATAH & 0x1) << 8) | inst->RXDATAL;
	}

	/*
	* @brief Push new read data into RX buffer of SPI class
	*/
	inline void push(void)
	{
		buffer[index] = read();
		index = (index + 1) % MLN_UART_BUF_SIZE;
	}
	/*
	* @brief Pull data from RX buffer of SPI class
	*
	* @param new_buffer Buffer to copy data to
	*
	* @returns Length of data copied
	*/
	inline uint8_t pull(uint8_t* new_buffer)
	{
		memccpy(new_buffer, buffer, 0, MLN_UART_BUF_SIZE);
		memset(buffer, 0, sizeof(buffer));

		uint8_t copied = index;
		index = 0;

		return copied;
	}

	/*
	* @brief Check whether USART peripheral TX is busy
	*
	* @returns Whether USART peripheral TX is busy
	*/
	inline const bool is_busy_tx(void) { return !(inst->STATUS & USART_DREIF_bm); }
	/*
	* @brief Check whether USART peripheral RX is busy
	*
	* @returns Whether USART peripheral RX is busy
	*/
	inline const bool is_busy_rx(void) { return !(inst->STATUS & USART_RXCIF_bm); }
	/*
	* @brief Check whether USART class has data available
	*
	* @returns Amount of bytes available
	*/
	inline const uint8_t data_available(void) { return index; }

	/*
	* @brief Run the saved ISR function of the USART class
	*/
	inline const void run_isr(void) { isr(); }
}; //mln_uart

int mln_uart_stream_write(char character, FILE *f)
{
	mln_uart_stream_uart->write(character);
	return 0;
}

int mln_uart_stream_read(FILE *f)
{
	return mln_uart_stream_uart->read();
}

ISR(USART3_RXC_vect)
{
	mln_uart_stream_uart->push();
	if(!mln_uart_stream_uart->is_busy_rx())
	mln_uart_stream_uart->run_isr();
}

#endif //__MLN_UART_H__

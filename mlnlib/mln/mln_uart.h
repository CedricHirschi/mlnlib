/**
 * @file mln_uart.h
 * @author C�dric Hirschi (cedr02@live.com)
 * @brief This peripheral is used to communicate with USART.
 * @version 0.1
 * @date 2023-04-27
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __MLN_UART_H__
#define __MLN_UART_H__

#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <avr/interrupt.h>

#include "mln_gpio.h"

#ifndef F_CPU
#error "F_CPU not defined"
#endif

/**
 * @brief Maximum UART buffer size
 *
 * @note Currently RX only
 * @note Can be changed without further problems
 *
 */
#define MLN_UART_BUF_SIZE 32

#define MLN_UART0_PIN_TX PA0
#define MLN_UART0_PIN_RX PA1
#define MLN_UART1_PIN_TX PC0
#define MLN_UART1_PIN_RX PC1
#define MLN_UART2_PIN_TX PF0
#define MLN_UART2_PIN_RX PF1
#ifdef USART5
#ifndef MLN_UART_NUM_INSTS
#define MLN_UART_NUM_INSTS 6
#endif
#define MLN_UART5_PIN_TX PG0
#define MLN_UART5_PIN_RX PG1
#endif
#ifdef USART4
#ifndef MLN_UART_NUM_INSTS
#define MLN_UART_NUM_INSTS 5
#endif
#define MLN_UART4_PIN_TX PE0
#define MLN_UART4_PIN_RX PE1
#endif
#ifdef USART3
#ifndef MLN_UART_NUM_INSTS
#define MLN_UART_NUM_INSTS 4
#endif
#define MLN_UART3_PIN_TX PB0
#define MLN_UART3_PIN_RX PB1
#endif
#ifndef MLN_UART_NUM_INSTS
#define MLN_UART_NUM_INSTS 3
#endif

/**
 * @brief Macro to calculate register value from baud rate
 *
 */
#define MLN_UART_BAUD_NUM(BAUD) ((float)(F_CPU * 64 / (16 * (float)BAUD)) + 0.5)

/**
 * @brief USART peripheral class
 *
 */
class mln_uart;

/**
 * @brief USART stream (for printf functionality)
 *
 */
mln_uart *mln_uart_stream_uart;

/**
 * @brief Helper function to write from std stream to USART peripheral
 *
 */
int mln_uart_stream_write(char character, FILE *f);

/**
 * @brief Helper function to read USART peripheral to std stream
 *
 */
int mln_uart_stream_read(FILE *f);

/**
 * @brief USART peripheral class
 *
 */
class mln_uart
{
	USART_t *inst;

	mln_gpio pin_tx;
	mln_gpio pin_rx;

	uint8_t buffer[MLN_UART_BUF_SIZE];
	uint8_t index;

	FILE f;

	void (*isr)(void);

	/**
	 * @brief Helper function to initialize pins used by `mln_uart` class
	 *
	 */
	inline void init_pins(USART_t *new_inst)
	{
		switch ((new_inst - &USART0) / 2)
		{
		case 0:
			pin_tx = mln_gpio(MLN_UART0_PIN_TX, MLN_GPIO_DIR_OUTPUT);
			pin_rx = mln_gpio(MLN_UART0_PIN_RX, MLN_GPIO_DIR_INPUT);
			break;
		case 1:
			pin_tx = mln_gpio(MLN_UART1_PIN_TX, MLN_GPIO_DIR_OUTPUT);
			pin_rx = mln_gpio(MLN_UART1_PIN_RX, MLN_GPIO_DIR_INPUT);
			break;
		case 2:
			pin_tx = mln_gpio(MLN_UART2_PIN_TX, MLN_GPIO_DIR_OUTPUT);
			pin_rx = mln_gpio(MLN_UART2_PIN_RX, MLN_GPIO_DIR_INPUT);
			break;
#ifdef USART3
		case 3:
			pin_tx = mln_gpio(MLN_UART3_PIN_TX, MLN_GPIO_DIR_OUTPUT);
			pin_rx = mln_gpio(MLN_UART3_PIN_RX, MLN_GPIO_DIR_INPUT);
			break;
#endif
#ifdef USART4
		case 4:
			pin_tx = mln_gpio(MLN_UART4_PIN_TX, MLN_GPIO_DIR_OUTPUT);
			pin_rx = mln_gpio(MLN_UART4_PIN_RX, MLN_GPIO_DIR_INPUT);
			break;
#endif
#ifdef USART5
		case 5:
			pin_tx = mln_gpio(MLN_UART5_PIN_TX, MLN_GPIO_DIR_OUTPUT);
			pin_rx = mln_gpio(MLN_UART5_PIN_RX, MLN_GPIO_DIR_INPUT);
			break;
#endif
		}
	}
	/**
	 * @brief Helper function setup std stream for `mln_uart` class
	 *
	 */
	inline void init_stream(void)
	{
		mln_uart_stream_uart = this;

		mln_uart_stream_uart->f.get = mln_uart_stream_read;
		mln_uart_stream_uart->f.put = mln_uart_stream_write;
		mln_uart_stream_uart->f.flags = _FDEV_SETUP_RW;

		stdout = &mln_uart_stream_uart->f;
		stdin = &mln_uart_stream_uart->f;
	}

public:
	inline mln_uart(USART_t *new_inst, uint32_t baud)
	{
		if ((new_inst - &USART0) / 2 > MLN_UART_NUM_INSTS)
			return;

		memset(buffer, 0, sizeof(buffer));
		index = 0;

		inst = new_inst;

		init_pins(inst);

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
		while (is_busy_tx())
			;

		inst->TXDATAL = data;
	}
	/*
	 * @brief Read one byte from USART peripheral
	 */
	inline const uint8_t read(void)
	{
		while (is_busy_rx())
			;

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
	inline uint8_t pull(uint8_t *new_buffer)
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
}; // mln_uart

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

	if (!mln_uart_stream_uart->is_busy_rx())
		mln_uart_stream_uart->run_isr();
}

#endif //__MLN_UART_H__

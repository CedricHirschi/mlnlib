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
#define F_CPU					4000000UL
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

USART_t* MLN_UART_TO_USART(UART_t uart);

int mln_uart_stream_write(char character, FILE *f);
int mln_uart_stream_read(FILE *f);

class mln_uart
{
public:

	//////////////////////////////////////////////////////////////////////////
	
	USART_t* inst;
	
	mln_gpio pin_tx;
	mln_gpio pin_rx;
	
	uint8_t buffer[MLN_UART_BUF_SIZE];
	uint8_t index;
	
	FILE f;
	
	void (*isr)(void);
	
	//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	//////////////////////////////////////////////////////////////////////////
	
	mln_uart(UART_t new_inst, uint32_t baud);
	
	//////////////////////////////////////////////////////////////////////////
	
	void init_pins(UART_t new_inst);
	void init_stream(void);
	
	//////////////////////////////////////////////////////////////////////////
	
	void set_isr(void (*new_isr)(void));
	
	//////////////////////////////////////////////////////////////////////////

	void write(const uint8_t data);
	uint8_t read(void);
	
	void push(void);
	void pull(uint8_t* buffer);
	
	//////////////////////////////////////////////////////////////////////////
	
	bool is_busy_tx(void);
	bool is_busy_rx(void);
	
	bool data_available(void);
	
	//////////////////////////////////////////////////////////////////////////
	
private:
	
}; //mln_uart

// void mln_uart_init_stream(mln_uart* uart);

#endif //__MLN_UART_H__

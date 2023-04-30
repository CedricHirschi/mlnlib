/*
 * mln_common.h
 *
 * Created: 04.04.2023 09:36:38
 *  Author: cedr0
 */

#ifndef MLN_COMMON_H_
#define MLN_COMMON_H_

#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "mln_gpio.h"
#include "mln_uart.h"
#include "mln_timer.h"
#include "mln_vref.h"
#include "mln_adc.h"
#include "mln_dac.h"
#include "mln_opamp.h"
#include "mln_spi.h"
#include "mln_twi.h"
#include "../devices/mcp4822.h"

void mln_init(void)
{

#if F_CPU == 1000000UL
	CCP = CCP_IOREG_gc;
	CLKCTRL.OSCHFCTRLA = CLKCTRL_FRQSEL_1M_gc;
	#pragma message("F_CPU = 1MHz")
#elif F_CPU == 2000000UL
	CCP = CCP_IOREG_gc;
	CLKCTRL.OSCHFCTRLA = CLKCTRL_FRQSEL_2M_gc;
	#pragma message("F_CPU = 2MHz")
#elif F_CPU == 3000000UL
	CCP = CCP_IOREG_gc;
	CLKCTRL.OSCHFCTRLA = CLKCTRL_FRQSEL_3M_gc;
	#pragma message("F_CPU = 3MHz")
	
#elif F_CPU == 4000000UL
	#pragma message("F_CPU = 4MHz")
	
#elif F_CPU == 8000000UL
	CCP = CCP_IOREG_gc;
	CLKCTRL.OSCHFCTRLA = CLKCTRL_FRQSEL_8M_gc;
	#pragma message("F_CPU = 8MHz")
#elif F_CPU == 12000000UL
	CCP = CCP_IOREG_gc;
	CLKCTRL.OSCHFCTRLA = CLKCTRL_FRQSEL_12M_gc;
	#pragma message("F_CPU = 12MHz")
#elif F_CPU == 16000000UL
	CCP = CCP_IOREG_gc;
	CLKCTRL.OSCHFCTRLA = CLKCTRL_FRQSEL_16M_gc;
	#pragma message("F_CPU = 16MHz")
#elif F_CPU == 20000000UL
	CCP = CCP_IOREG_gc;
	CLKCTRL.OSCHFCTRLA = CLKCTRL_FRQSEL_20M_gc;
	#pragma message("F_CPU = 20MHz")
#elif F_CPU == 24000000UL
	CCP = CCP_IOREG_gc;
	CLKCTRL.OSCHFCTRLA = CLKCTRL_FRQSEL_24M_gc;
	#pragma message("F_CPU = 24MHz")

#else
	#error F_CPU not supported or not defined
#endif

}

#endif /* MLN_COMMON_H_ */
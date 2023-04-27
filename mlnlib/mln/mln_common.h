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
#include "mln_spi.h"
#include "../devices/mcp4822.h"

void mln_init(void)
{
	CCP = CCP_IOREG_gc;
	CLKCTRL.OSCHFCTRLA = CLKCTRL_FRQSEL_24M_gc;
}

#endif /* MLN_COMMON_H_ */
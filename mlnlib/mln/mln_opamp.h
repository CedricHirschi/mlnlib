/**
 * @file mln_opamp.h
 * @author Cédric Hirschi (cedr02@live.com)
 * @brief This peripheral are general purpose opamps which can be configured in various ways, including resistor ladders.
 * @version 0.1
 * @date 2023-04-27
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __MLN_OPAMP_H
#define __MLN_OPAMP_H

#include <avr/io.h>

#define OPAMP_DEVICE_0 0
#define OPAMP_DEVICE_1 1
#ifdef OP2CTRLA
#define OPAMP_DEVICE_2 2
#warning "OPAMP_DEVICE_2 is defined"
#endif

#define OPAMP_MODE_DIRECT 0
#define OPAMP_MODE_FOLLOWER 1
#define OPAMP_MODE_NONINVERTING 2
#define OPAMP_MODE_INVERTING 3

#define OPAMP_DIRECT_POS_INP 0
#define OPAMP_DIRECT_POS_WIP 1
#define OPAMP_DIRECT_POS_DAC 2
#define OPAMP_DIRECT_POS_GND 3
#define OPAMP_DIRECT_POS_VDDDIV2 4
#define OPAMP_DIRECT_POS_LINKOUT 5
#define OPAMP_DIRECT_POS_LINKWIP 6

#define OPAMP_DIRECT_NEG_INN (0 << 4)
#define OPAMP_DIRECT_NEG_WIP (1 << 4)
#define OPAMP_DIRECT_NEG_OUT (2 << 4)
#define OPAMP_DIRECT_NEG_DAC (3 << 4)

#define OPAMP_FOLLOWER_POS_INP 0
#define OPAMP_FOLLOWER_POS_WIP 1
#define OPAMP_FOLLOWER_POS_DAC 2
#define OPAMP_FOLLOWER_POS_GND 3
#define OPAMP_FOLLOWER_POS_VDDDIV2 4
#define OPAMP_FOLLOWER_POS_LINKOUT 5
#define OPAMP_FOLLOWER_POS_LINKWIP 6

#define OPAMP_NONINVERTING_POS_INP 0
#define OPAMP_NONINVERTING_POS_WIP 1
#define OPAMP_NONINVERTING_POS_DAC 2
#define OPAMP_NONINVERTING_POS_GND 3
#define OPAMP_NONINVERTING_POS_VDDDIV2 4
#define OPAMP_NONINVERTING_POS_LINKOUT 5
#define OPAMP_NONINVERTING_POS_LINKWIP 6

#define OPAMP_NONINVERTING_POS_INP 0
#define OPAMP_NONINVERTING_POS_WIP 1
#define OPAMP_NONINVERTING_POS_DAC 2
#define OPAMP_NONINVERTING_POS_GND 3
#define OPAMP_NONINVERTING_POS_VDDDIV2 4
#define OPAMP_NONINVERTING_POS_LINKOUT 5
#define OPAMP_NONINVERTING_POS_LINKWIP 6

#define OPAMP_INVERTING_POS_INP 0
#define OPAMP_INVERTING_POS_WIP 1
#define OPAMP_INVERTING_POS_DAC 2
#define OPAMP_INVERTING_POS_GND 3
#define OPAMP_INVERTING_POS_VDDDIV2 4
#define OPAMP_INVERTING_POS_LINKOUT 5
#define OPAMP_INVERTING_POS_LINKWIP 6

#define OPAMP_INVERTING_NEG_INP (1 << 4)
#define OPAMP_INVERTING_NEG_INN (2 << 4)
#define OPAMP_INVERTING_NEG_DAC (3 << 4)
#define OPAMP_INVERTING_NEG_LINKOUT (4 << 4)
#define OPAMP_INVERTING_NEG_GND (5 << 4)

#define OPAMP_MUXTOP_OUT 1
#define OPAMP_MUXTOP_VDD 2

#define OPAMP_MUXBOT_INP (1 << 2)
#define OPAMP_MUXBOT_INN (2 << 2)
#define OPAMP_MUXBOT_DAC (3 << 2)
#define OPAMP_MUXBOT_LINKOUT (4 << 2)
#define OPAMP_MUXBOT_GND (5 << 2)

#define OPAMP_MUXPOS_INP 0
#define OPAMP_MUXPOS_WIP 1
#define OPAMP_MUXPOS_DAC 2
#define OPAMP_MUXPOS_GND 3
#define OPAMP_MUXPOS_VDDDIV2 4
#define OPAMP_MUXPOS_LINKOUT 5
#define OPAMP_MUXPOS_LINKWIP 6

#define OPAMP_MUXNEG_INN (0 << 4)
#define OPAMP_MUXNEG_WIP (1 << 4)
#define OPAMP_MUXNEG_OUT (2 << 4)
#define OPAMP_MUXNEG_DAC (3 << 4)

#define OPAMP_MUXWIP_0 (0 << 5)
#define OPAMP_MUXWIP_1 (1 << 5)
#define OPAMP_MUXWIP_2 (2 << 5)
#define OPAMP_MUXWIP_3 (3 << 5)
#define OPAMP_MUXWIP_4 (4 << 5)
#define OPAMP_MUXWIP_5 (5 << 5)
#define OPAMP_MUXWIP_6 (6 << 5)
#define OPAMP_MUXWIP_7 (7 << 5)

#define OPAMP_TIMEBASE_US (ceil(F_CPU / 1000000.0) - 1)

/* typedef struct
{
	uint8_t opamp_n : 2;

	uint8_t mode : 2;
	bool runstdby : 1;
	bool output : 1;
	bool lowpower : 1;

	uint8_t gain : 3;

	uint8_t in_a : 3;
	uint8_t in_b : 2;
} OPAMP_INIT_t; */

typedef struct
{
	uint8_t opamp_n : 2;

	bool runstdby : 1;
	bool output : 1;
	bool lowpower : 1;

	uint8_t in_pos;
	uint8_t in_neg;
} OPAMP_DIRECT_INIT_t;

typedef struct
{
	uint8_t opamp_n : 2;

	bool runstdby : 1;
	bool output : 1;
	bool lowpower : 1;

	uint8_t in_pos;
} OPAMP_FOLLOWER_INIT_t;

typedef struct
{
	uint8_t opamp_n : 2;

	bool runstdby : 1;
	bool output : 1;
	bool lowpower : 1;

	uint8_t gain;

	uint8_t in_pos;
} OPAMP_NONINVERTING_INIT_t;

typedef struct
{
	uint8_t opamp_n : 2;

	bool runstdby : 1;
	bool output : 1;
	bool lowpower : 1;

	uint8_t gain;

	uint8_t in_pos;
	uint8_t in_neg;
} OPAMP_INVERTING_INIT_t;

class mln_opamp
{

	void init_resmux(uint8_t opamp_n, uint8_t muxbot, uint8_t muxwip, uint8_t muxtop)
	{
		switch (opamp_n)
		{
		case OPAMP_DEVICE_0:
			OPAMP.OP0RESMUX = muxbot | muxwip | muxtop;
			break;
		case OPAMP_DEVICE_1:
			OPAMP.OP1RESMUX = muxbot | muxwip | muxtop;
			break;
#ifdef OPAMP_DEVICE_2
		case OPAMP_DEVICE_2:
			OPAMP.OP2RESMUX = muxbot | muxwip | muxtop;
			break;
#endif
		}
	}

	void init_inmux(uint8_t opamp_n, uint8_t muxpos, uint8_t muxneg)
	{
		switch (opamp_n)
		{
		case OPAMP_DEVICE_0:
			OPAMP.OP0INMUX = muxpos | muxneg;
			break;
		case OPAMP_DEVICE_1:
			OPAMP.OP1INMUX = muxpos | muxneg;
			break;
#ifdef OPAMP_DEVICE_2
		case OPAMP_DEVICE_2:
			OPAMP.OP2INMUX = muxpos | muxneg;
			break;
#endif
		}
	}

	void enable(const bool runstdby, const bool output, const bool lowpower, const uint8_t opamp_n)
	{
		// TIMEBASE: TIMEBASE(calculate)
		OPAMP.TIMEBASE = OPAMP_TIMEBASE_US;
		// PWRCTRL: IRSEL(lowpower)
		OPAMP.PWRCTRL = (lowpower ? OPAMP_PWRCTRL_IRSEL_REDUCED_gc : OPAMP_PWRCTRL_IRSEL_FULL_gc);
		// OPnCTRLA: ALWAYSON(true) and RUNSTDBY(runstdby) and OUTMODE(output)
		switch (opamp_n)
		{
		case OPAMP_DEVICE_0:
			OPAMP.OP0CTRLA = OPAMP_ALWAYSON_bm | (runstdby ? OPAMP_RUNSTBY_bm : 0) | (output ? OPAMP_OP1CTRLA_OUTMODE_NORMAL_gc : 0);
			break;
		case OPAMP_DEVICE_1:
			OPAMP.OP1CTRLA = OPAMP_ALWAYSON_bm | (runstdby ? OPAMP_RUNSTBY_bm : 0) | (output ? OPAMP_OP1CTRLA_OUTMODE_NORMAL_gc : 0);
			break;
#ifdef OPAMP_DEVICE_2
		case OPAMP_DEVICE_2:
			OPAMP.OP2CTRLA = OPAMP_ALWAYSON_bm | (runstdby ? OPAMP_RUNSTBY_bm : 0) | (output ? OPAMP_OP2CTRLA_OUTMODE_bm : 0);
			break;
#endif
		}
		// CTRLA: ENABLE(true)
		OPAMP.CTRLA = OPAMP_ENABLE_bm;
	}

public:
	mln_opamp() = default;
	mln_opamp(const OPAMP_DIRECT_INIT_t &init)
	{
		// RESMUX: nothing to do

		// INMUX: MUXPOS(in_a) and MUXNEG(in_b)
		init_inmux(init.opamp_n, init.in_pos, init.in_neg);

		enable(init.runstdby, init.output, init.lowpower, init.opamp_n);
	}
	mln_opamp(const OPAMP_FOLLOWER_INIT_t &init)
	{
		// RESMUX: nothing to do
		// INMUX: MUXPOS(in_a) and MUXNEG(OUT)
		init_inmux(init.opamp_n, init.in_pos, OPAMP_MUXNEG_OUT);

		enable(init.runstdby, init.output, init.lowpower, init.opamp_n);
	}
	mln_opamp(const OPAMP_NONINVERTING_INIT_t &init)
	{
		// RESMUX: MUXBOT(GND) and MUXWIP(gain) and MUXTOP(OUT)
		init_resmux(init.opamp_n, OPAMP_MUXBOT_GND, init.gain, OPAMP_MUXTOP_OUT);
		// INMUX: MUXPOS(in_a) and MUXNEG(WIP)
		init_inmux(init.opamp_n, init.in_pos, OPAMP_MUXNEG_WIP);

		enable(init.runstdby, init.output, init.lowpower, init.opamp_n);
	}
	mln_opamp(const OPAMP_INVERTING_INIT_t &init)
	{
		// RESMUX: MUXBOT(in_a) and MUXWIP(gain) and MUXTOP(OUT)
		init_resmux(init.opamp_n, init.in_neg, init.gain, OPAMP_MUXTOP_OUT);
		// INMUX: MUXPOS(in_b) and MUXNEG(WIP)
		init_inmux(init.opamp_n, init.in_pos, OPAMP_MUXNEG_WIP);

		enable(init.runstdby, init.output, init.lowpower, init.opamp_n);
	}
};

#endif // __MLN_OPAMP_H
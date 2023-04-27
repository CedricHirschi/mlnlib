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

/**
 * @brief Opamp timebase calculation macro
 * 
 */
#define OPAMP_TIMEBASE_US (ceil(F_CPU / 1000000.0) - 1)

/**
 * @brief Opamp device selection enum
 * 
 */
typedef enum
{
	OPAMP_DEVICE_0 = 0,
	OPAMP_DEVICE_1,
#ifdef OP2CTRLA
	OPAMP_DEVICE_2
#endif
} mln_opamp_device_t;

/**
 * @brief Opamp mode selection enum
 * 
 */
typedef enum
{
	OPAMP_MODE_DIRECT = 0,
	OPAMP_MODE_FOLLOWER,
	OPAMP_MODE_NONINVERTING,
	OPAMP_MODE_INVERTING
} mln_opamp_mode_t;

/**
 * @brief Opamp positive input selection enum (direct mode)
 * 
 */
typedef enum
{
	OPAMP_DIRECT_IN_POS_INP = 0,
	OPAMP_DIRECT_IN_POS_WIP,
	OPAMP_DIRECT_IN_POS_DAC,
	OPAMP_DIRECT_IN_POS_GND,
	OPAMP_DIRECT_IN_POS_VDDDIV2,
	OPAMP_DIRECT_IN_POS_LINKOUT,
	OPAMP_DIRECT_IN_POS_LINKWIP
} mln_opamp_direct_in_pos_t;

/**
 * @brief Opamp negative input selection enum (direct mode)
 * 
 */
typedef enum
{
	OPAMP_DIRECT_IN_NEG_INN = 0,
	OPAMP_DIRECT_IN_NEG_WIP,
	OPAMP_DIRECT_IN_NEG_OUT,
	OPAMP_DIRECT_IN_NEG_DAC
} mln_opamp_direct_in_neg_t;

/**
 * @brief Opamp input selection enum (follower mode)
 * 
 */
typedef enum
{
	OPAMP_FOLLOWER_IN_INP = 0,
	OPAMP_FOLLOWER_IN_WIP,
	OPAMP_FOLLOWER_IN_DAC,
	OPAMP_FOLLOWER_IN_GND,
	OPAMP_FOLLOWER_IN_VDDDIV2,
	OPAMP_FOLLOWER_IN_LINKOUT,
	OPAMP_FOLLOWER_IN_LINKWIP
} mln_opamp_follower_in_t;

/**
 * @brief Opamp input selection enum (non-inverting mode)
 * 
 */
typedef enum
{
	OPAMP_NONINVERTING_IN_INP = 0,
	OPAMP_NONINVERTING_IN_WIP,
	OPAMP_NONINVERTING_IN_DAC,
	OPAMP_NONINVERTING_IN_GND,
	OPAMP_NONINVERTING_IN_VDDDIV2,
	OPAMP_NONINVERTING_IN_LINKOUT,
	OPAMP_NONINVERTING_IN_LINKWIP
} mln_opamp_noninverting_in_t;

/**
 * @brief Opamp positive input selection enum (inverting mode)
 * 
 */
typedef enum
{
	OPAMP_INVERTING_IN_POS_INP = 0,
	OPAMP_INVERTING_IN_POS_WIP,
	OPAMP_INVERTING_IN_POS_DAC,
	OPAMP_INVERTING_IN_POS_GND,
	OPAMP_INVERTING_IN_POS_VDDDIV2,
	OPAMP_INVERTING_IN_POS_LINKOUT,
	OPAMP_INVERTING_IN_POS_LINKWIP
} mln_opamp_inverting_in_pos_t;

/**
 * @brief Opamp negative input selection enum (inverting mode)
 * 
 */
typedef enum
{
	OPAMP_INVERTING_IN_NEG_INP = (1 << 4),
	OPAMP_INVERTING_IN_NEG_INN,
	OPAMP_INVERTING_IN_NEG_DAC,
	OPAMP_INVERTING_IN_NEG_LINKOUT,
	OPAMP_INVERTING_IN_NEG_GND
} mln_opamp_inverting_in_neg_t;

/**
 * @brief Opamp gain selection enum (non-inverting mode)
 * 
 */
typedef enum
{
	OPAMP_GAIN_NONINVERTING_1_06 = (0 << 5),
	OPAMP_GAIN_NONINVERTING_1_14 = (1 << 5),
	OPAMP_GAIN_NONINVERTING_1_33 = (2 << 5),
	OPAMP_GAIN_NONINVERTING_2 = (3 << 5),
	OPAMP_GAIN_NONINVERTING_2_67 = (4 << 5),
	OPAMP_GAIN_NONINVERTING_4 = (5 << 5),
	OPAMP_GAIN_NONINVERTING_8 = (6 << 5),
	OPAMP_GAIN_NONINVERTING_16 = (7 << 5)
} mln_opamp_gain_noninverting_t;

/**
 * @brief Opamp gain selection enum (inverting mode)
 * 
 */
typedef enum
{
	OPAMP_GAIN_INVERTING_0_06 = (0 << 5),
	OPAMP_GAIN_INVERTING_0_14 = (1 << 5),
	OPAMP_GAIN_INVERTING_0_33 = (2 << 5),
	OPAMP_GAIN_INVERTING_1 = (3 << 5),
	OPAMP_GAIN_INVERTING_1_67 = (4 << 5),
	OPAMP_GAIN_INVERTING_3 = (5 << 5),
	OPAMP_GAIN_INVERTING_7 = (6 << 5),
	OPAMP_GAIN_INVERTING_15 = (7 << 5)
} mln_opamp_gain_inverting_t;

/**
 * @brief Opamp direct configuration struct
 * 
 * @param opamp_n Opamp device (0-3)
 * @param runstdby If true, the peripheral is also running in device standby
 * @param output If true, the output is enabled
 * @param lowpower If true, the low power mode is enabled (reduced output range)
 * @param in_pos Positive input selection
 * @param in_neg Negative input selection
 *
 */
typedef struct
{
	mln_opamp_device_t opamp_n : 2;

	bool runstdby : 1;
	bool output : 1;
	bool lowpower : 1;

	mln_opamp_direct_in_pos_t in_pos;
	mln_opamp_direct_in_neg_t in_neg;
} opamp_direct_init_t;

/**
 * @brief Opamp follower configuration struct
 * 
 * @param opamp_n Opamp device (0-3)
 * @param runstdby If true, the peripheral is also running in device standby
 * @param output If true, the output is enabled
 * @param lowpower If true, the low power mode is enabled (reduced output range)
 * @param in Input selection
 *
 */
typedef struct
{
	mln_opamp_device_t opamp_n : 2;

	bool runstdby : 1;
	bool output : 1;
	bool lowpower : 1;

	mln_opamp_follower_in_t in;
} opamp_follower_init_t;

/**
 * @brief Opamp non-inverting configuration struct
 * 
 * @param opamp_n Opamp device (0-3)
 * @param runstdby If true, the peripheral is also running in device standby
 * @param output If true, the output is enabled
 * @param lowpower If true, the low power mode is enabled (reduced output range)
 * @param gain Gain selection
 * @param in Input selection
 *
 */
typedef struct
{
	mln_opamp_device_t opamp_n : 2;

	bool runstdby : 1;
	bool output : 1;
	bool lowpower : 1;

	mln_opamp_gain_noninverting_t gain;

	mln_opamp_noninverting_in_t in;
} opamp_noninverting_init_t;

/**
 * @brief Opamp inverting configuration struct
 * 
 * @param opamp_n Opamp device (0-3)
 * @param runstdby If true, the peripheral is also running in device standby
 * @param output If true, the output is enabled
 * @param lowpower If true, the low power mode is enabled (reduced output range)
 * @param gain Gain selection
 * @param in_pos Positive input selection
 * @param in_neg Negative input selection
 *
 */
typedef struct
{
	mln_opamp_device_t opamp_n : 2;

	bool runstdby : 1;
	bool output : 1;
	bool lowpower : 1;

	mln_opamp_gain_inverting_t gain;

	mln_opamp_inverting_in_pos_t in_pos;
	mln_opamp_inverting_in_neg_t in_neg;
} OPAMP_INVERTING_INIT_t;

/**
 * @brief Opamp namespace
 * 
 */
namespace mln_opamp
{
	/**
	 * @brief Helper function to set the RESMUX register
	 * 
	 * @param opamp  Device
	 * @param muxbot Bottom resistor mux
	 * @param muxwip Wiper resistor mux
	 * @param muxtop Top resistor mux
	 */
	void init_resmux(mln_opamp_device_t opamp, uint8_t muxbot, uint8_t muxwip, uint8_t muxtop)
	{
		switch (opamp)
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

	/**
	 * @brief Helper function to set the INMUX register
	 * 
	 * @param opamp_n Device
	 * @param muxpos  Positive input mux
	 * @param muxneg  Negative input mux
	 */
	void init_inmux(const uint8_t& opamp_n, const uint8_t& muxpos, const uint8_t& muxneg)
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

	/**
	 * @brief Helper function to enable the opamp
	 * 
	 * @param runstdby Run in standby
	 * @param output   Enable output
	 * @param lowpower Low power mode
	 * @param opamp_n  Device
	 */
	void enable(const bool runstdby, const bool output, const bool lowpower, const uint8_t opamp)
	{
		// TIMEBASE: TIMEBASE(calculate)
		OPAMP.TIMEBASE = OPAMP_TIMEBASE_US;
		// PWRCTRL: IRSEL(lowpower)
		OPAMP.PWRCTRL = (lowpower ? OPAMP_PWRCTRL_IRSEL_REDUCED_gc : OPAMP_PWRCTRL_IRSEL_FULL_gc);
		// OPnCTRLA: ALWAYSON(true) and RUNSTDBY(runstdby) and OUTMODE(output)
		switch (opamp)
		{
		case OPAMP_DEVICE_0:
			OPAMP.OP0CTRLA = OPAMP_ALWAYSON_bm | (runstdby ? OPAMP_RUNSTBY_bm : 0) | (output ? OPAMP_OP1CTRLA_OUTMODE_NORMAL_gc : 0);
			break;
		case OPAMP_DEVICE_1:
			OPAMP.OP1CTRLA = OPAMP_ALWAYSON_bm | (runstdby ? OPAMP_RUNSTBY_bm : 0) | (output ? OPAMP_OP1CTRLA_OUTMODE_NORMAL_gc : 0);
			break;
#ifdef OPAMP_DEVICE_2
		case OPAMP_DEVICE_2:
			OPAMP.OP2CTRLA = OPAMP_ALWAYSON_bm | (runstdby ? OPAMP_RUNSTBY_bm : 0) | (output ? OPAMP_OP2CTRLA_OUTMODE_NORMAL_gc : 0);
			break;
#endif
		}
		// CTRLA: ENABLE(true)
		OPAMP.CTRLA = OPAMP_ENABLE_bm;
	}

	/**
	 * @brief Construct a new mln_opamp object (direct)
	 * 
	 * @param init Opamp configuration struct (direct)
	 */
	init(const OPAMP_DIRECT_INIT_t &init)
	{
		// RESMUX: nothing to do

		// INMUX: MUXPOS(in_a) and MUXNEG(in_b)
		init_inmux(init.opamp, init.in_pos, init.in_neg);

		enable(init.runstdby, init.output, init.lowpower, init.opamp);
	}

	/**
	 * @brief Construct a new mln_opamp object (follower)
	 * 
	 * @param init Opamp configuration struct (follower)
	 */
	init(const OPAMP_FOLLOWER_INIT_t &init)
	{
		// RESMUX: nothing to do
		// INMUX: MUXPOS(in_a) and MUXNEG(OUT)
		init_inmux(init.opamp, init.in, OPAMP_MUXNEG_OUT);

		enable(init.runstdby, init.output, init.lowpower, init.opamp);
	}

	/**
	 * @brief Construct a new mln_opamp object (non-inverting)
	 * 
	 * @param init Opamp configuration struct (non-inverting)
	 */
	init(const OPAMP_NONINVERTING_INIT_t &init)
	{
		// RESMUX: MUXBOT(GND) and MUXWIP(gain) and MUXTOP(OUT)
		init_resmux(init.opamp, OPAMP_MUXBOT_GND, init.gain, OPAMP_MUXTOP_OUT);
		// INMUX: MUXPOS(in_a) and MUXNEG(WIP)
		init_inmux(init.opamp, init.in, OPAMP_MUXNEG_WIP);

		enable(init.runstdby, init.output, init.lowpower, init.opamp);
	}

	/**
	 * @brief Construct a new mln_opamp object (inverting)
	 * 
	 * @param init Opamp configuration struct (inverting)
	 */
	init(const OPAMP_INVERTING_INIT_t &init)
	{
		// RESMUX: MUXBOT(in_a) and MUXWIP(gain) and MUXTOP(OUT)
		init_resmux(init.opamp, init.in_neg, init.gain, OPAMP_MUXTOP_OUT);
		// INMUX: MUXPOS(in_b) and MUXNEG(WIP)
		init_inmux(init.opamp, init.in_pos, OPAMP_MUXNEG_WIP);

		enable(init.runstdby, init.output, init.lowpower, init.opamp);
	}
};

#endif // __MLN_OPAMP_H
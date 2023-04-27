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

#define MLN_OPAMP_MUXTOP_OUT 1
#define MLN_OPAMP_MUXTOP_VDD 2

#define MLN_OPAMP_MUXBOT_INP (1 << 2)
#define MLN_OPAMP_MUXBOT_INN (2 << 2)
#define MLN_OPAMP_MUXBOT_DAC (3 << 2)
#define MLN_OPAMP_MUXBOT_LINKOUT (4 << 2)
#define MLN_OPAMP_MUXBOT_GND (5 << 2)

#define MLN_OPAMP_MUXPOS_INP 0
#define MLN_OPAMP_MUXPOS_WIP 1
#define MLN_OPAMP_MUXPOS_DAC 2
#define MLN_OPAMP_MUXPOS_GND 3
#define MLN_OPAMP_MUXPOS_VDDDIV2 4
#define MLN_OPAMP_MUXPOS_LINKOUT 5
#define MLN_OPAMP_MUXPOS_LINKWIP 6

#define MLN_OPAMP_MUXNEG_INN (0 << 4)
#define MLN_OPAMP_MUXNEG_WIP (1 << 4)
#define MLN_OPAMP_MUXNEG_OUT (2 << 4)
#define MLN_OPAMP_MUXNEG_DAC (3 << 4)

/**
 * @brief Opamp timebase calculation macro
 *
 */
#define MLN_OPAMP_TIMEBASE_US (ceil(F_CPU / 1000000.0) - 1)

/**
 * @brief Opamp device selection enum
 *
 */
typedef enum
{
	MLN_OPAMP_DEVICE_0 = 0,
	MLN_OPAMP_DEVICE_1,
#ifdef OP2CTRLA
	MLN_OPAMP_DEVICE_2
#endif
} mln_opamp_device_t;

/**
 * @brief Opamp mode selection enum
 *
 */
typedef enum
{
	MLN_OPAMP_MODE_DIRECT = 0,
	MLN_OPAMP_MODE_FOLLOWER,
	MLN_OPAMP_MODE_NONINVERTING,
	MLN_OPAMP_MODE_INVERTING
} mln_opamp_mode_t;

/**
 * @brief Opamp positive input selection enum (direct mode)
 *
 */
typedef enum
{
	MLN_OPAMP_DIRECT_IN_POS_INP = 0,
	MLN_OPAMP_DIRECT_IN_POS_WIP,
	MLN_OPAMP_DIRECT_IN_POS_DAC,
	MLN_OPAMP_DIRECT_IN_POS_GND,
	MLN_OPAMP_DIRECT_IN_POS_VDDDIV2,
	MLN_OPAMP_DIRECT_IN_POS_LINKOUT,
	MLN_OPAMP_DIRECT_IN_POS_LINKWIP
} mln_opamp_direct_in_pos_t;

/**
 * @brief Opamp negative input selection enum (direct mode)
 *
 */
typedef enum
{
	MLN_OPAMP_DIRECT_IN_NEG_INN = 0,
	MLN_OPAMP_DIRECT_IN_NEG_WIP,
	MLN_OPAMP_DIRECT_IN_NEG_OUT,
	MLN_OPAMP_DIRECT_IN_NEG_DAC
} mln_opamp_direct_in_neg_t;

/**
 * @brief Opamp input selection enum (follower mode)
 *
 */
typedef enum
{
	MLN_OPAMP_FOLLOWER_IN_INP = 0,
	MLN_OPAMP_FOLLOWER_IN_WIP,
	MLN_OPAMP_FOLLOWER_IN_DAC,
	MLN_OPAMP_FOLLOWER_IN_GND,
	MLN_OPAMP_FOLLOWER_IN_VDDDIV2,
	MLN_OPAMP_FOLLOWER_IN_LINKOUT,
	MLN_OPAMP_FOLLOWER_IN_LINKWIP
} mln_opamp_follower_in_t;

/**
 * @brief Opamp input selection enum (non-inverting mode)
 *
 */
typedef enum
{
	MLN_OPAMP_NONINVERTING_IN_INP = 0,
	MLN_OPAMP_NONINVERTING_IN_WIP,
	MLN_OPAMP_NONINVERTING_IN_DAC,
	MLN_OPAMP_NONINVERTING_IN_GND,
	MLN_OPAMP_NONINVERTING_IN_VDDDIV2,
	MLN_OPAMP_NONINVERTING_IN_LINKOUT,
	MLN_OPAMP_NONINVERTING_IN_LINKWIP
} mln_opamp_noninverting_in_t;

/**
 * @brief Opamp positive input selection enum (inverting mode)
 *
 */
typedef enum
{
	MLN_OPAMP_INVERTING_IN_POS_INP = 0,
	MLN_OPAMP_INVERTING_IN_POS_WIP,
	MLN_OPAMP_INVERTING_IN_POS_DAC,
	MLN_OPAMP_INVERTING_IN_POS_GND,
	MLN_OPAMP_INVERTING_IN_POS_VDDDIV2,
	MLN_OPAMP_INVERTING_IN_POS_LINKOUT,
	MLN_OPAMP_INVERTING_IN_POS_LINKWIP
} mln_opamp_inverting_in_pos_t;

/**
 * @brief Opamp negative input selection enum (inverting mode)
 *
 */
typedef enum
{
	MLN_OPAMP_INVERTING_IN_NEG_INP = (1 << 4),
	MLN_OPAMP_INVERTING_IN_NEG_INN,
	MLN_OPAMP_INVERTING_IN_NEG_DAC,
	MLN_OPAMP_INVERTING_IN_NEG_LINKOUT,
	MLN_OPAMP_INVERTING_IN_NEG_GND
} mln_opamp_inverting_in_neg_t;

/**
 * @brief Opamp gain selection enum (non-inverting mode)
 *
 */
typedef enum
{
	MLN_OPAMP_GAIN_NONINVERTING_1_06 = (0 << 5),
	MLN_OPAMP_GAIN_NONINVERTING_1_14 = (1 << 5),
	MLN_OPAMP_GAIN_NONINVERTING_1_33 = (2 << 5),
	MLN_OPAMP_GAIN_NONINVERTING_2 = (3 << 5),
	MLN_OPAMP_GAIN_NONINVERTING_2_67 = (4 << 5),
	MLN_OPAMP_GAIN_NONINVERTING_4 = (5 << 5),
	MLN_OPAMP_GAIN_NONINVERTING_8 = (6 << 5),
	MLN_OPAMP_GAIN_NONINVERTING_16 = (7 << 5)
} mln_opamp_gain_noninverting_t;

/**
 * @brief Opamp gain selection enum (inverting mode)
 *
 */
typedef enum
{
	MLN_OPAMP_GAIN_INVERTING_0_06 = (0 << 5),
	MLN_OPAMP_GAIN_INVERTING_0_14 = (1 << 5),
	MLN_OPAMP_GAIN_INVERTING_0_33 = (2 << 5),
	MLN_OPAMP_GAIN_INVERTING_1 = (3 << 5),
	MLN_OPAMP_GAIN_INVERTING_1_67 = (4 << 5),
	MLN_OPAMP_GAIN_INVERTING_3 = (5 << 5),
	MLN_OPAMP_GAIN_INVERTING_7 = (6 << 5),
	MLN_OPAMP_GAIN_INVERTING_15 = (7 << 5)
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
	mln_opamp_device_t opamp : 2;

	bool runstdby : 1;
	bool output : 1;
	bool lowpower : 1;

	mln_opamp_direct_in_pos_t in_pos;
	mln_opamp_direct_in_neg_t in_neg;
} mln_opamp_direct_init_t;

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
	mln_opamp_device_t opamp : 2;

	bool runstdby : 1;
	bool output : 1;
	bool lowpower : 1;

	mln_opamp_follower_in_t in;
} mln_opamp_follower_init_t;

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
	mln_opamp_device_t opamp : 2;

	bool runstdby : 1;
	bool output : 1;
	bool lowpower : 1;

	mln_opamp_gain_noninverting_t gain;

	mln_opamp_noninverting_in_t in;
} mln_opamp_noninverting_init_t;

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
	mln_opamp_device_t opamp = MLN_OPAMP_DEVICE_0;

	bool runstdby = false;
	bool output = true;
	bool lowpower = false;

	mln_opamp_gain_inverting_t gain = MLN_OPAMP_GAIN_INVERTING_1;

	mln_opamp_inverting_in_pos_t in_pos = MLN_OPAMP_INVERTING_IN_POS_VDDDIV2;
	mln_opamp_inverting_in_neg_t in_neg = MLN_OPAMP_INVERTING_IN_NEG_INN;
} mln_opamp_inverting_init_t;

/**
 * @brief Opamp peripheral namespace
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
	inline const void init_resmux(const mln_opamp_device_t &opamp, const uint8_t &muxbot, const uint8_t &muxwip, const uint8_t &muxtop)
	{
		switch (opamp)
		{
		case MLN_OPAMP_DEVICE_0:
			OPAMP.OP0RESMUX = muxbot | muxwip | muxtop;
			break;
		case MLN_OPAMP_DEVICE_1:
			OPAMP.OP1RESMUX = muxbot | muxwip | muxtop;
			break;
#ifdef MLN_OPAMP_DEVICE_2
		case MLN_OPAMP_DEVICE_2:
			OPAMP.OP2RESMUX = muxbot | muxwip | muxtop;
			break;
#endif
		}
	}

	/**
	 * @brief Helper function to set the INMUX register
	 *
	 * @param opamp Device
	 * @param muxpos  Positive input mux
	 * @param muxneg  Negative input mux
	 */
	inline const void init_inmux(const mln_opamp_device_t &opamp, const uint8_t &muxpos, const uint8_t &muxneg)
	{
		switch (opamp)
		{
		case MLN_OPAMP_DEVICE_0:
			OPAMP.OP0INMUX = muxpos | muxneg;
			break;
		case MLN_OPAMP_DEVICE_1:
			OPAMP.OP1INMUX = muxpos | muxneg;
			break;
#ifdef MLN_OPAMP_DEVICE_2
		case MLN_OPAMP_DEVICE_2:
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
	 *
	 * @note Is being called by the `init` functions
	 */
	inline const void enable(const mln_opamp_device_t &opamp, const bool runstdby, const bool output, const bool lowpower)
	{
		// TIMEBASE: TIMEBASE(calculate)
		OPAMP.TIMEBASE = MLN_OPAMP_TIMEBASE_US;
		// PWRCTRL: IRSEL(lowpower)
		OPAMP.PWRCTRL = (lowpower ? OPAMP_PWRCTRL_IRSEL_REDUCED_gc : OPAMP_PWRCTRL_IRSEL_FULL_gc);
		// OPnCTRLA: ALWAYSON(true) and RUNSTDBY(runstdby) and OUTMODE(output)
		switch (opamp)
		{
		case MLN_OPAMP_DEVICE_0:
			OPAMP.OP0CTRLA = OPAMP_ALWAYSON_bm | (runstdby ? OPAMP_RUNSTBY_bm : 0) | (output ? OPAMP_OP1CTRLA_OUTMODE_NORMAL_gc : 0);
			break;
		case MLN_OPAMP_DEVICE_1:
			OPAMP.OP1CTRLA = OPAMP_ALWAYSON_bm | (runstdby ? OPAMP_RUNSTBY_bm : 0) | (output ? OPAMP_OP1CTRLA_OUTMODE_NORMAL_gc : 0);
			break;
#ifdef MLN_OPAMP_DEVICE_2
		case MLN_OPAMP_DEVICE_2:
			OPAMP.OP2CTRLA = OPAMP_ALWAYSON_bm | (runstdby ? OPAMP_RUNSTBY_bm : 0) | (output ? OPAMP_OP2CTRLA_OUTMODE_NORMAL_gc : 0);
			break;
#endif
		}
		// CTRLA: ENABLE(true)
		OPAMP.CTRLA = OPAMP_ENABLE_bm;
	}

	/**
	 * @brief Enable Opamp peripheral
	 *
	 * @note Doesn't configure/enable single Opamps
	 *
	 */
	inline const void enable(void) { OPAMP.CTRLA |= OPAMP_ENABLE_bm; }

	/**
	 * @brief Disable Opamp peripheral
	 *
	 * @warning Disables all Opamps
	 *
	 */
	inline const void disable(void) { OPAMP.CTRLA &= ~OPAMP_ENABLE_bm; }

	/**
	 * @brief Construct a new mln_opamp object (direct)
	 *
	 * @param init Opamp configuration struct (direct)
	 */
	inline const void init(const mln_opamp_direct_init_t &init)
	{
		// RESMUX: nothing to do

		// INMUX: MUXPOS(in_pos) and MUXNEG(in_neg)
		init_inmux(init.opamp, init.in_pos, init.in_neg);

		enable(init.opamp, init.runstdby, init.output, init.lowpower);
	}

	/**
	 * @brief Construct a new mln_opamp object (follower)
	 *
	 * @param init Opamp configuration struct (follower)
	 */
	inline const void init(const mln_opamp_follower_init_t &init)
	{
		// RESMUX: nothing to do
		// INMUX: MUXPOS(in) and MUXNEG(OUT)
		init_inmux(init.opamp, init.in, MLN_OPAMP_MUXNEG_OUT);

		enable(init.opamp, init.runstdby, init.output, init.lowpower);
	}

	/**
	 * @brief Construct a new mln_opamp object (non-inverting)
	 *
	 * @param init Opamp configuration struct (non-inverting)
	 */
	inline const void init(const mln_opamp_noninverting_init_t &init)
	{
		// RESMUX: MUXBOT(GND) and MUXWIP(gain) and MUXTOP(OUT)
		init_resmux(init.opamp, MLN_OPAMP_MUXBOT_GND, init.gain, MLN_OPAMP_MUXTOP_OUT);
		// INMUX: MUXPOS(in) and MUXNEG(WIP)
		init_inmux(init.opamp, init.in, MLN_OPAMP_MUXNEG_WIP);

		enable(init.opamp, init.runstdby, init.output, init.lowpower);
	}

	/**
	 * @brief Construct a new mln_opamp object (inverting)
	 *
	 * @param init Opamp configuration struct (inverting)
	 */
	inline const void init(const mln_opamp_inverting_init_t &init)
	{
		// RESMUX: MUXBOT(in_neg) and MUXWIP(gain) and MUXTOP(OUT)
		init_resmux(init.opamp, init.in_neg, init.gain, MLN_OPAMP_MUXTOP_OUT);
		// INMUX: MUXPOS(in_pos) and MUXNEG(WIP)
		init_inmux(init.opamp, init.in_pos, MLN_OPAMP_MUXNEG_WIP);

		enable(init.opamp, init.runstdby, init.output, init.lowpower);
	}
};

#endif // __MLN_OPAMP_H
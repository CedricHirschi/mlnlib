#ifndef __MLN_OPAMP_H
#define __MLN_OPAMP_H

#include <avr/io.h>

namespace OPA_SETUP
{
	typedef enum CONFIG_e
	{
		TOPINS,
		FOLLOWER,
		NONINV,
		INV
	} CONFIG_t;

	typedef enum GAIN_NONINV_e
	{
		GAIN_1_06,
		GAIN_1_14,
		GAIN_1_33,
		GAIN_2,
		GAIN_2_67,
		GAIN_4,
		GAIN_8,
		GAIN_16
	} GAIN_NONINV_t;

	typedef enum GAIN_INV_e
	{
		GAIN_INV_0_06,
		GAIN_INV_0_14,
		GAIN_INV_0_33,
		GAIN_INV_1,
		GAIN_INV_1_67,
		GAIN_INV_3,
		GAIN_INV_7,
		GAIN_INV_15
	} GAIN_INV_t;

	typedef enum PIN_e
	{
		PIN_INN,
		PIN_INP,
		PIN_OUT
	} PIN_t;

	typedef enum MUX_e
	{
		MUXNEG,
		MUXPOS,
		MUXTOP,
		MUXBOT,
		MUXWIP
	} MUX_t;

	typedef enum MUXNEG_IN_e
	{
		MUXNEG_INN,
		MUXNEG_WIP,
		MUXNEG_OUT,
		MUXNEG_DAC
	} MUXNEG_IN_t;

	typedef enum MUXPOS_IN_e
	{
		MUXPOS_INP,
		MUXPOS_WIP,
		MUXPOS_DAC,
		MUXPOS_GND,
		MUXPOS_VDDDIV2,
		MUXPOS_LINKOUT,
		MUXPOS_LINKWIP
	} MUXPOS_IN_t;

	typedef enum MUXTOP_IN_e
	{
		MUXTOP_OFF,
		MUXTOP_OUT,
		MUXTOP_VDD
	} MUXTOP_IN_t;

	typedef enum MUXBOT_IN_e
	{
		MUXBOT_OFF,
		MUXBOT_INP,
		MUXBOT_INN,
		MUXBOT_DAC,
		MUXBOT_LINKOUT,
		MUXBOT_GND
	} MUXBOT_IN_t;

	typedef enum MUXWIP_IN_e
	{
		MUXWIP_WIP0,
		MUXWIP_WIP1,
		MUXWIP_WIP2,
		MUXWIP_WIP3,
		MUXWIP_WIP4,
		MUXWIP_WIP5,
		MUXWIP_WIP6,
		MUXWIP_WIP7
	} MUXWIP_IN_t;
}

typedef struct OPAMP_SETUP_s
{
	uint8_t opamp_n = 0;

	OPA_SETUP::CONFIG_t config = OPA_SETUP::TOPINS;

	OPA_SETUP::GAIN_INV_t gain_inv = OPA_SETUP::GAIN_INV_0_06;
	OPA_SETUP::GAIN_NONINV_t gain_noninv = OPA_SETUP::GAIN_1_06;

	OPA_SETUP::MUXPOS_IN_t pin_pos = OPA_SETUP::MUXPOS_INP;
	OPA_SETUP::MUXNEG_IN_t pin_neg = OPA_SETUP::MUXNEG_INN;

	bool run_in_standby = false;
	bool output = true;
} OPAMP_SETUP_t;

class mln_opamp
{
	OPAMP_SETUP_t *setup;

	void init_pin(OPA_SETUP::PIN_t pin)
	{
		switch (setup->opamp_n)
		{
		case 0:
			switch (pin)
			{
			case OPA_SETUP::PIN_INN:
				PORTD.DIRCLR = PIN3_bm;
				PORTD.PIN3CTRL = 0x00;
				break;
			case OPA_SETUP::PIN_INP:
				PORTD.DIRCLR = PIN1_bm;
				PORTD.PIN1CTRL = 0x00;
				break;
			case OPA_SETUP::PIN_OUT:
				PORTD.DIRSET = PIN2_bm;
				PORTD.PIN2CTRL = 0x00;
				break;
			}
			break;
		case 1:
			switch (pin)
			{
			case OPA_SETUP::PIN_INN:
				PORTD.DIRCLR = PIN7_bm;
				PORTD.PIN7CTRL = 0x00;
				break;
			case OPA_SETUP::PIN_INP:
				PORTD.DIRCLR = PIN4_bm;
				PORTD.PIN4CTRL = 0x00;
				break;
			case OPA_SETUP::PIN_OUT:
				PORTD.DIRSET = PIN5_bm;
				PORTD.PIN5CTRL = 0x00;
				break;
			}
			break;
#ifdef OPAMP2
		case 2:
			switch (pin)
			{
			case OPA_SETUP::PIN_INN:
				PORTE.DIRCLR = PIN3_bm;
				PORTE.PIN3CTRL = 0x00;
				break;
			case OPA_SETUP::PIN_INP:
				PORTE.DIRCLR = PIN1_bm;
				PORTE.PIN1CTRL = 0x00;
				break;
			case OPA_SETUP::PIN_OUT:
				PORTE.DIRSET = PIN2_bm;
				PORTE.PIN2CTRL = 0x00;
				break;
			}
			break;
#endif
		}
	}

	void set_mux(OPA_SETUP::MUX_t mux, uint8_t value)
	{
		switch (setup->opamp_n)
		{
		case 0:
			switch (mux)
			{
			case OPA_SETUP::MUXNEG:
				OPAMP.OP0INMUX = (OPAMP.OP0INMUX & ~0x70) | (value << 4);
				break;
			case OPA_SETUP::MUXPOS:
				OPAMP.OP0INMUX = (OPAMP.OP0INMUX & ~0x07) | value;
				break;
			case OPA_SETUP::MUXTOP:
				OPAMP.OP0RESMUX = (OPAMP.OP0RESMUX & ~0x03) | value;
				break;
			case OPA_SETUP::MUXBOT:
				OPAMP.OP0RESMUX = (OPAMP.OP0RESMUX & ~0x1C) | (value << 2);
				break;
			case OPA_SETUP::MUXWIP:
				OPAMP.OP0RESMUX = (OPAMP.OP0RESMUX & ~0xE0) | (value << 5);
				break;
			}
			break;
		case 1:
			switch (mux)
			{
			case OPA_SETUP::MUXNEG:
				OPAMP.OP1INMUX = (OPAMP.OP1INMUX & ~0x70) | (value << 4);
				break;
			case OPA_SETUP::MUXPOS:
				OPAMP.OP1INMUX = (OPAMP.OP1INMUX & ~0x07) | value;
				break;
			case OPA_SETUP::MUXTOP:
				OPAMP.OP1RESMUX = (OPAMP.OP1RESMUX & ~0x03) | value;
				break;
			case OPA_SETUP::MUXBOT:
				OPAMP.OP1RESMUX = (OPAMP.OP1RESMUX & ~0x1C) | (value << 2);
				break;
			case OPA_SETUP::MUXWIP:
				OPAMP.OP1RESMUX = (OPAMP.OP1RESMUX & ~0xE0) | (value << 5);
				break;
			}
			break;
#ifdef OPAMP2
		case 2:
			switch (mux)
			{
			case OPA_SETUP::MUXNEG:
				OPAMP.OP2INMUX = (OPAMP.OP2INMUX & ~0x70) | (value << 4);
				break;
			case OPA_SETUP::MUXPOS:
				OPAMP.OP2INMUX = (OPAMP.OP2INMUX & ~0x07) | value;
				break;
			case OPA_SETUP::MUXTOP:
				OPAMP.OP2RESMUX = (OPAMP.OP2RESMUX & ~0x03) | value;
				break;
			case OPA_SETUP::MUXBOT:
				OPAMP.OP2RESMUX = (OPAMP.OP2RESMUX & ~0x1C) | (value << 2);
				break;
			case OPA_SETUP::MUXWIP:
				OPAMP.OP2RESMUX = (OPAMP.OP2RESMUX & ~0xE0) | (value << 5);
				break;
			}
			break;
#endif
		}
	}

	void init_pins(void)
	{
		if (setup->output)
			init_pin(OPA_SETUP::PIN_OUT);

		switch (setup->config)
		{
		case OPA_SETUP::TOPINS:
			if (setup->pin_neg == OPA_SETUP::MUXNEG_INN)
				init_pin(OPA_SETUP::PIN_INN);
			if (setup->pin_pos == OPA_SETUP::MUXPOS_INP)
				init_pin(OPA_SETUP::PIN_INP);
			break;
		case OPA_SETUP::FOLLOWER:
			if (setup->pin_pos == OPA_SETUP::MUXPOS_INP)
				init_pin(OPA_SETUP::PIN_INP);
			break;
		case OPA_SETUP::NONINV:
			if (setup->pin_pos == OPA_SETUP::MUXPOS_INP)
				init_pin(OPA_SETUP::PIN_INP);
			break;
		case OPA_SETUP::INV:
			if (setup->pin_neg == OPA_SETUP::MUXNEG_INN)
				init_pin(OPA_SETUP::PIN_INN);
			break;
		}
	}

	void set_input_muxes(void)
	{
		switch (setup->config)
		{
		case OPA_SETUP::TOPINS:
			set_mux(OPA_SETUP::MUXNEG, setup->pin_neg);
			set_mux(OPA_SETUP::MUXPOS, setup->pin_pos);
			break;
		case OPA_SETUP::FOLLOWER:
			set_mux(OPA_SETUP::MUXNEG, OPA_SETUP::MUXNEG_OUT);
			set_mux(OPA_SETUP::MUXPOS, setup->pin_pos);
			break;
		case OPA_SETUP::NONINV:
			set_mux(OPA_SETUP::MUXNEG, OPA_SETUP::MUXNEG_WIP);
			set_mux(OPA_SETUP::MUXPOS, setup->pin_pos);
			break;
		case OPA_SETUP::INV:
			set_mux(OPA_SETUP::MUXNEG, OPA_SETUP::MUXNEG_WIP);
			set_mux(OPA_SETUP::MUXPOS, OPA_SETUP::MUXPOS_VDDDIV2);
			break;
		}
	}

	void set_wiper_muxes(void)
	{
		switch (setup->config)
		{
		case OPA_SETUP::TOPINS:
			break;
		case OPA_SETUP::FOLLOWER:
			break;
		case OPA_SETUP::NONINV:
			set_mux(OPA_SETUP::MUXBOT, OPA_SETUP::MUXBOT_GND);
			set_mux(OPA_SETUP::MUXWIP, (OPA_SETUP::MUXWIP_IN_t)setup->gain_noninv);
			set_mux(OPA_SETUP::MUXTOP, OPA_SETUP::MUXTOP_OUT);
			break;
		case OPA_SETUP::INV:
			set_mux(OPA_SETUP::MUXBOT, setup->pin_neg);
			set_mux(OPA_SETUP::MUXWIP, (OPA_SETUP::MUXWIP_IN_t)setup->gain_inv);
			set_mux(OPA_SETUP::MUXTOP, OPA_SETUP::MUXTOP_OUT);
			break;
		}
	}

public:
	mln_opamp() = default;

	mln_opamp(OPAMP_SETUP_t *new_setup)
	{
		setup = new_setup;

		// setup pins
		init_pins();

		// PORTD.PIN4CTRL = PORT_ISC_INPUT_DISABLE_gc;
		// PORTD.PIN7CTRL = PORT_ISC_INPUT_DISABLE_gc;

		// setup input muxes
		set_input_muxes();

		// setup wiper muxes
		set_wiper_muxes();

		switch (setup->opamp_n)
		{
		case 0:
			OPAMP.OP0CTRLA = OPAMP_OP0CTRLA_OUTMODE_NORMAL_gc | OPAMP_ALWAYSON_bm;
			break;
		case 1:
			OPAMP.OP1CTRLA = OPAMP_OP1CTRLA_OUTMODE_NORMAL_gc | OPAMP_ALWAYSON_bm;
			break;
#ifdef OPAMP2
		case 2:
			OPAMP.OP2CTRLA = OPAMP_OP2CTRLA_OUTMODE_NORMAL_gc | OPAMP_ALWAYSON_bm;
			break;
#endif
		}

		// OPAMP.OP1INMUX = OPAMP_OP0INMUX_MUXNEG_WIP_gc | OPAMP_OP0INMUX_MUXPOS_INP_gc;
		// OPAMP.OP1RESMUX = OPAMP_OP0RESMUX_MUXBOT_GND_gc | OPAMP_OP0RESMUX_MUXWIP_WIP3_gc | OPAMP_OP0RESMUX_MUXTOP_OUT_gc;

		OPAMP.CTRLA = OPAMP_ENABLE_bm;

		// while (!has_settled());
	}

	bool has_settled(void)
	{
		switch (setup->opamp_n)
		{
		case 0:
			return (OPAMP.OP0STATUS & OPAMP_SETTLED_bm);
		case 1:
			return (OPAMP.OP1STATUS & OPAMP_SETTLED_bm);
#ifdef OPAMP2
		case 2:
			return (OPAMP.OP2STATUS & OPAMP_SETTLED_bm);
#endif
		}

		return false;
	}
};

#endif // __MLN_OPAMP_H
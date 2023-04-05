/*
 * mln_dac.h
 *
 * Created: 05.04.2023 17:57:20
 *  Author: cedr0
 */


#ifndef MLN_DAC_H_
#define MLN_DAC_H_

struct mln_dac
{
	bool standby = false;
	bool buffer = false;

	void config(bool new_standby, bool new_buffer)
	{
		standby = new_standby;
		buffer = new_buffer;
	}

	void start(void)
	{
		DAC0.CTRLA |= 0x01;

		buffer ? (DAC0.CTRLA |= 0x40) : (DAC0.CTRLA &= ~0x40);
		standby ? (DAC0.CTRLA |= 0x80) : (DAC0.CTRLA &= ~0x80);
	}

	void stop(void)
	{
		DAC0.CTRLA &= ~0x01;
	}

	void set(uint16_t value)
	{
		DAC0.DATA = value << 6;
	}
};

#endif /* MLN_DAC_H_ */
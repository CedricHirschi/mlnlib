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
	
	/*
	* @brief Configure the DAC peripheral
	* 
	* @param standby Whether peripheral is active when device is in standby
	* @param buffer Whether DAC output is output on pin
	*/
	inline void config(bool standby, bool buffer)
	{
		buffer ? (DAC0.CTRLA |= 0x40) : (DAC0.CTRLA &= ~0x40);
		standby ? (DAC0.CTRLA |= 0x80) : (DAC0.CTRLA &= ~0x80);
	}
	
	/*
	* @brief Enable the DAC peripheral
	*/
	inline const void enable(void) { DAC0.CTRLA |= DAC_ENABLE_bm; }
	/*
	* @brief Disable the DAC peripheral
	*/
	inline const void disable(void) { DAC0.CTRLA &= ~DAC_ENABLE_bm; }
	
	/*
	* @brief Set the output of the DAC peripheral
	*
	* @param value The output to set to
	*/
	inline const void set(uint16_t value) { DAC0.DATA = value << 6; }
};

#endif /* MLN_DAC_H_ */
/*
 * mln_vref.h
 *
 * Created: 05.04.2023 17:23:37
 *  Author: cedr0
 */


#ifndef MLN_VREF_H_
#define MLN_VREF_H_

typedef enum mln_vref_per_e
{
	ADCREF,
	DACREF
} VREF_PER_t;

typedef enum mln_vref_sel_e
{
	_1V024,
	_2V048,
	_4V096,
	_2V500,
	VDD = 0x5,
	VREFA
} VREF_SEL_t;

struct mln_vref
{
	bool standby = false;

	/*
	* @brief Configure the VREF peripheral
	*
	* @param new_standby Whether peripheral is active when device is in standby
	*/
	void config(bool new_standby) { standby = new_standby; }
	
	/*
	* @brief Set voltages of VREF peripheral
	*
	* @param dac Reference voltage of DAC peripheral to set
	* @param adc Reference voltage of ADC peripheral to set
	*/
	void set(VREF_SEL_t dac, VREF_SEL_t adc)
	{
		VREF.DAC0REF = (standby << 7) | dac;
		VREF.ADC0REF = (standby << 7) | adc;
	}
};

#endif /* MLN_VREF_H_ */
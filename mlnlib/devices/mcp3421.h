/*
 * mcp3421.h
 *
 * Created: 06.05.2023 13:24:06
 *  Author: cedr0
 */ 


#ifndef MCP3421_H_
#define MCP3421_H_

const uint8_t mcp3421_reset_arr[] = {0x06};
const uint8_t mcp3421_config_arr[] = {0b00011100};

class mcp3421
{
	mln_twi twi;
	
	uint8_t buffer[5];
	
public:
	mcp3421(TWI_t* new_twi)
	{
		twi = mln_twi(new_twi);
		
		generalcall_reset();
		configure();
	}
	
	inline const bool generalcall_reset(void) { return twi.write(0x00, mcp3421_reset_arr, 1); }
	
	inline const bool configure(void) { return twi.write(0x68, mcp3421_config_arr, 1); }
	
	inline const bool read(int32_t& value)
	{
		if(!twi.read(0x68, buffer, 5)) return false;
		
		value = ((int32_t)(buffer[0] & 0x03) << 16) | ((int32_t)buffer[1] << 8) | (int32_t)(buffer[2]);
		
		return true;
	}
	
};


#endif /* MCP3421_H_ */
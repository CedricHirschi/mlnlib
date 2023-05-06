/*
 * mcp3421.h
 *
 * Created: 06.05.2023 13:24:06
 *  Author: cedr0
 */ 


#ifndef MCP3421_H_
#define MCP3421_H_

class mcp3421
{
	mln_twi twi;
	
public:
	mcp3421(TWI_t* new_twi)
	{
		twi = mln_twi(new_twi);
		
		printf("mcp3421 resetting...\t");
		
		uint8_t reset[] = {0x06};
			
		twi.write(0x00, reset, 1);
		
		_delay_ms(10);
		
		printf("done\n");
		printf("mcp3421 configuring...\t");
		
		uint8_t config[] = {0b00011100};
		
		twi.write(0x68, config, 1);
		
		printf("done\n");
	}
	
	int32_t read(void)
	{
		uint8_t buffer[5] = {0};
		
		if(!twi.read(0x68, buffer, 5)) return 0;
		
		return ((int32_t)(buffer[0] & 0x03) << 16) | ((int32_t)buffer[1] << 8) | (int32_t)(buffer[2]);
	}
	
};


#endif /* MCP3421_H_ */
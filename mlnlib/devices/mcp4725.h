/**
 * @file mcp4725.h
 * @author C?dric Hirschi (cedr02@live.com)
 * @brief MCP4725 DAC driver
 * @version 0.1
 * @date 2023-05-02
 *
 * @copyright Copyright (c) 2023
 *
 */


#ifndef MCP4725_H_
#define MCP4725_H_

#define MLN_MCP4725_C_FAST (0 << 5)
#define MLN_MCP4725_C_DAC (1 << 5)
#define MLN_MCP4725_C_EEPROM (2 << 5)

typedef enum
{
	MLN_MCP4725_PD_NORMAL = (0 << 3),
	MLN_MCP4725_PD_1k = (1 << 3),
	MLN_MCP4725_PD_100k = (2 << 3),
	MLN_MCP4725_PD_500k = (3 << 3)
} mln_mcp4725_pd_t;

class mcp4725
{
	mln_twi twi;
	uint8_t address;

	mln_mcp4725_pd_t powerdown;

	uint8_t buffer[2];

public:
	mcp4725(TWI_t *new_twi = &TWI0, uint8_t new_address = 0x60, mln_mcp4725_pd_t new_powerdown = MLN_MCP4725_PD_NORMAL)
	{
		address = new_address;
		twi = mln_twi(new_twi, 800000UL);

		power(new_powerdown);

		printf("powerdown = %u\taddress = 0x%x\n", powerdown, address);
	}

	inline const bool write(uint16_t data, bool eeprom = false)
	{
		buffer[0] = powerdown | (eeprom ? MLN_MCP4725_C_EEPROM : MLN_MCP4725_C_FAST) | (uint8_t)(data >> 8);
		buffer[1] = (uint8_t)(data & 0xFF);

		return twi.write(address, buffer, 2);
	}

	inline bool power(mln_mcp4725_pd_t new_powerdown)
	{
		buffer[0] = powerdown;
		buffer[1] = 0x00;

		return twi.write(address, buffer, 2);
	}
};



#endif /* MCP4725_H_ */
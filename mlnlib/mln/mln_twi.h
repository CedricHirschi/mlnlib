/**
 * @file mln_twi.h
 * @author C�dric Hirschi (cedr02@live.com)
 * @brief This peripheral is used to communicate with TWI/I2C.
 * @version 0.1
 * @date 2023-04-27
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef MLN_TWI_H_
#define MLN_TWI_H_

#include <avr/io.h>

#define MLN_TWI_TRISE 300UL

/**
 * @brief TWI peripheral class
 *
 */
class mln_twi
{
	int32_t I2Ccount;

	/**
	 * @brief Read one byte from TWI bus
	 *
	 * @returns Latest byte received from TWI bus
	 *
	 * @note Might wait for reception
	 *
	 */
	inline uint8_t read(void)
	{
		if (I2Ccount != 0)
			I2Ccount--;

		while (!(TWI0.MSTATUS & TWI_RIF_bm))
			;

		uint8_t data = TWI0.MDATA;

		if (I2Ccount != 0)
			TWI0.MCTRLB = TWI_MCMD_RECVTRANS_gc;
		else
			TWI0.MCTRLB = TWI_ACKACT_NACK_gc;

		return data;
	}

	/**
	 * @brief Read one last byte from TWI bus
	 *
	 * @returns Latest byte received from TWI bus
	 *
	 * @note Might wait for reception, tells slave that this should be last byte
	 *
	 */
	inline uint8_t readLast(void)
	{
		I2Ccount = 0;

		return read();
	}

	/**
	 * @brief Send one byte to TWI bus
	 *
	 * @param data Byte to be sent
	 *
	 * @returns Whether transaction was successful
	 * @retval true Transaction was successful
	 * @retval false Transaction was not acknowledged
	 *
	 * @note Waits for completed transaction, does not start nor stop it
	 *
	 */
	inline bool write(const uint8_t data)
	{
		TWI0.MCTRLB = TWI_MCMD_RECVTRANS_gc;

		TWI0.MDATA = data;

		while (!(TWI0.MSTATUS & TWI_WIF_bm))
			;
		if (TWI0.MSTATUS & (TWI_ARBLOST_bm | TWI_BUSERR_bm))
			return false;

		return !(TWI0.MSTATUS & TWI_RXACK_bm);
	}

	/**
	 * @brief Start TWI transaction
	 *
	 * @param address Address of slave device to address
	 * @param readcount Transaction type (0 = write, 1-2147483647 = read this many bytes, -1 = read unspecified bytes)
	 *
	 * @returns Whether transaction was started successfully
	 * @retval true Transaction was started successfully
	 * @retval false Arbitration lost or bus error, address was not acknowledged
	 *
	 */
	inline bool start(const uint8_t address, const int32_t readcount)
	{
		bool read;
		if (readcount == 0)
			read = 0;
		else
		{
			I2Ccount = readcount;
			read = 1;
		}
		TWI0.MADDR = address << 1 | read;

		while (!(TWI0.MSTATUS & (TWI_WIF_bm | TWI_RIF_bm)))
			;

		if (TWI0.MSTATUS & TWI_ARBLOST_bm)
		{
			while (!(TWI0.MSTATUS & TWI_BUSSTATE_IDLE_gc))
				;

			return false;
		}
		else if (TWI0.MSTATUS & TWI_RXACK_bm)
		{
			TWI0.MCTRLB |= TWI_MCMD_STOP_gc;

			while (!(TWI0.MSTATUS & TWI_BUSSTATE_IDLE_gc))
				;

			return false;
		}

		return true;
	}

	/**
	 * @brief Restart TWI transaction
	 *
	 * @param Address of slave device to address
	 * @param readcount Transaction type (0 = write, 1-2147483647 = read this many bytes, -1 = read unspecified bytes)
	 *
	 * @returns Whether transaction was started successfully
	 * @retval true Transaction was started successfully
	 * @retval false Arbitration lost or bus error, address was not acknowledged
	 *
	 */
	inline bool restart(const uint8_t address, const int32_t readcount)
	{
		return start(address, readcount);
	}

	/**
	 * @brief Stop TWI transaction
	 *
	 */
	inline void stop(void)
	{
		TWI0.MCTRLB |= TWI_MCMD_STOP_gc; // Send STOP
		while (!(TWI0.MSTATUS & TWI_BUSSTATE_IDLE_gc))
			; // Wait for bus to return to idle state
	}

public:
	/**
	 * @brief Default mln_twi initializer
	 *
	 * @param frequency TWI frequency to be used (default 100000)
	 *
	 */
	inline mln_twi(const uint32_t frequency = 100000UL)
	{
		uint32_t baud = ((F_CPU / frequency) - (((F_CPU * MLN_TWI_TRISE) / 1000) / 1000) / 1000 - 10) / 2;
		TWI0.MBAUD = (uint8_t)baud;

		TWI0.MCTRLA = TWI_ENABLE_bm;

		TWI0.MSTATUS = TWI_BUSSTATE_IDLE_gc;
	}

	/**
	 * @brief Read certain amount of bytes from TWI slave
	 *
	 * @param address Address of the slave device
	 * @param data Pointer to data buffer to be save data in
	 * @param data_length Amount of bytes to be read
	 *
	 * @note Starts and waits for completed transaction, stops it
	 *
	 */
	inline void read(const uint8_t address, uint8_t *data, const uint8_t data_length)
	{
		start(address, data_length);

		for (uint8_t i = 0; i < data_length; i++)
			data[i] = read();

		stop();
	}

	/**
	 * @brief Send certain amount of bytes to TWI slave
	 *
	 * @param address Address of the slave device
	 * @param data Pointer to data buffer to be sent
	 * @param data_length Length of data buffer to be sent
	 *
	 * @returns Whether transaction was successful
	 * @retval true Transaction was successful
	 * @retval false Transaction at address could not be started or was not acknowledged
	 *
	 * @note Starts and waits for completed transaction, stops it
	 *
	 */
	inline bool write(const uint8_t address, const uint8_t *data, const uint8_t data_length)
	{
		if (!start(address, 0))
			return false;

		for (uint8_t i = 0; i < data_length; i++)
			if (!write(data[i]))
				return false;

		stop();

		return true;
	}
};

#endif
/**
 * @file mln_spi.h
 * @author Cédric Hirschi (cedr02@live.com)
 * @brief This peripheral is used to communicate with SPI.
 * @version 0.1
 * @date 2023-04-27
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __MLN_SPI_H__
#define __MLN_SPI_H__

#include <avr/io.h>

#include "mln_gpio.h"

/**
 * @brief Maximum SPI buffer size
 *
 * @note Currently RX only
 * @note Can be changed without further problems
 *
 */
#define MLN_SPI_BUF_SIZE 32

#define MLN_SPI0_PIN_MOSI PA4 // ALT: PE0, PG4
#define MLN_SPI0_PIN_MISO PA5 // ALT: PE1, PG5
#define MLN_SPI0_PIN_SCK PA6  // ALT: PE2, PG6
#define MLN_SPI0_PIN_SS PA7	  // ALT: PE3, PG7

#define MLN_SPI1_PIN_MOSI PC0 // ALT: PB4, PC4
#define MLN_SPI1_PIN_MISO PC1 // ALT: PB5, PC5
#define MLN_SPI1_PIN_SCK PC2  // ALT: PB6, PC5
#define MLN_SPI1_PIN_SS PC3	  // ALT: PB7, PC7

/**
 * @brief SPI peripheral speed bitmaps
 *
 * @note Can be changed without further problems
 *
 */
#define MLN_SPI_CLKSEL (SPI_CLK2X_bm)

/**
 * @brief SPI peripheral class
 *
 */
class mln_spi
{
	SPI_t *spi;
	mln_gpio cs;

public:
	/**
	 * @brief Default `mln_spi` class initializer
	 *
	 * @note Selects SPI0 as peripheral and no CS pin as well as SPI mode 0
	 *
	 */
	inline mln_spi() : spi(&SPI0) {}
	/**
	 * @brief Initialize `mln_spi` class from specific SPI peripheral
	 *
	 * @param new_spi SPI peripheral to use
	 *
	 * @note Uses no CS pin as well as SPI mode 0
	 *
	 */
	inline mln_spi(SPI_t *new_spi)
	{
		spi = new_spi;

		mln_gpio(((spi == &SPI0) ? MLN_SPI0_PIN_MOSI : MLN_SPI1_PIN_MOSI), MLN_GPIO_DIR_OUTPUT);
		mln_gpio(((spi == &SPI0) ? MLN_SPI0_PIN_MISO : MLN_SPI1_PIN_MISO), MLN_GPIO_DIR_INPUT);
		mln_gpio(((spi == &SPI0) ? MLN_SPI0_PIN_SCK : MLN_SPI1_PIN_SCK), MLN_GPIO_DIR_OUTPUT);

		spi->CTRLA = SPI_ENABLE_bm | SPI_MASTER_bm | MLN_SPI_CLKSEL;
	}
	/**
	 * @brief Initialize `mln_spi` class from specific SPI peripheral and mode
	 *
	 * @param new_spi SPI peripheral to use
	 * @param mode SPI mode to be used (0-3)
	 *
	 * @note Uses no CS pin
	 *
	 */
	inline mln_spi(SPI_t *new_spi, uint8_t mode)
	{
		spi = new_spi;

		mln_gpio(((spi == &SPI0) ? MLN_SPI0_PIN_MOSI : MLN_SPI1_PIN_MOSI), MLN_GPIO_DIR_OUTPUT);
		mln_gpio(((spi == &SPI0) ? MLN_SPI0_PIN_MISO : MLN_SPI1_PIN_MISO), MLN_GPIO_DIR_INPUT);
		mln_gpio(((spi == &SPI0) ? MLN_SPI0_PIN_SCK : MLN_SPI1_PIN_SCK), MLN_GPIO_DIR_OUTPUT);

		spi->CTRLA = SPI_ENABLE_bm | SPI_MASTER_bm | MLN_SPI_CLKSEL;
		spi->CTRLB = mode;
	}
	/**
	 * @brief Initialize `mln_spi` class from specific SPI peripheral and cs pin
	 *
	 * @param new_spi SPI peripheral to use
	 * @param new_cs CS pin to be used
	 *
	 * @note Uses SPI mode 0
	 *
	 */
	inline mln_spi(SPI_t *new_spi, mln_pin_t& new_cs)
	{
		spi = new_spi;
		cs = mln_gpio(new_cs, MLN_GPIO_DIR_OUTPUT);

		mln_gpio(((spi == &SPI0) ? MLN_SPI0_PIN_MOSI : MLN_SPI1_PIN_MOSI), MLN_GPIO_DIR_OUTPUT);
		mln_gpio(((spi == &SPI0) ? MLN_SPI0_PIN_MISO : MLN_SPI1_PIN_MISO), MLN_GPIO_DIR_INPUT);
		mln_gpio(((spi == &SPI0) ? MLN_SPI0_PIN_SCK : MLN_SPI1_PIN_SCK), MLN_GPIO_DIR_OUTPUT);

		spi->CTRLA = SPI_ENABLE_bm | SPI_MASTER_bm | MLN_SPI_CLKSEL;
	}
	/**
	 * @brief Initialize `mln_spi` class from specific SPI peripheral and cs pin as well as SPI mode
	 *
	 * @param new_spi SPI peripheral to use
	 * @param new_cs CS pin to bes used
	 * @param mode SPI mode to be used (0-3)
	 *
	 */
	inline mln_spi(SPI_t *new_spi, mln_pin_t& new_cs, const uint8_t mode)
	{
		spi = new_spi;
		cs = mln_gpio(new_cs, MLN_GPIO_DIR_OUTPUT);

		mln_gpio(((spi == &SPI0) ? MLN_SPI0_PIN_MOSI : MLN_SPI1_PIN_MOSI), MLN_GPIO_DIR_OUTPUT);
		mln_gpio(((spi == &SPI0) ? MLN_SPI0_PIN_MISO : MLN_SPI1_PIN_MISO), MLN_GPIO_DIR_INPUT);
		mln_gpio(((spi == &SPI0) ? MLN_SPI0_PIN_SCK : MLN_SPI1_PIN_SCK), MLN_GPIO_DIR_OUTPUT);

		spi->CTRLA = SPI_ENABLE_bm | SPI_MASTER_bm | MLN_SPI_CLKSEL;
		spi->CTRLB = mode;
	}

	/**
	 * @brief Exchange package with SPI peripheral
	 *
	 * @param[in,out] *buffer Pointer to data buffer to be exchanged
	 * @param[in] length Length of buffer
	 *
	 */
	inline const void exchange(uint8_t *buffer, uint8_t length)
	{
		cs.clear();

		while (length--)
		{
			spi->DATA = *buffer;

			while (!(spi->INTFLAGS & SPI_RXCIF_bm));

			*buffer = spi->DATA;
			buffer++;
		}

		cs.clear();
	}
	/**
	 * @brief Send package with SPI peripheral
	 *
	 * @param[in] *buffer Pointer to data buffer to be sent
	 * @param[in] length Length of buffer
	 *
	 */
	inline const void write(uint8_t *buffer, uint8_t length)
	{
		cs.clear();

		while (length--)
		{
			spi->DATA = *buffer;
			buffer++;

			while (!(spi->INTFLAGS & SPI_RXCIF_bm));
		}

		cs.set();
	}
	/**
	 * @brief Receive package with SPI peripheral
	 *
	 * @param[out] *buffer Pointer to data buffer to be received
	 * @param[in] length Length of buffer
	 *
	 */
	inline const void read(uint8_t *buffer, uint8_t length)
	{
		cs.clear();

		while (length--)
		{
			spi->DATA = 0;

			while (!(spi->INTFLAGS & SPI_RXCIF_bm));

			*buffer = spi->DATA;
			buffer++;
		}

		cs.set();
	}
}; // mln_spi

#endif //__MLN_SPI_H__

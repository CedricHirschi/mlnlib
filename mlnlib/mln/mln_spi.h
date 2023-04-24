/*
 * mln_spi.h
 *
 * Created: 04.04.2023 21:24:31
 * Author: cedr0
 */

#ifndef __MLN_SPI_H__
#define __MLN_SPI_H__

#include <avr/io.h>

#include "mln_gpio.h"

#define MLN_SPI_BUF_SIZE 32

#define MLN_SPI0_PIN_MOSI PA4 // ALT: PE0, PG4
#define MLN_SPI0_PIN_MISO PA5 // ALT: PE1, PG5
#define MLN_SPI0_PIN_SCK PA6  // ALT: PE2, PG6
#define MLN_SPI0_PIN_SS PA7	  // ALT: PE3, PG7

#define MLN_SPI1_PIN_MOSI PC0 // ALT: PB4, PC4
#define MLN_SPI1_PIN_MISO PC1 // ALT: PB5, PC5
#define MLN_SPI1_PIN_SCK PC2  // ALT: PB6, PC5
#define MLN_SPI1_PIN_SS PC3	  // ALT: PB7, PC7

#define MLN_SPI_CLKSEL (SPI_CLK2X_bm)

class mln_spi
{
	SPI_t *spi;
	mln_gpio cs;

public:
	mln_spi() : spi(&SPI0) {}
	mln_spi(SPI_t *new_spi)
	{
		spi = new_spi;

		mln_gpio(((spi == &SPI0) ? MLN_SPI0_PIN_MOSI : MLN_SPI1_PIN_MOSI), OUTPUT);
		mln_gpio(((spi == &SPI0) ? MLN_SPI0_PIN_MISO : MLN_SPI1_PIN_MISO), INPUT);
		mln_gpio(((spi == &SPI0) ? MLN_SPI0_PIN_SCK : MLN_SPI1_PIN_SCK), OUTPUT);

		spi->CTRLA = SPI_ENABLE_bm | SPI_MASTER_bm | MLN_SPI_CLKSEL;
	}
	mln_spi(SPI_t *new_spi, uint8_t mode)
	{
		spi = new_spi;

		mln_gpio(((spi == &SPI0) ? MLN_SPI0_PIN_MOSI : MLN_SPI1_PIN_MOSI), OUTPUT);
		mln_gpio(((spi == &SPI0) ? MLN_SPI0_PIN_MISO : MLN_SPI1_PIN_MISO), INPUT);
		mln_gpio(((spi == &SPI0) ? MLN_SPI0_PIN_SCK : MLN_SPI1_PIN_SCK), OUTPUT);

		spi->CTRLA = SPI_ENABLE_bm | SPI_MASTER_bm | MLN_SPI_CLKSEL;
		spi->CTRLB = mode;
	}
	mln_spi(SPI_t *new_spi, PIN_t new_cs)
	{
		spi = new_spi;
		cs = mln_gpio(new_cs, OUTPUT);

		mln_gpio(((spi == &SPI0) ? MLN_SPI0_PIN_MOSI : MLN_SPI1_PIN_MOSI), OUTPUT);
		mln_gpio(((spi == &SPI0) ? MLN_SPI0_PIN_MISO : MLN_SPI1_PIN_MISO), INPUT);
		mln_gpio(((spi == &SPI0) ? MLN_SPI0_PIN_SCK : MLN_SPI1_PIN_SCK), OUTPUT);

		spi->CTRLA = SPI_ENABLE_bm | SPI_MASTER_bm | MLN_SPI_CLKSEL;
	}
	mln_spi(SPI_t *new_spi, PIN_t new_cs, uint8_t mode)
	{
		spi = new_spi;
		cs = mln_gpio(new_cs, OUTPUT);

		mln_gpio(((spi == &SPI0) ? MLN_SPI0_PIN_MOSI : MLN_SPI1_PIN_MOSI), OUTPUT);
		mln_gpio(((spi == &SPI0) ? MLN_SPI0_PIN_MISO : MLN_SPI1_PIN_MISO), INPUT);
		mln_gpio(((spi == &SPI0) ? MLN_SPI0_PIN_SCK : MLN_SPI1_PIN_SCK), OUTPUT);

		spi->CTRLA = SPI_ENABLE_bm | SPI_MASTER_bm | MLN_SPI_CLKSEL;
		spi->CTRLB = mode;
	}

	/*
	* @brief Exchange package with SPI peripheral
	*
	* @param[in] *buffer Pointer to data buffer to be sent
	* @param[out] *buffer Pointer to data buffer received
	* @param length Length of buffer
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
	/*
	* @brief Send package with SPI peripheral
	*
	* @param *buffer Pointer to data buffer to be sent
	* @param length Length of buffer
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
	/*
	* @brief Receive package with SPI peripheral
	*
	* @param[out] *buffer Pointer to data buffer to be received
	* @param length Length of buffer
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

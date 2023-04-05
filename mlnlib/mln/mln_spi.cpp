/*
 * mln_spi.cpp
 *
 * Created: 04.04.2023 21:24:30
 * Author: cedr0
 */

#include "mln_spi.h"

mln_spi::mln_spi(SPI_t *new_spi, PIN_t new_cs, uint8_t mode)
{
	spi = new_spi;
	cs = mln_gpio(new_cs, OUTPUT);

	mln_gpio(((spi == &SPI0) ? MLN_SPI0_PIN_MOSI : MLN_SPI1_PIN_MOSI), OUTPUT);
	mln_gpio(((spi == &SPI0) ? MLN_SPI0_PIN_MISO : MLN_SPI1_PIN_MISO), INPUT);
	mln_gpio(((spi == &SPI0) ? MLN_SPI0_PIN_SCK : MLN_SPI1_PIN_SCK), OUTPUT);

	spi->CTRLA = SPI_ENABLE_bm | SPI_MASTER_bm | SPI_CLK2X_bm;
	spi->CTRLB = mode;
}

mln_spi::mln_spi(SPI_t *new_spi, PIN_t new_cs)
{
	spi = new_spi;
	cs = mln_gpio(new_cs, OUTPUT);

	mln_gpio(((spi == &SPI0) ? MLN_SPI0_PIN_MOSI : MLN_SPI1_PIN_MOSI), OUTPUT);
	mln_gpio(((spi == &SPI0) ? MLN_SPI0_PIN_MISO : MLN_SPI1_PIN_MISO), INPUT);
	mln_gpio(((spi == &SPI0) ? MLN_SPI0_PIN_SCK : MLN_SPI1_PIN_SCK), OUTPUT);

	spi->CTRLA = SPI_ENABLE_bm | SPI_MASTER_bm | SPI_CLK2X_bm;
}

mln_spi::mln_spi(SPI_t *new_spi, uint8_t mode)
{
	spi = new_spi;

	mln_gpio(((spi == &SPI0) ? MLN_SPI0_PIN_MOSI : MLN_SPI1_PIN_MOSI), OUTPUT);
	mln_gpio(((spi == &SPI0) ? MLN_SPI0_PIN_MISO : MLN_SPI1_PIN_MISO), INPUT);
	mln_gpio(((spi == &SPI0) ? MLN_SPI0_PIN_SCK : MLN_SPI1_PIN_SCK), OUTPUT);

	spi->CTRLA = SPI_ENABLE_bm | SPI_MASTER_bm | SPI_CLK2X_bm;
	spi->CTRLB = mode;
}

mln_spi::mln_spi(SPI_t *new_spi)
{
	spi = new_spi;

	mln_gpio(((spi == &SPI0) ? MLN_SPI0_PIN_MOSI : MLN_SPI1_PIN_MOSI), OUTPUT);
	mln_gpio(((spi == &SPI0) ? MLN_SPI0_PIN_MISO : MLN_SPI1_PIN_MISO), INPUT);
	mln_gpio(((spi == &SPI0) ? MLN_SPI0_PIN_SCK : MLN_SPI1_PIN_SCK), OUTPUT);

	spi->CTRLA = SPI_ENABLE_bm | SPI_MASTER_bm | SPI_CLK2X_bm;
}

mln_spi::mln_spi()
{
}

void mln_spi::exchange(uint8_t *buffer, uint8_t length)
{
	cs.clear();

	while (length--)
	{
		spi->DATA = *buffer;
		while (!(spi->INTFLAGS & SPI_RXCIF_bm))
			;
		*buffer = spi->DATA;
		buffer++;
	}

	cs.clear();
}

void mln_spi::write(uint8_t *buffer, uint8_t length)
{
	cs.clear();

	while (length--)
	{
		spi->DATA = *buffer;
		buffer++;
		while (!(spi->INTFLAGS & SPI_RXCIF_bm))
			;
	}

	cs.set();
}

void mln_spi::read(uint8_t *buffer, uint8_t length)
{
	cs.clear();

	while (length--)
	{
		spi->DATA = 0;
		while (!(spi->INTFLAGS & SPI_RXCIF_bm))
			;
		*buffer = spi->DATA;
		buffer++;
	}

	cs.set();
}
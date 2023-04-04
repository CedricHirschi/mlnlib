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

#define MLN_SPI_BUF_SIZE	32

#define MLN_SPI0_PIN_MOSI		PA4		// ALT: PE0, PG4
#define MLN_SPI0_PIN_MISO		PA5		// ALT: PE1, PG5
#define MLN_SPI0_PIN_SCK		PA6		// ALT: PE2, PG6
#define MLN_SPI0_PIN_SS			PA7		// ALT: PE3, PG7

#define MLN_SPI1_PIN_MOSI		PC0		// ALT: PB4, PC4
#define MLN_SPI1_PIN_MISO		PC1		// ALT: PB5, PC5
#define MLN_SPI1_PIN_SCK		PC2		// ALT: PB6, PC5
#define MLN_SPI1_PIN_SS			PC3		// ALT: PB7, PC7

class mln_spi
{
public:
	SPI_t *spi;
	mln_gpio cs;

	mln_spi(SPI_t *new_spi, PIN_t cs, uint8_t mode);
	mln_spi(SPI_t *new_spi, PIN_t cs);
	mln_spi(SPI_t *new_spi);
	mln_spi();

	void exchange(uint8_t* buffer, uint8_t length);
	void write(uint8_t* buffer, uint8_t length);
	void read(uint8_t* buffer, uint8_t length);

private:

}; //mln_spi

#endif //__MLN_SPI_H__

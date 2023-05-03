/**
 * @file mln_gpio.h
 * @author C�dric Hirschi (cedr02@live.com)
 * @brief This peripheral is used to control the data flow from the pins of the device.
 * @version 0.1
 * @date 2023-04-27
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __MLN_GPIO_H__
#define __MLN_GPIO_H__

#include <avr/io.h>

#ifdef PORTA
#define PA0       \
	(mln_pin_t)   \
	{             \
		&PORTA, 0, (1 << 0) \
	}
#define PA1       \
	(mln_pin_t)   \
	{             \
		&PORTA, 1, (1 << 1) \
	}
#define PA2       \
	(mln_pin_t)   \
	{             \
		&PORTA, 2, (1 << 2) \
	}
#define PA3       \
	(mln_pin_t)   \
	{             \
		&PORTA, 3, (1 << 3) \
	}
#define PA4       \
	(mln_pin_t)   \
	{             \
		&PORTA, 4, (1 << 4) \
	}
#define PA5       \
	(mln_pin_t)   \
	{             \
		&PORTA, 5, (1 << 5) \
	}
#define PA6       \
	(mln_pin_t)   \
	{             \
		&PORTA, 6, (1 << 6) \
	}
#define PA7       \
	(mln_pin_t)   \
	{             \
		&PORTA, 7, (1 << 7) \
	}
#endif

#ifdef PORTB
#define PB0       \
	(mln_pin_t)   \
	{             \
		&PORTB, 0, (1 << 0) \
	}
#define PB1       \
	(mln_pin_t)   \
	{             \
		&PORTB, 1, (1 << 1) \
	}
#define PB2       \
	(mln_pin_t)   \
	{             \
		&PORTB, 2, (1 << 2) \
	}
#define PB3       \
	(mln_pin_t)   \
	{             \
		&PORTB, 3, (1 << 3) \
	}
#define PB4       \
	(mln_pin_t)   \
	{             \
		&PORTB, 4, (1 << 4) \
	}
#define PB5       \
	(mln_pin_t)   \
	{             \
		&PORTB, 5, (1 << 5) \
	}
#define PB6       \
	(mln_pin_t)   \
	{             \
		&PORTB, 6, (1 << 6) \
	}
#define PB7       \
	(mln_pin_t)   \
	{             \
		&PORTB, 7, (1 << 7) \
	}
#endif

#ifdef PORTC
#define PC0       \
	(mln_pin_t)   \
	{             \
		&PORTC, 0, (1 << 0) \
	}
#define PC1       \
	(mln_pin_t)   \
	{             \
		&PORTC, 1, (1 << 1) \
	}
#define PC2       \
	(mln_pin_t)   \
	{             \
		&PORTC, 2, (1 << 2) \
	}
#define PC3       \
	(mln_pin_t)   \
	{             \
		&PORTC, 3, (1 << 3) \
	}
#define PC4       \
	(mln_pin_t)   \
	{             \
		&PORTC, 4, (1 << 4) \
	}
#define PC5       \
	(mln_pin_t)   \
	{             \
		&PORTC, 5, (1 << 5) \
	}
#define PC6       \
	(mln_pin_t)   \
	{             \
		&PORTC, 6, (1 << 6) \
	}
#define PC7       \
	(mln_pin_t)   \
	{             \
		&PORTC, 7, (1 << 7) \
	}
#endif

#ifdef PORTD
#define PD0       \
	(mln_pin_t)   \
	{             \
		&PORTD, 0, (1 << 0) \
	}
#define PD1       \
	(mln_pin_t)   \
	{             \
		&PORTD, 1, (1 << 1) \
	}
#define PD2       \
	(mln_pin_t)   \
	{             \
		&PORTD, 2, (1 << 2) \
	}
#define PD3       \
	(mln_pin_t)   \
	{             \
		&PORTD, 3, (1 << 3) \
	}
#define PD4       \
	(mln_pin_t)   \
	{             \
		&PORTD, 4, (1 << 4) \
	}
#define PD5       \
	(mln_pin_t)   \
	{             \
		&PORTD, 5, (1 << 5) \
	}
#define PD6       \
	(mln_pin_t)   \
	{             \
		&PORTD, 6, (1 << 6) \
	}
#define PD7       \
	(mln_pin_t)   \
	{             \
		&PORTD, 7, (1 << 7) \
	}
#endif

#ifdef PORTE
#define PE0       \
	(mln_pin_t)   \
	{             \
		&PORTE, 0, (1 << 0) \
	}
#define PE1       \
	(mln_pin_t)   \
	{             \
		&PORTE, 1, (1 << 1) \
	}
#define PE2       \
	(mln_pin_t)   \
	{             \
		&PORTE, 2, (1 << 2) \
	}
#define PE3       \
	(mln_pin_t)   \
	{             \
		&PORTE, 3, (1 << 3) \
	}
#define PE4       \
	(mln_pin_t)   \
	{             \
		&PORTE, 4, (1 << 4) \
	}
#define PE5       \
	(mln_pin_t)   \
	{             \
		&PORTE, 5, (1 << 5) \
	}
#define PE6       \
	(mln_pin_t)   \
	{             \
		&PORTE, 6, (1 << 6) \
	}
#define PE7       \
	(mln_pin_t)   \
	{             \
		&PORTE, 7, (1 << 7) \
	}
#endif

#ifdef PORTF
#define PF0       \
	(mln_pin_t)   \
	{             \
		&PORTF, 0, (1 << 0) \
	}
#define PF1       \
	(mln_pin_t)   \
	{             \
		&PORTF, 1, (1 << 1) \
	}
#define PF2       \
	(mln_pin_t)   \
	{             \
		&PORTF, 2, (1 << 2) \
	}
#define PF3       \
	(mln_pin_t)   \
	{             \
		&PORTF, 3, (1 << 3) \
	}
#define PF4       \
	(mln_pin_t)   \
	{             \
		&PORTF, 4, (1 << 4) \
	}
#define PF5       \
	(mln_pin_t)   \
	{             \
		&PORTF, 5, (1 << 5) \
	}
#define PF6       \
	(mln_pin_t)   \
	{             \
		&PORTF, 6, (1 << 6) \
	}
#define PF7       \
	(mln_pin_t)   \
	{             \
		&PORTF, 7, (1 << 7) \
	}
#endif

#ifdef PORTG
#define PG0       \
	(mln_pin_t)   \
	{             \
		&PORTG, 0, (1 << 0) \
	}
#define PG1       \
	(mln_pin_t)   \
	{             \
		&PORTG, 1, (1 << 1) \
	}
#define PG2       \
	(mln_pin_t)   \
	{             \
		&PORTG, 2, (1 << 2) \
	}
#define PG3       \
	(mln_pin_t)   \
	{             \
		&PORTG, 3, (1 << 3) \
	}
#define PG4       \
	(mln_pin_t)   \
	{             \
		&PORTG, 4, (1 << 4) \
	}
#define PG5       \
	(mln_pin_t)   \
	{             \
		&PORTG, 5, (1 << 5) \
	}
#define PG6       \
	(mln_pin_t)   \
	{             \
		&PORTG, 6, (1 << 6) \
	}
#define PG7       \
	(mln_pin_t)   \
	{             \
		&PORTG, 7, (1 << 7) \
	}
#endif

/**
 * @brief Standard pin struct
 *
 */
typedef struct
{
	volatile PORT_t *port;
	uint8_t pin_num;
	uint8_t pin_bm;
} mln_pin_t;

/**
 * @brief Pin direction enum
 *
 */
typedef enum
{
	MLN_GPIO_DIR_OUTPUT = 0,
	MLN_GPIO_DIR_INPUT,
	MLN_GPIO_DIR_INPUT_PULLUP
} mln_gpio_dir_t;

/**
 * @brief Pin interrupt type enum
 *
 */
typedef enum
{
	MLN_GPIO_ISC_DISABLED = 0,
	MLN_GPIO_ISC_BOTHEDGES,
	MLN_GPIO_ISC_RISING,
	MLN_GPIO_ISC_FALLING,
	MLN_GPIO_ISC_LOWLEVEL = 5
} mln_gpio_isc_t;

/**
 * @brief GPIO peripheral class
 *
 */
class mln_gpio
{
	mln_pin_t pin;
	volatile uint8_t *pin_conf;

	/**
	 * @brief Configure pull of pin
	 *
	 * @param pull Direction to be set
	 *
	 */
	inline void conf_pull(const mln_gpio_dir_t pull)
	{
		if (pull == MLN_GPIO_DIR_INPUT_PULLUP)
			*pin_conf |= PORT_PULLUPEN_bm;
		else
			*pin_conf &= ~PORT_PULLUPEN_bm;
	}

public:
	/**
	 * @brief Default mln_gpio class initializer
	 *
	 */
	inline mln_gpio() = default;
	/**
	 * @brief mln_adc class initializer
	 *
	 * @param new_pin Pin to control
	 * @param direction Direction to initialize pin to
	 * @param inverted If true, pin is operated in inverted mode
	 *
	 */
	inline mln_gpio(const mln_pin_t &new_pin, const mln_gpio_dir_t &direction, const bool inverted = false)
	{
		pin = new_pin;
// 		port = new_pin.port;
// 		pin_num = new_pin.pin_num;
// 		pin_bm = new_pin.pin_bm;
		pin_conf = (uint8_t *)pin.port + 0x10 + pin.pin_num;
		*pin_conf = PORT_INVEN_bm * inverted;

		conf_dir(direction);
		conf_pull(direction);
	}

	/**
	 * @brief Attach interrupt to pin
	 *
	 * @param isc Interrupt type
	 *
	 */
	inline void attach_interrupt(const mln_gpio_isc_t isc) { *pin_conf = (*pin_conf & 0xF8) | isc; }

	/**
	 * @brief Set pin to HIGH
	 *
	 */
	inline const void set(void) { pin.port->OUTSET = pin.pin_bm; }
	/**
	 * @brief Set pin to HIGH (static version)
	 *
	 * @param new_pin Pin to set
	 *
	 */
	static inline const void set(const mln_pin_t& new_pin) { new_pin.port->OUTSET = new_pin.pin_bm; }
	/**
	 * @brief Clear pin to LOW
	 *
	 */
	inline const void clear(void) { pin.port->OUTCLR = pin.pin_bm; }
	/**
	 * @brief Set pin to LOW (static version)
	 *
	 * @param new_pin Pin to clear
	 *
	 */
	static inline const void clear(const mln_pin_t& new_pin) { new_pin.port->OUTCLR = new_pin.pin_bm; }
	/**
	 * @brief Toggle pin value
	 *
	 */
	inline const void toggle(void) { pin.port->OUTTGL = pin.pin_bm; }
	/**
	 * @brief Toggle pin value (static version)
	 *
	 * @param new_pin Pin to toggle
	 *
	 */
	static inline const void toggle(const mln_pin_t& new_pin) { new_pin.port->OUTTGL = new_pin.pin_bm; }

	/**
	 * @brief Put value on pin
	 *
	 * @param val Value to put on pin
	 *
	 */
	inline const void put(const bool val) { (val ? pin.port->OUTSET : pin.port->OUTCLR) = pin.pin_bm; }
	/**
	 * @brief Put value on pin (static version)
	 *
	 * @param new_pin Pin to put value on
	 * @param val Value to put on pin
	 *
	 */
	static inline const void put(const mln_pin_t& new_pin, const bool val) { (val ? new_pin.port->OUTSET : new_pin.port->OUTCLR) = new_pin.pin_bm; }

	/**
	 * @brief Get value of pin
	 *
	 */
	inline const bool get(void) { return pin.port->IN & pin.pin_bm; }
	/**
	 * @brief Get value of pin (static version)
	 *
	 */
	inline const bool get(const mln_pin_t& new_pin) { return new_pin.port->IN & new_pin.pin_bm; }

	/**
	 * @brief Configure direction of pin
	 *
	 * @param dir Direction to be set
	 *
	 */
	inline void conf_dir(const mln_gpio_dir_t &dir)
	{
		if (dir == MLN_GPIO_DIR_OUTPUT)
			pin.port->DIR |= pin.pin_bm;
		else
			pin.port->DIR &= ~pin.pin_bm;

		conf_pull(dir);
	}
	/**
	 * @brief Configure direction of pin (static version)
	 *
	 * @param new_pin Pin to configure
	 * @param dir Direction to be set
	 *
	 */
	inline void conf_dir(const mln_pin_t& new_pin, const mln_gpio_dir_t dir)
	{
		if (dir == MLN_GPIO_DIR_OUTPUT)
			new_pin.port->DIR |= new_pin.pin_bm;
		else
			new_pin.port->DIR &= ~new_pin.pin_bm;

		conf_pull(dir);
	}
}; // mln_gpio

#endif //__MLN_GPIO_H__

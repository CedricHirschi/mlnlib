# mlnlib - HAL for the AVR-Dx family of microcontrollers

In this repository you will find a set of libraries for the AVR-Dx family of microcontrollers.

The libraries are written in C++ and are designed to be used with the avr-g++ compiler. The libraries are designed to partially work together.

Libraries for the following peripherals are currently included:

* [ADC](mlnlib/mln/mln_adc.h)
* [DAC](mlnlib/mln/mln_dac.h)
* [GPIO](mlnlib/mln/mln_gpio.h)
* [OPAMP](mlnlib/mln/mln_opamp.h)
* [SPI](mlnlib/mln/mln_spi.h)
* [TCA](mlnlib/mln/mln_timer.h)
* [TWI/I2C](mlnlib/mln/mln_twi.h)
* [UART](mlnlib/mln/mln_uart.h)
* [VREF](mlnlib/mln/mln_vref.h)

There are also some implementations for some external devices:

* [MCP4822](mlnlib/devices/mcp4822.h)

## Installation

To install the libraries, simply include any header file into your project and use it normally.

Some libraries must have `F_CPU` defined. This can be done by adding `-DF_CPU=4000000UL` to the compiler flags with the frequency options described in `FRQSEL` [here](https://onlinedocs.microchip.com/oxy/GUID-09746E70-A26B-4669-B803-2A1D0E0F7E70-en-US-19/GUID-3CA52B62-CB27-45A0-93C7-68BDB8774A16.html#BITFIELD_A3K_MWD_X1B).

**Note**: The libraries partially depend on each other, for example the `mln_adc` library depends on the `mln_gpio` library. If you want to use the `mln_adc` library, you also need to include the `mln_gpio` library.

## Documentation

**[Click here for main documentation page](https://cedrichirschi.github.io/mlnlib/)**

The documentation can be found in the [`docs`](docs) folder. The documentation is generated using doxygen. To generate the documentation yourself, run `doxygen` in the root (location of Doxyfile). Some paths inside the Doxyfile must be changed.

## Building for testing

The library can be tested inside [`main.cpp`](mlnlib/main.cpp). As this library was developed in Microchip Studio 7, the following methods are available to build the library for testing:

Open the project in Microchip Studio 7 and build / run the project as normal.

## TODO

- **Overall:**
  - [x] Unify constant names (e.g. `MLN_ADC_IN_DACREF0` vs `DACREF0`)
  - [ ] Unify function names (e.g. `start`, `init`, etc. in every class)
  - [x] Add documentation in form of doxygen comments and config
- **`mln_adc`:**
  - [x] Add function to check if result is ready (change from private to public)
  - [ ] Add function to check if conversion is running
- **`mln_opamp` and `mln_dac` and `mln_vref`:**
  - [x] Move from class to namespace (no saved variables)
- **`mln_uart`:**
  - [x] Move `push` function from public to private (cannot be made private)
- **`mln_gpio`:**
  - [ ] For each function, add function available outside of class (e.g. `init_pin.toggle()` vs `mln_gpio::toggle(uninit_pin)`)
- **`mln_timer`:**
  - [ ] Add `CMP` functionality (multiple interrupts per TCA)
  - [ ] Add PWM

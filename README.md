# mlnlib - HAL for the AVR-Dx family of microcontrollers

In this repository you will find a set of libraries for the AVR-Dx family of microcontrollers.

The libraries are written in C++ and are designed to be used with the g++ compiler. The libraries are designed to work together.

Libraries for the following peripherals are currently included:

* [GPIO](mlnlib/mln/mln_gpio.h) (no PWM yet)
* [Timer tasks](mlnlib/mln/mln_timer.h) (TCA, no PWM yet)
* [SPI](mlnlib/mln/mln_spi.h)
* [UART](mlnlib/mln/mln_uart.h)
* [VREF](mlnlib/mln/mln_vref.h)
* [ADC](mlnlib/mln/mln_adc.h)
* [DAC](mlnlib/mln/mln_dac.h)

There are also some implementations for some external devices:

* [MCP4822](mlnlib/devices/mcp4822.h)

## Installation

To install the libraries, simply clone [`mln`](mlnlib/mln) and the [`devices`](mlnlib/devices) (if desired) folder under [`mlnlib`](mlnlib) into your project folder. The `mln` folder contains the libraries and the `device` folder contains the device specific files.

## Manuals

Manuals can be found in the [`man`](man) folder.

These include:

* Manuals for the libraries (can also be accessed by clicking on the links above)
* A manual for some [methods](man/methods.md) that are used in the libraries

## Examples

Examples for the libraries can be found in the [`examples`](examples) folder.

## Building for testing

The library can be tested inside [`main.cpp`](mlnlib/main.cpp). As this library was developed in Microchip Studio 7, the following methods are available to build the library for testing:

1. Open the project in Microchip Studio 7 and build / run the project
2. Run `make all` in the [`Debug`](mlnlib/Debug) folder to get the binaries and upload them to the microcontroller using a different tool

## TODO

- **Overall:**
  - [ ] Unify constant names (e.g. `MLN_ADC_IN_DACREF0` vs `DACREF0`)
  - [ ] Unify function names (e.g. `start`, `init`, etc. in every class)
  - [ ] Add documentation in form of doxygen comments and config
- **`mln_adc`:**
  - [ ] Add function to check if result is ready (change from private to public)
  - [ ] Add function to check if conversion is running
- **`mln_opamp` and `mln_dac` and `mln_vref`:**
  - [ ] Move from class to namespace (no saved variables)
- **`mln_uart`:**
  - [ ] Move `push` function from public to private
- **`mln_gpio`:**
  - [ ] For each function, add function available outside of class (e.g. `init_pin.toggle()` vs `mln_gpio::toggle(uninit_pin)`)
- **`mln_timer`:**
  - [ ] Add `CMP` functionality (multiple interrupts per TCA)
  - [ ] Add PWM

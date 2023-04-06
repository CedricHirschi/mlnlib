# mlnlib - HAL for the AVR-Dx family of microcontrollers

In this repository you will find a set of libraries for the AVR-Dx family of microcontrollers.

The libraries are written in C++ and are designed to be used with the g++ compiler. The libraries are designed to work together.

Libraries for the following peripherals are currently included:

* GPIO (no PWM yet)
* Timer tasks (TCA)
* SPI
* UART
* VREF
* ADC
* DAC

There are also some implementations for some external devices:

* MCP4822

## Installation

To install the libraries, simply clone [`mln`](mlnlib/mln) and the [`devices`](mlnlib/devices) (if desired) folder under [`mlnlib`](mlnlib) into your project folder. The `mln` folder contains the libraries and the `device` folder contains the device specific files.

## Manuals

Manuals can be found in the [`man`](man) folder.

These include:

* Manuals for the libraries (can also be accessed by clicking on the links above)
* A manual for some methods that are used in the libraries

## Examples

Examples for the libraries can be found in the [`examples`](examples) folder.

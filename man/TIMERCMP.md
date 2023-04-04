# Multiple Periodic Timer Events

## Introduction

You can add multiple periodic timer events per `TCA` timer in an AVR128DB48 microcontroller. For the AVR128DB48, the `TCA` timer has three compare channels (`CMP0`, `CMP1`, and `CMP2`) and three corresponding interrupts (`TCA0_CMP0_vect`, `TCA0_CMP1_vect`, and `TCA0_CMP2_vect`). You can use these compare channels to generate multiple periodic timer events.

### Steps

To set up multiple periodic timer events, follow these steps:

#### 1. Configure the TCA timer:

   a. Set the mode of operation (e.g., Normal mode, Split mode, etc.).

   b. Set the clock source and prescaler value.

   c. Enable the timer.

#### 2. Set up the compare channels:

   a. For each compare channel, set the corresponding compare register (e.g., `TCA0.SINGLE.CMP0`, `TCA0.SINGLE.CMP1`, `TCA0.SINGLE.CMP2`) to the desired value.

   b. Enable the corresponding compare channel interrupt by setting the appropriate bit in the `TCA0.SINGLE.INTCTRL` register (e.g., `TCA_SINGLE_CMP0EN_bm`, `TCA_SINGLE_CMP1EN_bm`, `TCA_SINGLE_CMP2EN_bm`).

#### 3. Implement the corresponding ISR (Interrupt Service Routine) for each compare channel. In the ISR, you can perform the desired action for each periodic timer event.

#### 4. Enable global interrupts.

## Example

Here's a simple example of setting up two periodic timer events using `TCA0`:

```c
#include <avr/io.h>
#include <avr/interrupt.h>

void TCA0_init(void) {
    TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV1024_gc | TCA_SINGLE_ENABLE_bm; // Set clock source and enable timer
    TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_NORMAL_gc; // Set mode of operation (Normal mode)

    TCA0.SINGLE.CMP0 = 3124; // Set compare value for CMP0
    TCA0.SINGLE.CMP1 = 6249; // Set compare value for CMP1

    TCA0.SINGLE.INTCTRL = TCA_SINGLE_CMP0EN_bm | TCA_SINGLE_CMP1EN_bm; // Enable interrupts for CMP0 and CMP1
}

ISR(TCA0_CMP0_vect) {
    // Your code for the first periodic event

    TCA0.SINGLE.INTFLAGS = TCA_SINGLE_CMP0_bm; // Clear the interrupt flag
}

ISR(TCA0_CMP1_vect) {
    // Your code for the second periodic event

    TCA0.SINGLE.INTFLAGS = TCA_SINGLE_CMP1_bm; // Clear the interrupt flag
}

int main(void) {
    TCA0_init();
    sei(); // Enable global interrupts

    while (1) {
        // Your main loop code
    }
}
```

In this example, the `TCA0` timer is set up with two compare channels (`CMP0` and `CMP1`) to generate two periodic timer events. The ISR for each compare channel is implemented to handle the desired actions for each event.

## Calculations

### Calculating the register values

To calculate the values to be written into the CMPn registers based on the desired period between timer events and timer clock divider, you can use the following formula:

$$
per = \frac{F_{CPU}}{P \cdot f} - 1
$$

Where:
- $per$ is the value to be written into the compare register (`CMP0`, `CMP1`, or `CMP2`)
- $F_{CPU}$ is the microcontroller's clock frequency in Hz (e.g., 4 MHz)
- $P$ is the timer clock divider (e.g., 1, 2, 4, 8, 16, 64, 256, or 1024)
- $f$ is the desired frequency of the timer event in Hz

For example, if you want a timer event with a period of 500 ms (2 Hz) and a prescaler of 64, you can calculate the CMPn value as follows:

$$
per = \frac{4'000'000}{64 \cdot 2} - 1 = 31249
$$

### Calculating the maximum periods

To calculate the maximum period depending on the clock division, you can use the following formula:

$$
T_{max} = \frac{P \cdot (2^{n} - 1)}{F_{CPU}}
$$

Where:
- $T_{max}$ is the maximum period in seconds
- $P$ is the timer clock divider (e.g., 1, 2, 4, 8, 16, 64, 256, or 1024)
- $F_{CPU}$ is the microcontroller's clock frequency in Hz (e.g., 4 MHz)
- $2^{n} - 1$ is the maximum value that can be stored in a n-bit register (65,535 for a 16-bit register)

For example, if you have a 16-bit timer with a prescaler of 64 and a clock frequency of 4 MHz, you can calculate the maximum period as follows:

$$
T_{max} = \frac{64 \cdot (65,535)}{4'000'000} \approx 1.049\ s
$$

### Calculating the achieved period

To calculate the achieved period $T_{ach}$, you can use the following formula:

$$
T_{ach} = \frac{(per + 1) \cdot P}{F_{CPU}}
$$

Where:
- $per$ is the value written into the compare register (CMP0, CMP1, or CMP2)
- $P$ is the timer clock divider (e.g., 1, 2, 4, 8, 16, 64, 256, or 1024)
- $F_{CPU}$ is the microcontroller's clock frequency in Hz (e.g., 20 MHz)

For example, if you have a $per$ value of 30000, a prescaler of 64, and a clock frequency of 4 MHz, you can calculate the achieved period as follows:

$$
T_{ach} = \frac{(30000 + 1) \cdot 64}{4'000'000} \approx 480\ ms
$$
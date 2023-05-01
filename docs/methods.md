# PIN interrupts on MegaAVR series microcontrollers

## AVR128DB48

To attach interrupts to a pin in an AVR128DB48 microcontroller, you need to follow these steps:

1. Configure the pin as an input.
2. Enable the appropriate interrupt.
3. Set the desired interrupt triggering condition.
4. Write an ISR (Interrupt Service Routine) function to handle the interrupt.
5. Enable global interrupts.

Here's an example of how to attach a falling-edge interrupt to pin `PA0`:

### 1. Configure the pin as an input:

```c
#include <avr/io.h>

int main(void)
{
    PORTA.DIRCLR = PIN0_bm; // Set PA0 as input
    // ...
}
```

### 2. Enable the appropriate interrupt:

In this, we are enabling a falling-edge interrupt on pin `PA0`. To do this, you need to set the appropriate interrupt sense control bits in the `PINnCTRL` register for the pin.

```c
#include <avr/io.h>

int main(void)
{
    PORTA.DIRCLR = PIN0_bm; // Set PA0 as input
    PORTA.PIN0CTRL = PORT_ISC_FALLING_gc; // Enable falling edge interrupt on PA0
    // ...
}
```

### 3. Set the desired interrupt triggering condition:

In this example, we've already set the interrupt triggering condition to falling-edge in the previous step using `PORT_ISC_FALLING_gc`. If you want to use other triggering conditions, you can replace it with one of the following options:

- `PORT_ISC_BOTHEDGES_gc`: Both edges (rising and falling) trigger the interrupt.
- `PORT_ISC_RISING_gc`: Rising edge triggers the interrupt.
- `PORT_ISC_LEVEL_gc`: Low level triggers the interrupt.

### 4. Write an ISR (Interrupt Service Routine) function to handle the interrupt:

```c
#include <avr/io.h>
#include <avr/interrupt.h>

ISR(PORTA_PORT_vect)
{
    // Handle the interrupt, e.g., toggle an LED on PA1
    PORTA.OUTTGL = PIN1_bm;

    // Clear the interrupt flag
    PORTA.INTFLAGS = PIN0_bm;
}

int main(void)
{
    // ...
}
```

### 5. Enable global interrupts:

```c
#include <avr/io.h>
#include <avr/interrupt.h>

ISR(PORTA_PORT_vect)
{
    // Handle the interrupt, e.g., toggle an LED on PA1
    PORTA.OUTTGL = PIN1_bm;

    // Clear the interrupt flag
    PORTA.INTFLAGS = PIN0_bm;
}

int main(void)
{
    PORTA.DIRCLR = PIN0_bm; // Set PA0 as input
    PORTA.PIN0CTRL = PORT_ISC_FALLING_gc; // Enable falling edge interrupt on PA0

    // Enable global interrupts
    sei();

    while (1)
    {
        // Main loop
    }
}
```

By following these steps, you can attach interrupts to a pin in an AVR128DB48 microcontroller.

### Important registers and bitmaps

- `PORTx.DIR`: Port Data Direction
  - `PINn_bm`: Bit mask for pin n
- `PORTx.PINnCTRL`: Pin n Control Register
  - `PORT_ISC_FALLING_gc`: Falling edge triggers the interrupt
  - `PORT_ISC_RISING_gc`: Rising edge triggers the interrupt
  - `PORT_ISC_BOTHEDGES_gc`: Both edges (rising and falling) trigger the interrupt
  - `PORT_ISC_LEVEL_gc`: Low level triggers the interrupt
- `PORTx.INTFLAGS`: Port Interrupt Flags
  - `PINn_bm`: Bit mask for pin n interrupt flag

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

### Calculating the maximum period

To calculate the maximum period depending on the clock division, you can use the following formula:

$$
T_{max} = \frac{P \cdot top}{F_{CPU}}
$$

Where:
- $T_{max}$ is the maximum period in seconds
- $P$ is the timer clock divider (e.g., 1, 2, 4, 8, 16, 64, 256, or 1'024)
- $F_{CPU}$ is the microcontroller's clock frequency in Hz (e.g., 4 MHz)
- $top$ is the top value that is written in the `PER` register (the maximum value the counter counts up to) ( max. $2^n - 1$ for a $n$-bit timer)

For example, if you have a 16-bit timer with unchanged `PER` register, a prescaler of 256 and a clock frequency of 4 MHz, you can calculate the maximum period as follows:

$$
T_{max} = \frac{256 \cdot 65,535}{4'000'000} \approx 4.19\ s
$$

### Calculating the register value

To calculate the values to be written into the CMPn registers based on the desired period between timer events and timer clock divider, you can use the following formula:

$$
per = \left \lfloor \frac{F_{CPU} \cdot T_{des}}{P} \right \rfloor - 1
$$

Where:
- $per$ is the value to be written into the compare register (`CMP0`, `CMP1`, or `CMP2`)
- $F_{CPU}$ is the microcontroller's clock frequency in Hz (e.g., 4 MHz)
- $P$ is the timer clock divider (e.g., 1, 2, 4, 8, 16, 64, 256, or 1'024)
- $T_{des}$ is the desired period of the timer event in seconds

For example, if you want a timer event with a period of 3.75s and a prescaler of 256, you can calculate the CMPn value as follows:

$$
per = \left\lfloor \frac{4'000'000 \cdot 2}{256} \right\rfloor - 1 = \lfloor 58'592.75 \rfloor = 58'592
$$

### Calculating the achieved period

To calculate the achieved period $T_{ach}$, you can use the following formula:

$$
T_{ach} = \frac{(per + 1) \cdot P}{F_{CPU}}
$$

Where:
- $per$ is the value written into the compare register (CMP0, CMP1, or CMP2)
- $P$ is the timer clock divider (e.g., 1, 2, 4, 8, 16, 64, 256, or 1'024)
- $F_{CPU}$ is the microcontroller's clock frequency in Hz (e.g., 4 MHz)

For example, if you have a $per$ value of 30000, a prescaler of 64, and a clock frequency of 4 MHz, you can calculate the achieved period as follows:

$$
T_{ach} = \frac{(30'000 + 1) \cdot 64}{4'000'000} \approx 480\ ms
$$

### Calculating the achieved error and maximum error

Calculating the error in regards to the desired period $T_{des}$, you can use the following formula:

$$
\epsilon = T_{ach} - T_{des} = \frac{\left [ \left (\left \lfloor \frac{F_{CPU} \cdot T_{des}}{P} \right \rfloor - 1 \right ) + 1 \right] \cdot P}{F_{CPU}} - T_{des} = \frac{\left \lfloor \frac{F_{CPU} \cdot T_{des}}{P} \right \rfloor \cdot P}{F_{CPU}} - T_{des}
$$

The maximum error is $P / F_{CPU}$, which is the smallest possible period increment.

For above example, you can calculate the error as follows:

$$
\epsilon = \frac{\left \lfloor \frac{4'000'000 \cdot 3.75}{256} \right \rfloor \cdot 256}{4'000'000} - 3.75 = -48\ \mu s
$$

### Rounding errors

This error will always be negative because of the rounding down of the `per` value. If you want to you can add $0.5$ to the `per` value before rounding down to get lower rounding errors:

$$
per = \left \lfloor \frac{F_{CPU} \cdot T_{des}}{P} + 0.5 \right \rfloor - 1
$$

The maximum error will then be $P / (2 \cdot F_{CPU})$.

For above example, this will then result in the following error:

$$
\epsilon = \frac{\left \lfloor \frac{4'000'000 \cdot 3.75}{256} + 0.5 \right \rfloor \cdot 256}{4'000'000} - 3.75 = 16\ \mu s
$$
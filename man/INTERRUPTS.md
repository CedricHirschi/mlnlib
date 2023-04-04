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

## ATMega328P

### Example

Here's an example of attaching a falling-edge interrupt to pin PD2 (INT0):

```c
#include <avr/io.h>
#include <avr/interrupt.h>

ISR(INT0_vect)
{
    // Handle the interrupt
}

int main(void)
{
    DDRD &= ~(1 << PD2); // Set PD2 as input
    EIMSK |= (1 << INT0); // Enable INT0 interrupt
    EICRA &= ~((1 << ISC00) | (1 << ISC01)); // Clear ISC00 and ISC01
    EICRA |= (1 << ISC01); // Set falling edge interrupt on INT0
    sei(); // Enable global interrupts
    // ...
}
```

### Important registers and bitmaps

- `DDRx`: Port Data Direction
  - `PDn`: Pin n data direction bit
- `EIMSK`: External Interrupt Mask Register
  - `INT0`: Enable INT0 interrupt
- `EICRA`: External Interrupt Control Register A
  - `ISC00` and `ISC01`: Interrupt Sense Control bits for INT0
- `PORTx`: Port Data Register
  - `PDn`: Pin n data bit
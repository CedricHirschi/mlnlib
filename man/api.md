# Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`namespace `[`mln_dac`](#namespacemln__dac) | DAC peripheral namespace.
`namespace `[`mln_opamp`](#namespacemln__opamp) | Opamp peripheral namespace.
`namespace `[`mln_vref`](#namespacemln__vref) | Voltage reference peripheral namespace.
`class `[`mcp4822`](#classmcp4822) | MCP4822 DAC driver.
`class `[`mln_adc`](#classmln__adc) | ADC peripheral class.
`class `[`mln_gpio`](#classmln__gpio) | GPIO peripheral class.
`class `[`mln_spi`](#classmln__spi) | SPI peripheral class.
`class `[`mln_timer`](#classmln__timer) | TCA peripheral class.
`class `[`mln_twi`](#classmln__twi) | 
`class `[`mln_uart`](#classmln__uart) | USART peripheral class.
`struct `[`mln_opamp_direct_init_t`](#structmln__opamp__direct__init__t) | Opamp direct configuration struct.
`struct `[`mln_opamp_follower_init_t`](#structmln__opamp__follower__init__t) | Opamp follower configuration struct.
`struct `[`mln_opamp_inverting_init_t`](#structmln__opamp__inverting__init__t) | Opamp inverting configuration struct.
`struct `[`mln_opamp_noninverting_init_t`](#structmln__opamp__noninverting__init__t) | Opamp non-inverting configuration struct.
`struct `[`mln_pin_t`](#structmln__pin__t) | Standard pin struct.

# namespace `mln_dac` {#namespacemln__dac}

DAC peripheral namespace.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline const void `[`config`](#namespacemln__dac_1ab2c0496dcd73d12a31eef2d5eabdf83b)`(bool standby,bool buffer)`            | Configure the DAC peripheral.
`public inline const void `[`enable`](#namespacemln__dac_1a2d97bbee2cf33201636fc81a9b2cf7fd)`(void)`            | Enable the DAC peripheral.
`public inline const void `[`disable`](#namespacemln__dac_1a52324ac73ef79d3a9e78e5633e861f58)`(void)`            | Disable the DAC peripheral.
`public inline const void `[`set`](#namespacemln__dac_1a4d7ff2ec27518ae7f3db709efaf73d8d)`(uint16_t value)`            | Set the output of the DAC peripheral.

## Members

#### `public inline const void `[`config`](#namespacemln__dac_1ab2c0496dcd73d12a31eef2d5eabdf83b)`(bool standby,bool buffer)` {#namespacemln__dac_1ab2c0496dcd73d12a31eef2d5eabdf83b}

Configure the DAC peripheral.

#### Parameters
* `standby` If true, the peripheral is also running in device standby 

* `buffer` If true, the dac output is buffered and output to the pin

#### `public inline const void `[`enable`](#namespacemln__dac_1a2d97bbee2cf33201636fc81a9b2cf7fd)`(void)` {#namespacemln__dac_1a2d97bbee2cf33201636fc81a9b2cf7fd}

Enable the DAC peripheral.

#### `public inline const void `[`disable`](#namespacemln__dac_1a52324ac73ef79d3a9e78e5633e861f58)`(void)` {#namespacemln__dac_1a52324ac73ef79d3a9e78e5633e861f58}

Disable the DAC peripheral.

#### `public inline const void `[`set`](#namespacemln__dac_1a4d7ff2ec27518ae7f3db709efaf73d8d)`(uint16_t value)` {#namespacemln__dac_1a4d7ff2ec27518ae7f3db709efaf73d8d}

Set the output of the DAC peripheral.

#### Parameters
* `value` The output of the DAC peripheral

Remember to call `enable` to enable the peripheral

# namespace `mln_opamp` {#namespacemln__opamp}

Opamp peripheral namespace.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline const void `[`init_resmux`](#namespacemln__opamp_1ac9965ec24ade069bc4a7a739497df142)`(const `[`mln_opamp_device_t`](#mln__opamp_8h_1af933df376949fd10542121c2129b7371)` & opamp,const uint8_t & muxbot,const uint8_t & muxwip,const uint8_t & muxtop)`            | Helper function to set the RESMUX register.
`public inline const void `[`init_inmux`](#namespacemln__opamp_1a4ce3a5b37432e37c667746efcb2b8c5a)`(const `[`mln_opamp_device_t`](#mln__opamp_8h_1af933df376949fd10542121c2129b7371)` & opamp,const uint8_t & muxpos,const uint8_t & muxneg)`            | Helper function to set the INMUX register.
`public inline const void `[`enable`](#namespacemln__opamp_1a0a0427ac35a59542fc395c8d72517e95)`(const `[`mln_opamp_device_t`](#mln__opamp_8h_1af933df376949fd10542121c2129b7371)` & opamp,const bool runstdby,const bool output,const bool lowpower)`            | Helper function to enable the opamp.
`public inline const void `[`enable`](#namespacemln__opamp_1aeb5706e96c49d3fe7a7d65f29164e27d)`(void)`            | Enable Opamp peripheral.
`public inline const void `[`disable`](#namespacemln__opamp_1a55e930138c7f5bd00bdb349f1c2d034b)`(void)`            | Disable Opamp peripheral.
`public inline const void `[`init`](#namespacemln__opamp_1acf2adf43ce7883bd341a2f4ad1a61435)`(const `[`mln_opamp_direct_init_t`](#structmln__opamp__direct__init__t)` & init)`            | Construct a new [mln_opamp](#namespacemln__opamp) object (direct)
`public inline const void `[`init`](#namespacemln__opamp_1a36c5a08e9119da136ab848754879ff11)`(const `[`mln_opamp_follower_init_t`](#structmln__opamp__follower__init__t)` & init)`            | Construct a new [mln_opamp](#namespacemln__opamp) object (follower)
`public inline const void `[`init`](#namespacemln__opamp_1a73bee02c68a8d1ace2d5bbadc50c19c5)`(const `[`mln_opamp_noninverting_init_t`](#structmln__opamp__noninverting__init__t)` & init)`            | Construct a new [mln_opamp](#namespacemln__opamp) object (non-inverting)
`public inline const void `[`init`](#namespacemln__opamp_1a8a9105145e18299dcd0bb4b5527580fd)`(const `[`mln_opamp_inverting_init_t`](#structmln__opamp__inverting__init__t)` & init)`            | Construct a new [mln_opamp](#namespacemln__opamp) object (inverting)

## Members

#### `public inline const void `[`init_resmux`](#namespacemln__opamp_1ac9965ec24ade069bc4a7a739497df142)`(const `[`mln_opamp_device_t`](#mln__opamp_8h_1af933df376949fd10542121c2129b7371)` & opamp,const uint8_t & muxbot,const uint8_t & muxwip,const uint8_t & muxtop)` {#namespacemln__opamp_1ac9965ec24ade069bc4a7a739497df142}

Helper function to set the RESMUX register.

#### Parameters
* `opamp` Device 

* `muxbot` Bottom resistor mux 

* `muxwip` Wiper resistor mux 

* `muxtop` Top resistor mux

#### `public inline const void `[`init_inmux`](#namespacemln__opamp_1a4ce3a5b37432e37c667746efcb2b8c5a)`(const `[`mln_opamp_device_t`](#mln__opamp_8h_1af933df376949fd10542121c2129b7371)` & opamp,const uint8_t & muxpos,const uint8_t & muxneg)` {#namespacemln__opamp_1a4ce3a5b37432e37c667746efcb2b8c5a}

Helper function to set the INMUX register.

#### Parameters
* `opamp` Device 

* `muxpos` Positive input mux 

* `muxneg` Negative input mux

#### `public inline const void `[`enable`](#namespacemln__opamp_1a0a0427ac35a59542fc395c8d72517e95)`(const `[`mln_opamp_device_t`](#mln__opamp_8h_1af933df376949fd10542121c2129b7371)` & opamp,const bool runstdby,const bool output,const bool lowpower)` {#namespacemln__opamp_1a0a0427ac35a59542fc395c8d72517e95}

Helper function to enable the opamp.

#### Parameters
* `runstdby` Run in standby 

* `output` Enable output 

* `lowpower` Low power mode 

* `opamp_n` Device

Is being called by the `init` functions

#### `public inline const void `[`enable`](#namespacemln__opamp_1aeb5706e96c49d3fe7a7d65f29164e27d)`(void)` {#namespacemln__opamp_1aeb5706e96c49d3fe7a7d65f29164e27d}

Enable Opamp peripheral.

Doesn't configure/enable single Opamps

#### `public inline const void `[`disable`](#namespacemln__opamp_1a55e930138c7f5bd00bdb349f1c2d034b)`(void)` {#namespacemln__opamp_1a55e930138c7f5bd00bdb349f1c2d034b}

Disable Opamp peripheral.

Disables all Opamps

#### `public inline const void `[`init`](#namespacemln__opamp_1acf2adf43ce7883bd341a2f4ad1a61435)`(const `[`mln_opamp_direct_init_t`](#structmln__opamp__direct__init__t)` & init)` {#namespacemln__opamp_1acf2adf43ce7883bd341a2f4ad1a61435}

Construct a new [mln_opamp](#namespacemln__opamp) object (direct)

#### Parameters
* `init` Opamp configuration struct (direct)

#### `public inline const void `[`init`](#namespacemln__opamp_1a36c5a08e9119da136ab848754879ff11)`(const `[`mln_opamp_follower_init_t`](#structmln__opamp__follower__init__t)` & init)` {#namespacemln__opamp_1a36c5a08e9119da136ab848754879ff11}

Construct a new [mln_opamp](#namespacemln__opamp) object (follower)

#### Parameters
* `init` Opamp configuration struct (follower)

#### `public inline const void `[`init`](#namespacemln__opamp_1a73bee02c68a8d1ace2d5bbadc50c19c5)`(const `[`mln_opamp_noninverting_init_t`](#structmln__opamp__noninverting__init__t)` & init)` {#namespacemln__opamp_1a73bee02c68a8d1ace2d5bbadc50c19c5}

Construct a new [mln_opamp](#namespacemln__opamp) object (non-inverting)

#### Parameters
* `init` Opamp configuration struct (non-inverting)

#### `public inline const void `[`init`](#namespacemln__opamp_1a8a9105145e18299dcd0bb4b5527580fd)`(const `[`mln_opamp_inverting_init_t`](#structmln__opamp__inverting__init__t)` & init)` {#namespacemln__opamp_1a8a9105145e18299dcd0bb4b5527580fd}

Construct a new [mln_opamp](#namespacemln__opamp) object (inverting)

#### Parameters
* `init` Opamp configuration struct (inverting)

# namespace `mln_vref` {#namespacemln__vref}

Voltage reference peripheral namespace.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline const void `[`set`](#namespacemln__vref_1a692b2b7ba6828000729917de5eb8b7aa)`(`[`MLN_VREF_SEL_t`](#mln__vref_8h_1ae495fc779ce5af55e739c012fe4caf4a)` adc,`[`MLN_VREF_SEL_t`](#mln__vref_8h_1ae495fc779ce5af55e739c012fe4caf4a)` dac,`[`MLN_VREF_SEL_t`](#mln__vref_8h_1ae495fc779ce5af55e739c012fe4caf4a)` ac,bool standby)`            | Configure and set voltages of the VREF peripheral.

## Members

#### `public inline const void `[`set`](#namespacemln__vref_1a692b2b7ba6828000729917de5eb8b7aa)`(`[`MLN_VREF_SEL_t`](#mln__vref_8h_1ae495fc779ce5af55e739c012fe4caf4a)` adc,`[`MLN_VREF_SEL_t`](#mln__vref_8h_1ae495fc779ce5af55e739c012fe4caf4a)` dac,`[`MLN_VREF_SEL_t`](#mln__vref_8h_1ae495fc779ce5af55e739c012fe4caf4a)` ac,bool standby)` {#namespacemln__vref_1a692b2b7ba6828000729917de5eb8b7aa}

Configure and set voltages of the VREF peripheral.

#### Parameters
* `dac` Reference voltage of DAC peripheral to set 

* `adc` Reference voltage of ADC peripheral to set 

* `ac` Reference voltage of AC peripheral to set 

* `standby` If true, the peripheral is also running in device standby

# class `mcp4822` {#classmcp4822}

MCP4822 DAC driver.

Utilizes the [mln_spi](#classmln__spi) and [mln_gpio](#classmln__gpio) libraries

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  `[`mcp4822`](#classmcp4822_1a86073139fbeebb12385516ad911847af)`(SPI_t * new_spi,`[`mln_pin_t`](#structmln__pin__t)` cs,`[`mln_pin_t`](#structmln__pin__t)` new_ldac)` | Construct a new [mcp4822](#classmcp4822) object.
`public inline void `[`set_gain`](#classmcp4822_1ab5995c3e631c799d35da2b1ae2ab021a)`(`[`mln_mcp4822_gain_t`](#mcp4822_8h_1a405a5c74199b2cc7e82ed3bead405a91)` new_gain)` | Set the gain of the DAC.
`public inline void `[`write`](#classmcp4822_1ad9d33f039c793af64c51c77a6203197c)`(const `[`mln_mcp4822_channel_t`](#mcp4822_8h_1a7e58481bb9c447a43a8cf2f482bcfcbb)` channel,const uint16_t value)` | Write a value to the DAC.

## Members

#### `public inline  `[`mcp4822`](#classmcp4822_1a86073139fbeebb12385516ad911847af)`(SPI_t * new_spi,`[`mln_pin_t`](#structmln__pin__t)` cs,`[`mln_pin_t`](#structmln__pin__t)` new_ldac)` {#classmcp4822_1a86073139fbeebb12385516ad911847af}

Construct a new [mcp4822](#classmcp4822) object.

#### Parameters
* `new_spi` SPI interface to use 

* `cs` Chip select pin 

* `new_ldac` LDAC pin

#### `public inline void `[`set_gain`](#classmcp4822_1ab5995c3e631c799d35da2b1ae2ab021a)`(`[`mln_mcp4822_gain_t`](#mcp4822_8h_1a405a5c74199b2cc7e82ed3bead405a91)` new_gain)` {#classmcp4822_1ab5995c3e631c799d35da2b1ae2ab021a}

Set the gain of the DAC.

#### Parameters
* `new_gain` The new gain

The gain is set for both channels, only applies from the next write

#### `public inline void `[`write`](#classmcp4822_1ad9d33f039c793af64c51c77a6203197c)`(const `[`mln_mcp4822_channel_t`](#mcp4822_8h_1a7e58481bb9c447a43a8cf2f482bcfcbb)` channel,const uint16_t value)` {#classmcp4822_1ad9d33f039c793af64c51c77a6203197c}

Write a value to the DAC.

#### Parameters
* `channel` The channel to write to 

* `value` The value to write

# class `mln_adc` {#classmln__adc}

ADC peripheral class.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  `[`mln_adc`](#classmln__adc_1a6e055cc7727403cd94606f5d32867ec3)`()` | Default `[mln_adc](#classmln__adc)` class initializer.
`public inline  `[`mln_adc`](#classmln__adc_1aa94f66bed48040b8f744a1fbf16ac18d)`(const `[`mln_pin_t`](#structmln__pin__t)` & pin)` | Initialize `[mln_adc](#classmln__adc)` class from pin.
`public inline  `[`mln_adc`](#classmln__adc_1afb23838575ae29e899bf108e09e08cbb)`(const `[`mln_adc_in_t`](#mln__adc_8h_1a8b46c7c728d2203051bada5c588b72e9)` in)` | Initialize `[mln_adc](#classmln__adc)` class from adc input.
`public inline const void `[`config`](#classmln__adc_1a715704c24ca9c2c62b22917d79d6c2d5)`(const bool standby,const `[`mln_adc_resolution_t`](#mln__adc_8h_1a0d59f42a8f91323537152a301270a004)` res,const `[`mln_adc_accumulation_t`](#mln__adc_8h_1a59aa030466723b07fda5aab69e6390a5)` samp,const `[`mln_adc_prescaler_t`](#mln__adc_8h_1a8686df8036c6ba2fc811904bf82cfa18)` presc)` | Configure the ADC peripheral.
`public inline const void `[`enable`](#classmln__adc_1a2490fadc8bf4c906124a1a01c83d6d0e)`(void)` | Enable the ADC peripheral.
`public inline const void `[`disable`](#classmln__adc_1acf7fda713d82aaaa1421c7527866b894)`(void)` | Disable the ADC peripheral.
`public inline void `[`set_in`](#classmln__adc_1a29d0b97e4bd9da7c031ab369b8552e26)`(const `[`mln_pin_t`](#structmln__pin__t)` & pin)` | Configure the input pin of the ADC peripheral.
`public inline const void `[`set_in`](#classmln__adc_1a110c322e75ec55665b7dc97fd2e245bb)`(const `[`mln_adc_in_t`](#mln__adc_8h_1a8b46c7c728d2203051bada5c588b72e9)` in)` | Configure the input of the ADC peripheral.
`public inline const void `[`start`](#classmln__adc_1a456941f8b507ca65e3d6866f7f2052bd)`(void)` | Start reading of ADC peripheral.
`public inline const bool `[`has_result`](#classmln__adc_1a9246f67d595392f5e276c809d577f4d1)`(void)` | Check whether ADC peripheral has a result ready.
`public inline const uint16_t `[`read`](#classmln__adc_1aa8ef679b5ebc4305eee3c28c74293290)`(void)` | Read current result from ADC peripheral.
`public inline const uint16_t `[`read`](#classmln__adc_1acfbee9e71086e830e938ea6574681717)`(const `[`mln_pin_t`](#structmln__pin__t)` & pin)` | Change input pin and read result from ADC peripheral.
`public inline const uint16_t `[`read`](#classmln__adc_1a038ac36045c11bdff561c3062f61795a)`(const `[`mln_adc_in_t`](#mln__adc_8h_1a8b46c7c728d2203051bada5c588b72e9)` in)` | Change input and read result from ADC peripheral.

## Members

#### `public inline  `[`mln_adc`](#classmln__adc_1a6e055cc7727403cd94606f5d32867ec3)`()` {#classmln__adc_1a6e055cc7727403cd94606f5d32867ec3}

Default `[mln_adc](#classmln__adc)` class initializer.

Selects ADC0 as peripheral and GND as input

#### `public inline  `[`mln_adc`](#classmln__adc_1aa94f66bed48040b8f744a1fbf16ac18d)`(const `[`mln_pin_t`](#structmln__pin__t)` & pin)` {#classmln__adc_1aa94f66bed48040b8f744a1fbf16ac18d}

Initialize `[mln_adc](#classmln__adc)` class from pin.

#### Parameters
* `pin` Pin to set adc to

Set the pin as input before this

#### `public inline  `[`mln_adc`](#classmln__adc_1afb23838575ae29e899bf108e09e08cbb)`(const `[`mln_adc_in_t`](#mln__adc_8h_1a8b46c7c728d2203051bada5c588b72e9)` in)` {#classmln__adc_1afb23838575ae29e899bf108e09e08cbb}

Initialize `[mln_adc](#classmln__adc)` class from adc input.

#### Parameters
* `pin` Pin to set adc to

#### `public inline const void `[`config`](#classmln__adc_1a715704c24ca9c2c62b22917d79d6c2d5)`(const bool standby,const `[`mln_adc_resolution_t`](#mln__adc_8h_1a0d59f42a8f91323537152a301270a004)` res,const `[`mln_adc_accumulation_t`](#mln__adc_8h_1a59aa030466723b07fda5aab69e6390a5)` samp,const `[`mln_adc_prescaler_t`](#mln__adc_8h_1a8686df8036c6ba2fc811904bf82cfa18)` presc)` {#classmln__adc_1a715704c24ca9c2c62b22917d79d6c2d5}

Configure the ADC peripheral.

#### Parameters
* `standby` If true, the peripheral is also running in device standby 

* `res` Resolution to be utilized 

* `samp` Number of samples to be acquired per reading 

* `presc` The frequency prescaler to be used

#### `public inline const void `[`enable`](#classmln__adc_1a2490fadc8bf4c906124a1a01c83d6d0e)`(void)` {#classmln__adc_1a2490fadc8bf4c906124a1a01c83d6d0e}

Enable the ADC peripheral.

#### `public inline const void `[`disable`](#classmln__adc_1acf7fda713d82aaaa1421c7527866b894)`(void)` {#classmln__adc_1acf7fda713d82aaaa1421c7527866b894}

Disable the ADC peripheral.

#### `public inline void `[`set_in`](#classmln__adc_1a29d0b97e4bd9da7c031ab369b8552e26)`(const `[`mln_pin_t`](#structmln__pin__t)` & pin)` {#classmln__adc_1a29d0b97e4bd9da7c031ab369b8552e26}

Configure the input pin of the ADC peripheral.

#### Parameters
* `pin` Pin to read from

#### `public inline const void `[`set_in`](#classmln__adc_1a110c322e75ec55665b7dc97fd2e245bb)`(const `[`mln_adc_in_t`](#mln__adc_8h_1a8b46c7c728d2203051bada5c588b72e9)` in)` {#classmln__adc_1a110c322e75ec55665b7dc97fd2e245bb}

Configure the input of the ADC peripheral.

#### Parameters
* `in` Input to read from

#### `public inline const void `[`start`](#classmln__adc_1a456941f8b507ca65e3d6866f7f2052bd)`(void)` {#classmln__adc_1a456941f8b507ca65e3d6866f7f2052bd}

Start reading of ADC peripheral.

#### `public inline const bool `[`has_result`](#classmln__adc_1a9246f67d595392f5e276c809d577f4d1)`(void)` {#classmln__adc_1a9246f67d595392f5e276c809d577f4d1}

Check whether ADC peripheral has a result ready.

#### Returns
Whether ADC peripheral has a result ready 

#### Parameters
* `true` Result is ready 

* `false` Result not ready

#### `public inline const uint16_t `[`read`](#classmln__adc_1aa8ef679b5ebc4305eee3c28c74293290)`(void)` {#classmln__adc_1aa8ef679b5ebc4305eee3c28c74293290}

Read current result from ADC peripheral.

#### Parameters
* `-1` If peripheral is disabled 

* `result` else

If no reading is available, a new reading is started and waited until result is available 

Previous reading will be returned, if available and not already read out

#### `public inline const uint16_t `[`read`](#classmln__adc_1acfbee9e71086e830e938ea6574681717)`(const `[`mln_pin_t`](#structmln__pin__t)` & pin)` {#classmln__adc_1acfbee9e71086e830e938ea6574681717}

Change input pin and read result from ADC peripheral.

#### Parameters
* `pin` Pin to change to

#### Parameters
* `-1` If peripheral is disabled 

* `result` else

If no reading is available, a new reading is started and waited until result is available 

Previous reading will be discarded, if available and not already read out

#### `public inline const uint16_t `[`read`](#classmln__adc_1a038ac36045c11bdff561c3062f61795a)`(const `[`mln_adc_in_t`](#mln__adc_8h_1a8b46c7c728d2203051bada5c588b72e9)` in)` {#classmln__adc_1a038ac36045c11bdff561c3062f61795a}

Change input and read result from ADC peripheral.

#### Parameters
* `pin` Pin to change to

#### Parameters
* `-1` If peripheral is disabled 

* `result` else

If no reading is available, a new reading is started and waited until result is available 

Previous reading will be discarded, if available and not already read out

# class `mln_gpio` {#classmln__gpio}

GPIO peripheral class.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  `[`mln_gpio`](#classmln__gpio_1ae5f3e9e14f4c417a62638716798989c5)`() = default` | Default [mln_gpio](#classmln__gpio) class initializer.
`public inline  `[`mln_gpio`](#classmln__gpio_1affe4c21e6ced29a732aca17f9d683de7)`(const `[`mln_pin_t`](#structmln__pin__t)` & new_pin,const `[`mln_gpio_dir_t`](#mln__gpio_8h_1a3b39a8438117dc8dc97942e72edc36ff)` & direction,const bool inverted)` | [mln_adc](#classmln__adc) class initializer
`public inline void `[`attach_interrupt`](#classmln__gpio_1ac41887f494ca6e20f0f3447a1ad9c80b)`(`[`mln_gpio_isc_t`](#mln__gpio_8h_1a874d15679b0e76b5d3a88d83f001ad6c)` isc)` | Attach interrupt to pin.
`public inline const void `[`set`](#classmln__gpio_1a6658a4ffd79c21c982ca896521db7386)`(void)` | Set pin to HIGH.
`public inline const void `[`clear`](#classmln__gpio_1a0aa0cdb1d45809203f26c801dfac2a09)`(void)` | Clear pin to LOW.
`public inline const void `[`toggle`](#classmln__gpio_1ac9e4e237a5fd9383a3c3f86187bf3903)`(void)` | Toggle pin value.
`public inline const void `[`put`](#classmln__gpio_1a0bb9556f20f7246d0b8c17bf011da273)`(bool val)` | Put value on pin.
`public inline const bool `[`get`](#classmln__gpio_1a39a371791690744ad8331f14619631f8)`(void)` | Get value of pin.
`public inline void `[`conf_dir`](#classmln__gpio_1a2f4ffd9b40007e973417f095540b4133)`(const `[`mln_gpio_dir_t`](#mln__gpio_8h_1a3b39a8438117dc8dc97942e72edc36ff)` & dir)` | Configure direction of pin.
`public inline void `[`conf_pull`](#classmln__gpio_1a12d182512a3b0b99111f65a2f591130c)`(const `[`mln_gpio_dir_t`](#mln__gpio_8h_1a3b39a8438117dc8dc97942e72edc36ff)` & pull)` | Configure pull of pin.

## Members

#### `public inline  `[`mln_gpio`](#classmln__gpio_1ae5f3e9e14f4c417a62638716798989c5)`() = default` {#classmln__gpio_1ae5f3e9e14f4c417a62638716798989c5}

Default [mln_gpio](#classmln__gpio) class initializer.

#### `public inline  `[`mln_gpio`](#classmln__gpio_1affe4c21e6ced29a732aca17f9d683de7)`(const `[`mln_pin_t`](#structmln__pin__t)` & new_pin,const `[`mln_gpio_dir_t`](#mln__gpio_8h_1a3b39a8438117dc8dc97942e72edc36ff)` & direction,const bool inverted)` {#classmln__gpio_1affe4c21e6ced29a732aca17f9d683de7}

[mln_adc](#classmln__adc) class initializer

#### Parameters
* `new_pin` Pin to control 

* `direction` Direction to initialize pin to 

* `inverted` If true, pin is operated in inverted mde

#### `public inline void `[`attach_interrupt`](#classmln__gpio_1ac41887f494ca6e20f0f3447a1ad9c80b)`(`[`mln_gpio_isc_t`](#mln__gpio_8h_1a874d15679b0e76b5d3a88d83f001ad6c)` isc)` {#classmln__gpio_1ac41887f494ca6e20f0f3447a1ad9c80b}

Attach interrupt to pin.

#### Parameters
* `isc` Interrupt type

#### `public inline const void `[`set`](#classmln__gpio_1a6658a4ffd79c21c982ca896521db7386)`(void)` {#classmln__gpio_1a6658a4ffd79c21c982ca896521db7386}

Set pin to HIGH.

#### `public inline const void `[`clear`](#classmln__gpio_1a0aa0cdb1d45809203f26c801dfac2a09)`(void)` {#classmln__gpio_1a0aa0cdb1d45809203f26c801dfac2a09}

Clear pin to LOW.

#### `public inline const void `[`toggle`](#classmln__gpio_1ac9e4e237a5fd9383a3c3f86187bf3903)`(void)` {#classmln__gpio_1ac9e4e237a5fd9383a3c3f86187bf3903}

Toggle pin value.

#### `public inline const void `[`put`](#classmln__gpio_1a0bb9556f20f7246d0b8c17bf011da273)`(bool val)` {#classmln__gpio_1a0bb9556f20f7246d0b8c17bf011da273}

Put value on pin.

#### Parameters
* `val` Value to put on pin

#### `public inline const bool `[`get`](#classmln__gpio_1a39a371791690744ad8331f14619631f8)`(void)` {#classmln__gpio_1a39a371791690744ad8331f14619631f8}

Get value of pin.

#### `public inline void `[`conf_dir`](#classmln__gpio_1a2f4ffd9b40007e973417f095540b4133)`(const `[`mln_gpio_dir_t`](#mln__gpio_8h_1a3b39a8438117dc8dc97942e72edc36ff)` & dir)` {#classmln__gpio_1a2f4ffd9b40007e973417f095540b4133}

Configure direction of pin.

#### Parameters
* `dir` Direction to be set

#### `public inline void `[`conf_pull`](#classmln__gpio_1a12d182512a3b0b99111f65a2f591130c)`(const `[`mln_gpio_dir_t`](#mln__gpio_8h_1a3b39a8438117dc8dc97942e72edc36ff)` & pull)` {#classmln__gpio_1a12d182512a3b0b99111f65a2f591130c}

Configure pull of pin.

#### Parameters
* `pull` Direction to be set

# class `mln_spi` {#classmln__spi}

SPI peripheral class.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  `[`mln_spi`](#classmln__spi_1a00b52c469eec2d54ed1214a4f3d9fd54)`()` | Default `[mln_spi](#classmln__spi)` class initializer.
`public inline  `[`mln_spi`](#classmln__spi_1a1dc67d2d3a15c0f9842f67938dc91e22)`(SPI_t * new_spi)` | Initialize `[mln_spi](#classmln__spi)` class from specific SPI peripheral.
`public inline  `[`mln_spi`](#classmln__spi_1a5e9bdd50fc97acdf828939d89ad236f9)`(SPI_t * new_spi,uint8_t mode)` | Initialize `[mln_spi](#classmln__spi)` class from specific SPI peripheral and mode.
`public inline  `[`mln_spi`](#classmln__spi_1a78a3b8fc32da31e86fb279e4d62aa6e8)`(SPI_t * new_spi,`[`mln_pin_t`](#structmln__pin__t)` & new_cs)` | Initialize `[mln_spi](#classmln__spi)` class from specific SPI peripheral and cs pin.
`public inline  `[`mln_spi`](#classmln__spi_1ac0744fc5b0e103415bd7f6c342b3194d)`(SPI_t * new_spi,`[`mln_pin_t`](#structmln__pin__t)` & new_cs,const uint8_t mode)` | Initialize `[mln_spi](#classmln__spi)` class from specific SPI peripheral and cs pin as well as SPI mode.
`public inline const void `[`exchange`](#classmln__spi_1ad2fffc17a0b845791b8f4f86e667e364)`(uint8_t * buffer,uint8_t length)` | Exchange package with SPI peripheral.
`public inline const void `[`write`](#classmln__spi_1af145b40e4b5496b5aa1c14f7ae6c15a2)`(uint8_t * buffer,uint8_t length)` | Send package with SPI peripheral.
`public inline const void `[`read`](#classmln__spi_1ae799463466c65fa23df52f146961f42a)`(uint8_t * buffer,uint8_t length)` | Receive package with SPI peripheral.

## Members

#### `public inline  `[`mln_spi`](#classmln__spi_1a00b52c469eec2d54ed1214a4f3d9fd54)`()` {#classmln__spi_1a00b52c469eec2d54ed1214a4f3d9fd54}

Default `[mln_spi](#classmln__spi)` class initializer.

Selects SPI0 as peripheral and no CS pin as well as SPI mode 0

#### `public inline  `[`mln_spi`](#classmln__spi_1a1dc67d2d3a15c0f9842f67938dc91e22)`(SPI_t * new_spi)` {#classmln__spi_1a1dc67d2d3a15c0f9842f67938dc91e22}

Initialize `[mln_spi](#classmln__spi)` class from specific SPI peripheral.

#### Parameters
* `new_spi` SPI peripheral to use

Uses no CS pin as well as SPI mode 0

#### `public inline  `[`mln_spi`](#classmln__spi_1a5e9bdd50fc97acdf828939d89ad236f9)`(SPI_t * new_spi,uint8_t mode)` {#classmln__spi_1a5e9bdd50fc97acdf828939d89ad236f9}

Initialize `[mln_spi](#classmln__spi)` class from specific SPI peripheral and mode.

#### Parameters
* `new_spi` SPI peripheral to use 

* `mode` SPI mode to be used (0-3)

Uses no CS pin

#### `public inline  `[`mln_spi`](#classmln__spi_1a78a3b8fc32da31e86fb279e4d62aa6e8)`(SPI_t * new_spi,`[`mln_pin_t`](#structmln__pin__t)` & new_cs)` {#classmln__spi_1a78a3b8fc32da31e86fb279e4d62aa6e8}

Initialize `[mln_spi](#classmln__spi)` class from specific SPI peripheral and cs pin.

#### Parameters
* `new_spi` SPI peripheral to use 

* `new_cs` CS pin to be used

Uses SPI mode 0

#### `public inline  `[`mln_spi`](#classmln__spi_1ac0744fc5b0e103415bd7f6c342b3194d)`(SPI_t * new_spi,`[`mln_pin_t`](#structmln__pin__t)` & new_cs,const uint8_t mode)` {#classmln__spi_1ac0744fc5b0e103415bd7f6c342b3194d}

Initialize `[mln_spi](#classmln__spi)` class from specific SPI peripheral and cs pin as well as SPI mode.

#### Parameters
* `new_spi` SPI peripheral to use 

* `new_cs` CS pin to bes used 

* `mode` SPI mode to be used (0-3)

#### `public inline const void `[`exchange`](#classmln__spi_1ad2fffc17a0b845791b8f4f86e667e364)`(uint8_t * buffer,uint8_t length)` {#classmln__spi_1ad2fffc17a0b845791b8f4f86e667e364}

Exchange package with SPI peripheral.

#### Parameters
* `*buffer` Pointer to data buffer to be exchanged 

* `length` Length of buffer

#### `public inline const void `[`write`](#classmln__spi_1af145b40e4b5496b5aa1c14f7ae6c15a2)`(uint8_t * buffer,uint8_t length)` {#classmln__spi_1af145b40e4b5496b5aa1c14f7ae6c15a2}

Send package with SPI peripheral.

#### Parameters
* `*buffer` Pointer to data buffer to be sent 

* `length` Length of buffer

#### `public inline const void `[`read`](#classmln__spi_1ae799463466c65fa23df52f146961f42a)`(uint8_t * buffer,uint8_t length)` {#classmln__spi_1ae799463466c65fa23df52f146961f42a}

Receive package with SPI peripheral.

#### Parameters
* `*buffer` Pointer to data buffer to be received 

* `length` Length of buffer

# class `mln_timer` {#classmln__timer}

TCA peripheral class.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public void(* `[`isr`](#classmln__timer_1a607a0f743963cea10089758cf0600a2e) | ISR function currently stored in the class.
`public inline  `[`mln_timer`](#classmln__timer_1ac44fb64119f1adc515488dfa36fb5981)`(uint16_t period)` | [mln_timer](#classmln__timer) class initializer
`public inline void `[`set_isr`](#classmln__timer_1aeb16cfd705c6627d22cf0d311094242b)`(void(*)(void) f)` | Set ISR function of TCA peripheral.
`public inline const void `[`start`](#classmln__timer_1a6d22a0a1ba7339fb17bd8f137726bace)`(void)` | Start TCA peripheral.
`public inline const void `[`stop`](#classmln__timer_1ad06a5923262d674648369b0fe8fee7fe)`(void)` | Stop TCA peripheral.
`public inline const bool `[`is_running`](#classmln__timer_1aa4f9753cdeeb66e4489b6ba5802379e7)`(void)` | Check if TCA peripheral is running.
`public inline const float `[`get_period`](#classmln__timer_1adfdd8df8386b642eb810a914391668bb)`(void)` | 

## Members

#### `public void(* `[`isr`](#classmln__timer_1a607a0f743963cea10089758cf0600a2e) {#classmln__timer_1a607a0f743963cea10089758cf0600a2e}

ISR function currently stored in the class.

#### `public inline  `[`mln_timer`](#classmln__timer_1ac44fb64119f1adc515488dfa36fb5981)`(uint16_t period)` {#classmln__timer_1ac44fb64119f1adc515488dfa36fb5981}

[mln_timer](#classmln__timer) class initializer

#### Parameters
* `period` Desired period

#### `public inline void `[`set_isr`](#classmln__timer_1aeb16cfd705c6627d22cf0d311094242b)`(void(*)(void) f)` {#classmln__timer_1aeb16cfd705c6627d22cf0d311094242b}

Set ISR function of TCA peripheral.

#### `public inline const void `[`start`](#classmln__timer_1a6d22a0a1ba7339fb17bd8f137726bace)`(void)` {#classmln__timer_1a6d22a0a1ba7339fb17bd8f137726bace}

Start TCA peripheral.

#### `public inline const void `[`stop`](#classmln__timer_1ad06a5923262d674648369b0fe8fee7fe)`(void)` {#classmln__timer_1ad06a5923262d674648369b0fe8fee7fe}

Stop TCA peripheral.

#### `public inline const bool `[`is_running`](#classmln__timer_1aa4f9753cdeeb66e4489b6ba5802379e7)`(void)` {#classmln__timer_1aa4f9753cdeeb66e4489b6ba5802379e7}

Check if TCA peripheral is running.

#### Returns
Whether TCA peripheral is running 

#### Parameters
* `true` Peripheral is running 

* `false` Peripheral is not running

#### `public inline const float `[`get_period`](#classmln__timer_1adfdd8df8386b642eb810a914391668bb)`(void)` {#classmln__timer_1adfdd8df8386b642eb810a914391668bb}

# class `mln_twi` {#classmln__twi}

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  `[`mln_twi`](#classmln__twi_1aca2ba071cd738c5a0914f8906ddcb5b5)`(const uint32_t frequency)` | Default [mln_twi](#classmln__twi) initializer.
`public inline void `[`read`](#classmln__twi_1a362b494a7cf58d3b9d2ba1870b4ecbeb)`(const uint8_t address,uint8_t * data,const uint8_t data_length)` | Read certain amount of bytes from TWI slave.
`public inline bool `[`write`](#classmln__twi_1a749b27d1e8b0d240423f8656fe8f63c9)`(const uint8_t address,const uint8_t * data,const uint8_t data_length)` | Send certain amount of bytes to TWI slave.

## Members

#### `public inline  `[`mln_twi`](#classmln__twi_1aca2ba071cd738c5a0914f8906ddcb5b5)`(const uint32_t frequency)` {#classmln__twi_1aca2ba071cd738c5a0914f8906ddcb5b5}

Default [mln_twi](#classmln__twi) initializer.

#### Parameters
* `frequency` TWI frequency to be used (default 100000)

#### `public inline void `[`read`](#classmln__twi_1a362b494a7cf58d3b9d2ba1870b4ecbeb)`(const uint8_t address,uint8_t * data,const uint8_t data_length)` {#classmln__twi_1a362b494a7cf58d3b9d2ba1870b4ecbeb}

Read certain amount of bytes from TWI slave.

#### Parameters
* `address` Address of the slave device 

* `data` Pointer to data buffer to be save data in 

* `data_length` Amount of bytes to be read

Starts and waits for completed transaction, stops it

#### `public inline bool `[`write`](#classmln__twi_1a749b27d1e8b0d240423f8656fe8f63c9)`(const uint8_t address,const uint8_t * data,const uint8_t data_length)` {#classmln__twi_1a749b27d1e8b0d240423f8656fe8f63c9}

Send certain amount of bytes to TWI slave.

#### Parameters
* `address` Address of the slave device 

* `data` Pointer to data buffer to be sent 

* `data_length` Length of data buffer to be sent

#### Returns
Whether transaction was successful 

#### Parameters
* `true` Transaction was successful 

* `false` Transaction at address could not be started or was not acknowledged

Starts and waits for completed transaction, stops it

# class `mln_uart` {#classmln__uart}

USART peripheral class.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  `[`mln_uart`](#classmln__uart_1af0bfb0e87493c5d264962646b0ce1730)`(USART_t * new_inst,uint32_t baud)` | 
`public inline void `[`set_isr`](#classmln__uart_1adc22948c3bbceebd2a4b396860e0d356)`(void(*)(void) new_isr)` | 
`public inline const void `[`write`](#classmln__uart_1a191f2aaf8afffffe993395c60c71d93e)`(const uint8_t data)` | 
`public inline const uint8_t `[`read`](#classmln__uart_1aae2b6c410d718d6ce64e0990895c1cf8)`(void)` | 
`public inline void `[`push`](#classmln__uart_1ac2a9b7607750c2623b9c4a1a4e7d42d3)`(void)` | 
`public inline uint8_t `[`pull`](#classmln__uart_1a5b81e87c2bd1249bacc266f92024e4db)`(uint8_t * new_buffer)` | 
`public inline const bool `[`is_busy_tx`](#classmln__uart_1a154c813c497997ca1b80202c55fcabdc)`(void)` | 
`public inline const bool `[`is_busy_rx`](#classmln__uart_1af0c4c2c4fe9410c26be25854ea42abae)`(void)` | 
`public inline const uint8_t `[`data_available`](#classmln__uart_1af705656475771cd2df0d8f3fed1624c4)`(void)` | 
`public inline const void `[`run_isr`](#classmln__uart_1a0c237c85758c352b5c83a73a86c0410b)`(void)` | 

## Members

#### `public inline  `[`mln_uart`](#classmln__uart_1af0bfb0e87493c5d264962646b0ce1730)`(USART_t * new_inst,uint32_t baud)` {#classmln__uart_1af0bfb0e87493c5d264962646b0ce1730}

#### `public inline void `[`set_isr`](#classmln__uart_1adc22948c3bbceebd2a4b396860e0d356)`(void(*)(void) new_isr)` {#classmln__uart_1adc22948c3bbceebd2a4b396860e0d356}

#### `public inline const void `[`write`](#classmln__uart_1a191f2aaf8afffffe993395c60c71d93e)`(const uint8_t data)` {#classmln__uart_1a191f2aaf8afffffe993395c60c71d93e}

#### `public inline const uint8_t `[`read`](#classmln__uart_1aae2b6c410d718d6ce64e0990895c1cf8)`(void)` {#classmln__uart_1aae2b6c410d718d6ce64e0990895c1cf8}

#### `public inline void `[`push`](#classmln__uart_1ac2a9b7607750c2623b9c4a1a4e7d42d3)`(void)` {#classmln__uart_1ac2a9b7607750c2623b9c4a1a4e7d42d3}

#### `public inline uint8_t `[`pull`](#classmln__uart_1a5b81e87c2bd1249bacc266f92024e4db)`(uint8_t * new_buffer)` {#classmln__uart_1a5b81e87c2bd1249bacc266f92024e4db}

#### `public inline const bool `[`is_busy_tx`](#classmln__uart_1a154c813c497997ca1b80202c55fcabdc)`(void)` {#classmln__uart_1a154c813c497997ca1b80202c55fcabdc}

#### `public inline const bool `[`is_busy_rx`](#classmln__uart_1af0c4c2c4fe9410c26be25854ea42abae)`(void)` {#classmln__uart_1af0c4c2c4fe9410c26be25854ea42abae}

#### `public inline const uint8_t `[`data_available`](#classmln__uart_1af705656475771cd2df0d8f3fed1624c4)`(void)` {#classmln__uart_1af705656475771cd2df0d8f3fed1624c4}

#### `public inline const void `[`run_isr`](#classmln__uart_1a0c237c85758c352b5c83a73a86c0410b)`(void)` {#classmln__uart_1a0c237c85758c352b5c83a73a86c0410b}

# struct `mln_opamp_direct_init_t` {#structmln__opamp__direct__init__t}

Opamp direct configuration struct.

#### Parameters
* `opamp_n` Opamp device (0-3) 

* `runstdby` If true, the peripheral is also running in device standby 

* `output` If true, the output is enabled 

* `lowpower` If true, the low power mode is enabled (reduced output range) 

* `in_pos` Positive input selection 

* `in_neg` Negative input selection

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public `[`mln_opamp_device_t`](#mln__opamp_8h_1af933df376949fd10542121c2129b7371)` `[`opamp`](#structmln__opamp__direct__init__t_1a5fc77b3ac8e87686e453efb2980db426) | 
`public bool `[`runstdby`](#structmln__opamp__direct__init__t_1a15b0fafe6f0031bd428b2abd38a76541) | 
`public bool `[`output`](#structmln__opamp__direct__init__t_1a44eef8b9c9486ccb88a41b18d0f2c370) | 
`public bool `[`lowpower`](#structmln__opamp__direct__init__t_1a2360775d9d1bc3f2d8325214a7777994) | 
`public `[`mln_opamp_direct_in_pos_t`](#mln__opamp_8h_1a3cbfa5e9fcaadbb6ab2224a97065bcb4)` `[`in_pos`](#structmln__opamp__direct__init__t_1ade598e4d918498e63d9ad71033111cae) | 
`public `[`mln_opamp_direct_in_neg_t`](#mln__opamp_8h_1a62018af5255e8c12c3b59ee9d4285668)` `[`in_neg`](#structmln__opamp__direct__init__t_1a53f4a90392f861a763378bb20f77ce4f) | 

## Members

#### `public `[`mln_opamp_device_t`](#mln__opamp_8h_1af933df376949fd10542121c2129b7371)` `[`opamp`](#structmln__opamp__direct__init__t_1a5fc77b3ac8e87686e453efb2980db426) {#structmln__opamp__direct__init__t_1a5fc77b3ac8e87686e453efb2980db426}

#### `public bool `[`runstdby`](#structmln__opamp__direct__init__t_1a15b0fafe6f0031bd428b2abd38a76541) {#structmln__opamp__direct__init__t_1a15b0fafe6f0031bd428b2abd38a76541}

#### `public bool `[`output`](#structmln__opamp__direct__init__t_1a44eef8b9c9486ccb88a41b18d0f2c370) {#structmln__opamp__direct__init__t_1a44eef8b9c9486ccb88a41b18d0f2c370}

#### `public bool `[`lowpower`](#structmln__opamp__direct__init__t_1a2360775d9d1bc3f2d8325214a7777994) {#structmln__opamp__direct__init__t_1a2360775d9d1bc3f2d8325214a7777994}

#### `public `[`mln_opamp_direct_in_pos_t`](#mln__opamp_8h_1a3cbfa5e9fcaadbb6ab2224a97065bcb4)` `[`in_pos`](#structmln__opamp__direct__init__t_1ade598e4d918498e63d9ad71033111cae) {#structmln__opamp__direct__init__t_1ade598e4d918498e63d9ad71033111cae}

#### `public `[`mln_opamp_direct_in_neg_t`](#mln__opamp_8h_1a62018af5255e8c12c3b59ee9d4285668)` `[`in_neg`](#structmln__opamp__direct__init__t_1a53f4a90392f861a763378bb20f77ce4f) {#structmln__opamp__direct__init__t_1a53f4a90392f861a763378bb20f77ce4f}

# struct `mln_opamp_follower_init_t` {#structmln__opamp__follower__init__t}

Opamp follower configuration struct.

#### Parameters
* `opamp_n` Opamp device (0-3) 

* `runstdby` If true, the peripheral is also running in device standby 

* `output` If true, the output is enabled 

* `lowpower` If true, the low power mode is enabled (reduced output range) 

* `in` Input selection

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public `[`mln_opamp_device_t`](#mln__opamp_8h_1af933df376949fd10542121c2129b7371)` `[`opamp`](#structmln__opamp__follower__init__t_1a6c022089d17ea89aa446ad3ffc5d7c52) | 
`public bool `[`runstdby`](#structmln__opamp__follower__init__t_1a6952f9f93b8f8a47afdf1ed49a1e3ab2) | 
`public bool `[`output`](#structmln__opamp__follower__init__t_1a5548c6b637a8dd2fae7a9bbd203fee0c) | 
`public bool `[`lowpower`](#structmln__opamp__follower__init__t_1aaca698be49562ebff80f53de02a49020) | 
`public `[`mln_opamp_follower_in_t`](#mln__opamp_8h_1aa540c6514f278505956aadd10817ba10)` `[`in`](#structmln__opamp__follower__init__t_1a8c7941a2f53d1fc113cbae443d296c58) | 

## Members

#### `public `[`mln_opamp_device_t`](#mln__opamp_8h_1af933df376949fd10542121c2129b7371)` `[`opamp`](#structmln__opamp__follower__init__t_1a6c022089d17ea89aa446ad3ffc5d7c52) {#structmln__opamp__follower__init__t_1a6c022089d17ea89aa446ad3ffc5d7c52}

#### `public bool `[`runstdby`](#structmln__opamp__follower__init__t_1a6952f9f93b8f8a47afdf1ed49a1e3ab2) {#structmln__opamp__follower__init__t_1a6952f9f93b8f8a47afdf1ed49a1e3ab2}

#### `public bool `[`output`](#structmln__opamp__follower__init__t_1a5548c6b637a8dd2fae7a9bbd203fee0c) {#structmln__opamp__follower__init__t_1a5548c6b637a8dd2fae7a9bbd203fee0c}

#### `public bool `[`lowpower`](#structmln__opamp__follower__init__t_1aaca698be49562ebff80f53de02a49020) {#structmln__opamp__follower__init__t_1aaca698be49562ebff80f53de02a49020}

#### `public `[`mln_opamp_follower_in_t`](#mln__opamp_8h_1aa540c6514f278505956aadd10817ba10)` `[`in`](#structmln__opamp__follower__init__t_1a8c7941a2f53d1fc113cbae443d296c58) {#structmln__opamp__follower__init__t_1a8c7941a2f53d1fc113cbae443d296c58}

# struct `mln_opamp_inverting_init_t` {#structmln__opamp__inverting__init__t}

Opamp inverting configuration struct.

#### Parameters
* `opamp_n` Opamp device (0-3) 

* `runstdby` If true, the peripheral is also running in device standby 

* `output` If true, the output is enabled 

* `lowpower` If true, the low power mode is enabled (reduced output range) 

* `gain` Gain selection 

* `in_pos` Positive input selection 

* `in_neg` Negative input selection

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public `[`mln_opamp_device_t`](#mln__opamp_8h_1af933df376949fd10542121c2129b7371)` `[`opamp`](#structmln__opamp__inverting__init__t_1aa567bb32127bbde42541de4baf196507) | 
`public bool `[`runstdby`](#structmln__opamp__inverting__init__t_1a60563fb167bdac63d1aaed678330818c) | 
`public bool `[`output`](#structmln__opamp__inverting__init__t_1aa101e9c80c6634e7c6619e9185f755d8) | 
`public bool `[`lowpower`](#structmln__opamp__inverting__init__t_1a4b9c20a314a139618eaa9d98c962ff80) | 
`public `[`mln_opamp_gain_inverting_t`](#mln__opamp_8h_1adc2fb00f90dbb5185d25dc8f69961708)` `[`gain`](#structmln__opamp__inverting__init__t_1aa45d742667435f689283cf61c0d8e90c) | 
`public `[`mln_opamp_inverting_in_pos_t`](#mln__opamp_8h_1a5da13e036048d87b6b4a566d1770e47d)` `[`in_pos`](#structmln__opamp__inverting__init__t_1a6995509762d60e733e7d0fc0f8db5870) | 
`public `[`mln_opamp_inverting_in_neg_t`](#mln__opamp_8h_1a0024b5fd4e9c3baf4c207587bf9facd6)` `[`in_neg`](#structmln__opamp__inverting__init__t_1ab28be21b933eb5fd76c583f372e0a9b7) | 

## Members

#### `public `[`mln_opamp_device_t`](#mln__opamp_8h_1af933df376949fd10542121c2129b7371)` `[`opamp`](#structmln__opamp__inverting__init__t_1aa567bb32127bbde42541de4baf196507) {#structmln__opamp__inverting__init__t_1aa567bb32127bbde42541de4baf196507}

#### `public bool `[`runstdby`](#structmln__opamp__inverting__init__t_1a60563fb167bdac63d1aaed678330818c) {#structmln__opamp__inverting__init__t_1a60563fb167bdac63d1aaed678330818c}

#### `public bool `[`output`](#structmln__opamp__inverting__init__t_1aa101e9c80c6634e7c6619e9185f755d8) {#structmln__opamp__inverting__init__t_1aa101e9c80c6634e7c6619e9185f755d8}

#### `public bool `[`lowpower`](#structmln__opamp__inverting__init__t_1a4b9c20a314a139618eaa9d98c962ff80) {#structmln__opamp__inverting__init__t_1a4b9c20a314a139618eaa9d98c962ff80}

#### `public `[`mln_opamp_gain_inverting_t`](#mln__opamp_8h_1adc2fb00f90dbb5185d25dc8f69961708)` `[`gain`](#structmln__opamp__inverting__init__t_1aa45d742667435f689283cf61c0d8e90c) {#structmln__opamp__inverting__init__t_1aa45d742667435f689283cf61c0d8e90c}

#### `public `[`mln_opamp_inverting_in_pos_t`](#mln__opamp_8h_1a5da13e036048d87b6b4a566d1770e47d)` `[`in_pos`](#structmln__opamp__inverting__init__t_1a6995509762d60e733e7d0fc0f8db5870) {#structmln__opamp__inverting__init__t_1a6995509762d60e733e7d0fc0f8db5870}

#### `public `[`mln_opamp_inverting_in_neg_t`](#mln__opamp_8h_1a0024b5fd4e9c3baf4c207587bf9facd6)` `[`in_neg`](#structmln__opamp__inverting__init__t_1ab28be21b933eb5fd76c583f372e0a9b7) {#structmln__opamp__inverting__init__t_1ab28be21b933eb5fd76c583f372e0a9b7}

# struct `mln_opamp_noninverting_init_t` {#structmln__opamp__noninverting__init__t}

Opamp non-inverting configuration struct.

#### Parameters
* `opamp_n` Opamp device (0-3) 

* `runstdby` If true, the peripheral is also running in device standby 

* `output` If true, the output is enabled 

* `lowpower` If true, the low power mode is enabled (reduced output range) 

* `gain` Gain selection 

* `in` Input selection

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public `[`mln_opamp_device_t`](#mln__opamp_8h_1af933df376949fd10542121c2129b7371)` `[`opamp`](#structmln__opamp__noninverting__init__t_1a249b036d07d7c4359590fe3aad276bd0) | 
`public bool `[`runstdby`](#structmln__opamp__noninverting__init__t_1a599f1edb282177319e4472a72c96c598) | 
`public bool `[`output`](#structmln__opamp__noninverting__init__t_1ad0290dd56789b92e07feeb10220a7e5c) | 
`public bool `[`lowpower`](#structmln__opamp__noninverting__init__t_1a29df863195f4e55100e1d034e27e5231) | 
`public `[`mln_opamp_gain_noninverting_t`](#mln__opamp_8h_1a2fa59d453ef8befab0cd54b16d4f7e63)` `[`gain`](#structmln__opamp__noninverting__init__t_1a3efc50eab8537bc884df64a3cb1a865e) | 
`public `[`mln_opamp_noninverting_in_t`](#mln__opamp_8h_1ae0ead844924e9725d7f748ba47c647b2)` `[`in`](#structmln__opamp__noninverting__init__t_1a71cbb9424292a6b99549ebcf084a1502) | 

## Members

#### `public `[`mln_opamp_device_t`](#mln__opamp_8h_1af933df376949fd10542121c2129b7371)` `[`opamp`](#structmln__opamp__noninverting__init__t_1a249b036d07d7c4359590fe3aad276bd0) {#structmln__opamp__noninverting__init__t_1a249b036d07d7c4359590fe3aad276bd0}

#### `public bool `[`runstdby`](#structmln__opamp__noninverting__init__t_1a599f1edb282177319e4472a72c96c598) {#structmln__opamp__noninverting__init__t_1a599f1edb282177319e4472a72c96c598}

#### `public bool `[`output`](#structmln__opamp__noninverting__init__t_1ad0290dd56789b92e07feeb10220a7e5c) {#structmln__opamp__noninverting__init__t_1ad0290dd56789b92e07feeb10220a7e5c}

#### `public bool `[`lowpower`](#structmln__opamp__noninverting__init__t_1a29df863195f4e55100e1d034e27e5231) {#structmln__opamp__noninverting__init__t_1a29df863195f4e55100e1d034e27e5231}

#### `public `[`mln_opamp_gain_noninverting_t`](#mln__opamp_8h_1a2fa59d453ef8befab0cd54b16d4f7e63)` `[`gain`](#structmln__opamp__noninverting__init__t_1a3efc50eab8537bc884df64a3cb1a865e) {#structmln__opamp__noninverting__init__t_1a3efc50eab8537bc884df64a3cb1a865e}

#### `public `[`mln_opamp_noninverting_in_t`](#mln__opamp_8h_1ae0ead844924e9725d7f748ba47c647b2)` `[`in`](#structmln__opamp__noninverting__init__t_1a71cbb9424292a6b99549ebcf084a1502) {#structmln__opamp__noninverting__init__t_1a71cbb9424292a6b99549ebcf084a1502}

# struct `mln_pin_t` {#structmln__pin__t}

Standard pin struct.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public volatile PORT_t * `[`port`](#structmln__pin__t_1acb218068b34c351c9cd6824d105475b5) | 
`public uint8_t `[`pin_num`](#structmln__pin__t_1a15b083d2cc20d9d9ae3d51b7d4d60c79) | 

## Members

#### `public volatile PORT_t * `[`port`](#structmln__pin__t_1acb218068b34c351c9cd6824d105475b5) {#structmln__pin__t_1acb218068b34c351c9cd6824d105475b5}

#### `public uint8_t `[`pin_num`](#structmln__pin__t_1a15b083d2cc20d9d9ae3d51b7d4d60c79) {#structmln__pin__t_1a15b083d2cc20d9d9ae3d51b7d4d60c79}

Generated by [Moxygen](https://sourcey.com/moxygen)
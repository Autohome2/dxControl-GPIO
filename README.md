# GPIO for Speeduino

The Gpio for Speeduino are a family of multipurpose general programmable input and output modules.
The modules are programmed via Tunerstudio either via the serial port or over the integrated CanBus network

The modules can use several different processor board types, including different arduino, teensy,  stm32.

main mothe rboard fitted with a Teensy 3.2 and daughter boards
To date there are three types of daughter boards u

	1 8ch digital inputs 

	2.8ch universal inputs,these can accept both digital and analogue voltages up to 500v peak!

	3.8ch high side output drivers.these have full error/fault logging capability.

The motherboard can accept any combination of up to four of these daughter boards

The module can also accept inputs from Canbus and output to Canbus too!

Io operations are programmed with logic, < ,>,= and AND



Version 1.00

This firmware supports up to 16 output channels and 16 input channels from local sources. The Canbus functions are disabled
The Output channels can be activated via up to two conditions with logical operations of < , > , = and AND
There are 8 pwm channels with independantly selectable frequency and  duty cycle. These pwm channels can be allocated to any output channel. 
In addition the pwm duty cycle is programmed using either a fixed on DC and off DC , with a curve or a table.The table axis can use and input channel data!

The firmware supports the use of either a teensy 3.2 or a teensy 3.5 .
Due to these MCU actual hardware restrictions the number of physical io may be limited , see below.

Teensy 3.2

18 io if the hidden smt pads are not utilised of these 10 are outputs and 8 are inputs(although this could be reconfigured if you wanted). 
The inputs are either digital or analog capable 

Teensy 3.5

32 io if the hidden smt pads are not utilised of these 16 are outputs and 16 are inputs(although this could be reconfigured if you wanted). 
The inputs are either digital or analog capable 



Version 2.00

This version adds the ability to accept data from remote modules over a Canbus network.


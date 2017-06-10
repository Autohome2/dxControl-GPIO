# GPIO for Speeduino

The Gpio for Speeduino are a family of multipurpose general programmable input and output modules that can be used both in conjunction with the Speeduino engine ECU or standalone.
The modules are programmed via Tunerstudio either via the serial port or over the integrated CanBus network(certain variants only)

The modules can use several different processor board types, including different arduino, teensy and stm32.

Io operations are programmed with logic, < ,>,= and bitwise AND . some variants offer 2 or even 3 connecting logic conditions.

Versions 
GPIO MINI V0.001

This firmware supports up to 16 output channels , 16 input channels and 16 analog channels from local sources subject to MCU capability.
MCU supported are currently Arduino Pro-Mini , Arduino Uno and Arduino Mega2560.
The Output channels can be activated via one condition with logical operations of < , > and =
Only onboard(local) io are supported in this version.

GPIO MINI V0.002

This firmware offers the same features as V0.001 but with the ability to also access the values from a Speeduino ECU connected directly using the Speeduino Serial3 support.

GPIO STD Version 1.00

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

GPIO STD Version 2.00

This version adds the ability to accept data from remote modules over a Canbus network.


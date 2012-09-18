MiniProject01
=======

In this project, I use the GPIO interrupt from an external pushbutton to trigger temperature 
readings off of the TC74 temperature sensor. The temperature in degrees Celsius is output to 
the terminal. Every time the temperature sensor is read LED0 is toggled.

At the same time, an analog input is read at 100Hz. The voltage is used to control the 
PWM duty cycle on an output that goes to LED1. The program handles the ^C interrupt by 
printing a shutdown message to the terminal.

Hardware Setup
=======

The pinout is shown below. These pin numbers refer to Table 11 - Expansion Header P9 Pinout

PIN14 -> LED1
PIN15 -> LED0
PIN19 -> TC74 I2C CLOCK
PIN20 -> TC74 I2C DATA
PIN27 -> BUTTON
PIN36 -> POTENTIOMETER

Software Setup
=======

This software requires the following repositories:

git@github.com:MarkAYoder/BeagleBoard-exercises
git@github.com:millerap/ECE497

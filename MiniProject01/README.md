MiniProject01
=======

In this project, I use the GPIO interrupt from an external pushbutton to trigger temperature 
readings off of the TC74 temperature sensor. The temperature in degrees Celsius is output to 
the terminal.

At the same time, an analog input is read once a second. The voltage is used to control the 
PWM duty cycle on an output that goes to LED1. A heartbeat pattern is output on LED0. The 
program handles the ^C interrupt by printing a shutdown message to the terminal.

# freeRTOS_blinky

Simple Keil uVision FreeRTOS project intended for the <b>Texas Instruments TM4C123</b> microcontroller.

This project utilizes a <b>Round Robin</b> scheduling algothrim to switch between two threads
- One thread blinks the on-board blue LED at a rate of 500 ms
- The second thread polls on the on-board switch and when pressed, toggles an off-board LED.

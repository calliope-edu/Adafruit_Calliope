# Calliope Arduino library

### This is a fork of [Adafruit's micro:bit library](https://github.com/adafruit/Adafruit_Microbit)
The fork was modified to support the Calliope mini V3 and include an example project to show core functionalities of the Calliope mini V3.

Included: 

  * Sample project for Calliope mini 3 using RGB leds, motor driver, microphone, LED matrix, buttons
  * Sample project for Calliope mini 1 and 2 using microphone, LED matrix, buttons, BLE. mini 2.0 needs the [DAPLink USB firmware](https://calliope.cc/faq/0253_calliopemini_if.hex). mini 2.1 can only be flashed by exporting the binary hex file (CTRL + ALT + S) and drag and drop.
  * Adafruit_GFX compatible LED Matrix driver on Timer 2
  * BLE Serial client device for talking to Adafruit Bluefruit Connect App & Adafruit IO (Based v. heavily on Sandeep Mistry's BLE Code!) (BLE only working on Calliope mini 1 & 2!)
  * Internal die temperature read (but its not very good)

A detailed guide for the usage of Adafruit's microbit library can be found here: https://learn.adafruit.com/use-micro-bit-with-arduino

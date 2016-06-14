## PIC18-Examples

This repository contains example codes for the PIC18 microcontrollers. These codes are meant to help you get started with basic features of the PIC18 microcontrollers.

### 1. Interfacing PIC18F46K22 with Arduino GSM/GPRS Shield

![Arduino GSM/GPRS Shield](https://raw.githubusercontent.com/usamamuneeb/PIC18-Examples/master/pic18-gsm/image.jpg "Arduino GSM/GPRS Shield")

Example folder: [Click Here](https://github.com/usamamuneeb/PIC18-Examples/tree/master/pic18-gsm)

#### What you build:

A device capable of sending SMS throug the GSM shield, takes input via the 4x4 keypad and provides a UI to the user via the LCD. You will compile the project using MikroC Pro for PIC.

#### Interfaces with:
1. 4x4 keypad
2. LCD Screen
3. Arduino GSM/GPS Shield

The [additional-documentation](https://github.com/usamamuneeb/PIC18-Examples/tree/master/pic18-gsm/additional-documentation) folder provides the datasheet for the GSM shield, as well as the SIM9000 chip embedded on it.

For connections to the GSM Shield, see [pinout.png](https://raw.githubusercontent.com/usamamuneeb/PIC18-Examples/master/pic18-gsm/pinout.jpg). You only need to connect TX, RX, 5V and GND.

For connections to the LCD screen and keypad, consult the Proteus ISIS project/or the `sbit` declarations at the program header.

#### Known issues:

1. TX and RX are marked incorrectly, try flipping them to see if it works.
2. Demo Limit (MikroC Pro for PIC). I have already commented out part of the code to keep it to the minimal that will compile. If you are using the full version, you can remove the comment outs.

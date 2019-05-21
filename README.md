# Remote Surgery System

This is a class project for University of Washington EE/CSE 474: Introduction to Embedded Systems with Dr. Peckol

The project was built by Doruk Arisoy, Richard Wang and Kristi Stefanovicz.

This project uses the Arduino MEGA, Arduino UNO boards and ESP8266 WIFI board. The UNO is designed to collect data from a patient (i.e. blood pressure, body temperature, pulse rate...) and send this data to the MEGA. MEGA has a TFT LCD display. After receiving the data, MEGA processes it and displays useful information on the TFT LCD display. The WIFI board is used to be able to get the data of the system from a remote device.

# TODO list:
MEGA:
- [x] Fix doubly linked list
- [x] Display mode on keypad (coordinates need to be fixed)
- [x] Respiration variables
- [x] Warning flashes / new warning stuff
- [x] remote peripheral communication
- [ ] add interupts

UNO:
- [ ] Raw respiration rate from function generator
- [ ] measure pressure with buttons
- [ ] mega interupt trigger

REMOTE:
- [x] implement website
- [x] implement communication with mega
- [x] test

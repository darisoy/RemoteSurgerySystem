# Remote Surgery System

This is a class project for University of Washington EE/CSE 474: Introduction to Embedded Systems with Dr. Peckol

The project was built by Doruk Arisoy, Richard Wang and Kristi Stefanovicz.

This project uses the Arduino MEGA, Arduino UNO boards and ESP8266 WIFI board. The UNO is designed to collect data from a patient (i.e. blood pressure, body temperature, pulse rate...) and send this data to the MEGA. MEGA has a TFT LCD display. After receiving the data, MEGA processes it and displays useful information on the TFT LCD display. The WIFI board is used to be able to get the data of the system from a remote device.

# TODO list:
MEGA:
- [x] EKG add to comms
- [x] EKG add to measure, compute, comms, remotecomms, warning, display, touch
- [x] add commands
- [x] remote comms
- [x] test

UNO:
- [x] FIX temp reading

REMOTE:
- [x] send commands
- [x] get data every 5 seconds
- [x] patient name, doc name, product name
- [x] display EKG

# Remote Surgery System

This is a class project for University of Washington EE/CSE 474: Introduction to Embedded Systems with Dr. Peckol

The project was built by Doruk Arisoy, Richard Wang and Kristi Stefanovicz.

This project uses the Arduino MEGA and Arduino UNO boards. The UNO is designed to collect data from a patient (i.e. blood pressure, body temperature, pulse rate...) and send this data to the MEGA. MEGA has a TFT LCD display. After receiving the data, MEGA processes it and displays useful information on the TFT LCD display.

# TODO list:
- [ ] Fix diastolic value generation (@rrwang97)
- [ ] figure out TouchScreen and going between two pages (@d1r1karsy)
- [ ] interrupt for scheduler, using doublylinked list
- [ ] buffers
- [ ] ADC for pulse and pulse rate computation
- [ ] warning/alarms (acknowledgements and UNO LEDs)

# Questions:
- how is TS supposed to check every 2 seconds when the task is only executed every 5 seconds
- when the user selects which data to be displayed, is that for menu or for annunciate screen?

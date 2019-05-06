# Remote Surgery System

This is a class project for University of Washington EE/CSE 474: Introduction to Embedded Systems with Dr. Peckol

The project was built by Doruk Arisoy, Richard Wang and Kristi Stefanovicz.

This project uses the Arduino MEGA and Arduino UNO boards. The UNO is designed to collect data from a patient (i.e. blood pressure, body temperature, pulse rate...) and send this data to the MEGA. MEGA has a TFT LCD display. After receiving the data, MEGA processes it and displays useful information on the TFT LCD display.

# TODO list:
- [x] Fix diastolic value generation
- [ ] Fix 5 seconds per task
- [ ] TouchScreen and going between screen (separate task)
- [ ] interrupt for scheduler, using doublylinked list
- [ ] global timer for scheduler
- [ ] buffers
- [ ] ADC for pulse and pulse rate computation
- [ ] warning/alarms (acknowledgements and UNO LEDs)

# Questions [SOLVED]:
- how is TS supposed to check every 2 seconds when the task is only executed every 5 seconds: ignore 5 second rule for this
- when the user selects which data to be displayed, is that only for menu or for annunciate screen as well? only for menu (design decision)
- pressure buffer is 16 long. do we need a new buffer structure? 0-7 sys, 8-15 dia
- amplify the pulse voltage in code
- LEDs on uno not necessary

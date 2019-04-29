//Peripheral Subsystem
#include "dataStructs.h"            //connect variables from dataStructs file
#include "Measure.h"                // connect the function to the header file

void setup() {                      //setup portion of the arduino code
    initialize();                   //call the initialize function
    Serial.begin(9600);             //initialize the serial with 9600 baud rate
    pinMode(13, INPUT);             //setup pin 13 to be an input
    pinMode(12, INPUT);             //setup pin 12 to be an input
    pinMode(11, INPUT);             //setup pin 11 to be an input
    pinMode(10, INPUT);             //setup pin 10 to be an input
}

void loop() {                       //code arduino constatly loops through
    measureFunction(MeasureData,    //pass in struct
                    pTempCount,     //pass in the pointer that points to temp count
                    pPulseCount,    //pass in the pointer that points to pulse count
                    pSysCount,      //pass in the pointer that points to systolic count
                    pDiaCount);     //pass in the pointer that points to diastolic count
}

void initialize() {                 //initializing the global variables
    temperatureRaw    = 75;         //set initial temperature to be 75
    systolicPressRaw  = 80;         //set initial systolic pressure to be 80
    diastolicPressRaw = 80;         //set initial diastolic pressure to be 80
    pulseRateRaw      = 50;         //set initial pulse rate to be 50
}

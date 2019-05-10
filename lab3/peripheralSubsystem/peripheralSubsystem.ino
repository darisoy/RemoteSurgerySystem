//Peripheral Subsystem
#include "dataStructs.h"            //connect variables from dataStructs file
#include "Measure.h"                // connect the function to the header file
#include <FreqMeasure.h>

void setup() {                      //setup portion of the arduino code
    initialize();                   //call the initialize function
    Serial.begin(9600);             //initialize the serial with 9600 baud rate
    pinMode(14, INPUT);             //setup pin 13 to be an input

    FreqMeasure.begin();

    *pSysCount=0;                         //initialize the pointer to the systolic counter
    *pDiaCount=0;                         //initialize the pointer to the diastolic counter
    *pDiastolicFunction=0;                //initialize the pointer to the diastolic function
    *pSystolicFunction=0;                 //initialize the pointer to the systolic function

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
    pinHigh = false;
}

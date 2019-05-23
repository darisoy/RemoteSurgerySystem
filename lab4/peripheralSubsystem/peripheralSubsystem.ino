//Peripheral Subsystem
#include "dataStructs.h"            //connect variables from dataStructs file
#include "Measure.h"                // connect the function to the header file
#include <FreqMeasure.h>
#define REQ 14                                              //set the keyword TEM_REQ to represent the number 13
#define RESP 2
#define BUTTON1 13
#define BUTTON2 10
#define APIN 15

void setup() {                      //setup portion of the arduino code
    initialize();                   //call the initialize function
    Serial.begin(9600);             //initialize the serial with 9600 baud rate
    pinMode(REQ, INPUT);             //setup pin 14 to be an input
    pinMode(RESP, INPUT);
    pinMode(BUTTON1, INPUT);
    pinMode(BUTTON2, INPUT);
    pinMode(APIN, INPUT);
    FreqMeasure.begin();            //setup the frequency measurement
}

void loop() {                       //code arduino constatly loops through
    measureFunction(MeasureData,    //pass in struct
                    &tempCount,     //pass in the pointer that points to temp count
                    &pulseCount,    //pass in the pointer that points to pulse count
                    &sysCount,      //pass in the pointer that points to systolic count
                    &diaCount);     //pass in the pointer that points to diastolic count
}

void initialize() {                 //initializing the global variables
    temperatureRaw    = 75;         //set initial temperature to be 75
    systolicPressRaw  = 80;         //set initial systolic pressure to be 80
    diastolicPressRaw = 80;         //set initial diastolic pressure to be 80
    pulseRateRaw      = 50;         //set initial pulse rate to be 50

    sysCount=0;                     //initialize the pointer to the systolic counter
    diaCount=0;                     //initialize the pointer to the diastolic counter
    tempCount = 0;                  //initialize the pointer to the temperature counter
    pulseCount = 0;                 //initialize the pointer to the diastolic counter
    *pDiastolicFunction=0;          //initialize the pointer to the diastolic function
    *pSystolicFunction=0;           //initialize the pointer to the systolic function

    pinHighPS = false;              //set the inital state for pin mode
    pinHighNS = false;              //set the inital state for pin mode

    pulseSum = 0;
    pulseCount = 0;


    respLastState = false;
    respCount = 0;
    respPrevCount = millis();
}

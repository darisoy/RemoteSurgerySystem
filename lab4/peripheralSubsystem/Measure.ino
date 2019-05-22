#include "Measure.h"                                        //import the header of this function
#include "dataStructs.h"                                    //import the variables
#include <stdio.h>                                          //import necessary header files
#include <stdbool.h>                                        //import necessary header files
#include <stddef.h>                                         //import necessary header files
#define REQ 14                                              //set the keyword TEM_REQ to represent the number 13
#define RESP 2

void measureFunction(struct controlMeasureData measureData,
                     int* pTempCount,
                     int* pPulseCount,
                     int* pSysCount,
                     int* pDiaCount) {
    measureData.pTemperatureRaw    = &temperatureRaw;       //assign raw temp's address to temp pointer from stuct
    measureData.pSystolicPressRaw  = &systolicPressRaw;     //assign raw sys's address to sys pointer from stuct
    measureData.pDiastolicPressRaw = &diastolicPressRaw;    //assign raw dia's address to dia pointer from stuct
    measureData.pPulseRateRaw      = &pulseRateRaw;         //assign raw pulse's address to pulse pointer from stuct
    measureData.pRespRaw           = &respRaw;

    if (!pinHighPS && (digitalRead(REQ) == HIGH)) {         //check if the request pin turned high
        pinHighNS = true;                                   //if so, make the current state true
    } else if (pinHighPS && (digitalRead(REQ) == HIGH)) {   //if request pin is true and it has been true
        pinHighNS = true;                                   // keep the current state true
    } else {                                                //in any other case
      pinHighNS = false;                                    //make current case false
    }

    if (digitalRead(BUTTON1) == HIGH && !b1HighPS){
      b1HighNS = true;
    } else if (b1HighPS && digitalRead(BUTTON1) == HIGH){
      b1HighNS = true;
    } else {
      b1HighNS = false;
    }

    if (!b1HighPS && b1HighNS){
      bloodPressureRawData();
    }

    if (!pinHighPS && pinHighNS) {                          //if request pin has turned high after being low, then execute
        temperatureRawData(pTempCount);                     //call the temperatureRawData function to generate temp data
        Serial.print("VT");                                 //print "VT" on the serial
        if (*measureData.pTemperatureRaw < 10) {            //if value for the raw temp. pointer is less than 10
            Serial.print("00");                             //print "00" on the serial
        } else if (*measureData.pTemperatureRaw < 100) {    //if value for the raw temp. pointer is less than 100
            Serial.print("0");                              //print "0" on the serial
        }
        Serial.print(*measureData.pTemperatureRaw);         //print the value for the raw temp. pointer on the serial

        bloodPressureRawData();
        Serial.print("S");                                  //print "VS" on the serial
        if (*measureData.pSystolicPressRaw < 10) {          //if value for the raw sys. pointer is less than 10
            Serial.print("00");                             //print "00" on the serial
        } else if (*measureData.pSystolicPressRaw < 100) {  //if value for the raw sys. pointer is less than 100
            Serial.print("0");                              //print "0" on the serial
        }
        Serial.print(*measureData.pSystolicPressRaw);       //print the value for the raw sys. pointer on the serial

        Serial.print("D");                                  //print "VD" on the serial
        if (*measureData.pDiastolicPressRaw < 10) {         //if value for the raw dia. pointer is less than 10
            Serial.print("00");                             //print "00" on the serial
        } else if (*measureData.pDiastolicPressRaw < 100) { //if value for the raw dia. pointer is less than 100
            Serial.print("0");                              //print "0" on the serial
        }
        Serial.print(*measureData.pDiastolicPressRaw);      //print the value for the raw dia. pointer on the serial

        pulseRateRawData();                      //call the pulseRateRawData function to generate pulse data
        Serial.print("P");                                  //print "VP" on the serial
        if (*measureData.pPulseRateRaw < 10) {              //if value for the raw pulse. pointer is less than 10
            Serial.print("00");                             //print "00" on the serial
        } else if (*measureData.pPulseRateRaw < 100) {      //if value for the raw pulse. pointer is less than 100
            Serial.print("0");                              //print "0" on the serial
        }
        Serial.print(*measureData.pPulseRateRaw);         //print the value for the raw pulse. pointer on the serial

        respRawData();                      //call the pulseRateRawData function to generate pulse data
        Serial.print("R");                                  //print "VP" on the serial
        if (*measureData.pRespRaw < 10) {              //if value for the raw pulse. pointer is less than 10
            Serial.print("00");                             //print "00" on the serial
        } else if (*measureData.pRespRaw < 100) {      //if value for the raw pulse. pointer is less than 100
            Serial.print("0");                              //print "0" on the serial
        }
        Serial.println(*measureData.pRespRaw);         //print the value for the raw pulse. pointer on the serial
    }
    pinHighPS = pinHighNS;
    b1HighPS = b1HighNS;
    b2HighPS = b2HighNS;
    pulseRateRawData();
    respRawData();
}

void temperatureRawData(int* pCount) {                      //simulates temperature data, takes an int pointer as input
    if (tempBool == 1){                                     //if temperature boolean is 1
        if (*pCount % 2 == 0) {                             //if counter is even
            temperatureRaw += 2;                            //incremenet temp by 2
        } else {                                            //if counter is odd
            temperatureRaw--;                               //decrement temp by 1
        }
    } else {                                                //if temperature boolean is 0
        if (*pCount % 2 == 0){                              //if counter is even
            temperatureRaw -= 2;                            //decrement temp by 2
        } else {                                            //if counter is odd
            temperatureRaw++;                               //incremenet temp by 1
        }
    }
    if (temperatureRaw < 15) {                              //if temperature is less than 15
        tempBool = 1;                                       //set temperature boolean to 1
    } else if (temperatureRaw > 50) {                       //if temperature is greater than 50
        tempBool = 0;                                       //set temperature boolean to 0
    }
    (*pCount)++;                                            //incremenet the value of the counter pointer by 1
}

void bloodPressureRawData(){
  if (digitalRead(BUTTON2) == HIGH){
      systolicPressRaw += systolicPressRaw * 0.1;
      diastolicPressRaw += diastolicPressRaw * 0.1;
  } else {
      systolicPressRaw -= systolicPressRaw * 0.1;
      diastolicPressRaw -= diastolicPressRaw * 0.1;
  }
}

void pulseRateRawData() {                        //simulates diastolic press. data, takes an int pointer as input
    if (FreqMeasure.available()) {                          //execute if the frequency measurement is available
        pulseSum = pulseSum + FreqMeasure.read();                     //add the frequency measurement to the running sum count
        pulseCount = pulseCount + 1;                                  //incremenet the count by one
        if (pulseCount > 30) {                                   //if counter is greater than 30
            pulseRateRaw = (int)
            FreqMeasure.countToFrequency(pulseSum / pulseCount);      //average the frequency from past 30 counts
            pulseSum = 0;                                        //reset veriable to 0 for next frequency calculaiton
            pulseCount = 0;                                      //reset veriable to 0 for next frequency calculaiton
        }
    }
}

void respRawData() {
//    respInputState = digitalRead(RESP);
//        Serial.println("respCount | respInputState | respLastState | respRaw\n");
//        Serial.print(respCount);
//        Serial.print("   ");
//        Serial.print(respInputState);
//        Serial.print("   ");
//        Serial.print(respLastState);
//        Serial.println("   ");
//        Serial.print(respRaw);
//        Serial.println("   ");
//
//    if (respInputState != respLastState) {
//        respCount++;
//        respLastState = respInputState;
//
//    }
//
//
//    // runs every half second, count is equal to Hz
//    if (millis() - respPrevCount >= 500) {
//        respPrevCount += 500;
//        respRaw = respCount;
//        respCount = 0;
//    }
// Use the rising edge of an interrupt to increment count.
// Use first interrupt to mark time.
// Every time reading is requested,
// report count/(current time - marked time),
// then reset all.

//attachInterrupt(digitalPinToInterrupt(RESP), count)

}

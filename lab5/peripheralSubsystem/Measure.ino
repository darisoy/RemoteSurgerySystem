#include "Measure.h"                                        //import the header of this function
#include "dataStructs.h"                                    //import the variables
#include <stdio.h>                                          //import necessary header files
#include <stdbool.h>                                        //import necessary header files
#include <stddef.h>                                         //import necessary header files

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
    measureData.pFrequency         = &frequency;

    if (!pinHighPS && (digitalRead(MEGAREQ) == HIGH)) {         //check if the request pin turned high
        pinHighNS = true;                                   //if so, make the current state true
    } else if (pinHighPS && (digitalRead(MEGAREQ) == HIGH)) {   //if request pin is true and it has been true
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

    getFrequency();

    if (digitalRead(MEGAACK) == HIGH) {
        megaAckowledge = true;
    }

    if (!pinHighPS && pinHighNS && megaAckowledge) {                          //if request pin has turned high after being low, then execute
        temperatureRawData(pTempCount);                     //call the temperatureRawData function to generate temp data
        Serial.print("VT");                                 //print "VT" on the serial
        if (*measureData.pTemperatureRaw < 10) {            //if value for the raw temp. pointer is less than 10
            Serial.print("00");                             //print "00" on the serial
        } else if (*measureData.pTemperatureRaw < 100) {    //if value for the raw temp. pointer is less than 100
            Serial.print("0");                              //print "0" on the serial
        }
        Serial.print(*measureData.pTemperatureRaw);         //print the value for the raw temp. pointer on the serial

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
        Serial.print(*measureData.pRespRaw);         //print the value for the raw pulse. pointer on the serial

        EKGRawData();                      //call the pulseRateRawData function to generate pulse data
        frequency = EKGProcessing(void* EKGData);
        Serial.print("F");                                  //print "VP" on the serial
        if (*measureData.pFrequency < 10) {              //if value for the raw pulse. pointer is less than 10
            Serial.print("000");                             //print "00" on the serial
        } else if (*measureData.pFrequency < 100) {      //if value for the raw pulse. pointer is less than 100
            Serial.print("00");                              //print "0" on the serial
        } else if (*measureData.pFrequency < 1000) {
            Serial.print("0");
        }
        Serial.println(*measureData.pFrequency);

        megaAckowledge = false;
    }
    pinHighPS = pinHighNS;
    b1HighPS = b1HighNS;
    b2HighPS = b2HighNS;
    pulseRateRawData();
    if (pulseRateRaw)
    respRawData();
}

void temperatureRawData(int* pCount) {                      //simulates temperature data, takes an int pointer as input
    double tempTemp  = (analogRead(TEMP) / 1023) * 200;
    temperatureRaw = (int) tempTemp;
}

void getFrequency() {
    if (FreqMeasure.available()) {                          //execute if the frequency measurement is available
        pulseSum = pulseSum + FreqMeasure.read();                     //add the frequency measurement to the running sum count
        pulseCount = pulseCount + 1;                                  //incremenet the count by one
        if (pulseCount > 30) {                                   //if counter is greater than 30
            frequency = (int) FreqMeasure.countToFrequency(pulseSum / pulseCount);      //average the frequency from past 30 counts
            pulseSum = 0;                                        //reset veriable to 0 for next frequency calculaiton
            pulseCount = 0;                                      //reset veriable to 0 for next frequency calculaiton
        }
    }
}

void bloodPressureRawData() {
    if (digitalRead(BUTTON2) == HIGH) {
        systolicCount++;
        if (systolicCount >= 10){
            systolicPressRaw = frequency;
            systolicCount = 0;
        }
    } else {
        diastolicCount++;
        if (diastolicCount >= 10){
            diastolicPressRaw = frequency;
            diastolicCount = 0;
        }
    }
}

void pulseRateRawData() {                        //simulates diastolic press. data, takes an int pointer as input
    pulseRateRaw = frequency;
}

void respRawData() {
    respRaw = frequency / 3;
}

void EKGRawData(void* data) {
  struct controlEKGData* EKGData = (struct controlEKGData*) data;
  EKGData->EKGRealDataPtr = EKGRealData;
  EKGData->EKGImagDataPtr = EKGImagData;
  EKGData->samplingFrequencyPtr = samplingFreq;
  //double sampleFrequency = 2 * frequency;
  //decide what frequency to limit our EKG data
  int startTime = millis();
  for (int i = 0; i < 256; i++){
    *EKGData->EKGRealDataPtr[i] = analogRead(EKGPIN) / 1023 * 3.3 - 2.5;
    *EKGData->EKGImagDataPtr[i] = 0;
  }
  int time = millis() - startTime;
  *EKGData->samplingFrequencyPtr = 256 / time;
}

int EKGProcessing(void* data) {
  //double sampleFrequency = 2 * frequency;
  struct controlEKGData* EKGData = (struct controlEKGData*) data;
  EKGData->EKGRealDataPtr = EKGRealData;
  EKGData->EKGImagDataPtr = EKGImagData;
  EKGData->samplingFrequencyPtr = samplingFreq;
  int m_index = opfft(EKGData->EKGRealDataPtr, EKG->EKGImagDataPtr);
  int m = 8;
  int fftOutput = *EKGData->samplingFrequencyPtr * m_index / pow(2, m);
  return fftOutput;
}

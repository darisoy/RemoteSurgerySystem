//System Control Subsystem

#include  "dataStructs.h"

#include "Measure.h"



#define TEM_REQ 13

#define SYS_REQ 12

#define DIA_REQ 11

#define PUL_REQ 10

// #define BAT_REQ  9



//variables for the measurement function

void* measureDataStruct;

int tempCount;

int pulseCount;

int sysCount;

int diaCount;

int tempBool;

int pulseBool;

int* pDiastolicFunction;

int* pSystolicFunction;



char dataTransfered[5];



void setup() {

    initialize();

    Serial.begin(9600);

    pinMode(13, INPUT);

    pinMode(12, INPUT);

    pinMode(11, INPUT);

    pinMode(10, INPUT);

    //pinMode(9, INPUT);

}



void loop() {
    //measureFunction((void*) measureDataStruct);
    communications();
}



void initialize(){

    //initializing the global variables

    temperatureRaw = 75;

    systolicPressRaw = 80;

    diastolicPressRaw = 80;

    pulseRateRaw = 50;

    batteryState = 200;

    tempCorrected = NULL;

    systolicPressCorrected = NULL;

    diastolicPressCorrected = NULL;

    pulseRateCorrected = NULL;

    batteryState = 200;

    bpOutOfRange = 0;

    tempOutOfRange = 0;

    pulseOutOfRange = 0;

}



int pTempBool = 0;

void temperatureRawData(int* pCount){

    if (pTempBool == 1){

        if (*pCount % 2 == 0){

          temperatureRaw += 2;

        }else {

          temperatureRaw--;

        }

    }else {

        if (*pCount % 2 == 0){

          temperatureRaw -= 2;

        }else{

          temperatureRaw++;

        }

    }

    if (temperatureRaw < 15){

        pTempBool = 1;

    }else if (temperatureRaw > 50){

        pTempBool = 0;

    }

    (*pCount)++;

}



void systolicPressRawData(int* pCount){

  if (systolicPressRaw <= 100){

    if (*pCount % 2 == 0){

      systolicPressRaw += 3;

    }else {

      systolicPressRaw--;

    }

  }else {

    *pSystolicFunction = 1;

    if (*pDiastolicFunction){

      systolicPressRaw = 0;

      *pCount = -1;

    }

  }

  (*pCount)++;

}



void diastolicPressRawData(int* pCount){
  if (diastolicPressRaw >= 40){

    if (*pCount % 2 == 0){

      diastolicPressRaw -= 2;

    }else {

      diastolicPressRaw++;

    }

  }else {

    *pDiastolicFunction = 1;

    if (*pSystolicFunction){

      diastolicPressRaw = 0;

      *pCount = -1;

    }
  }
  (*pCount)++;

}



int pPulseBool = 0;

void pulseRateRawData(int* pCount){

  if (pPulseBool == 1){

    if (*pCount % 2 == 0){

      pulseRateRaw++;

    }else {

      pulseRateRaw -= 3;

    }

  }else {

    if (*pCount % 2 == 0){

      pulseRateRaw--;

    }else {

      pulseRateRaw +=3;

    }

  }

  if (pulseRateRaw > 40){

    pPulseBool = 1;

  }

  if (pulseRateRaw < 15){

    pPulseBool = 0;

  }

  (*pCount)++;

}

 void communications() {
    int * pTempCount = &tempCount;
    int * pSysCount = &sysCount;
    int * pDiaCount = &diaCount;
    int * pPulseCount = &pulseCount;
     if (digitalRead(TEM_REQ) == HIGH) {
       temperatureRawData(pTempCount);
       Serial.print("VT");
       if (temperatureRaw < 10) {
         Serial.print("00");
       } else if (temperatureRaw < 100) {
         Serial.print("0");
       }
       Serial.println(temperatureRaw);
     }
     while (digitalRead(TEM_REQ) == HIGH) {
      delay(100);
     }

     if (digitalRead(SYS_REQ) == HIGH) {
       systolicPressRawData(pSysCount);
       Serial.print("VS");
       if (systolicPressRaw < 10) {
         Serial.print("00");
       } else if (systolicPressRaw < 100) {
         Serial.print("0");
       }
       Serial.println(systolicPressRaw);
     }
     while (digitalRead(SYS_REQ) == HIGH) {
      delay(100);
     }

     if (digitalRead(DIA_REQ) == HIGH) {
       diastolicPressRawData(pDiaCount);
       Serial.print("VD");
       if (diastolicPressRaw < 10) {
         Serial.print("00");
       } else if (diastolicPressRaw < 100) {
         Serial.print("0");
       }
       Serial.println(diastolicPressRaw);
     }
     while (digitalRead(DIA_REQ) == HIGH) {
      delay(100);
     }

     if (digitalRead(PUL_REQ) == HIGH) {
       pulseRateRawData(pPulseCount);
       Serial.print("VP");
       if (pulseRateRaw < 10) {
         Serial.print("00");
       } else if (pulseRateRaw < 100) {
         Serial.print("0");
       }
       Serial.println(pulseRateRaw);
     }
     while (digitalRead(PUL_REQ) == HIGH) {
      delay(100);
     }
 }

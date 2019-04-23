//System Control Subsystem
#include  "dataStructs.h"
#include "Measure.h"

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
}

void loop() {
    measureFunction((void*) measureDataStruct);
    communications();
}

void initialize(){
    //initializing the global variables
    temperatureRaw = 75;
    systolicPressRaw = 80;
    diastolicPressRaw = 80;
    pulseRateRaw = 50;
    tempCorrected = NULL;
    systolicPressCorrected = NULL;
    diastolicPressCorrected = NULL;
    pulseRateCorrected = NULL;
    batteryState = 200;
    bpOutOfRange = 0;
    tempOutOfRange = 0;
    pulseOutOfRange = 0;
}

void measureFunction(void* measureDataStruct){
    int * pTempCount = &tempCount;
    int * pSysCount = &sysCount;
    int * pDiaCount = &diaCount;
    int * pPulseCount = &pulseCount;
    temperatureRawData(pTempCount);
    systolicPressRawData(pSysCount);
    diastolicPressRawData(pDiaCount);
    pulseRateRawData(pPulseCount);
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
    Serial.readBytes(dataTransfered, 5);
    if (dataTransfered[0] == 'T' && dataTransfered[1] == 'R') {
      Serial.print("TV");
      if (temperatureRaw < 10) {
        Serial.print("00");
      } else if (temperatureRaw < 100) {
        Serial.print("0");
      }
      Serial.println(temperatureRaw);
    }

    if (dataTransfered[0] == 'S' && dataTransfered[1] == 'R') {
      Serial.print("SV");
      if (systolicPressRaw < 10) {
        Serial.print("00");
      } else if (systolicPressRaw < 100) {
        Serial.print("0");
      }
      Serial.println(systolicPressRaw);
    }

    if (dataTransfered[0] == 'D' && dataTransfered[1] == 'R') {
      Serial.print("DV");
      if (diastolicPressRaw < 10) {
        Serial.print("00");
      } else if (diastolicPressRaw < 100) {
        Serial.print("0");
      }
      Serial.println(diastolicPressRaw);
    }

    if (dataTransfered[0] == 'P' && dataTransfered[1] == 'R') {
      Serial.print("PV");
      if (pulseRateRaw < 10) {
        Serial.print("00");
      } else if (pulseRateRaw < 100) {
        Serial.print("0");
      }
      Serial.println(pulseRateRaw);
    }

    if (dataTransfered[0] == 'D' && dataTransfered[1] == 'R') {
      Serial.print("BV");
    //  if (temperatureRaw < 10) {
    //    Serial.print("00");
    //  } else if (temperatureRaw < 100) {
    //    Serial.print("0");
    //  }
    //  Serial.print(temperatureRaw);
      Serial.println("100");
    }
}

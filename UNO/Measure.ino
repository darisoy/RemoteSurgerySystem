#include "Measure.h"
#include "dataStructs.h"
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#define TEM_REQ 13
#define SYS_REQ 12
#define DIA_REQ 11
#define PUL_REQ 10

void measureFunction(struct controlMeasureData measureData, int* pTempCount, int* pPulseCount, int* pSysCount, int* pDiaCount) {
    measureData.pTemperatureRaw = &temperatureRaw;
    measureData.pSystolicPressRaw = &systolicPressRaw;
    measureData.pDiastolicPressRaw = &diastolicPressRaw;
    measureData.pPulseRateRaw = &pulseRateRaw;

    if (digitalRead(TEM_REQ) == HIGH) {
       temperatureRawData(pTempCount);
       Serial.print("VT");
       if (*measureData.pTemperatureRaw < 10) {
         Serial.print("00");
       } else if (*measureData.pTemperatureRaw < 100) {
         Serial.print("0");
       }
       Serial.println(*measureData.pTemperatureRaw);
     }
     while (digitalRead(TEM_REQ) == HIGH) {
      delay(100);
     }

     if (digitalRead(SYS_REQ) == HIGH) {
       systolicPressRawData(pSysCount);
       Serial.print("VS");
       if (*measureData.pSystolicPressRaw < 10) {
         Serial.print("00");
       } else if (*measureData.pSystolicPressRaw < 100) {
         Serial.print("0");
       }
       Serial.println(*measureData.pSystolicPressRaw);
     }
     while (digitalRead(SYS_REQ) == HIGH) {
      delay(100);
     }

     if (digitalRead(DIA_REQ) == HIGH) {
       diastolicPressRawData(pDiaCount);
       Serial.print("VD");
       if (*measureData.pDiastolicPressRaw < 10) {
         Serial.print("00");
       } else if (*measureData.pDiastolicPressRaw < 100) {
         Serial.print("0");
       }
       Serial.println(*measureData.pDiastolicPressRaw);
     }
     while (digitalRead(DIA_REQ) == HIGH) {
      delay(100);
     }

     if (digitalRead(PUL_REQ) == HIGH) {
       pulseRateRawData(pPulseCount);
       Serial.print("VP");
       if (*measureData.pPulseRateRaw < 10) {
         Serial.print("00");
       } else if (*measureData.pPulseRateRaw < 100) {
         Serial.print("0");
       }
       Serial.println(*measureData.pPulseRateRaw);
     }
     while (digitalRead(PUL_REQ) == HIGH) {
      delay(100);
     }
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

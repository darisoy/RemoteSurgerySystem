#include "Measure.h"
#include "dataStructs.h"
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

#define TEM_REQ 13
#define SYS_REQ 12
#define DIA_REQ 11
#define PUL_REQ 10
// #define BAT_REQ  9

void measureFunction(void* measureDataStruct){
    struct controlMeasureData *mData = (struct controlMeasureData*) measureDataStruct;
    mData->pTemperatureRaw = &temperatureRaw;
    mData->pSystolicPressRaw = &systolicPressRaw;
    mData->pDiastolicPressRaw = &diastolicPressRaw;
    mData->pPulseRateRaw = &pulseRateRaw;

    if (digitalRead(TEM_REQ) == HIGH) {
        Serial.print("TV");
        if (*pTemperatureRaw < 10) {
            Serial.print("00");
        } else if (*pTemperatureRaw < 100) {
            Serial.print("0");
        }
        Serial.println(*pTemperatureRaw);
    }

    if (digitalRead(SYS_REQ) == HIGH) {
        Serial.print("SV");
        if (*pSystolicPressRaw < 10) {
            Serial.print("00");
        } else if (*pSystolicPressRaw < 100) {
            Serial.print("0");
        }
        Serial.println(*pSystolicPressRaw);
    }

    if (digitalRead(DIA_REQ) == HIGH) {
        Serial.print("DV");
        if (*pDiastolicPressRaw < 10) {
            Serial.print("00");
        } else if (*pDiastolicPressRaw < 100) {
            Serial.print("0");
        }
        Serial.println(*pDiastolicPressRaw);
    }

    if (digitalRead(PUL_REQ) == HIGH) {
        Serial.print("PV");
        if (*pPulseRateRaw < 10) {
            Serial.print("00");
        } else if (*pPulseRateRaw < 100) {
            Serial.print("0");
        }
        Serial.println(*pPulseRateRaw);
    }

    // if (digitalRead(BAT_REQ) == HIGH) {
    //     Serial.print("BV");
    //     if (batteryState < 10) {
    //        Serial.print("00");
    //     } else if (batteryState < 100) {
    //        Serial.print("0");
    //     }
    //     Serial.print(batteryState);
    //     Serial.println("100");
    // }
}

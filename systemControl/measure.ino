#include "Measure.h"
#include "dataStructs.h"
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

void measureFunction(void* measureDataStruct) {
 struct controlMeasureData *mData = (struct controlMeasureData*) measureDataStruct;
 mData->pTemperatureRaw = &temperatureRaw;
 mData->pSystolicPressRaw = &systolicPressRaw;
 mData->pDiastolicPressRaw = &diastolicPressRaw;
 mData->pPulseRateRaw = &pulseRateRaw;

  if (Serial1.read() == 'V') {
        Serial1.readBytes(dataTransfered, 4);
        Serial.print(dataTransfered[0]);
        Serial.print(dataTransfered[1]);
        Serial.print(dataTransfered[2]);
        Serial.println(dataTransfered[3]);
        unsigned int digit1 = dataTransfered[1] - '0';
        unsigned int digit2 = dataTransfered[2] - '0';
        unsigned int digit3 = dataTransfered[3] - '0';
        if (digit1 < 10 && digit2 < 10 && digit3 < 10) {
            if (dataTransfered[0] == 'T') {
                *mData->pTemperatureRaw = (digit1 * 100) + (digit2 * 10) + (digit3 * 1);
            }
            if (dataTransfered[0] == 'S') {
                *mData->pSystolicPressRaw = (digit1 * 100) + (digit2 * 10) + (digit3 * 1);
            }
            if (dataTransfered[0] == 'D') {
                *mData->pDiastolicPressRaw = (digit1 * 100) + (digit2 * 10) + (digit3 * 1);
            }
            if (dataTransfered[0] == 'P') {
                *mData->pPulseRateRaw = (digit1 * 100) + (digit2 * 10) + (digit3 * 1);
            }
        }
    }
}

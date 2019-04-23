#include "Display.h"
#include "dataStructs.h"
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

void displayFunction(void* displayDataStruct){
  struct controlDisplayData *dData = (struct controlDisplayData*) displayDataStruct;
  dData->pTempCorrected = &tempCorrected;                        
  dData->pSystolicPressCorrected = &systolicPressCorrected;
  dData->pDiastolicPressCorrected = &diastolicPressCorrected;
  dData->pPulseRateCorrected = &pulseRateCorrected;
  dData->pBatteryState = &batteryState;
}

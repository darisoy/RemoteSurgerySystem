#include "Warning.h"
#include "dataStructs.h"
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

void alarmFunction(void* warningStruct){
  struct controlWarningAlarmData *wData = (struct controlWarningAlarmData*) warningStruct;
  wData->pTempCorrected = &tempCorrected;
  wData->pSystolicPressCorrected = &systolicPressCorrected;
  wData->pDiastolicPressCorrected = &diastolicPressCorrected;
  wData->pPulseRateCorrected = &pulseRateCorrected;
  wData->pBatteryState = &batteryState;

  tempGoodBool = (*wData->pTempCorrected <= 37.8) && (*wData->pTempCorrected >= 36.1);
  sysGoodBool = (*wData->pSystolicPressCorrected == 120);
  diaGoodBool = (*wData->pDiastolicPressCorrected == 80);
  prGoodBool = (*wData->pPulseRateCorrected > 60.0) && (*wData->pPulseRateCorrected < 100.0);
  batteryGoodBool = (*wData->pBatteryState >= 40);
}

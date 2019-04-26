#include "Compute.h"
#include "dataStructs.h"
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

void computeFunction(void* computeDataStruct){
  struct controlComputeData *cData = (struct controlComputeData*) computeDataStruct;
  cData->pTemperatureRaw = &temperatureRaw;
  cData->pSystolicPressRaw = &systolicPressRaw;
  cData->pDiastolicPressRaw = &diastolicPressRaw;
  cData->pPulseRateRaw = &pulseRateRaw;
  cData->pTempCorrected = &tempCorrected;                        //pointer to the first element in the array
  cData->pSystolicPressCorrected = &systolicPressCorrected;
  cData->pDiastolicPressCorrected = &diastolicPressCorrected;
  cData->pPulseRateCorrected = &pulseRateCorrected;

  *cData->pTempCorrected = 5 + (0.75 * (*cData->pTemperatureRaw));
  *cData->pSystolicPressCorrected = 9 + (2 * (*cData->pSystolicPressRaw));
  *cData->pDiastolicPressCorrected = 6 + (1.5 * (*cData->pDiastolicPressRaw));
  *cData->pPulseRateCorrected = 8 + (3 * (*cData->pPulseRateRaw));
}

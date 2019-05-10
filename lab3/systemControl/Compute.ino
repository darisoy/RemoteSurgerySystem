#include "Compute.h"                                                                 //import the header of this function
#include "dataStructs.h"                                                             //import the variables
#include <stdio.h>                                                                   //import necessary header files
#include <stdbool.h>                                                                 //import necessary header files
#include <stddef.h>                                                                  //import necessary header files

void computeFunction(void* computeDataStruct){                                       //function that computes data, takes compute struct as input
  struct controlComputeData *cData = (struct controlComputeData*) computeDataStruct; //deference the compute struct

  *cData->pTempCorrected           = 5 + (0.75 * (*cData->pTemperatureRaw));         //convert raw temp and point pTempCorrected pointer to it
  *cData->pSystolicPressCorrected  = 9 + (2    * (*cData->pSystolicPressRaw));       //convert raw sys and point pSystolicPressCorrected pointer to it
  *cData->pDiastolicPressCorrected = 6 + (1.5  * (*cData->pDiastolicPressRaw));      //convert raw dia and point pDiastolicPressCorrected pointer to it
  *cData->pPulseRateCorrected      = 8 + (3    * (*cData->pPulseRateRaw));           //convert raw pulse and point pPulseRateCorrected pointer to it
}

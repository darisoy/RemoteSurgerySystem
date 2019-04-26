#include "Compute.h"                                                                 //import the header of this function
#include "dataStructs.h"                                                             //import the variables
#include <stdio.h>                                                                   //import necessary header files
#include <stdbool.h>                                                                 //import necessary header files
#include <stddef.h>                                                                  //import necessary header files

void computeFunction(void* computeDataStruct){                                       //function that computes data, takes compute struct as input
  struct controlComputeData *cData = (struct controlComputeData*) computeDataStruct; //deference the compute struct
  cData->pTemperatureRaw            = &temperatureRaw;                               //assign raw temp's address to raw temp pointer from compute struct
  cData->pSystolicPressRaw          = &systolicPressRaw;                             //assign raw sys's address to raw sys pointer from compute struct
  cData->pDiastolicPressRaw         = &diastolicPressRaw;                            //assign raw dia's address to raw dia pointer from compute struct
  cData->pPulseRateRaw              = &pulseRateRaw;                                 //assign raw pulse's address to raw pulse pointer from compute struct
  cData->pTempCorrected             = &tempCorrected;                                //assign corrected temp's address to corrected temp pointer from compute struct
  cData->pSystolicPressCorrected    = &systolicPressCorrected;                       //assign corrected sys's address to corrected sys pointer from compute struct
  cData->pDiastolicPressCorrected   = &diastolicPressCorrected;                      //assign corrected dia's address to corrected dia pointer from compute struct
  cData->pPulseRateCorrected        = &pulseRateCorrected;                           //assign corrected pulse's address to corrected pulse pointer from compute struct

  *cData->pTempCorrected           = 5 + (0.75 * (*cData->pTemperatureRaw));         //convert raw temp and point pTempCorrected pointer to it
  *cData->pSystolicPressCorrected  = 9 + (2    * (*cData->pSystolicPressRaw));       //convert raw sys and point pSystolicPressCorrected pointer to it
  *cData->pDiastolicPressCorrected = 6 + (1.5  * (*cData->pDiastolicPressRaw));      //convert raw dia and point pDiastolicPressCorrected pointer to it
  *cData->pPulseRateCorrected      = 8 + (3    * (*cData->pPulseRateRaw));           //convert raw pulse and point pPulseRateCorrected pointer to it
}

#include "Compute.h"                                                                 //import the header of this function
#include "dataStructs.h"                                                             //import the variables
#include <stdio.h>                                                                   //import necessary header files
#include <stdbool.h>                                                                 //import necessary header files
#include <stddef.h>                                                                  //import necessary header files

void computeFunction(void* computeDataStruct){                                       //function that computes data, takes compute struct as input
  struct controlComputeData *cData = (struct controlComputeData*) computeDataStruct; //deference the compute struct
  cData->pTemperatureRawBuf         = &temperatureRawBuffer;                               //assign raw temp's address to raw temp pointer from compute struct
  cData->pBloodPressRawBuf->frontList          = &systolicRawBuffer;
  cData->pBloodPressRawBuf->backList           = &diastolicRawBuffer;
  cData->pPulseRateRawBuf              = &pulseRateRawBuffer;                                 //assign raw pulse's address to raw pulse pointer from compute struct
  cData->pTempCorrectedBuf             = &tempCorrectedBuffer;                                //assign corrected temp's address to corrected temp pointer from compute struct
  cData->pBloodPressCorrectedBuf->frontList    = &systolicCorrectedBuffer;
  cData->pBloodPressCorrectedBuf->backList      = &diastolicCorrectedBuffer;
  cData->pPulseRateCorrectedBuf        = &pulseRateCorrectedBuffer;                           //assign corrected pulse's address to corrected pulse pointer from compute struct

  BufferWrite(cData->pTempCorrectedBuf, 5 + (0.75 * (BufferRead(cData->pTemperatureRaw))));         //convert raw temp and point pTempCorrected pointer to it
  BufferWrite(cData->pBlodPressCorrectedBuf->frontList, 9 + (2    * (BufferRead(cData->pBloodPressRawBuf.frontList)));       //convert raw sys and point pSystolicPressCorrected pointer to it
  BufferWrite(cData->pBloodPressCorrectedBuf->backList, 6 + (1.5  * (BufferRead(cData->pBloodPressRawBuf.endList)));      //convert raw dia and point pDiastolicPressCorrected pointer to it
  BufferWrite(cData->pPulseRateCorrectedBuf, 8 + (3    * (BufferRead(cData->pPulseRateRaw))));           //convert raw pulse and point pPulseRateCorrected pointer to it
}

#include "Compute.h"                                                                 //import the header of this function
#include "dataStructs.h"                                                             //import the variables
#include <stdio.h>                                                                   //import necessary header files
#include <stdbool.h>                                                                 //import necessary header files
#include <stddef.h>                                                                  //import necessary header files

void computeFunction(void* computeDataStruct){                                         //function that computes data, takes compute struct as input
    struct controlComputeData *cData = (struct controlComputeData*) computeDataStruct; //deference the compute struct
    cData->pTemperatureRaw            = &tempRawData;                               //assign raw temp's address to raw temp pointer from compute struct
    cData->pSystolicPressRaw          = &sysRawData;                             //assign raw sys's address to raw sys pointer from compute struct
    cData->pDiastolicPressRaw         = &diaRawData;                            //assign raw dia's address to raw dia pointer from compute struct
    cData->pPulseRateRaw              = &pulseRawData;                                 //assign raw pulse's address to raw pulse pointer from compute struct
    cData->pRespRaw                   = &respRawData;
    cData->pTempCorrected             = &tempComputedData;                                //assign corrected temp's address to corrected temp pointer from compute struct
    cData->pSystolicPressCorrected    = &sysComputedData;                       //assign corrected sys's address to corrected sys pointer from compute struct
    cData->pDiastolicPressCorrected   = &diaComputedData;                      //assign corrected dia's address to corrected dia pointer from compute struct
    cData->pPulseRateCorrected        = &pulseComputedData;                           //assign corrected pulse's address to corrected pulse pointer from compute struct
    cData->pRespCorrected             = &respComputedData;

    Serial.println("In COMPUTE");
    cData->pTempCorrected->push(5 + (0.75 * (cData->pTemperatureRaw->last())));                          //convert raw temp and push it to the buffer
    cData->pSystolicPressCorrected->push(9 + (2    * (cData->pSystolicPressRaw->last())));                            //convert raw sys and push it to the buffer
    cData->pDiastolicPressCorrected->push(6 + (1.5  * (cData->pDiastolicPressRaw->last())));                            //convert raw dia and push it to the buffer
    cData->pPulseRateCorrected->push(8 + (3    * (cData->pPulseRateRaw->last())));                        //convert raw pulse and push it to the buffer
    cData->pRespCorrected->push(7 + (3    * (cData->pRespRaw->last())));                        //convert raw pulse and push it to the buffer
}

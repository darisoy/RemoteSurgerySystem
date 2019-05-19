#include "Compute.h"                                                                 //import the header of this function
#include "dataStructs.h"                                                             //import the variables
#include <stdio.h>                                                                   //import necessary header files
#include <stdbool.h>                                                                 //import necessary header files
#include <stddef.h>                                                                  //import necessary header files

void computeFunction(void* computeDataStruct){                                         //function that computes data, takes compute struct as input
    struct controlComputeData *cData = (struct controlComputeData*) computeDataStruct; //deference the compute struct
    cData->pTemperatureRaw            = &temperatureRaw;                               //assign raw temp's address to raw temp pointer from compute struct
    cData->pSystolicPressRaw          = &systolicPressRaw;                             //assign raw sys's address to raw sys pointer from compute struct
    cData->pDiastolicPressRaw         = &diastolicPressRaw;                            //assign raw dia's address to raw dia pointer from compute struct
    cData->pPulseRateRaw              = &pulseRateRaw;                                 //assign raw pulse's address to raw pulse pointer from compute struct
    cData->pTempCorrected             = &tempCorrected;                                //assign corrected temp's address to corrected temp pointer from compute struct
    cData->pSystolicPressCorrected    = &systolicPressCorrected;                       //assign corrected sys's address to corrected sys pointer from compute struct
    cData->pDiastolicPressCorrected   = &diastolicPressCorrected;                      //assign corrected dia's address to corrected dia pointer from compute struct
    cData->pPulseRateCorrected        = &pulseRateCorrected;                           //assign corrected pulse's address to corrected pulse pointer from compute struct

    tempComputedData.push(5 + (0.75 * (tempRawData.last())));                          //convert raw temp and push it to the buffer
    sysComputedData.push(9 + (2    * (sysRawData.last())));                            //convert raw sys and push it to the buffer
    diaComputedData.push(6 + (1.5  * (diaRawData.last())));                            //convert raw dia and push it to the buffer
    pulseComputedData.push(8 + (3    * (pulseRawData.last())));                        //convert raw pulse and push it to the buffer
    respComputedData.push(7 + (3    * (respRawData.last())));                        //convert raw pulse and push it to the buffer
}

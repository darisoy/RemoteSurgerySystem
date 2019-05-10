#include "Compute.h"                                                                 //import the header of this function
#include "dataStructs.h"                                                             //import the variables
#include <stdio.h>                                                                   //import necessary header files
#include <stdbool.h>                                                                 //import necessary header files
#include <stddef.h>                                                                  //import necessary header files

void computeFunction(void* computeDataStruct){                                       //function that computes data, takes compute struct as input
  struct controlComputeData *cData = (struct controlComputeData*) computeDataStruct; //deference the compute struct

  tempComputedData.push(5 + (0.75 * (tempRawData.first())));         //convert raw temp and point pTempComputed pointer to it
  sysComputedData.push(9 + (2    * (sysRawData.first())));       //convert raw sys and point pSystolicPressComputed pointer to it
  diaComputedData.push(6 + (1.5  * (diaRawData.first())));      //convert raw dia and point pDiastolicPressComputed pointer to it
  pulseComputedData.push(8 + (3    * (pulseRawData.first())));           //convert raw pulse and point pPulseRateComputed pointer to it
}

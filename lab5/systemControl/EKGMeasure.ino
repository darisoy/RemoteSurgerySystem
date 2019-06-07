#include "EKGMeasure.h"                                                                            //import the header of this function
#include "dataStructs.h"                                                                        //import the variables
#include <stdio.h>                                                                              //import necessary header files
#include <stdbool.h>                                                                            //import necessary header files
#include <stddef.h>
#include "arduinoFFT.h"
#include "datastructs.h"


void EKGMeasureFunction(void* data) {
  struct controlEKGData* EKGData = (struct controlEKGData*) data;
  EKGData->EKGRealDataPtr = &vReal;
  EKGData->EKGImagDataPtr = &vImag;
  EKGData->EKGFrequencyPtr = &ekgData;

  for(int i=0; i<SAMPLES; i++)
    {
        microseconds = micros();    //Overflows after around 70 minutes!
     
        vReal[i] = analogRead(EKGPIN);
        vImag[i] = 0;
     
        while(micros() < (microseconds + sampling_period_us)){
        }
    }
    
  runEKGProcess = true;
}

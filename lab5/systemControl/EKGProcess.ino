#include "EKGProcess.h"                                                                            //import the header of this function
#include "dataStructs.h"                                                                        //import the variables
#include <stdio.h>                                                                              //import necessary header files
#include <stdbool.h>                                                                            //import necessary header files
#include <stddef.h>

void EKGProcessFunction(void* data) {
  //double sampleFrequency = 2 * frequency;
  struct controlEKGData* EKGData = (struct controlEKGData*) data;
  EKGData->EKGRealDataPtr = &vReal;
  EKGData->EKGImagDataPtr = &vImag;
  EKGData->EKGFrequencyPtr = &ekgData;

    if (collectData) {
        FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
        FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
        FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
        (*EKGData->EKGFrequencyPtr).push(FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY));
    }


  //Serial.println((*EKGData->EKGFrequencyPtr).last());

  runEKGProcess = false;
}

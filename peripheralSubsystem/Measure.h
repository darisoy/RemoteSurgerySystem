#include <stdio.h>                                          //import the stdio.h file
void measureFunction(                                       //header for measureFuction
                     struct controlMeasureData MeasureData, //takes in struct
                     int* pTempCount,                       //takes in pointer to temperature count
                     int* pPulseCount,                      //takes in pointer to pulse count
                     int* pSysCount,                        //takes in pointer to systolic press. count
                     int* pDiaCount);                       //takes in pointer to diastolic press. count

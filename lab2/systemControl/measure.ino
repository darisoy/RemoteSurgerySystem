#include "Measure.h"                                                                            //import the header of this function
#include "dataStructs.h"                                                                        //import the variables
#include <stdio.h>                                                                              //import necessary header files
#include <stdbool.h>                                                                            //import necessary header files
#include <stddef.h>                                                                             //import necessary header files

void measureFunction(void* measureDataStruct) {                                                 //function that recieves the raw data from UNO, takes measure struct as input
    struct controlMeasureData *mData = (struct controlMeasureData*) measureDataStruct;          //deference the display struct
    mData->pTemperatureRaw     = &temperatureRaw;                                               //assign raw temp's address to raw temp pointer from compute struct
    mData->pSystolicPressRaw   = &systolicPressRaw;                                             //assign raw sys's address to raw sys pointer from compute struct
    mData->pDiastolicPressRaw  = &diastolicPressRaw;                                            //assign raw dia's address to raw dia pointer from compute struct
    mData->pPulseRateRaw       = &pulseRateRaw;                                                 //assign raw pulse's address to raw pulse pointer from compute struct

    if (Serial1.read() == 'V') {                                                                //check if the letter 'V' is printed on serial1
        Serial1.readBytes(dataTransfered, 4);                                                   //store the next 4 characters written on serial one to dataTranfered character array
        unsigned int digit1 = dataTransfered[1] - '0';                                          //convert the characters to digits
        unsigned int digit2 = dataTransfered[2] - '0';                                          //convert the characters to digits
        unsigned int digit3 = dataTransfered[3] - '0';                                          //convert the characters to digits
        if (digit1 < 10 && digit2 < 10 && digit3 < 10) {                                        //make sure all of those digits are less than 10
            if (dataTransfered[0] == 'T') {                                                     //if the second charater is 'T', that means the data being sent is temperature
                *mData->pTemperatureRaw = (digit1 * 100) + (digit2 * 10) + (digit3 * 1);        //assign the value of the temperature raw pointer from the measure struct to the temperature data
            }
            if (dataTransfered[0] == 'S') {                                                     //if the second charater is 'S', that means the data being sent is systolic pressure
                *mData->pSystolicPressRaw = (digit1 * 100) + (digit2 * 10) + (digit3 * 1);      //assign the value of the systolic raw pointer from the measure struct to the systolic data
            }
            if (dataTransfered[0] == 'D') {                                                     //if the second charater is 'D', that means the data being sent is diastolic pressure
                *mData->pDiastolicPressRaw = (digit1 * 100) + (digit2 * 10) + (digit3 * 1);     //assign the value of the diastolic raw pointer from the measure struct to the diastolic data
            }
            if (dataTransfered[0] == 'P') {                                                     //if the second charater is 'P', that means the data being sent is pulse rate
                *mData->pPulseRateRaw = (digit1 * 100) + (digit2 * 10) + (digit3 * 1);          //assign the value of the pulse raw pointer from the measure struct to the pulse data
            }
        }
    }
}

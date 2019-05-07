#include "Measure.h"                                                                            //import the header of this function
#include "dataStructs.h"                                                                        //import the variables
#include <stdio.h>                                                                              //import necessary header files
#include <stdbool.h>                                                                            //import necessary header files
#include <stddef.h>                                                                             //import necessary header files

void measureFunction(void* measureDataStruct) {                                                 //function that recieves the raw data from UNO, takes measure struct as input
    struct controlMeasureData *mData = (struct controlMeasureData*) measureDataStruct;          //deference the display struct
    mData->pTemperatureRawBuf    = &temperatureRawBuf;                                               //assign raw temp's address to raw temp pointer from compute struct
    mData->pBloodPressRawbuf   = &bloodPressRawBuf;                                             //assign raw sys's address to raw sys pointer from compute struct
    mData->pPulseRateRawBuf      = &pulseRateRawBuf;                                                 //assign raw pulse's address to raw pulse pointer from compute struct

    if (Serial1.read() == 'V') {                                                                //check if the letter 'V' is printed on serial1
        Serial1.readBytes(dataTransfered, 16);                                                   //store the next 4 characters written on serial one to dataTranfered character array
        Serial.print(dataTransfered[0]);                                                        //print the charater array on serial for troubleshooting purposes
        Serial.print(dataTransfered[1]);                                                        //print the charater array on serial for troubleshooting purposes
        Serial.print(dataTransfered[2]);                                                        //print the charater array on serial for troubleshooting purposes
        Serial.println(dataTransfered[3]);                                                      //print the charater array on serial for troubleshooting purposes
        unsigned int digit1 = dataTransfered[1] - '0';                                          //convert the characters to digits
        unsigned int digit2 = dataTransfered[2] - '0';
        unsigned int digit3 = dataTransfered[3] - '0';
        unsigned int digit5 = dataTransfered[5] - '0';
        unsigned int digit6 = dataTransfered[6] - '0';
        unsigned int digit7 = dataTransfered[7] - '0';
        unsigned int digit9 = dataTransfered[9] - '0';
        unsigned int digit10 = dataTransfered[10] - '0';
        unsigned int digit11 = dataTransfered[11] - '0';
        unsigned int digit13 = dataTransfered[13] - '0';
        unsigned int digit14 = dataTransfered[14] - '0';
        unsigned int digit15 = dataTransfered[15] - '0';

        if ((dataTransfered[0] == 'T')  && (digit1 < 10)  && (digit2 < 10)  && (digit3 < 10)  &&
            (dataTransfered[4] == 'S')  && (digit5 < 10)  && (digit6 < 10)  && (digit7 < 10)  &&
            (dataTransfered[8] == 'D')  && (digit9 < 10)  && (digit10 < 10) && (digit11 < 10) &&
            (dataTransfered[12] == 'P') && (digit13 < 10) && (digit14 < 10) && (digit15 < 10)) {
            BufferWrite(*mData->pTemperatureRawBuf, (digit1 * 100) + (digit2 * 10) + (digit3 * 1));        //assign the value of the temperature raw pointer from the measure struct to the temperature data
            BufferWrite(*mData->pSystolicRawBuf, (digit5 * 100) + (digit6 * 10) + (digit7 * 1));      //assign the value of the systolic raw pointer from the measure struct to the systolic data
            BufferWrite(*mData->pDiastolicRawBuf, (digit9 * 100) + (digit10 * 10) + (digit11 * 1));     //assign the value of the diastolic raw pointer from the measure struct to the diastolic data
            BufferWrite(*mData->pPulseRateRawBuf, (digit13 * 100) + (digit14 * 10) + (digit15 * 1));          //assign the value of the pulse raw pointer from the measure struct to the pulse data
            *mData->pBloodPressRawBuf.list = *mData->pSystolicRawBuf + *mData->pDiastolicRawBuf;
        }
    }
}

#include "Warning.h"                                                                                 //import the header of this function
#include "dataStructs.h"                                                                             //import the variables
#include <stdio.h>                                                                                   //import necessary header files
#include <stdbool.h>                                                                                 //import necessary header files
#include <stddef.h>                                                                                  //import necessary header files

void alarmFunction(void* warningStruct){                                                             //function that checks if alarms should be going off, takes in the warning struct
    struct controlWarningAlarmData *wData = (struct controlWarningAlarmData*) warningStruct;         //deference the warning struct
    wData->pTempCorrected           = &tempCorrected;                                                //assign corrected temp's address to corrected temp pointer from warning struct
    wData->pSystolicPressCorrected  = &systolicPressCorrected;                                       //assign corrected sys's address to corrected sys pointer from warning struct
    wData->pDiastolicPressCorrected = &diastolicPressCorrected;                                      //assign corrected fia's address to corrected dia pointer from warning struct
    wData->pPulseRateCorrected      = &pulseRateCorrected;                                           //assign corrected pulse's address to corrected pulse pointer from warning struct
    wData->pBatteryState            = &batteryState;                                                 //assign battery state's address to battery state pointer from warning struct

    if ((tempComputedData.last() <= 39.7) && (tempComputedData.last() >= 34.3)) {                    //if value of the corrected temp pointer is less than 37.8 and greater than 36.1, make the boolean true, otherwise false
        tempGoodBool = 0;                                                                            //change data text color
        if (annunciation == 0) {                                                                          //execute if in annunciation page
            ack_T.drawButton(true);                                                                  // draw inverse button
        }
    // } else if (tempComputedData.last() >= 43.5 || tempComputedData.last() <= 30.7) {                                                      //check if sys is more than 20% out of range
    //     tempGoodBool = 2;                                                                             //change data text color
    //     tempMeasure++;                                                                                //keep track of how long it has been out of range for
    //     if (tempMeasure > 5) {                                                                        //if data out of range for more than 5 times in a row
    //         if (annunciation == 0) {                                                                      //execute if in annunciation page
    //             ack_T.drawButton();                                                                  // draw normal button
    //         }
    //     }
    } else {                                                                                         //if data out of range
        tempGoodBool = 1;                                                                            //change data text color
        tempMeasure++;                                                                               //keep track of how long it has been out of range for
        if (tempMeasure > 5) {                                                                       //if data out of range for more than 5 times in a row
            tempGoodBool = 2;                                                                        //change data text color
            if (annunciation == 0) {                                                                      //execute if in annunciation page
                ack_T.drawButton();                                                                  // draw normal button
            }
        }
    }

    if ((sysComputedData.last() >= 114) && (sysComputedData.last() <= 136.5)) {                        //if value of the corrected sys pointer is 120, make the boolean true, otherwise false
        sysGoodBool = 0;                                                                             //change data text color
        if (annunciation == 0) {                                                                          //execute if in annunciation page
            ack_S.drawButton(true);                                                                  // draw inverse button
        }
    // } else if (sysComputedData.last() >= 156 || sysComputedData.last() <= 96) {                                                      //check if sys is more than 20% out of range
    //     sysGoodBool = 2;                                                                             //change data text color
    //     sysMeasure++;                                                                                //keep track of how long it has been out of range for
    //     if (sysMeasure > 5) {                                                                        //if data out of range for more than 5 times in a row
    //         if (annunciation == 0) {                                                                      //execute if in annunciation page
    //             ack_S.drawButton();                                                                  // draw normal button
    //         }
    //     }
    } else {                                                                                         //if data out of range
        sysGoodBool = 1;                                                                             //change data text color
        sysMeasure++;                                                                                //keep track of how long it has been out of range for
        if (sysMeasure > 5) {                                                                        //if data out of range for more than 5 times in a row
            sysGoodBool = 2;                                                                         //change data text color
            if (annunciation == 0) {                                                                      //execute if in annunciation page
                ack_S.drawButton();                                                                  // draw normal button
            }
        }
    }

    if ((diaComputedData.last() <= 84) && (diaComputedData.last() >= 66.5)) {                           //if value of the corrected dia pointer is 80, make the boolean true, otherwise false
        diaGoodBool = 0;                                                                             //change data text color
        if (annunciation == 0) {                                                                          //execute if in annunciation page
            ack_D.drawButton(true);                                                                  // draw inverse button
        }
    } else {                                                                                         //if data out of range
        diaGoodBool = 1;                                                                             //change data text color
        diaMeasure++;                                                                                //keep track of how long it has been out of range for
        if (diaMeasure > 5) {                                                                        //if data out of range for more than 5 times in a row
            diaGoodBool = 2;                                                                         //change data text color
            if (annunciation == 0) {                                                                      //execute if in annunciation page
                ack_D.drawButton();                                                                  // draw normal button
            }
        }
    }

    if ((pulseComputedData.last() >= 57) && (pulseComputedData.last() <= 105)) {                   //if value of the corrected pulse rate pointer is greater than 60 and less than 100, make the boolean true, otherwise false
        prGoodBool = 0;                                                                              //change data text color
        if (annunciation == 0) {                                                                          //execute if in annunciation page
            ack_P.drawButton(true);                                                                  // draw inverse button
        }
    // } else if (pulseComputedData.last() >= 115 || pulseComputedData.last() <= 51) {                                                      //check if sys is more than 20% out of range
    //     prGoodBool = 2;                                                                             //change data text color
    //     prMeasure++;                                                                                //keep track of how long it has been out of range for
    //     if (prMeasure > 5) {                                                                        //if data out of range for more than 5 times in a row
    //         if (annunciation == 0) {                                                                      //execute if in annunciation page
    //             ack_P.drawButton();                                                                  // draw normal button
    //         }
    //     }
    } else {                                                                                         //if data out of range
        prGoodBool = 1;                                                                              //change data text color
        prMeasure++;                                                                                 //keep track of how long it has been out of range for
        if (prMeasure > 5) {                                                                         //if data out of range for more than 5 times in a row
            prGoodBool = 2;                                                                          //change data text color
            if (annunciation == 0) {                                                                      //execute if in annunciation page
                ack_P.drawButton();                                                                  // draw normal button
            }
        }
    }

    if ((respComputedData.last() <= 26.25) && (respComputedData.last() >= 11.4)) {                   //if value of the corrected pulse rate pointer is greater than 60 and less than 100, make the boolean true, otherwise false
        rrGoodBool = 0;                                                                              //change data text color
        if (annunciation == 0) {                                                                          //execute if in annunciation page
            ack_R.drawButton(true);                                                                  // draw inverse button
        }
    // } else if (respComputedData.last() >= 28.8 || respComputedData.last() <= 10.2) {                                                      //check if sys is more than 20% out of range
    //        rrGoodBool = 2;                                                                             //change data text color
    //        rrMeasure++;                                                                                //keep track of how long it has been out of range for
    //        if (rrMeasure > 5) {                                                                        //if data out of range for more than 5 times in a row
    //            if (annunciation == 0) {                                                                      //execute if in annunciation page
    //                ack_R.drawButton();                                                                  // draw normal button
    //            }
    //        }
    } else {                                                                                         //if data out of range
        rrGoodBool = 1;                                                                              //change data text color
        rrMeasure++;                                                                                 //keep track of how long it has been out of range for
        if (rrMeasure > 5) {                                                                         //if data out of range for more than 5 times in a row
            rrGoodBool = 2;                                                                          //change data text color
            if (annunciation == 0) {                                                                      //execute if in annunciation page
                ack_R.drawButton();                                                                  // draw normal button
            }
        }
    }

    if (*wData->pBatteryState >= 40) {                                                               //if value of the battery state pointer is greater than 40, make the boolean true, otherwise false
        batteryGoodBool = 0;                                                                         //change data text color
        if (annunciation == 0) {                                                                          //execute if in annunciation page
            ack_B.drawButton(true);                                                                  // draw inverse button
        }
    } else {                                                                                         //if data out of range
        batteryGoodBool = 1;                                                                         //change data text color
        batMeasure++;                                                                                //keep track of how long it has been out of range for
        if (batMeasure > 5) {                                                                        //if data out of range for more than 5 times in a row
            batteryGoodBool = 2;                                                                     //change data text color
            if (annunciation == 0) {                                                                      //execute if in annunciation page
                ack_B.drawButton();                                                                  // draw normal button
            }
        }
    }

}

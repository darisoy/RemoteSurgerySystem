#include "Warning.h"                                                                                 //import the header of this function
#include "dataStructs.h"                                                                             //import the variables
#include <stdio.h>                                                                                   //import necessary header files
#include <stdbool.h>                                                                                 //import necessary header files
#include <stddef.h>                                                                                  //import necessary header files

void alarmFunction(void* warningStruct){                                                             //function that checks if alarms should be going off, takes in the warning struct
    struct controlWarningAlarmData *wData = (struct controlWarningAlarmData*) warningStruct;           //deference the warning struct
    wData->pTempCorrected           = &tempCorrected;                                                  //assign corrected temp's address to corrected temp pointer from warning struct
    wData->pSystolicPressCorrected  = &systolicPressCorrected;                                         //assign corrected sys's address to corrected sys pointer from warning struct
    wData->pDiastolicPressCorrected = &diastolicPressCorrected;                                        //assign corrected fia's address to corrected dia pointer from warning struct
    wData->pPulseRateCorrected      = &pulseRateCorrected;                                             //assign corrected pulse's address to corrected pulse pointer from warning struct
    wData->pBatteryState            = &batteryState;                                                   //assign battery state's address to battery state pointer from warning struct
    if ((tempComputedData.last() <= 37.8) && (tempComputedData.last() >= 36.1)) {            //if value of the corrected temp pointer is less than 37.8 and greater than 36.1, make the boolean true, otherwise false
        tempGoodBool = 0;
        if (annunciation) {
            ack_T.drawButton(true);
        }
    } else {
        tempGoodBool = 1;
        tempMeasure++;
        if (tempMeasure > 5) {
            tempGoodBool = 2;
            if (annunciation) {
                ack_T.drawButton();
            }
        }
    }

    if ((sysComputedData.last() >= 120) && (sysComputedData.last() <= 130)) {                                        //if value of the corrected sys pointer is 120, make the boolean true, otherwise false
        sysGoodBool = 0;
        if (annunciation) {
            ack_S.drawButton(true);
        }
    } else if (sysComputedData.last() >= 156) {
        sysGoodBool = 2;
    } else {
        sysGoodBool = 1;
        sysMeasure++;
        if (sysMeasure > 5) {
            sysGoodBool = 2;
            if (annunciation) {
                ack_S.drawButton();
            }
        }
    }

    if ((diaComputedData.last() <= 80) && (diaComputedData.last()>= 70)) {                                        //if value of the corrected dia pointer is 80, make the boolean true, otherwise false
        diaGoodBool = 0;
        if (annunciation) {
            ack_D.drawButton(true);
        }
    } else {
        diaGoodBool = 1;
        diaMeasure++;
        if (diaMeasure > 5) {
            diaGoodBool = 2;
            if (annunciation) {
                ack_D.drawButton();
            }
        }
    }

    if ((pulseComputedData.last() > 60.0) && (pulseComputedData.last()< 100.0)) {   //if value of the corrected pulse rate pointer is greater than 60 and less than 100, make the boolean true, otherwise false
        prGoodBool = 0;
        if (annunciation) {
            ack_P.drawButton(true);
        }
    } else {
        prGoodBool = 1;
        prMeasure++;
        if (prMeasure > 5) {
            prGoodBool = 2;
            if (annunciation) {
                ack_P.drawButton();
            }
        }
    }

    if (*wData->pBatteryState >= 40) {                                                   //if value of the battery state pointer is greater than 40, make the boolean true, otherwise false
        batteryGoodBool = 0;
        if (annunciation) {
            ack_B.drawButton(true);
        }
    } else {
        batteryGoodBool = 1;
        batMeasure++;
        if (batMeasure > 5) {
            batteryGoodBool = 2;
            if (annunciation) {
                ack_B.drawButton();
            }
        }
    }

}

#include "Warning.h"                                                                                 //import the header of this function
#include "dataStructs.h"                                                                             //import the variables
#include <stdio.h>                                                                                   //import necessary header files
#include <stdbool.h>                                                                                 //import necessary header files
#include <stddef.h>                                                                                  //import necessary header files

void alarmFunction(void* warningStruct){                                                             //function that checks if alarms should be going off, takes in the warning struct
    struct controlWarningAlarmData *wData = (struct controlWarningAlarmData*) warningStruct;           //deference the warning struct

    if ((tempComputedData.first() <= 37.8) && (tempComputedData.first() >= 36.1)) {            //if value of the corrected temp pointer is less than 37.8 and greater than 36.1, make the boolean true, otherwise false
        tempGoodBool = 0;
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

    if ((sysComputedData.first() >= 120) && (sysComputedData.first() <= 130)) {                                        //if value of the corrected sys pointer is 120, make the boolean true, otherwise false
        sysGoodBool = 0;
        if (annunciation) {
            ack_S.drawButton(true);
        }
    } else if (sysComputedData.first() >= 156) {
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

    if ((diaComputedData.first() <= 80) && (diaComputedData.first()>= 70)) {                                        //if value of the corrected dia pointer is 80, make the boolean true, otherwise false
        diaGoodBool = 0;
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

    if ((pulseComputedData.first() > 60.0) && (pulseComputedData.first()< 100.0)) {   //if value of the corrected pulse rate pointer is greater than 60 and less than 100, make the boolean true, otherwise false
        prGoodBool = 0;
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

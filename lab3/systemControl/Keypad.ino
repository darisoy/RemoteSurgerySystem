#include "Keypad.h"                                                                         //import the header of this function
#include "dataStructs.h"                                                                    //import the variables
#include <stdio.h>                                                                          //import necessary header files
#include <stdbool.h>                                                                        //import necessary header files
#include <stddef.h>                                                                         //import necessary header files

#define TS_MINX 120
#define TS_MAXX 900
#define TS_MINY 70
#define TS_MAXY 920
#define MINPRESSURE 10
#define MAXPRESSURE 1000

void keypadFunction(void* keypadDataStruct){
    struct controlKeypadData *kData = (struct controlKeypadData*) keypadDataStruct;         //deference the keypad struct
    kData->pMeasurementSelection = &measurementSelection;
    kData->pAlarmAcknowledge     = &alarmAcknowledge;

    digitalWrite(13, HIGH);
    TSPoint p = ts.getPoint();
    digitalWrite(13, LOW);
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);


    p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());                                       // scale from 0->1023 to tft.width
    p.y = (tft.height()-map(p.y, TS_MINY, TS_MAXY, 0, tft.height()));                       // scale from 0->1023 to tft.width

    if (menu.contains(p.x, p.y)) {                                                          //check is touch was within the button location
        menu.press(true);  // tell the button it is pressed
    } else {
        menu.press(false);  // tell the button it is NOT pressed
    }

    if (annunciate.contains(p.x, p.y)) {                                                          //check is touch was within the button location
        annunciate.press(true);  // tell the button it is pressed
    } else {
        annunciate.press(false);  // tell the button it is NOT pressed
    }

    if (an_T.contains(p.x, p.y)) {                                                          //check is touch was within the button location
        an_T.press(true);  // tell the button it is pressed
    } else {
        an_T.press(false);  // tell the button it is NOT pressed
    }

    if (an_S.contains(p.x, p.y)) {                                                          //check is touch was within the button location
        an_S.press(true);  // tell the button it is pressed
    } else {
        an_S.press(false);  // tell the button it is NOT pressed
    }

    if (an_D.contains(p.x, p.y)) {                                                          //check is touch was within the button location
        an_D.press(true);  // tell the button it is pressed
    } else {
        an_D.press(false);  // tell the button it is NOT pressed
    }

    if (an_P.contains(p.x, p.y)) {                                                          //check is touch was within the button location
        an_P.press(true);  // tell the button it is pressed
    } else {
        an_P.press(false);  // tell the button it is NOT pressed
    }

    if (exp1.contains(p.x, p.y)) {                                                          //check is touch was within the button location
        exp1.press(true);  // tell the button it is pressed
    } else {
        exp1.press(false);  // tell the button it is NOT pressed
    }

    if (exp2.contains(p.x, p.y)) {                                                          //check is touch was within the button location
        exp2.press(true);  // tell the button it is pressed
    } else {
        exp2.press(false);  // tell the button it is NOT pressed
    }

    if (ack_T.contains(p.x, p.y)) {                                                          //check is touch was within the button location
        ack_T.press(true);  // tell the button it is pressed
    } else {
        ack_T.press(false);  // tell the button it is NOT pressed
    }

    if (annunciation && tempGoodBool == 2 && ack_T.contains(p.x, p.y)) {
        ack_T.drawButton(true);
        tempMeasure = 0;
    }

    if (annunciation && sysGoodBool == 2 && ack_S.contains(p.x, p.y)) {
        ack_S.drawButton(true);
        sysMeasure = 0;
    }

    if (annunciation && diaGoodBool == 2 && ack_D.contains(p.x, p.y)) {
        ack_D.drawButton(true);
        diaMeasure = 0;
    }

    if (annunciation && prGoodBool == 2 && ack_P.contains(p.x, p.y)) {
        ack_P.drawButton(true);
        prMeasure = 0;
    }

    if (annunciation && batteryGoodBool == 2 && ack_B.contains(p.x, p.y)) {
        ack_B.drawButton(true);
        batMeasure = 0;
    }
}

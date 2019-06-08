#include "Keypad.h"                                                                         //import the header of this function
#include "dataStructs.h"                                                                    //import the variables
#include <stdio.h>                                                                          //import necessary header files
#include <stdbool.h>                                                                        //import necessary header files
#include <stddef.h>                                                                         //import necessary header files

#define TS_MINX 120                                                                         //define constants
#define TS_MAXX 900                                                                         //define constants
#define TS_MINY 70                                                                          //define constants
#define TS_MAXY 920                                                                         //define constants
#define MINPRESSURE 10                                                                      //define constants
#define MAXPRESSURE 1000                                                                    //define constants

void keypadFunction(void* keypadDataStruct){                                                //function that controls the touchscreen
    struct controlKeypadData *kData = (struct controlKeypadData*) keypadDataStruct;         //deference the keypad struct
    kData->pMeasurementSelection = &measurementSelection;                                   //assign measurementSelection's address to measurementSelection pointer from keypad struct
    kData->pAlarmAcknowledge     = &alarmAcknowledge;                                       //assign alarmAcknowledge's address to alarmAcknowledge pointer from keypad struct

    digitalWrite(13, HIGH);                                                                 //set pin 13 to be high
    TSPoint p = ts.getPoint();                                                              //get the coordinates of the touch on the screen
    digitalWrite(13, LOW);                                                                  //set pin 13 to be low
    pinMode(XM, OUTPUT);                                                                    //set pin to be output
    pinMode(YP, OUTPUT);                                                                    //set pin to be output

    p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());                                       // scale from 0->1023 to tft.width
    p.y = (tft.height()-map(p.y, TS_MINY, TS_MAXY, 0, tft.height()));                       // scale from 0->1023 to tft.width

    if (menu.contains(p.x, p.y)) {                                                          //check is touch was within the button location
        menu.press(true);                                                                   // tell the button it is pressed
    } else {                                                                                //if it doesn't contain it
        menu.press(false);                                                                  // tell the button it is NOT pressed
    }

    if (annunciate.contains(p.x, p.y)) {                                                    //check is touch was within the button location
        annunciate.press(true);                                                             // tell the button it is pressed
    } else {                                                                                //if it doesn't contain it
        annunciate.press(false);                                                            // tell the button it is NOT pressed
    }

    if (display.contains(p.x, p.y)) {                                                    //check is touch was within the button location
        display.press(true);                                                             // tell the button it is pressed
    } else {                                                                                //if it doesn't contain it
        display.press(false);                                                            // tell the button it is NOT pressed
    }

    if (exp1.contains(p.x, p.y)) {                                                          //check is touch was within the button location
        exp1.press(true);                                                                   // tell the button it is pressed
        trafficSwitch = 1;
    } else {                                                                                //if it doesn't contain it
        exp1.press(false);                                                                  // tell the button it is NOT pressed
    }

    if (exp2.contains(p.x, p.y)) {                                                          //check is touch was within the button location
        exp2.press(true);                                                                   // tell the button it is pressed
        trafficSwitch = 0;
    } else {                                                                                //if it doesn't contain it
        exp2.press(false);                                                                  // tell the button it is NOT pressed
    }

    if (an_T.contains(p.x, p.y)) {                                                          //check is touch was within the button location
        an_T.press(true);                                                                   // tell the button it is pressed
    } else {                                                                                //if it doesn't contain it
        an_T.press(false);                                                                  // tell the button it is NOT pressed
    }

    if (an_S.contains(p.x, p.y)) {                                                          //check is touch was within the button location
        an_S.press(true);                                                                   // tell the button it is pressed
    } else {                                                                                //if it doesn't contain it
        an_S.press(false);                                                                  // tell the button it is NOT pressed
    }

    if (an_D.contains(p.x, p.y)) {                                                          //check is touch was within the button location
        an_D.press(true);                                                                   // tell the button it is pressed
    } else {                                                                                //if it doesn't contain it
        an_D.press(false);                                                                  // tell the button it is NOT pressed
    }

    if (an_P.contains(p.x, p.y)) {                                                          //check is touch was within the button location
        an_P.press(true);                                                                   // tell the button it is pressed
    } else {                                                                                //if it doesn't contain it
        an_P.press(false);                                                                  // tell the button it is NOT pressed
    }

    if (an_R.contains(p.x, p.y)) {                                                         //check is touch was within the button location
        an_R.press(true);                                                                  // tell the button it is pressed
    } else {                                                                                //if it doesn't contain it
        an_R.press(false);                                                                 // tell the button it is NOT pressed
    }

    if (an_E.contains(p.x, p.y)) {                                                         //check is touch was within the button location
        an_E.press(true);                                                                  // tell the button it is pressed
    } else {                                                                                //if it doesn't contain it
        an_E.press(false);                                                                 // tell the button it is NOT pressed
    }


    if ((annunciation == 0) && tempGoodBool == 2 && ack_T.contains(p.x, p.y)) {                    //check if the ack button should be removed
        ack_T.drawButton(true);                                                             //draw the inverse of the
        tempMeasure = 0;                                                                    //change data text color
    }

    if ((annunciation == 0) && sysGoodBool == 2 && ack_S.contains(p.x, p.y)) {                     //check if the ack button should be removed
        ack_S.drawButton(true);                                                             //draw the inverse of the
        sysMeasure = 0;                                                                     //change data text color
    }

    if ((annunciation == 0) && diaGoodBool == 2 && ack_D.contains(p.x, p.y)) {                     //check if the ack button should be removed
        ack_D.drawButton(true);                                                             //draw the inverse of the
        diaMeasure = 0;                                                                     //change data text color
    }

    if ((annunciation == 0) && prGoodBool == 2 && ack_P.contains(p.x, p.y)) {                      //check if the ack button should be removed
        ack_P.drawButton(true);                                                             //draw the inverse of the
        prMeasure = 0;                                                                      //change data text color
    }

    if ((annunciation == 0) && batteryGoodBool == 2 && ack_B.contains(p.x, p.y)) {                 //check if the ack button should be removed
        ack_B.drawButton(true);                                                             //draw the inverse of the
        batMeasure = 0;                                                                     //change data text color
    }

    if ((annunciation == 0) && rrGoodBool == 2 && ack_R.contains(p.x, p.y)) {                 //check if the ack button should be removed
        ack_R.drawButton(true);                                                             //draw the inverse of the
        rrMeasure = 0;                                                                     //change data text color
    }

    if ((annunciation == 0) && ekgGoodBool == 2 && ack_E.contains(p.x, p.y)) {                 //check if the ack button should be removed
        ack_E.drawButton(true);                                                             //draw the inverse of the
        ekgMeasure = 0;                                                                     //change data text color
    }
}

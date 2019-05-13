#include "Display.h"                                                                        //import the header of this function
#include "dataStructs.h"                                                                    //import the variables
#include <stdio.h>                                                                          //import necessary header files
#include <stdbool.h>                                                                        //import necessary header files
#include <stddef.h>                                                                         //import necessary header files

boolean annunciation;
boolean bool_T = false;
boolean bool_S = false;
boolean bool_D = false;
boolean bool_P = false;

void displayFunction(void* displayDataStruct){                                              //function that display the data on the TFT LCD display, takes display struct as input
    struct controlDisplayData *dData = (struct controlDisplayData*) displayDataStruct;        //deference the display struct
    dData->pTempCorrected           = &tempCorrected;                                         //assign corrected temp's address to corrected temp pointer from display struct
    dData->pSystolicPressCorrected  = &systolicPressCorrected;                                //assign corrected sys's address to corrected sys pointer from display struct
    dData->pDiastolicPressCorrected = &diastolicPressCorrected;                               //assign corrected dia's address to corrected dia pointer from display struct
    dData->pPulseRateCorrected      = &pulseRateCorrected;                                    //assign corrected pulse's address to corrected pulse pointer from display struct
    dData->pBatteryState            = &batteryState;                                          //assign battery state's address to battery state pointer from display struct


    if (annunciate.justPressed()) {
        annunciate.drawButton(true);  // draw invert!
        tft.fillScreen(BLACK);
        menu.drawButton();
        annunciate.drawButton();
        exp1.drawButton();
        exp2.drawButton();
        annunciation = true;
        Serial.println("annunciation is pressed");
    }
    if (annunciate.justReleased()) {
        annunciate.drawButton();  // draw normal
    }
    if (menu.justPressed()) {
        menu.drawButton(true);  // draw invert!
        tft.fillScreen(BLACK);
        annunciate.drawButton();
        menu.drawButton();
        exp1.drawButton();
        exp2.drawButton();
        annunciation = false;
    }
    if (menu.justReleased()) {
        menu.drawButton();  // draw normal
    }

    if (exp1.justPressed()) {
        exp1.drawButton(true);  // draw invert!
    }

    if (exp1.justReleased()) {
        exp1.drawButton();  // draw normal
    }

    if (exp2.justPressed()) {
        exp2.drawButton(true);  // draw invert!
    }

    if (exp2.justReleased()) {
        exp2.drawButton();  // draw normal
    }
    if (annunciation) {
        tft.setCursor(0, 0);                                                                      //move cursor to the begining of the display
        tft.setTextSize(2);                                                                       //set font size to be 2
        tft.setTextColor(WHITE, BLACK);                                                           //set font color to be white with black background
        tft.println("results from patient");
        tft.setCursor(0, 25);                                                     //print "results from patient" on display
        tft.print("Temp: ");                                                                      //print "Temp:" on display
        if (tempGoodBool == 0) {                                                                       //if temperature is within range
            tft.setTextColor(GREEN, BLACK);                                                       //set font color to be green with black background
        } else if (tempGoodBool == 1){                                                                                  //if temperature is out of range
            tft.setTextColor(ORANGE, BLACK);
        } else {
            tft.setTextColor(RED, BLACK);                                                         //set font color to be red with black background
        }
        tft.print(tempComputedData[0]);                                                      //print the value of the corrected temp pointer that is in the display struct on the display
        tft.println(" C   ");                                                                     //print "C" on display

        tft.setTextColor(WHITE, BLACK);
        tft.setCursor(0, 50);                                                           //set font color to be white with black background
        tft.print("Syst: ");                                                                      //print "Syst:" on display
        if (sysGoodBool == 0) {                                                                        //if systolic pres is within range
            tft.setTextColor(GREEN, BLACK);                                                       //set font color to be green with black background
        } else if (sysGoodBool == 1) {                                                                                  //if temperature is out of range
            tft.setTextColor(ORANGE, BLACK);
        } else {                                                                                  //if sys is out of range
            tft.setTextColor(RED, BLACK);                                                         //set font color to be red with black background
        }
        tft.print(sysComputedData[0]);                                               //print the value of the corrected syst pointer that is in the display struct on the display
        tft.println(" mmHg ");                                                                   //print "mm Hg" on display

        tft.setTextColor(WHITE, BLACK);
        tft.setCursor(0, 75);                                                           //set font color to be white with black background
        tft.print("Dias: ");                                                                      //print "Dias:" on display
        if (diaGoodBool == 0) {                                                                        //if diastolic pres is within range
            tft.setTextColor(GREEN, BLACK);                                                       //set font color to be green with black background
        } else if (diaGoodBool == 1){                                                                                  //if temperature is out of range
            tft.setTextColor(ORANGE, BLACK);
        } else {                                                                                  //if dia is out of range
            tft.setTextColor(RED, BLACK);                                                         //set font color to be red with black background
        }
        tft.print(diaComputedData[0]);                                              //print the value of the corrected dia pointer that is in the display struct on the display
        tft.println(" mmHg ");                                                                   //print "mm Hg" on display

        tft.setTextColor(WHITE, BLACK);
        tft.setCursor(0, 100);                                                          //set font color to be white with black background
        tft.print("Puls: ");                                                                      //print "Puls:" on display
        if (prGoodBool == 0) {                                                                         //if pulse is within range
            tft.setTextColor(GREEN, BLACK);                                                       //set font color to be green with black background
        } else if (prGoodBool == 1){                                                                                  //if temperature is out of range
            tft.setTextColor(ORANGE, BLACK);
        } else {                                                                                  //if pulse is out of range
            tft.setTextColor(RED, BLACK);                                                         //set font color to be red with black background
        }
        tft.print(pulseComputedData[0]);                                                   //print the value of the corrected pulse pointer that is in the display struct on the display
        tft.println(" BPM ");                                                                     //print "BPM" on display

        tft.setTextColor(WHITE, BLACK);
        tft.setCursor(0, 125);                                                           //set font color to be white with black background
        tft.print("Batt: ");                                                                      //print "Batt:" on display
        if (batteryGoodBool == 0) {                                                                    //if battery is within range
            tft.setTextColor(GREEN, BLACK);                                                       //set font color to be green with black background
        } else if (batteryGoodBool == 1){                                                                                  //if temperature is out of range
            tft.setTextColor(ORANGE, BLACK);
        } else {                                                                                  //if battery is out of range
            tft.setTextColor(RED, BLACK);                                                         //set font color to be red with black background
        }
        tft.print((*dData->pBatteryState) / 2);                                                   //print half of the value of the battery state pointer that is in the display struct on the display
        tft.println("%      ");                                                                   //print "%" on display
    } else {
        tft.setTextSize(3);
        tft.setTextColor(RED, BLACK);
        tft.setCursor(75, 10);
        tft.print("MENU");
        tft.setTextColor(YELLOW, BLACK);
        tft.setCursor(8, 8);
        an_T.drawButton();
        if (an_T.justReleased()) {
            an_T.drawButton();  // draw normal
        }
        if (an_T.justPressed()) {
            an_T.drawButton(true);  // draw invert!
            bool_T = !bool_T;
        }
        if (bool_T) {
            tft.setTextColor(WHITE, BLACK);
        } else {
            tft.setTextColor(BLACK, BLACK);
        }
        tft.setCursor(35, 38);
        tft.print(tempComputedData[0]);
        tft.print("  ");
        tft.setTextSize(2);
        tft.setCursor(165, 45);
        tft.print(" C ");                                                                     //print "C" on display

        tft.setTextSize(3);
        tft.setTextColor(YELLOW, BLACK);
        tft.setCursor(8, 75);
        an_S.drawButton();
        if (an_S.justReleased()) {
            an_S.drawButton();  // draw normal
        }
        if (an_S.justPressed()) {
            an_S.drawButton(true);  // draw invert!
            bool_S = !bool_S;
        }
        if (bool_S) {
            tft.setTextColor(WHITE, BLACK);
        } else {
            tft.setTextColor(BLACK, BLACK);
        }
        tft.setCursor(35, 75);
        tft.print(sysComputedData[0]);                                               //print the value of the corrected syst pointer that is in the display struct on the display
        tft.print("  ");
        tft.setTextSize(2);
        tft.setCursor(165, 82);
        tft.print(" mmHg ");                                                                   //print "mm Hg" on display

        tft.setTextSize(3);
        tft.setTextColor(YELLOW, BLACK);
        tft.setCursor(8, 112);
        an_D.drawButton();
        if (an_D.justReleased()) {
            an_D.drawButton();  // draw normal
        }
        if (an_D.justPressed()) {
            an_D.drawButton(true);  // draw invert!
            bool_D = !bool_D;
        }
        if (bool_D) {
            tft.setTextColor(WHITE, BLACK);
        } else {
            tft.setTextColor(BLACK, BLACK);
        }
        tft.setCursor(35, 112);
        tft.print(diaComputedData[0]);                                              //print the value of the corrected dia pointer that is in the display struct on the display
        tft.print("  ");
        tft.setTextSize(2);
        tft.setCursor(165, 119);
        tft.print(" mmHg ");                                                                   //print "mm Hg" on display

        tft.setTextSize(3);
        tft.setTextColor(YELLOW, BLACK);
        tft.setCursor(8, 149);
        an_P.drawButton();
        if (an_P.justReleased()) {
            an_P.drawButton();  // draw normal
        }
        if (an_P.justPressed()) {
            an_P.drawButton(true);  // draw invert!
            bool_P = !bool_P;
        }
        if (bool_P) {
            tft.setTextColor(WHITE, BLACK);
        } else {
            tft.setTextColor(BLACK, BLACK);
        }
        tft.setCursor(35, 149);
        tft.print(pulseComputedData[0]);                                                   //print the value of the corrected pulse pointer that is in the display struct on the display
        tft.print("  ");
        tft.setTextSize(2);
        tft.setCursor(165, 156);
        tft.print(" BPM ");
    }
}

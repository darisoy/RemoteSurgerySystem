#include "Display.h"                                                                        //import the header of this function
#include "dataStructs.h"                                                                    //import the variables
#include <stdio.h>                                                                          //import necessary header files
#include <stdbool.h>                                                                        //import necessary header files
#include <stddef.h>                                                                         //import necessary header files

void displayFunction(void* displayDataStruct){                                              //function that display the data on the TFT LCD display, takes display struct as input
    struct controlDisplayData *dData = (struct controlDisplayData*) displayDataStruct;        //deference the display struct
    dData->pTempCorrected           = &tempCorrected;                                         //assign corrected temp's address to corrected temp pointer from display struct
    dData->pSystolicPressCorrected  = &systolicPressCorrected;                                //assign corrected sys's address to corrected sys pointer from display struct
    dData->pDiastolicPressCorrected = &diastolicPressCorrected;                               //assign corrected dia's address to corrected dia pointer from display struct
    dData->pPulseRateCorrected      = &pulseRateCorrected;                                    //assign corrected pulse's address to corrected pulse pointer from display struct
    dData->pBatteryState            = &batteryState;                                          //assign battery state's address to battery state pointer from display struct

    digitalWrite(13, HIGH);
    TSPoint p = ts.getPoint();
    digitalWrite(13, LOW);
    pinMode(A3, OUTPUT);
    pinMode(A2, OUTPUT);
    Serial.println(p.x);
    Serial.println(p.y);

    tft.setCursor(0, 0);                                                                      //move cursor to the begining of the display
    tft.setTextSize(2);                                                                       //set font size to be 2

    //boolean test = p.x > 736 && p.x < 855 && p.y > 255 && p.y < 725
    //if in annuciate
    if (false) {
        tft.setTextColor(WHITE, BLACK);                                                           //set font color to be white with black background
        tft.println("results from patient");                                                      //print "results from patient" on display
        tft.print("Temp: ");                                                                      //print "Temp:" on display
        if (tempGoodBool) {                                                                       //if temperature is within range
            tft.setTextColor(GREEN, BLACK);                                                       //set font color to be green with black background
        } else {                                                                                  //if temperature is out of range
            tft.setTextColor(RED, BLACK);                                                         //set font color to be red with black background
        }
        tft.print(*dData->pTempCorrected);                                                        //print the value of the corrected temp pointer that is in the display struct on the display
        tft.println(" C   ");                                                                     //print "C" on display

        tft.setTextColor(WHITE, BLACK);                                                           //set font color to be white with black background
        tft.print("Syst: ");                                                                      //print "Syst:" on display
        if (sysGoodBool) {                                                                        //if systolic pres is within range
            tft.setTextColor(GREEN, BLACK);                                                       //set font color to be green with black background
        } else {                                                                                  //if sys is out of range
            tft.setTextColor(RED, BLACK);                                                         //set font color to be red with black background
        }
        tft.print(*dData->pSystolicPressCorrected);                                               //print the value of the corrected syst pointer that is in the display struct on the display
        tft.println(" mm Hg ");                                                                   //print "mm Hg" on display

        tft.setTextColor(WHITE, BLACK);                                                           //set font color to be white with black background
        tft.print("Dias: ");                                                                      //print "Dias:" on display
        if (diaGoodBool) {                                                                        //if diastolic pres is within range
            tft.setTextColor(GREEN, BLACK);                                                       //set font color to be green with black background
        } else {                                                                                  //if dia is out of range
            tft.setTextColor(RED, BLACK);                                                         //set font color to be red with black background
        }
        tft.print(*dData->pDiastolicPressCorrected);                                              //print the value of the corrected dia pointer that is in the display struct on the display
        tft.println(" mm Hg ");                                                                   //print "mm Hg" on display

        tft.setTextColor(WHITE, BLACK);                                                           //set font color to be white with black background
        tft.print("Puls: ");                                                                      //print "Puls:" on display
        if (prGoodBool) {                                                                         //if pulse is within range
            tft.setTextColor(GREEN, BLACK);                                                       //set font color to be green with black background
        } else {                                                                                  //if pulse is out of range
            tft.setTextColor(RED, BLACK);                                                         //set font color to be red with black background
        }
        tft.print(*dData->pPulseRateCorrected);                                                   //print the value of the corrected pulse pointer that is in the display struct on the display
        tft.println(" BPM ");                                                                     //print "BPM" on display

        tft.setTextColor(WHITE, BLACK);                                                           //set font color to be white with black background
        tft.print("Batt: ");                                                                      //print "Batt:" on display
        if (batteryGoodBool) {                                                                    //if battery is within range
            tft.setTextColor(GREEN, BLACK);                                                       //set font color to be green with black background
        } else {                                                                                  //if battery is out of range
            tft.setTextColor(RED, BLACK);                                                         //set font color to be red with black background
        }
        tft.print((*dData->pBatteryState) / 2);                                                   //print half of the value of the battery state pointer that is in the display struct on the display
        tft.println("%      ");                                                                   //print "%" on display
    } else {
        tft.setTextSize(3);
        tft.setTextColor(YELLOW, BLACK);
        tft.setCursor(8, 8);
        tft.print("T");                                                                      //print "Temp:" on display
        tft.setTextColor(WHITE, BLACK);
        tft.setCursor(35, 8);
        tft.print(*dData->pTempCorrected);                                                        //print the value of the corrected temp pointer that is in the display struct on the display
        tft.print("  ");
        tft.setTextSize(2);
        tft.setCursor(165, 15);
        tft.print(" C ");                                                                     //print "C" on display

        tft.setTextSize(3);
        tft.setTextColor(YELLOW, BLACK);
        tft.setCursor(8, 38);
        tft.print("S");                                                                      //print "Syst:" on display
        tft.setTextColor(WHITE, BLACK);
        tft.setCursor(35, 38);
        tft.print(*dData->pSystolicPressCorrected);                                               //print the value of the corrected syst pointer that is in the display struct on the display
        tft.print("  ");
        tft.setTextSize(2);
        tft.setCursor(165, 45);
        tft.print(" mmHg ");                                                                   //print "mm Hg" on display

        tft.setTextSize(3);
        tft.setTextColor(YELLOW, BLACK);
        tft.setCursor(8, 68);
        tft.print("D");                                                                      //print "Dias:" on display
        tft.setTextColor(WHITE, BLACK);
        tft.setCursor(35, 68);
        tft.print(*dData->pDiastolicPressCorrected);                                              //print the value of the corrected dia pointer that is in the display struct on the display
        tft.print("  ");
        tft.setTextSize(2);
        tft.setCursor(165, 75);
        tft.print(" mmHg ");                                                                   //print "mm Hg" on display

        tft.setTextSize(3);
        tft.setTextColor(YELLOW, BLACK);
        tft.setCursor(8, 98);
        tft.print("P");                                                                      //print "Puls:" on display
        tft.setTextColor(WHITE, BLACK);
        tft.setCursor(35, 98);
        tft.print(*dData->pPulseRateCorrected);                                                   //print the value of the corrected pulse pointer that is in the display struct on the display
        tft.print("  ");
        tft.setTextSize(2);
        tft.setCursor(165, 105);
        tft.print(" BPM ");
    }

    tft.setTextSize(2);
    tft.fillRoundRect(80, 225, 80, 40, 8, RED);
    tft.drawRoundRect(80, 225, 80, 40, 8, WHITE);
    tft.setCursor(95, 235);
    tft.setTextColor(WHITE);
    tft.println("menu");
    if (p.x > 50 && p.x < 190 && p.y > 275 && p.y < 315) {
        tft.fillRoundRect(50, 275, 140, 40, 8, RED);
        Serial.println("HERE");
    } else {
        tft.fillRoundRect(50, 275, 140, 40, 8, BLUE);
    }

    tft.drawRoundRect(50, 275, 140, 40, 8, WHITE);
    tft.setCursor(60, 285);
    tft.setTextColor(WHITE);
    tft.println("annunciate");

}

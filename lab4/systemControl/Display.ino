#include "Display.h"                                                                          //import the header of this function
#include "dataStructs.h"                                                                      //import the variables
#include <stdio.h>                                                                            //import necessary header files
#include <stdbool.h>                                                                          //import necessary header files
#include <stddef.h>                                                                           //import necessary header files

int annunciation = 1;                                                                         //initialize boolean values for this file
boolean bool_T = false;                                                                       //initialize boolean values for this file
boolean bool_S = false;                                                                       //initialize boolean values for this file
boolean bool_D = false;                                                                       //initialize boolean values for this file
boolean bool_P = false;                                                                       //initialize boolean values for this file
boolean bool_R = false;

boolean tempflash = true;
boolean pulseflash = true;
boolean spressflash = true;
boolean dpressflash = true;

void inverseT() {
    tempflash = !tempflash;
}

void inverseP() {
    pulseflash = !pulseflash;
}

void inverseS() {
    spressflash = !spressflash;
}

void inverseD() {
    dpressflash = !dpressflash;
}

TimedAction tflash = TimedAction(1000, inverseT);            //initalize TimedAction to make sure function runs only every Xms
TimedAction pflash = TimedAction(2000, inverseP);            //initalize TimedAction to make sure function runs only every Xms
TimedAction sflash = TimedAction(500, inverseS);            //initalize TimedAction to make sure function runs only every Xms
TimedAction dflash = TimedAction(500, inverseD);            //initalize TimedAction to make sure function runs only every Xms

void displayFunction(void* displayDataStruct){                                                //function that display the data on the TFT LCD display, takes display struct as input
    struct controlDisplayData *dData = (struct controlDisplayData*) displayDataStruct;        //deference the display struct
    dData->pTempCorrected           = &tempComputedData;                                         //assign corrected temp's address to corrected temp pointer from display struct
    dData->pSystolicPressCorrected  = &sysComputedData;                                //assign corrected sys's address to corrected sys pointer from display struct
    dData->pDiastolicPressCorrected = &diaComputedData;                               //assign corrected dia's address to corrected dia pointer from display struct
    dData->pPulseRateCorrected      = &pulseComputedData;                                    //assign corrected pulse's address to corrected pulse pointer from display struct
    dData->pRespCorrected           = &respComputedData;
    dData->pBatteryState            = &batteryState;                                          //assign battery state's address to battery state pointer from display struct

    if (annunciate.justPressed()) {                                                           //execute if annunciate button is just pressed
        annunciate.drawButton(true);                                                          // draw inverted button
        tft.fillScreen(BLACK);                                                                //fill the screen in black
        menu.drawButton();                                                                    // draw normal button
        annunciate.drawButton();                                                              // draw normal button
        display.drawButton();
        exp1.drawButton();                                                                    // draw normal button
        exp2.drawButton();                                                                    // draw normal button
        annunciation = 0;                                                                  //set annunciation bool to be true
    }
    if (annunciate.justReleased()) {                                                          //check if the button is just released
        annunciate.drawButton();                                                              // draw normal button
    }

    if (menu.justPressed()) {                                                                 //check if the button is just pressed
        menu.drawButton(true);                                                                // draw inverted button
        tft.fillScreen(BLACK);                                                                //fill the screen in black
        annunciate.drawButton();                                                              // draw normal button
        menu.drawButton();                                                                    // draw normal button
        display.drawButton();
        exp1.drawButton();                                                                    // draw normal button
        exp2.drawButton();                                                                    // draw normal button
        annunciation = 1;                                                                 //set annunciation bool to be false
    }
    if (menu.justReleased()) {                                                                //if button is just released, execute
        menu.drawButton();                                                                    // draw normal button
    }

    if (display.justPressed()) {                                                                 //check if the button is just pressed
        display.drawButton(true);                                                                // draw inverted button
        tft.fillScreen(BLACK);                                                                //fill the screen in black
        annunciate.drawButton();                                                              // draw normal button
        menu.drawButton();                                                                    // draw normal button
        exp1.drawButton();                                                                    // draw normal button
        display.drawButton();
        exp2.drawButton();                                                                    // draw normal button
        annunciation = 2;                                                                 //set annunciation bool to be false
    }
    if (display.justReleased()) {                                                                //if button is just released, execute
        display.drawButton();                                                                    // draw normal button
    }

    if (exp1.justPressed()) {                                                                 //if button is just pressed, execute
        exp1.drawButton(true);                                                                // draw inverted button
    }
    if (exp1.justReleased()) {                                                                //if button is just released, execute
        exp1.drawButton();                                                                    // draw normal button
    }

    if (exp2.justPressed()) {                                                                 //if button is just pressed, execute
        exp2.drawButton(true);                                                                // draw inverted button
    }
    if (exp2.justReleased()) {                                                                //if button is just released, execute
        exp2.drawButton();                                                                    // draw normal button
    }

    if (annunciation == 0) {                                                                       //execute if in annunciation page
        tft.setCursor(50, 0);                                                                  //move cursor to the begining of the display
        tft.setTextSize(2);                                                                   //set font size to be 2
        tft.setTextColor(WHITE, BLACK);                                                       //set font color to be white with black background
        tft.println("ANNUNCIATION");                                                  //print the string on display
        tft.setCursor(0, 25);                                                                 //print "results from patient" on display
        tft.print("Temp: ");                                                                  //print "Temp:" on display
        if (tempGoodBool == 0) {                                                              //if temperature is within range
            tft.setTextColor(GREEN, BLACK);                                                   //set font color to be green with black background
        } else if (tempGoodBool == 1){                                                        //if temperature is out of range
            //flash every second
            tflash.check();
            if (tempflash) {
                tft.setTextColor(ORANGE, BLACK);                                                  //set font color with black background
            } else {
                tft.setTextColor(BLACK, BLACK);
            }
        } else {                                                                              //if temperature is out of range for too long
            tft.setTextColor(RED, BLACK);                                                     //set font color to be red with black background
        }
        tft.print(dData->pTempCorrected->last());                                                   //print the last value of the corrected temp buffer
        tft.println(" C   ");                                                                 //print "C" on display

        tft.setTextColor(WHITE, BLACK);                                                       //set font color with black background
        tft.setCursor(0, 50);                                                                 //set font color to be white with black background
        tft.print("Syst: ");                                                                  //print "Syst:" on display
        if (sysGoodBool == 0) {                                                               //if systolic pres is within range
            tft.setTextColor(GREEN, BLACK);                                                   //set font color to be green with black background
        } else if (sysGoodBool == 1) {                                                        //if sys is out of range
            //flash every 0.5 second
            sflash.check();
            if (spressflash) {
                tft.setTextColor(ORANGE, BLACK);                                                  //set font color with black background
            } else {
                tft.setTextColor(BLACK, BLACK);
            }
        } else {                                                                              //if temperature is out of range for too long
            tft.setTextColor(RED, BLACK);                                                     //set font color to be red with black background
        }
        tft.print(dData->pSystolicPressCorrected->last());                                                    //print the last value of the corrected syst buffer
        tft.println(" mmHg ");                                                                //print "mm Hg" on display

        tft.setTextColor(WHITE, BLACK);                                                       //set font color with black background
        tft.setCursor(0, 75);                                                                 //set font color to be white with black background
        tft.print("Dias: ");                                                                  //print "Dias:" on display
        if (diaGoodBool == 0) {                                                               //if diastolic pres is within range
            tft.setTextColor(GREEN, BLACK);                                                   //set font color to be green with black background
        } else if (diaGoodBool == 1){                                                         //if dia is out of range
            //flash every 0.5 second
            dflash.check();
            if (dpressflash) {
                tft.setTextColor(ORANGE, BLACK);                                                  //set font color with black background
            } else {
                tft.setTextColor(BLACK, BLACK);
            }
        } else {                                                                              //if temperature is out of range for too long
            tft.setTextColor(RED, BLACK);                                                     //set font color to be red with black background
        }
        tft.print(dData->pDiastolicPressCorrected->last());                                                    //print the last value of the corrected dia buffer
        tft.println(" mmHg ");                                                                //print "mm Hg" on display

        tft.setTextColor(WHITE, BLACK);                                                       //set font color with black background
        tft.setCursor(0, 100);                                                                //set font color to be white with black background
        tft.print("Puls: ");                                                                  //print "Puls:" on display
        if (prGoodBool == 0) {                                                                //if pulse is within range
            tft.setTextColor(GREEN, BLACK);                                                   //set font color to be green with black background
        } else if (prGoodBool == 1) {                                                          //if pulse is out of range
            //flash every 2 sec
            pflash.check();
            if (pulseflash) {
                tft.setTextColor(ORANGE, BLACK);                                                  //set font color with black background
            } else {
                tft.setTextColor(BLACK, BLACK);
            }
        } else {                                                                              //if temperature is out of range for too long
            tft.setTextColor(RED, BLACK);                                                     //set font color to be red with black background
        }
        tft.print(dData->pPulseRateCorrected->last());                                                  //print the last value of the corrected pulse buffer
        tft.println(" BPM ");                                                                 //print "BPM" on display

        tft.setTextColor(WHITE, BLACK);                                                       //set font color with black background
        tft.setCursor(0, 125);                                                                //set font color to be white with black background
        tft.print("Resp: ");                                                                  //print "Batt:" on display
        if (rrGoodBool == 0) {                                                           //if battery is within range
            tft.setTextColor(GREEN, BLACK);                                                   //set font color to be green with black background
        } else if (rrGoodBool == 1) {                                                     //if battery is out of range
            tft.setTextColor(ORANGE, BLACK);                                                  //set font color with black background
        } else {                                                                              //if temperature is out of range for too long
            tft.setTextColor(RED, BLACK);                                                     //set font color to be red with black background
        }
        tft.print(dData->pRespCorrected->last());                                                  //print the last value of the corrected pulse buffer
        tft.println(" RR ");

        //TODO: fix coordinates
        tft.setTextColor(WHITE, BLACK);                                                       //set font color with black background
        tft.setCursor(0, 150);                                                                //set font color to be white with black background
        tft.print("Batt: ");                                                                  //print "Batt:" on display
        if (batteryGoodBool == 0) {                                                           //if battery is within range
            tft.setTextColor(GREEN, BLACK);                                                   //set font color to be green with black background
        } else if (batteryGoodBool == 1) {                                                     //if battery is out of range
            tft.setTextColor(ORANGE, BLACK);                                                  //set font color with black background
        } else {                                                                              //if temperature is out of range for too long
            tft.setTextColor(RED, BLACK);                                                     //set font color to be red with black background
        }
        tft.print((*dData->pBatteryState) / 2);                                               //print half of the value of the battery state pointer that is in the display struct on the display
        tft.println("%      ");                                                               //print "%" on display

    } else if (annunciation == 1) {                                                                                  //execute if in execute menu page
        tft.setTextSize(3);                                                                   //set font size to be 3
        tft.setTextColor(RED, BLACK);                                                         //set font color with black background
        tft.setCursor(75, 10);                                                                //move cursor to the specific x, y location on display
        tft.print("MENU");                                                                    //print the string on display
        tft.setTextColor(YELLOW, GREY);                                                      //set font color with black background
        tft.setCursor(8, 38);                                                                  //move cursor to the specific x, y location on display
        tft.print("T");
        if (bool_T) {                                                                         //execute if boolean color select is true
            tft.setTextColor(WHITE, BLACK);                                                   //set font color with black background
        } else {                                                                              //if false
            tft.setTextColor(BLACK, BLACK);                                                   //set font color with black background
        }
        tft.setCursor(35, 38);                                                                //move cursor to the specific x, y location on display
        tft.print(dData->pTempCorrected->last());                                                   //print the last value of the corrected temp buffer
        tft.print("  ");                                                                      //print the space on display
        tft.setTextSize(2);                                                                   //set font size to be 2
        tft.setCursor(165, 45);                                                               //move cursor to the specific x, y location on display
        tft.print(" C ");                                                                     //print "C" on display

        tft.setTextSize(3);                                                                   //set font size to be 3
        tft.setTextColor(YELLOW, GREY);                                                      //set font color with black background
        tft.setCursor(8, 75);                                                                 //move cursor to the specific x, y location on display
        tft.print("S");
        if (bool_S) {                                                                         //execute if boolean color select is true
            tft.setTextColor(WHITE, BLACK);                                                   //set font color with black background
        } else {                                                                              //if false
            tft.setTextColor(BLACK, BLACK);                                                   //set font color with black background
        }
        tft.setCursor(35, 75);                                                                //move cursor to the specific x, y location on display
        tft.print(dData->pSystolicPressCorrected->last());                                                    //print the last value of the corrected sys buffer
        tft.print("  ");                                                                      //print the space on display
        tft.setTextSize(2);                                                                   //set font size to be 2
        tft.setCursor(165, 82);                                                               //move cursor to the specific x, y location on display
        tft.print(" mmHg ");                                                                  //print "mm Hg" on display

        tft.setTextSize(3);                                                                   //set font size to be 3
        tft.setTextColor(YELLOW, GREY);                                                      //set font color with black background
        tft.setCursor(8, 112);                                                                //move cursor to the specific x, y location on display
        tft.print("D");
        if (bool_D) {                                                                         //execute if boolean color select is true
            tft.setTextColor(WHITE, BLACK);                                                   //set font color with black background
        } else {                                                                              //if false
            tft.setTextColor(BLACK, BLACK);                                                   //set font color with black background
        }
        tft.setCursor(35, 112);                                                               //move cursor to the specific x, y location on display
        tft.print(dData->pDiastolicPressCorrected->last());                                                    //print the last value of the corrected dia buffer
        tft.print("  ");                                                                      //print the space on display
        tft.setTextSize(2);                                                                   //set font size to be 2
        tft.setCursor(165, 119);                                                              //move cursor to the specific x, y location on display
        tft.print(" mmHg ");                                                                  //print "mm Hg" on display

        tft.setTextSize(3);                                                                   //set font size to be 3
        tft.setTextColor(YELLOW, GREY);                                                      //set font color with black background
        tft.setCursor(8, 149);                                                                //move cursor to the specific x, y location on display
        tft.print("P");
        if (bool_P) {                                                                         //execute if boolean color select is true
            tft.setTextColor(WHITE, BLACK);                                                   //set font color with black background
        } else {                                                                              //if false
            tft.setTextColor(BLACK, BLACK);                                                   //set font color with black background
        }
        tft.setCursor(35, 149);                                                               //move cursor to the specific x, y location on display
        tft.print(dData->pPulseRateCorrected->last());                                                  //print the value of the corrected pulse pointer that is in the display struct on the display
        tft.print("  ");                                                                      //print the space on display
        tft.setTextSize(2);                                                                   //set font size to be 2
        tft.setCursor(165, 156);                                                              //move cursor to the specific x, y location on display
        tft.print(" BPM ");                                                                   //print the string on display

        tft.setTextSize(3);                                                                   //set font size to be 3
        tft.setTextColor(YELLOW, GREY);                                                      //set font color with black background
        tft.setCursor(8, 186);
        tft.print("R");                                                              //move cursor to the specific x, y location on display
        if (bool_R) {                                                                         //execute if boolean color select is true
            tft.setTextColor(WHITE, BLACK);                                                   //set font color with black background
        } else {                                                                              //if false
            tft.setTextColor(BLACK, BLACK);                                                   //set font color with black background
        }
        tft.setCursor(35, 186);                                                               //move cursor to the specific x, y location on display
        tft.print(dData->pRespCorrected->last());                                                  //print the value of the corrected pulse pointer that is in the display struct on the display
        tft.print("  ");                                                                      //print the space on display
        tft.setTextSize(2);                                                                   //set font size to be 2
        tft.setCursor(165, 193);                                                              //move cursor to the specific x, y location on display
        tft.print(" RR ");
    } else { //display
        tft.setTextSize(3);                                                                   //set font size to be 3
        tft.setTextColor(RED, BLACK);                                                         //set font color with black background
        tft.setCursor(55, 5);                                                                //move cursor to the specific x, y location on display
        tft.print("DISPLAY");

        if (bool_T) {
            an_T.drawButton(true);
        } else {
            an_T.drawButton();                                                                    // draw normal button
        }
        if (an_T.justReleased()) {                                                             //if button is just pressed, execute
            bool_T = !bool_T;                                                                 //invert the boolean select
        }

        if (bool_S) {
            an_S.drawButton(true);
        } else {
            an_S.drawButton();                                                                    // draw normal button
        }                                                                   // draw normal button
        if (an_S.justReleased()) {                                                             //if button is just pressed, execute
            bool_S = !bool_S;                                                                 //invert the boolean select
        }

        if (bool_D) {
            an_D.drawButton(true);
        } else {
            an_D.drawButton();                                                                    // draw normal button
        }                                                                    // draw normal button
        if (an_D.justReleased()) {                                                             //if button is just pressed, execute
            bool_D = !bool_D;                                                                 //invert the boolean select
        }

        if (bool_P) {
            an_P.drawButton(true);
        } else {
            an_P.drawButton();                                                                    // draw normal button
        }                                                                   // draw normal button
        if (an_P.justReleased()) {                                                             //if button is just pressed, execute
            bool_P = !bool_P;                                                                 //invert the boolean select
        }

        if (bool_R) {
            an_R.drawButton(true);
        } else {
            an_R.drawButton();                                                                    // draw normal button
        }
        if (an_R.justReleased()) {                                                             //if button is just pressed, execute
            bool_R = !bool_R;                                                                 //invert the boolean select
        }
    }
}

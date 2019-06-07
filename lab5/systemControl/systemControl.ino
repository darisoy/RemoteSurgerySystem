#include <Elegoo_GFX.h>                                         // Core graphics library
#include <Elegoo_TFTLCD.h>                                      // Hardware-specific library
#include <TouchScreen.h>                                        // Touch screen library
#include <TimedAction.h>                                        // Timed-Action method library
#include <CircularBuffer.h>                                     // Circular buffer library

#define LCD_RESET A4                                            // Can alternately just connect to Arduino's reset pin
#define LCD_CS A3                                               // Chip Select goes to Analog 3
#define LCD_CD A2                                               // Command/Data goes to Analog 2
#define LCD_WR A1                                               // LCD Write goes to Analog 1
#define LCD_RD A0                                               // LCD Read goes to Analog 0
#define YP A3                                                   // must be an analog pin, use "An" notation!
#define XM A2                                                   // must be an analog pin, use "An" notation!
#define YM 9                                                    // can be a digital pin
#define XP 8                                                    // can be a digital pin

#define BLACK   0x0000                                          //set the keyword BLACK   to represent the number 0x0000
#define BLUE    0x001F                                          //set the keyword BLUE    to represent the number 0x001F
#define RED     0xF800                                          //set the keyword RED     to represent the number 0xF800
#define GREEN   0x07E0                                          //set the keyword GREEN   to represent the number 0x07E0
#define CYAN    0x07FF                                          //set the keyword CYAN    to represent the number 0x07FF
#define MAGENTA 0xF81F                                          //set the keyword MAGENTA to represent the number 0xF81F
#define YELLOW  0xFFE0                                          //set the keyword YELLOW  to represent the number 0xFFE0
#define WHITE   0xFFFF                                          //set the keyword WHITE   to represent the number 0xFFFF
#define ORANGE  0xFD20                                          //set the keyword ORGANE  to represent the number 0xFD20
#define GREY    0xC618                                           //set the keyword Grey    to represent the number 0xC618

#define UNOREQ 22                                                  // Initializes RED 22
#define UNOACK 23
#define WIFIREQ 53
#define WIFIACK 52
#define WARN 20
#define EKGPIN 82
#define BLUEPIN 28
#define REDPIN 27
#define WHITEPIN 30

#include "dataStructs.h"                                        // Iimport the variables used in the file
Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);   // TFT setup
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);              // Touch screen setup

void setup(void) {                                              //setup portion of the arduino code
    //Serial.begin(9600);                                         //initialize the serial with 9600 baud rate
    Serial1.begin(9600);                                        //initialize the serial1 with 9600 baud rate
    Serial2.begin(9600);
    tftSetup();                                                 //call the method that detects the TFT and it's version
    pinMode(UNOREQ, OUTPUT);                                       //setup pin 22 to be an output
    pinMode(UNOACK, OUTPUT);
    pinMode(WIFIREQ, INPUT);
    pinMode(WIFIACK, INPUT);
    pinMode(EKGPIN, INPUT);

    Serial.begin(115200);
    sampling_period_us = round(1000000*(1.0/SAMPLING_FREQUENCY));

    initialize();                                               //call the method that initalizes the variables
    measureT.functionPtr = measureFunction;                     //set the functionPtr of measureT to be the address of the measureFunction
    measureT.dataPtr = (void*) &MeasureData;                    //set the dataPtr of measureT to be the address of the MeasureData pointer
    measureT.timedActionPtr = &task0;                           //set the timedActionPtr of measureT to be the address of task0
    measureT.next = &EKGMeasureT;                                   //set the TCB pointer next to the address of statusT
    measureT.prev = &remoteComT;                                   //set the TCB pointer prev to the address of keypadT
    measureT.TCBname = 1;

    computeT.functionPtr = computeFunction;                     //set the functionPtr of computeT to be the computeFunction
    computeT.dataPtr = (void*) &ComputeData;                    //set the dataPtr of computeT to be the address of the ComputeData pointer
    computeT.timedActionPtr = &task1;                           //set the timedActionPtr of computeT to be the address of task1
    computeT.next = NULL;                                       //set the next TCB pointer to nothing
    computeT.prev = NULL;                                       //set the prev TCB pointer to nothing
    computeT.TCBname = 2;

    EKGMeasureT.functionPtr = EKGMeasureFunction;
    EKGMeasureT.dataPtr = (void*) &EKGData;
    EKGMeasureT.timedActionPtr = &task8;
    EKGMeasureT.next = &statusT;
    EKGMeasureT.prev = &measureT;
    EKGMeasureT.TCBname = 9;

    EKGProcessT.functionPtr = EKGProcessFunction;
    EKGProcessT.dataPtr = (void*) &EKGData;
    EKGProcessT.timedActionPtr = &task9;
    EKGProcessT.next = NULL;
    EKGProcessT.prev = NULL;
    EKGProcessT.TCBname = 10;

    statusT.functionPtr = statusFunction;                       //set the functionPtr of statusT to be the statusFunction
    statusT.dataPtr = (void*) &StatusData;                      //set the dataPtr of statusT to be the address of the StatusData pointer
    statusT.timedActionPtr = &task2;                            //set the timedActionPtr of statusT to be the address of task2
    statusT.next = &warningT;                                   //set the next TCB pointer to the address of warningT
    statusT.prev = &EKGMeasureT;                                   //set the prev TCB pointer to the address of measureT
    statusT.TCBname = 3;

    warningT.functionPtr = alarmFunction;                       //set the functionPtr of warningT to be the alarmFunction
    warningT.dataPtr = (void*) &AlarmData;                      //set the dataPtr of warningT to be the address of the AlarmData pointer
    warningT.timedActionPtr = &task3;                           //set the timedActionPtr of warningT to be the address of task3
    warningT.next = &displayT;                                  //set the next TCB pointer to the address of displayT
    warningT.prev = &statusT;                                   //set the prev TCB pointer to the address of statusT
    warningT.TCBname = 4;

    displayT.functionPtr = displayFunction;                     //set the functionPtr of displayT to be the displayFunction
    displayT.dataPtr = (void*) &DisplayData;                    //set the dataPtr of displayT to be the address of the DisplayData pointer
    displayT.timedActionPtr = &task4;                           //set the timedActionPtr of displayT to the address of task4
    displayT.next = &keypadT;                                   //set the next TCB pointer to the address of keypadT
    displayT.prev = &warningT;                                  //set the prev TCB pointer to the address of warningT
    displayT.TCBname = 5;

    keypadT.functionPtr = keypadFunction;                       //set the functionPtr of keypadT to be the keypadFunction
    keypadT.dataPtr = (void*) &KeypadData;                      //set the dataPtr of keypadT to be the address of the KeypadData cast as a void*
    keypadT.timedActionPtr = &task5;                            //set the timedActionPtr of keypadT to the address of task5
    keypadT.next = &communicationT;                             //set the next TCB pointer to the address of communicationT
    keypadT.prev = &displayT;                                   //set the prev TCB pointer to the address of displayT
    keypadT.TCBname = 6;

    communicationT.functionPtr = communicationFunction;         //set the functionPtr of communicationT to be the communicationFunction
    communicationT.timedActionPtr = &task6;                     //set the timedActionPtr of communicationT to be the address of task6
    communicationT.next = &remoteComT;                            //set the next TCB pointer to be the address of measureT
    communicationT.prev = &keypadT;                            //set the prev TCB pointer to be the address of displayT
    communicationT.TCBname = 7;

    remoteComT.functionPtr = remoteComFunction;
    remoteComT.dataPtr = (void*) &RemoteComData;
    remoteComT.timedActionPtr = &task7;
    remoteComT.next = &measureT;
    remoteComT.prev = &communicationT;
    remoteComT.TCBname = 8;

    trafficT.functionPtr = trafficFunction;
    trafficT.dataPtr = (void*) &trafficData;
    trafficT.next = NULL;
    trafficT.prev = NULL;
    trafficT.TCBname = 11;

    scheduler.front = &measureT;                                //set the front TCB pointer of scheduler to be the address of measureT
    scheduler.back = &remoteComT;                                  //set the back TCB pointer of scheduler to be the address of keypadT
    scheduler.placeholder = scheduler.front;                    //set the placeholder TCB pointer of scheduler to be equal to the scheduler.front TCB pointer
    scheduler.size = 8;                                         //set the size of scheduler to be 7
}

void loop(void) {                                               //code arduino constatly loops through
    schedulerFunctionRun(&scheduler);                           //run the schedulerFunctionRun on the placeholder TCB pointer
}


void tftSetup(void) {
    tft.reset();                                                        //resets the TFT LCD display
    uint16_t identifier = tft.readID();                                 //gets the id of the driver
    if(identifier == 0x9325) {                                          //checks if driver id is 0x9325
        Serial.println(F("Found ILI9325 LCD driver"));                  //prints the driver name on the serial monitor
    } else if(identifier == 0x9328) {                                   //checks if driver id is 0x9328
        Serial.println(F("Found ILI9328 LCD driver"));                  //prints the driver name on the serial monitor
    } else if(identifier == 0x4535) {                                   //checks if driver id is 0x4535
        Serial.println(F("Found LGDP4535 LCD driver"));                 //prints the driver name on the serial monitor
    }else if(identifier == 0x7575) {                                    //checks if driver id is 0x7575
        Serial.println(F("Found HX8347G LCD driver"));                  //prints the driver name on the serial monitor
    } else if(identifier == 0x9341) {                                   //checks if driver id is 0x9341
        Serial.println(F("Found ILI9341 LCD driver"));                  //prints the driver name on the serial monitor
    } else if(identifier == 0x8357) {                                   //checks if driver id is 0x8357
        Serial.println(F("Found HX8357D LCD driver"));                  //prints the driver name on the serial monitor
    } else if(identifier==0x0101){                                      //checks if driver id is 0x0101
        identifier=0x9341;                                              //sets the driver id to be 0x9341
        Serial.println(F("Found 0x9341 LCD driver"));                   //prints the driver name on the serial monitor
    } else if(identifier==0x1111){                                      //checks if driver id is 0x1111
        identifier=0x9328;                                              //sets the driver id to be 0x9341
        Serial.println(F("Found 0x9328 LCD driver"));                   //prints the driver name on the serial monitor
    } else {                                                            //if none of the previous ids match
        Serial.print(F("Unknown LCD driver chip: "));                   //prints on the serial monitor that it couldnt find driver name
        Serial.println(identifier, HEX);                                //prints the id it found
        Serial.println(F("If using the Elegoo 2.8\" TFT Arduino shield, the line:"));
        Serial.println(F("  #define USE_Elegoo_SHIELD_PINOUT"));
        Serial.println(F("should appear in the library header (Elegoo_TFT.h)."));
        Serial.println(F("If using the breakout board, it should NOT be #defined!"));
        Serial.println(F("Also if using the breakout, double-check that all wiring"));
        Serial.println(F("matches the tutorial."));
        identifier=0x9328;                                              //sets the driver id to be 0x9328

    }

    tft.begin(identifier);                                                          //initializes the LCD screen
    tft.setRotation(0);                                                             //set the screen to be potrait orientation
    tft.fillScreen(BLACK);                                                          //fills the screen with the color black
    menu.initButton(&tft, 40, 260, 60, 30, WHITE, BLUE, WHITE, "menu", 2);          // set location of button: x, y, w, h, outline, fill, text
    annunciate.initButton(&tft, 140, 300, 100, 30, WHITE, BLUE, WHITE, "announ", 2); // set location of button: x, y, w, h, outline, fill, text
    display.initButton(&tft, 40, 300, 60, 30, WHITE, BLUE, WHITE, "disp", 2); // set location of button: x, y, w, h, outline, fill, text
    exp1.initButton(&tft, 120, 260, 60, 30, WHITE, BLUE, WHITE, "exp1", 2);         // set location of button: x, y, w, h, outline, fill, text
    exp2.initButton(&tft, 200, 260, 60, 30, WHITE, BLUE, WHITE, "exp2", 2);         // set location of button: x, y, w, h, outline, fill, text
    an_T.initButton(&tft, 120, 50, 150, 30, BLACK, GREY, YELLOW, "temperature", 2);             // set location of button: x, y, w, h, outline, fill, text
    an_S.initButton(&tft, 120, 85, 150, 30, BLACK, GREY, YELLOW, "sys press", 2);             // set location of button: x, y, w, h, outline, fill, text
    an_D.initButton(&tft, 120, 120, 150, 30, BLACK, GREY, YELLOW, "dia press", 2);            // set location of button: x, y, w, h, outline, fill, text
    an_P.initButton(&tft, 120, 155, 150, 30, BLACK, GREY, YELLOW, "pulse", 2);            // set location of button: x, y, w, h, outline, fill, text
    an_R.initButton(&tft, 120, 190, 150, 30, BLACK, GREY, YELLOW, "respiration", 2);            // set location of button: x, y, w, h, outline, fill, text
    an_E.initButton(&tft, 120, 225, 150, 30, BLACK, GREY, YELLOW, "ekg", 2);
    ack_T.initButton(&tft, 230, 30, 20, 20, BLACK, RED, BLACK, "", 3);              // set location of button: x, y, w, h, outline, fill, text
    ack_S.initButton(&tft, 230, 56, 20, 20, BLACK, RED, BLACK, "", 3);              // set location of button: x, y, w, h, outline, fill, text
    ack_D.initButton(&tft, 230, 82, 20, 20, BLACK, RED, BLACK, "", 3);              // set location of button: x, y, w, h, outline, fill, text
    ack_P.initButton(&tft, 230, 108, 20, 20, BLACK, RED, BLACK, "", 3);             // set location of button: x, y, w, h, outline, fill, text
    ack_R.initButton(&tft, 230, 134, 20, 20, BLACK, RED, BLACK, "", 3);             // set location of button: x, y, w, h, outline, fill, text
    ack_E.initButton(&tft, 230, 160, 20, 20, BLACK, RED, BLACK, "", 3);
    ack_B.initButton(&tft, 230, 188, 20, 20, BLACK, RED, BLACK, "", 3);             // set location of button: x, y, w, h, outline, fill, text

    menu.drawButton();                                                              //draw normal button
    annunciate.drawButton();                                                        //draw normal button
    display.drawButton();
    exp1.drawButton();                                                              //draw normal button
    exp2.drawButton();                                                              //draw normal button
}

void initialize(void) {
    tempRawData.push(75);             //initializes the raw temp value to be 0
    sysRawData.push(80);           //initializes the raw systolic value to be 0
    diaRawData.push(80);          //initializes the raw diastolic value to be 0
    pulseRawData.push(0);               //initializes the raw pulse rate value to be 0
    respRawData.push(0);
    ekgData.push(0);
    batteryState = 200;             //initialized the battery value to be 200

    tempGoodBool = true;            //initialize warning boolean for temp to be true
    sysGoodBool = true;             //initialize warning boolean for systolic to be true
    diaGoodBool = true;             //initialize warning boolean for diastolic to be true
    prGoodBool = true;              //initialize warning boolean for pulse to be true
    batteryGoodBool = true;         //initialize warning boolean for battery to be true

    tempMeasure = 0;                //initialize the tempMeasure value to be 0
    sysMeasure = 0;                 //initialize the sysMeasure value to be 0
    diaMeasure = 0;                 //initialize the diaMeasure value to be 0
    prMeasure = 0;                  //initialize the prMeasure value to be 0
    batMeasure = 0;                 //initialize the batMeasure value to be 0
    runCompute = false;              //initialize the compute boolean to be true
    runEKGProcess = false;

    wifiAckowledge = true;

    pinHighPS = false;              //set the inital state for pin mode
    pinHighNS = false;              //set the inital state for pin mode

<<<<<<< HEAD
    displayEnabled = true;
=======
    displayEnabled = false;
>>>>>>> 537929fd5c39a22d166f377c00b0b6c80bcfbf03
}

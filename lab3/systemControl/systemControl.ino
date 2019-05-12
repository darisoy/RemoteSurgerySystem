#include <Elegoo_GFX.h>                                         // Core graphics library
#include <Elegoo_TFTLCD.h>                                      // Hardware-specific library
#include <TouchScreen.h>
#include <TimedAction.h>
#include <CircularBuffer.h>

#define LCD_RESET A4                                            // Can alternately just connect to Arduino's reset pin
#define LCD_CS A3                                               // Chip Select goes to Analog 3
#define LCD_CD A2                                               // Command/Data goes to Analog 2
#define LCD_WR A1                                               // LCD Write goes to Analog 1
#define LCD_RD A0                                               // LCD Read goes to Analog 0
#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin

#define BLACK   0x0000                                          //set the keyword BLACK   to represent the number 0x0000
#define BLUE    0x001F                                          //set the keyword BLUE    to represent the number 0x001F
#define RED     0xF800                                          //set the keyword RED     to represent the number 0xF800
#define GREEN   0x07E0                                          //set the keyword GREEN   to represent the number 0x07E0
#define CYAN    0x07FF                                          //set the keyword CYAN    to represent the number 0x07FF
#define MAGENTA 0xF81F                                          //set the keyword MAGENTA to represent the number 0xF81F
#define YELLOW  0xFFE0                                          //set the keyword YELLOW  to represent the number 0xFFE0
#define WHITE   0xFFFF                                          //set the keyword WHITE   to represent the number 0xFFFF
#define ORANGE  0xFD20
#define GREY   0xC618

#define REQ 22
#include "dataStructs.h" //import the variables used in the file
Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

void setup(void) {                                              //setup portion of the arduino code
    Serial.begin(9600);                                         //initialize the serial with 9600 baud rate
    Serial1.begin(9600);                                        //initialize the serial1 with 9600 baud rate
    tftSetup();                                                 //call the method that detects the TFT and it's version
    pinMode(REQ, OUTPUT);                                   //setup pin 22 to be an output
    initialize();                                               //call the method that initalizes the variables
    measureT.functionPtr = measureFunction;
    measureT.dataPtr = (void*) &MeasureData;                    //set the dataPtr of measureT to be the address of the MeasureData pointer
    measureT.timedActionPtr = &task0;
    measureT.next = &computeT;
    measureT.prev = &keypadT;                                                //assign raw pulse's address to raw pulse pointer from compute struct

    computeT.functionPtr = computeFunction;                     //set the functionPtr of computeT to be the computeFunction
    computeT.dataPtr = (void*) &ComputeData;                    //set the dataPtr of computeT to be the address of the ComputeData pointer
    computeT.timedActionPtr = &task1;
    computeT.next = &statusT;
    computeT.prev = &measureT;

    statusT.functionPtr = statusFunction;                       //set the functionPtr of statusT to be the statusFunction
    statusT.dataPtr = (void*) &StatusData;                      //set the dataPtr of statusT to be the address of the StatusData pointer
    statusT.timedActionPtr = &task2;
    statusT.next = &warningT;
    statusT.prev = &computeT;

    warningT.functionPtr = alarmFunction;                       //set the functionPtr of warningT to be the alarmFunction
    warningT.dataPtr = (void*) &AlarmData;                      //set the dataPtr of warningT to be the address of the AlarmData pointer
    warningT.timedActionPtr = &task3;
    warningT.next = &displayT;
    warningT.prev = &statusT;

    displayT.functionPtr = displayFunction;                     //set the functionPtr of displayT to be the displayFunction
    displayT.dataPtr = (void*) &DisplayData;                    //set the dataPtr of displayT to be the address of the DisplayData pointer
    displayT.timedActionPtr = &task4;
    displayT.next = &keypadT;
    displayT.prev = &warningT;

    keypadT.functionPtr = keypadFunction;
    keypadT.dataPtr = (void*) &KeypadData;
    keypadT.timedActionPtr = &task5;
    keypadT.next = &measureT;
    keypadT.prev = &displayT;

    

    scheduler.front = &measureT;
    scheduler.back = &keypadT;
    scheduler.placeholder = scheduler.front;
    scheduler.size = 6;
}

void loop(void) {                                               //code arduino constatly loops through
    schedulerFunctionRun(&scheduler);
    // task0.check();
    // task1.check();
    // task2.check();
    // task3.check();
    // task4.check();
    // task5.check();
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
    tft.begin(identifier);                                              //initializes the LCD screen
    tft.setRotation(0);
    tft.fillScreen(BLACK);                                              //fills the screen with the color black
    menu.initButton(&tft, 50, 240, 80, 40, WHITE, BLUE, WHITE, "menu", 2); // x, y, w, h, outline, fill, text
    annunciate.initButton(&tft, 60, 290, 100, 40, WHITE, BLUE, WHITE, "announ", 2);
    exp1.initButton(&tft, 180, 240, 80, 40, WHITE, BLUE, WHITE, "exp1", 2);
    exp2.initButton(&tft, 180, 290, 80, 40, WHITE, BLUE, WHITE, "exp2", 2);
    an_T.initButton(&tft, 18, 50, 30, 30, BLACK, GREY, YELLOW, "T", 3);
    an_S.initButton(&tft, 18, 87, 30, 30, BLACK, GREY, YELLOW, "S", 3);
    an_D.initButton(&tft, 18, 124, 30, 30, BLACK, GREY, YELLOW, "D", 3);
    an_P.initButton(&tft, 18, 161, 30, 30, BLACK, GREY, YELLOW, "P", 3);
    ack_T.initButton(&tft, 220, 30, 20, 20, BLACK, RED, BLACK, "", 3);
    ack_S.initButton(&tft, 220, 57, 20, 20, BLACK, RED, BLACK, "", 3);
    ack_D.initButton(&tft, 220, 84, 20, 20, BLACK, RED, BLACK, "", 3);
    ack_P.initButton(&tft, 220, 111, 20, 20, BLACK, RED, BLACK, "", 3);
    ack_B.initButton(&tft, 220, 138, 20, 20, BLACK, RED, BLACK, "", 3);
    menu.drawButton();
    annunciate.drawButton();
    exp1.drawButton();
    exp2.drawButton();
}

void initialize(void) {
    temperatureRaw = 0;             //initializes the raw temp value to be 0
    systolicPressRaw = 0;           //initializes the raw systolic value to be 0
    diastolicPressRaw = 0;          //initializes the raw diastolic value to be 0
    pulseRateRaw = 0;               //initializes the raw pulse rate value to be 0
    batteryState = 200;             //initialized the battery value to be 200

    tempCorrected = 0;              //initalizes the corrected temp value to be 0
    systolicPressCorrected = 0;     //initalizes the corrected systolic value to be 0
    diastolicPressCorrected = 0;    //initalizes the corrected diastolic value to be 0
    pulseRateCorrected = 0;         //initalizes the corrected pulse rate value to be 0

    tempGoodBool = true;            //initialize warning boolean for temp to be true
    sysGoodBool = true;             //initialize warning boolean for systolic to be true
    diaGoodBool = true;             //initialize warning boolean for diastolic to be true
    prGoodBool = true;              //initialize warning boolean for pulse to be true
    batteryGoodBool = true;         //initialize warning boolean for battery to be true

    tempMeasure = 0;
    sysMeasure = 0;
    diaMeasure = 0;
    prMeasure = 0;
    batMeasure = 0;

    // for (int counter = 0; counter < 8; counter++) {
    //     tempRawData.push(counter * 4 + 12);
    //     sysRawData.push(counter * 4 + 12);
    //     diaRawData.push(counter * 4 + 12);
    //     pulseRawData.push(counter * 4 + 12);
    //
    //     tempComputedData.push(counter * 4 + 12);
    //     sysComputedData.push(counter * 4 + 12);
    //     diaComputedData.push(counter * 4 + 12);
    //     pulseComputedData.push(counter * 4 + 12);
    // }
}

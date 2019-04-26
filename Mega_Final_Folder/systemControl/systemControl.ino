#include <Elegoo_GFX.h>    // Core graphics library
#include <Elegoo_TFTLCD.h> // Hardware-specific library

#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

// Assign human-readable names to some common 16-bit color values:
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define TEM_REQ 22
#define SYS_REQ 23
#define DIA_REQ 24
#define PUL_REQ 25

//Pass in dataStructs.h
#include "dataStructs.h"
Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
void setup(void) {
    Serial.begin(9600);
    Serial1.begin(9600);

    tftSetup();

    pinMode(TEM_REQ, OUTPUT);
    pinMode(SYS_REQ, OUTPUT);
    pinMode(DIA_REQ, OUTPUT);
    pinMode(PUL_REQ, OUTPUT);

    initialize();
    measureT.functionPtr = measureFunction;
    measureT.dataPtr = (void*) &MeasureData;
    taskQueue[0] = measureT;
    computeT.functionPtr = computeFunction;
    computeT.dataPtr = (void*) &ComputeData;
    taskQueue[1] = computeT;
    statusT.functionPtr = statusFunction;
    statusT.dataPtr = (void*) &StatusData;
    taskQueue[2] = statusT;
    warningT.functionPtr = alarmFunction;
    warningT.dataPtr = (void*) &AlarmData;
    taskQueue[3] = warningT;
    displayT.functionPtr = displayFunction;
    displayT.dataPtr = (void*) &DisplayData;
    taskQueue[4] = displayT;
    
}

int timer;
char dataTransfered[5];

//The task queue is filled with void structs
void loop(void) {
    int start0 = -6000;
    int start1 = -6000;
    int start2 = -6000;
    int start3 = -6000;
    int start4 = -6000;
    
    if (millis() - start0 >= 5000) {
      start0 = millis();
      taskQueue[0].functionPtr(taskQueue[0].dataPtr);
    }

    if (millis() - start1 >= 5000) {
      start1 = millis();
    taskQueue[1].functionPtr(taskQueue[1].dataPtr);
    }

    if (millis() - start2 >= 5000) {
      start2 = millis();
    taskQueue[2].functionPtr(taskQueue[2].dataPtr);
    }
    
    if (millis() - start3 >= 5000) {
      start3 = millis();
    taskQueue[3].functionPtr(taskQueue[3].dataPtr);
    }
    
    if (millis() - start4 >= 5000) {
      start4 = millis();
    taskQueue[4].functionPtr(taskQueue[4].dataPtr);
    }
    
    timer++;
    if (timer > 15) {
        timer = 0;
    }
    if (timer == 0) {
        digitalWrite(TEM_REQ, HIGH);
    } else {
        digitalWrite(TEM_REQ, LOW);
    }
    if (timer == 4) {
        digitalWrite(SYS_REQ, HIGH);
    } else {
        digitalWrite(SYS_REQ, LOW);
    }
    if (timer == 8) {
        digitalWrite(DIA_REQ, HIGH);
    } else {
        digitalWrite(DIA_REQ, LOW);
    }
    if (timer == 12) {
        digitalWrite(PUL_REQ, HIGH);
    } else {
        digitalWrite(PUL_REQ, LOW);
    }
}

void tftSetup() {
    tft.reset();

    uint16_t identifier = tft.readID();
    if (identifier == 0x9325) {
        Serial.println(F("Found ILI9325 LCD driver"));
    } else if(identifier == 0x9328) {
        Serial.println(F("Found ILI9328 LCD driver"));
    } else if(identifier == 0x4535) {
        Serial.println(F("Found LGDP4535 LCD driver"));
    }else if(identifier == 0x7575) {
        Serial.println(F("Found HX8347G LCD driver"));
    } else if(identifier == 0x9341) {
        Serial.println(F("Found ILI9341 LCD driver"));
    } else if(identifier == 0x8357) {
        Serial.println(F("Found HX8357D LCD driver"));
    } else if(identifier==0x0101) {
        identifier=0x9341;
        Serial.println(F("Found 0x9341 LCD driver"));
    }
    else if(identifier==0x1111) {
        identifier=0x9328;
        Serial.println(F("Found 0x9328 LCD driver"));
    }
    else {
        Serial.print(F("Unknown LCD driver chip: "));
        Serial.println(identifier, HEX);
        Serial.println(F("If using the Elegoo 2.8\" TFT Arduino shield, the line:"));
        Serial.println(F("  #define USE_Elegoo_SHIELD_PINOUT"));
        Serial.println(F("should appear in the library header (Elegoo_TFT.h)."));
        Serial.println(F("If using the breakout board, it should NOT be #defined!"));
        Serial.println(F("Also if using the breakout, double-check that all wiring"));
        Serial.println(F("matches the tutorial."));
        identifier=0x9328;
    }
    tft.begin(identifier);
    tft.fillScreen(BLACK);
}

void initialize() {
    //raw data
    temperatureRaw = 0;
    systolicPressRaw = 0;
    diastolicPressRaw = 0;
    pulseRateRaw = 0;
    batteryState = 200;

    //computed data
    tempCorrected = 0;
    systolicPressCorrected = 0;
    diastolicPressCorrected = 0;
    pulseRateCorrected = 0;

    //warning booleans
    tempGoodBool = true;
    sysGoodBool = true;
    diaGoodBool = true;
    prGoodBool = true;
    batteryGoodBool = true;

    timer = 0;
}

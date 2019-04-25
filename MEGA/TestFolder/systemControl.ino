//#include <Elegoo_GFX.h>    // Core graphics library
//#include <Elegoo_TFTLCD.h> // Hardware-specific library

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
}

int timer;
char dataTransfered[5];
void* taskQueue[7];

//The task queue is filled with void structs 
void loop(void) {
  taskQueue[0] = measureTCB;
  taskQueue[1] = intraComTCB;
  taskqueue[2] = computeTCB;
  taskQueue[3] = statusTCB;
  taskQueue[4] = warningTCB;
  taskqueue[5] = displayTCB;
  
    sendMeasure();
    measureFunction(measureData);
    compute();
    calculateWarnings();
    displayResults();
    timer++;
    if (timer > 15) {
        timer = 0;
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

    measureFunctionPtr = &measureFunction;
    measureDataPtr = &measureData;
}

void sendMeasure() {
    if (timer == 3) {
        digitalWrite(TEM_REQ, HIGH);
    } else {
        digitalWrite(TEM_REQ, LOW);
    }
    if (timer == 6) {
        digitalWrite(SYS_REQ, HIGH);
    } else {
        digitalWrite(SYS_REQ, LOW);
    }
    if (timer == 9) {
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

void compute() {
    tempCorrected = 5 + (0.75 * temperatureRaw);
    systolicPressCorrected = 9 + (2 * systolicPressRaw);
    diastolicPressCorrected = 6 + (1.5 * diastolicPressRaw);
    pulseRateCorrected = 8 + (3 * pulseRateRaw);
    batteryState--;
    if (batteryState <= 1) {
        batteryState = 200;
    }
}

void calculateWarnings() {
    tempGoodBool = (tempCorrected <= 37.8) && (tempCorrected >= 36.1);
    sysGoodBool = (systolicPressCorrected == 120);
    diaGoodBool = (diastolicPressCorrected == 80);
    prGoodBool = (pulseRateCorrected > 60.0) && (pulseRateCorrected < 100.0);
    batteryGoodBool = (batteryState >= 40);
}

void displayResults() {
    tft.setCursor(0, 0);
    tft.setTextSize(2);

    tft.setTextColor(WHITE, BLACK);
    tft.println("results from patient");
    tft.print("Temp: ");
    if (tempGoodBool) {
        tft.setTextColor(GREEN, BLACK);
    } else {
        tft.setTextColor(RED, BLACK);
    }
    tft.print(tempCorrected);
    tft.println(" C   ");

    tft.setTextColor(WHITE, BLACK);
    tft.print("Syst: ");
    if (sysGoodBool) {
        tft.setTextColor(GREEN, BLACK);
    } else {
        tft.setTextColor(RED, BLACK);
    }
    tft.print(systolicPressCorrected);
    tft.println(" mm Hg ");

    tft.setTextColor(WHITE, BLACK);
    tft.print("Dias: ");
    if (diaGoodBool) {
        tft.setTextColor(GREEN, BLACK);
    } else {
        tft.setTextColor(RED, BLACK);
    }
    tft.print(diastolicPressCorrected);
    tft.println(" mm Hg ");

    tft.setTextColor(WHITE, BLACK);
    tft.print("Puls: ");
    if (prGoodBool) {
        tft.setTextColor(GREEN, BLACK);
    } else {
        tft.setTextColor(RED, BLACK);
    }
    tft.print(pulseRateCorrected);
    tft.println(" BPM ");

    tft.setTextColor(WHITE, BLACK);
    tft.print("Batt: ");
    if (batteryGoodBool) {
        tft.setTextColor(GREEN, BLACK);
    } else {
        tft.setTextColor(RED, BLACK);
    }
    int batteryPercentage = batteryState / 2;
    tft.print(batteryPercentage);
    tft.println("%      ");
    tft.println("                     ");
    tft.println("                     ");
    tft.println("                     ");
    tft.println("                     ");
}


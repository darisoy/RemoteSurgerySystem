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

Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
void setup(void) {
    Serial.begin(9600);
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
    Serial1.begin(9600);
}

//raw data
double temperatureRaw = 0;
double systolicPressRaw = 0;
double diastolicPressRaw = 0;
double pulseRateRaw = 0;
double batteryState = 0;

//computed data
double tempCorrected = 0;
double sysCorrected = 0;
double diasCorrected = 0;
double prCorrected = 0;

//warning booleans
boolean tempGoodBool = true;
boolean sysGoodBool = true;
boolean diaGoodBool = true;
boolean prGoodBool = true;
boolean batteryGoodBool = true;

int timer = 0;
char dataTransfered[5];

void loop(void) {

    //Serial1.readBytes(testing, 20);
    // if (testing[0] == 'T' && testing[4] == 'S' && testing[8] == 'D' && testing[12] == 'P' && testing[16] == 'B') {
    //     temperatureRaw = ((testing[1] - '0') * 100) + ((testing[2] - '0') * 10) + ((testing[3] - '0') * 1);
    //     systolicPressRaw = ((testing[5] - '0') * 100) + ((testing[6] - '0') * 10) + ((testing[7] - '0') * 1);
    //     diastolicPressRaw = ((testing[9] - '0') * 100) + ((testing[10] - '0') * 10) + ((testing[11] - '0') * 1);
    //     pulseRateRaw = ((testing[13] - '0') * 100) + ((testing[14] - '0') * 10) + ((testing[15] - '0') * 1);
    //     batteryState  = ((testing[17] - '0') * 100) + ((testing[18] - '0') * 10) + ((testing[19] - '0') * 1);
    // }

    Serial1.readBytes(dataTransfered, 5);
    if (timer % 100 == 0) {
        Serial1.println("TRXXX");
    }
    if (timer % 200 == 0) {
        Serial1.println("SRXXX");
    }
    if (timer % 300 == 0) {
        Serial1.println("DRXXX");
    }
    if (timer % 400 == 0) {
        Serial1.println("PRXXX");
    }
    if (timer % 500 == 0) {
        Serial1.println("BRXXX");
    }

    if (dataTransfered[0] == 'T' && dataTransfered[1] == 'V') {
        temperatureRaw = ((dataTransfered[2] - '0') * 100) + ((dataTransfered[3] - '0') * 10) + ((dataTransfered[4] - '0') * 1);
        tempCorrected = 5 + (0.75 * temperatureRaw);
    }
    if (dataTransfered[0] == 'S' && dataTransfered[1] == 'V') {
        systolicPressRaw = ((dataTransfered[2] - '0') * 100) + ((dataTransfered[3] - '0') * 10) + ((dataTransfered[4] - '0') * 1);
        sysCorrected = 9 + (2 * systolicPressRaw);
    }
    if (dataTransfered[0] == 'D' && dataTransfered[1] == 'V') {
        diastolicPressRaw = ((dataTransfered[2] - '0') * 100) + ((dataTransfered[3] - '0') * 10) + ((dataTransfered[4] - '0') * 1);
        diasCorrected = 6 + (1.5 * diastolicPressRaw);
    }
    if (dataTransfered[0] == 'P' && dataTransfered[1] == 'V') {
        pulseRateRaw = ((dataTransfered[2] - '0') * 100) + ((dataTransfered[3] - '0') * 10) + ((dataTransfered[4] - '0') * 1);
        prCorrected = 8 + (3 * pulseRateRaw);
    }
    if (dataTransfered[0] == 'B' && dataTransfered[1] == 'V') {
        batteryState = ((dataTransfered[2] - '0') * 100) + ((dataTransfered[3] - '0') * 10) + ((dataTransfered[4] - '0') * 1);
    }
    calculateWarnings();
    displayResults();
}

void calculateWarnings() {
    tempGoodBool = (tempCorrected <= 37.8) && (tempCorrected >= 36.1);
    sysGoodBool = (sysCorrected == 120);
    diaGoodBool = (diasCorrected == 80);
    prGoodBool = (prCorrected >= 60) && (prCorrected <= 100);
    batteryGoodBool = (batteryState >= 20);
}

void displayResults() {
    tft.setCursor(0, 0);
    tft.setTextSize(2);

    tft.setTextColor(WHITE, BLACK);
    tft.println("results from patient:");
    tft.print("Temperature: ");
    if (tempGoodBool) {
        tft.setTextColor(GREEN, BLACK);
    } else {
        tft.setTextColor(RED, BLACK);
    }
    tft.print(tempCorrected);
    tft.println(" C   ");

    tft.setTextColor(WHITE, BLACK);
    tft.print("Systolic P: ");
    if (sysGoodBool) {
        tft.setTextColor(GREEN, BLACK);
    } else {
        tft.setTextColor(RED, BLACK);
    }
    tft.print(sysCorrected);
    tft.println(" mm Hg ");

    tft.setTextColor(WHITE, BLACK);
    tft.print("Diastolic P: ");
    if (diaGoodBool) {
        tft.setTextColor(GREEN, BLACK);
    } else {
        tft.setTextColor(RED, BLACK);
    }
    tft.print(diasCorrected);
    tft.println(" mm Hg ");

    tft.setTextColor(WHITE, BLACK);
    tft.print("Pulse rate: ");
    if (prCorrected) {
        tft.setTextColor(GREEN, BLACK);
    } else {
        tft.setTextColor(RED, BLACK);
    }
    tft.print(prCorrected);
    tft.println(" BPM ");

    tft.setTextColor(WHITE, BLACK);
    tft.print("Batter: ");
    if (batteryGoodBool) {
        tft.setTextColor(GREEN, BLACK);
    } else {
        tft.setTextColor(RED, BLACK);
    }
    tft.print(batteryState);
    tft.println("   ");
    timer++;
}

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

double temp = 0;
double sys = 0;
double d = 0;
double pres = 0;
double bat = 0;
char testing[20];

void loop(void) {
    Serial1.readBytes(testing, 20);
    Serial.println(testing);
    if (testing[0] == 'T') {
        tft.setCursor(0, 0);
        tft.setTextColor(GREEN, BLACK);
        tft.setTextSize(2);
        tft.println("results from UNO:");
        temp = ((testing[1] - '0') * 100) + ((testing[2] - '0') * 10) + ((testing[3] - '0') * 1);
        sys  = ((testing[5] - '0') * 100) + ((testing[6] - '0') * 10) + ((testing[7] - '0') * 1);
        d    = ((testing[9] - '0') * 100) + ((testing[10] - '0') * 10) + ((testing[11] - '0') * 1);
        pres = ((testing[13] - '0') * 100) + ((testing[14] - '0') * 10) + ((testing[15] - '0') * 1);
        bat  = ((testing[17] - '0') * 100) + ((testing[18] - '0') * 10) + ((testing[19] - '0') * 1);
        tft.print("temp = ");
        tft.print(temp);
        tft.println("   ");
        tft.print("sys  = ");
        tft.print(sys);
        tft.println("   ");
        tft.print("dia  = ");
        tft.print(d);
        tft.println("   ");
        tft.print("pres = ");
        tft.print(pres);
        tft.println("   ");
        tft.print("bat  = ");
        tft.print(bat);
        tft.println("   ");
    }
}

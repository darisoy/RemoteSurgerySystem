//Peripheral Subsystem
#include  "dataStructs.h"
#include "Measure.h"

//variables for the measurement function
int tempCount;
int pulseCount;
int sysCount;
int diaCount;
int tempBool;
int pulseBool;
int* pDiastolicFunction;
int* pSystolicFunction;

void setup() {
    initialize();
    Serial.begin(9600);
    pinMode(13, INPUT);
    pinMode(12, INPUT);
    pinMode(11, INPUT);
    pinMode(10, INPUT);
}

void loop() {
  int* pTempCount;
  int* pPulseCount;
  int* pSysCount;
  int* pDiaCount; 
  measureFunction(MeasureData, pTempCount, pPulseCount, pSysCount, pDiaCount);
}

void initialize(){
    //initializing the global variables
    temperatureRaw = 75;
    systolicPressRaw = 80;
    diastolicPressRaw = 80;
    pulseRateRaw = 50;
    batteryState = 200;
    tempCorrected = NULL;
    systolicPressCorrected = NULL;
    diastolicPressCorrected = NULL;
    pulseRateCorrected = NULL;
    batteryState = 200;
    bpOutOfRange = 0;
    tempOutOfRange = 0;
    pulseOutOfRange = 0;
}

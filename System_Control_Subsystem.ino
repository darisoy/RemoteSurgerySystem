//System Control Subsystem
#include  "dataStructs.h"
// unsigned int temperatureRaw;
// unsigned int systolicPressRaw;
// unsigned int diastolicPressRaw;
// unsigned int pulseRateRaw;
//
// unsigned char* tempCorrected;
// unsigned char* systolicPressCorrected;
// unsigned char* diastolicPressCorrected;
// unsigned char* pulseRateCorrected;
//
// unsigned short batteryState;
//
// unsigned char bpOutOfRange;
// unsigned char tempOutOfRange;
// unsigned char pulseOutOfRange;

//variables for the measurement function
int tempCount;
int pulseCount;
int sysCount;
int diaCount;
int tempBool;
int pulseBool;
int* pDiastolicFunction;
int* pSystolicFunction;

//bool bpHigh;
//bool tempHigh;
//bool pulseLow;

void setup() {

}

void loop() {
  // put your main code here, to run repeatedly:
  initialize();
  measure(void* measureDataPtr);
}

void initialize(){
  //initializing the global variables
  temperatureRaw = 75;
  systolicPressRaw = 80;
  diastolicPressRaw = 80;
  pulseRateRaw = 50;
  tempCorrected = NULL;
  systolicPressCorrected = NULL;
  diastolicPressCorrected = NULL;
  pulseRateCorrected = NULL;
  batteryState = 200;
  bpOutOfRange = 0;
  tempOutOfRange = 0;
  pulseOutOfRange = 0;
//  bpHigh = FALSE;
//  tempHigh = FALSE;
//  pulseLow = FALSE;

}

void measure(void* ptr){
  
  int * pTempCount = &tempCount;
  int * pSysCount = &sysCount;
  int * pDiaCount = &diaCount;
  int * pPulseCount = &pulseCount;
  int * pTempBool = 0;                   //temperatureRawData should be decreasing
  int * pPulseBool = 0;
  temperatureRawData(pTempCount, pTempBool);
  systolicPressRawData(pSysCount);
  diastolicPressRawData(pDiaCount);
  pulseRateRawData(pPulseCount, pPulseBool);
}

void temperatureRawData(int* pCount, int* pTempBool){
  if (pTempBool){
    if (*pCount % 2){
      temperatureRaw += 2;
    }else {
      temperatureRaw--;
    }
  }else {
    if (*pCount % 2){
      temperatureRaw -= 2;
    }else{
      temperatureRaw++;
    }
  }
  if (temperatureRaw < 15){
    *pTempBool = 1;
  }
  if (temperatureRaw > 50){
    *pTempBool = 0;
  }
  (*pCount)++;
}

void systolicPressRawData(int* pCount){
  if (systolicPressRaw <= 100){
    if (*pCount % 2){
      systolicPressRaw += 3;
    }else {
      systolicPressRaw--;
    }
  }else {
    *pSystolicFunction = 1;
    if (*pDiastolicFunction){
      systolicPressRaw = 0;
      *pCount = -1;
    }
  }
  (*pCount)++;
}

void diastolicPressRawData(int* pCount){
  if (diastolicPressRaw >= 40){
    if (*pCount % 2){
      diastolicPressRaw -= 2;
    }else {
      diastolicPressRaw++;
    }
  }else {
    *pDiastolicFunction = 1;
    if (*pSystolicFunction){
      diastolicPressRaw = 0;
      *pCount = -1;
    }
  }
  (*pCount)++;
}

void pulseRateRawData(int* pCount, int* pPulseBool){
  if (*pPulseBool){
    if (*pCount % 2){
      pulseRateRaw++;
    }else {
      pulseRateRaw -= 3;
    }
  }else {
    if (*pCount % 2){
      pulseRateRaw--;
    }else {
      pulseRateRaw +=3;
    }
  }
  if (pulseRateRaw > 40){
    *pPulseBool = 1;
  }
  if (pulseRateRaw < 15){
    *pPulseBool = 0;
  }
  (*pCount)++;
}

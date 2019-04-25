//System Control Subsystem Variables
#ifndef dataStructs
#define dataStructs

#include <stdbool.h>

                                          //creates the boolean variable
enum _myBool { FALSE = 0, TRUE = 1 };
typedef enum _myBool Bool;

                                          //initializes all variables needed for the system control
unsigned int temperatureRaw;
unsigned int systolicPressRaw;
unsigned int diastolicPressRaw;
unsigned int pulseRateRaw;

double tempCorrected;
double systolicPressCorrected;
double diastolicPressCorrected;
double pulseRateCorrected;

unsigned short batteryState;

unsigned char bpOutOfRange;
unsigned char tempOutOfRange;
unsigned char pulseOutOfRange;

//warning booleans
boolean tempGoodBool;
boolean sysGoodBool;
boolean diaGoodBool;
boolean prGoodBool;
boolean batteryGoodBool;

//initialize pointer to function
void* measureFunctionPtr;
typedef struct controlMeasureData measureData;
void* measureDataPtr;

struct controlMeasureData{
  unsigned int* pTemperatureRaw;
  unsigned int* pSystolicPressRaw;
  unsigned int* pDiastolicPressRaw;
  unsigned int* pPulseRateRaw;
}MeasureData;

struct controlComputeData{
  unsigned int* pTemperatureRaw;
  unsigned int* pSystolicPressRaw;
  unsigned int* pDiastolicPressRaw;
  unsigned int* pPulseRateRaw;
  unsigned char* pTempCorrected;                        //pointer to the first element in the array
  unsigned char* pSystolicPressCorrected;
  unsigned char* pDiastolicPressCorrected;
  unsigned char* pPulseRateCorrected;
}ComputeData;

struct controlDisplayData{
  unsigned char* pTempCorrected;                        //pointer to the first element in the array
  unsigned char* pSystolicPressCorrected;
  unsigned char* pDiasCorrected;
  unsigned char* pPulseRateCorrected;
  unsigned short* pBatteryState;
}DisplayData;

struct controlWarningAlarmData{
  unsigned int* pTemperatureRaw;
  unsigned int* pSystolicPressRaw;
  unsigned int* pDiastolicPressRaw;
  unsigned int* pPulseRateRaw;
  unsigned short* pBatteryState;
}WarningAlarmData;

struct controlStatus{
  unsigned short* pBatteryState;
}Status;

struct controlSchedulerData{

}SchedulerData;



//Create task queue data structs
void measureTCB{
  void measureFunctionPtr(void*);
  void* measureDataPtr;
}

#endif

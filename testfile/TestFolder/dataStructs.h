//System Control Subsystem Variables
#ifndef dataStructs
#define dataStructs

#include <stdbool.h>

                                          //creates the boolean variable
enum _myBool { FALSE = 0, TRUE = 1 };
typedef enum _myBool Bool;

void* taskQueue[7];

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
  unsigned int* pTempCorrected;
  unsigned int* pSystolicPressCorrected;
  unsigned int* pDiastolicPressCorrected;
  unsigned int* pPulseRateCorrected;
  unsigned short* pBatteryState;
}AlarmData;

struct controlStatus{
  unsigned short* pBatteryState;
}Status;

struct controlSchedulerData{

}SchedulerData;


//initialize pointer to function

//Create task queue data structs
struct MeasureTCB{
  void measureFunctionPtr(void*);
  void* measureDataPtr;
};
typedef struct MeasureTCB mTCB;

struct ComputeTCB{
  void computeFunctionPtr(void*);
  void* computeDataPtr;
};
typedef struct ComputeTCB cTCB;

struct StatusTCB{
  void statusFunctionPtr(void*);
  void* statusDataPtr;
};
typedef struct StatusTCB sTCB;

struct WarningTCB{
  void alarmFunctionPtr(void*);
  void* alarmDataPtr;
};
typedef struct WarningTCB wTCB;

struct DisplayTCB{
  void displayFunctionPtr(void*);
  void* displayDataPtr;
};
typedef struct DisplayTCB dTCB;

#endif

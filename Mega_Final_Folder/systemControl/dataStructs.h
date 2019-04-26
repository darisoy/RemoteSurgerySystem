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
bool tempGoodBool;
bool sysGoodBool;
bool diaGoodBool;
bool prGoodBool;
bool batteryGoodBool;

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
  double* pTempCorrected;                        //pointer to the first element in the array
  double* pSystolicPressCorrected;
  double* pDiastolicPressCorrected;
  double* pPulseRateCorrected;
}ComputeData;

struct controlDisplayData{
  double* pTempCorrected;                        //pointer to the first element in the array
  double* pSystolicPressCorrected;
  double* pDiastolicPressCorrected;
  double* pPulseRateCorrected;
  unsigned short* pBatteryState;
}DisplayData;

struct controlWarningAlarmData{
  double* pTempCorrected;
  double* pSystolicPressCorrected;
  double* pDiastolicPressCorrected;
  double* pPulseRateCorrected;
  unsigned short* pBatteryState;
}AlarmData;

struct controlStatus{
  unsigned short* pBatteryState;
}StatusData;

struct controlSchedulerData{

}SchedulerData;


//initialize pointer to function

//Create task queue data structs
struct MyTCB{
  void (*functionPtr)(void*);
  void* dataPtr;
}TCB;
MyTCB taskQueue[6];
MyTCB measureT, computeT, statusT, warningT, displayT;


#endif

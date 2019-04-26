//System Control Subsystem Variables
#ifndef dataStructs                     //check to see if variables are defined elsewhere
#define dataStructs                     //assigns definiton to dataStructs
#include <stdbool.h>                    //import necessary files

enum _myBool { FALSE = 0, TRUE = 1 };   //define boolean values
typedef enum _myBool Bool;              //creates the boolean variable

unsigned int temperatureRaw;            //initializes temperature variable
unsigned int systolicPressRaw;          //initializes syst. press. variable
unsigned int diastolicPressRaw;         //initializes dias. press. variable
unsigned int pulseRateRaw;              //initializes pulse rate variable

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

struct controlMeasureData {             //create the MeasureData struct
    unsigned int* pTemperatureRaw;      //struct contains temp data
    unsigned int* pSystolicPressRaw;    //struct contains syst. press. data
    unsigned int* pDiastolicPressRaw;   //struct contains dia. press. data
    unsigned int* pPulseRateRaw;        //struct contains pulse rate data
} MeasureData;                          //struct name

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

//Create task queue data structs
struct MyTCB{
  void (*functionPtr)(void*);
  void* dataPtr;
}TCB;
MyTCB taskQueue[6];
MyTCB measureT,
      computeT,
      statusT,
      warningT,
      displayT;

#endif

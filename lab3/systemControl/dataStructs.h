//System Control Subsystem Variables
#ifndef dataStructs                     //check to see if variables are defined elsewhere
#define dataStructs                     //assigns definiton to dataStructs
#include <stdbool.h>                    //import necessary files

enum _myBool { FALSE = 0, TRUE = 1 };   //define boolean values
typedef enum _myBool Bool;              //creates the boolean variable

unsigned int temperatureRaw;            //initializes the raw temperature variable
unsigned int systolicPressRaw;          //initializes the raw syst. press. variable
unsigned int diastolicPressRaw;         //initializes the raw dias. press. variable
unsigned int pulseRateRaw;              //initializes the raw pulse rate variable

double tempCorrected;                   //initalizes the corrected temperature variable
double systolicPressCorrected;          //initalizes the corrected syst. press. variable
double diastolicPressCorrected;         //initalizes the corrected dias. press. variable
double pulseRateCorrected;              //initalizes the corrected pulse rate variable

unsigned int measurementSelection;
unsigned int alarmAcknowledge;

unsigned short batteryState;            //initializes the battery state variable


int tempGoodBool;                      //initialized the warning boolean for temperature
int sysGoodBool;                       //initialized the warning boolean for systolic
int diaGoodBool;                       //initialized the warning boolean for diastolic
int prGoodBool;                        //initialized the warning boolean for pulse
int batteryGoodBool;                   //initialized the warning boolean for battery

int timer;                              //initializes timer that will schedule when data will be requested
char dataTransfered[16];                 //initializes 5 long character array that will hold read values on serial

int tempMeasure;
int sysMeasure;
int diaMeasure;
int prMeasure;
int batMeasure;

struct controlMeasureData {             //create the MeasureData struct
    unsigned int* pTemperatureRaw;      //struct contains raw temp data
    unsigned int* pSystolicPressRaw;    //struct contains raw syst. press. data
    unsigned int* pDiastolicPressRaw;   //struct contains raw dia. press. data
    unsigned int* pPulseRateRaw;        //struct contains raw pulse rate data
} MeasureData;                          //struct name

struct controlComputeData {             //create the controlComputeData struct
    unsigned int* pTemperatureRaw;      //struct contains raw temp data
    unsigned int* pSystolicPressRaw;    //struct contains raw syst. press. data
    unsigned int* pDiastolicPressRaw;   //struct contains raw dia. press. data
    unsigned int* pPulseRateRaw;        //struct contains raw pulse rate data
    double* pTempCorrected;             //struct contains corrected temp data
    double* pSystolicPressCorrected;    //struct contains corrected syst. press. data
    double* pDiastolicPressCorrected;   //struct contains corrected dia. press. data
    double* pPulseRateCorrected;        //struct contains corrected pulse rate data
} ComputeData;                          //struct name

struct controlDisplayData {             //create the controlDisplayData struct
    double* pTempCorrected;             //struct contains corrected temp data
    double* pSystolicPressCorrected;    //struct contains corrected syst. press. data
    double* pDiastolicPressCorrected;   //struct contains corrected dia. press. data
    double* pPulseRateCorrected;        //struct contains corrected pulse rate data
    unsigned short* pBatteryState;      //struct contians battery data
} DisplayData;                          //struct name

struct controlWarningAlarmData {        //create the controlWarningAlarmData struct
    double* pTempCorrected;             //struct contains corrected temp data
    double* pSystolicPressCorrected;    //struct contains corrected syst. press. data
    double* pDiastolicPressCorrected;   //struct contains corrected dia. press. data
    double* pPulseRateCorrected;        //struct contains corrected pulse rate data
    unsigned short* pBatteryState;      //struct contians battery data
} AlarmData;                            //struct name

struct controlStatus {                  //create the controlStatus struct
    unsigned short* pBatteryState;      //struct contains battery state data
} StatusData;                           //struct name

struct controlSchedulerData {           //create the controlSchedulerData struct
                                        //struct does not contian any variables
} SchedulerData;                        //struct name

struct controlKeypadData {             //create the MeasureData struct
  unsigned int* pMeasurementSelection;
  unsigned int* pAlarmAcknowledge;
} KeypadData;

struct MyTCB {                          //create the task control block struct
  void (*functionPtr)(void*);           //struct contains a pointer to a function
  void* dataPtr;                        //struct contains a pointer
  TimedAction* timedActionPtr;
  MyTCB* next;
  MyTCB* prev;
} TCB;                                  //struct name

MyTCB taskQueue[6];                     //initialize a 6 element array with MyTCB stuct
MyTCB measureT,                         //initialize the measureT object using MyTCB struct
      computeT,                         //initialize the computeT object using MyTCB struct
      statusT,                          //initialize the statusT object using MyTCB struct
      warningT,                         //initialize the warningT object using MyTCB struct
      displayT,                         //initialize the displayT object using MyTCB struct
      keypadT;

struct LinkedList{
  MyTCB* front;
  MyTCB* back;
  MyTCB* placeholder;
  int size;
}List;

LinkedList scheduler;

void calltask0() {
  measureT.functionPtr(measureT.dataPtr);
}
void calltask1() {
  computeT.functionPtr(computeT.dataPtr);
}
void calltask2() {
  statusT.functionPtr(statusT.dataPtr);
}
void calltask3() {
  keypadT.functionPtr(keypadT.dataPtr);
}
void calltask4() {
  warningT.functionPtr(warningT.dataPtr);
}
void calltask5() {
  displayT.functionPtr(displayT.dataPtr);
}

TimedAction task0 = TimedAction(5000, calltask0);
TimedAction task1 = TimedAction(5000, calltask1);
TimedAction task2 = TimedAction(5000, calltask2);
TimedAction task3 = TimedAction(10, calltask3);
TimedAction task4 = TimedAction(5000, calltask4);
TimedAction task5 = TimedAction(100, calltask5);

#endif

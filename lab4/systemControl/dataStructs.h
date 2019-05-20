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
unsigned int respRateRaw;              //initializes the raw pulse rate variable


double tempCorrected;                   //initalizes the corrected temperature variable
double systolicPressCorrected;          //initalizes the corrected syst. press. variable
double diastolicPressCorrected;         //initalizes the corrected dias. press. variable
double pulseRateCorrected;              //initalizes the corrected pulse rate variable
double respRateCorrected;              //initalizes the corrected pulse rate variable

unsigned int measurementSelection;      //variable that determines which measurement is selected
unsigned int alarmAcknowledge;          //variable that determines which alarm is acknowledged

unsigned short batteryState;            //initializes the battery state variable

int tempGoodBool;                       //initialized the warning boolean for temperature
int sysGoodBool;                        //initialized the warning boolean for systolic
int diaGoodBool;                        //initialized the warning boolean for diastolic
int prGoodBool;                         //initialized the warning boolean for pulse
int rrGoodBool;                         //initialized the warning boolean for pulse
int batteryGoodBool;                    //initialized the warning boolean for battery

int timer;                              //initializes timer that will schedule when data will be requested
char dataTransfered[20];                //initializes 5 long character array that will hold read values on serial

int tempMeasure;                        //initialize variables that select data colors
int sysMeasure;                         //initialize variables that select data colors
int diaMeasure;                         //initialize variables that select data colors
int prMeasure;                          //initialize variables that select data colors
int batMeasure;                         //initialize variables that select data colors
int rrMeasure;                          //initialize variables that select data colors

Elegoo_GFX_Button menu;                 //initialize the button
Elegoo_GFX_Button annunciate;           //initialize the button
Elegoo_GFX_Button display;              //initialize the button
Elegoo_GFX_Button exp1;                 //initialize the button
Elegoo_GFX_Button exp2;                 //initialize the button

Elegoo_GFX_Button an_T;                 //initialize the button
Elegoo_GFX_Button an_S;                 //initialize the button
Elegoo_GFX_Button an_D;                 //initialize the button
Elegoo_GFX_Button an_P;                 //initialize the button
Elegoo_GFX_Button an_R;                 //initialize the button

Elegoo_GFX_Button ack_T;                //initialize the button
Elegoo_GFX_Button ack_S;                //initialize the button
Elegoo_GFX_Button ack_D;                //initialize the button
Elegoo_GFX_Button ack_P;                //initialize the button
Elegoo_GFX_Button ack_B;                //initialize the button
Elegoo_GFX_Button ack_R;                //initialize the button

boolean pinHighPS;                      //initializes the boolean values for sending signal states
boolean pinHighNS;                      //initializes the boolean values for sending signal states

CircularBuffer<double,8> tempRawData;                                      //initialize raw buffer
CircularBuffer<double,8> pulseRawData;                                     //initialize raw buffer
CircularBuffer<double,8> sysRawData;                                       //initialize raw buffer
CircularBuffer<double,8> diaRawData;                                       //initialize raw buffer
//CircularBuffer[2] bpRawBuffer = {sysRawData, diaRawData};                  //initialize raw combined buffer
CircularBuffer<double,8> respRawData;                                       //initialize raw buffer

CircularBuffer<double,8> tempComputedData;                                 //initalize computed buffer
CircularBuffer<double,8> pulseComputedData;                                //initalize computed buffer
CircularBuffer<double,8> sysComputedData;                                  //initalize computed buffer
CircularBuffer<double,8> diaComputedData;                                  //initalize computed buffer
//CircularBuffer[2] bpComputedBuffer = {sysComputedData, diaComputedData};   //initialize corrected combined buffer
CircularBuffer<double,8> respComputedData;                                       //initialize raw buffer

boolean runCompute;                                                        //initalize boolean that determines when to run compute


struct controlMeasureData {             //create the MeasureData struct
    unsigned int* pTemperatureRaw;      //struct contains raw temp data
    unsigned int* pSystolicPressRaw;    //struct contains raw syst. press. data
    unsigned int* pDiastolicPressRaw;   //struct contains raw dia. press. data
    unsigned int* pPulseRateRaw;        //struct contains raw pulse rate data
    unsigned int* pMeasurementSelection;
    unsigned int* pRespRawData;
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

struct controlKeypadData {              //create the MeasureData struct
  unsigned int pMeasurementSelection;   //variable that selectes the measurement
  unsigned int pAlarmAcknowledge;       //variable that acknowledges alarms
} KeypadData;                           //struct name

struct MyTCB {                          //create the task control block struct
  void (*functionPtr)(void*);           //struct contains a pointer to a function
  void* dataPtr;                        //struct contains a pointer
  TimedAction* timedActionPtr;          //struct contains a pointer to TimedAction
  MyTCB* next;                          //struct contains a pointer to next function
  MyTCB* prev;                          //struct contains a pointer to previous function
} TCB;                                  //struct name

MyTCB measureT,                         //initialize the measureT object using MyTCB struct
      computeT,                         //initialize the computeT object using MyTCB struct
      statusT,                          //initialize the statusT object using MyTCB struct
      warningT,                         //initialize the warningT object using MyTCB struct
      displayT,                         //initialize the displayT object using MyTCB struct
      keypadT,                          //initialize the keypadT object using MyTCB struct
      communicationT;                   //initialize the communicationT object using MyTCB struct

struct LinkedList{                      //create the LinkedList struct
  MyTCB* front;                         //struct contains TCB pointer to front of the list
  MyTCB* back;                          //struct contains TCB pointer to back of the list
  MyTCB* placeholder;                   //struct contains TCB pointer to task on the list
  int size;                             //struct contains size of the list
}List;                                  //struct name

LinkedList scheduler;                                       //initalize scheduler

void calltask0() {                                          //function that simply runs a task
  measureT.functionPtr(measureT.dataPtr);                   //run the measure function with measure data of that task
}
void calltask1() {                                          //function that simply runs a task
  computeT.functionPtr(computeT.dataPtr);                   //run the compute function with compute data of that task
}
void calltask2() {                                          //function that simply runs a task
  statusT.functionPtr(statusT.dataPtr);                     //run the status function with status data of that task
}
void calltask3() {                                          //function that simply runs a task
  keypadT.functionPtr(keypadT.dataPtr);                     //run the keypad function with keypad data of that task
}
void calltask4() {                                          //function that simply runs a task
  warningT.functionPtr(warningT.dataPtr);                   //run the warning function with warning data of that task
}
void calltask5() {                                          //function that simply runs a task
  displayT.functionPtr(displayT.dataPtr);                   //run the display function with display data of that task
}
void calltask6(){                                           //function that simply runs a task
  communicationT.functionPtr(communicationT.dataPtr);       //run the communication function with communication data of that task
}

TimedAction task0 = TimedAction(5000, calltask0);            //initalize TimedAction to make sure function runs only every Xms
TimedAction task1 = TimedAction(5000, calltask1);            //initalize TimedAction to make sure function runs only every Xms
TimedAction task2 = TimedAction(5000, calltask2);            //initalize TimedAction to make sure function runs only every Xms
TimedAction task3 = TimedAction(100, calltask3);             //initalize TimedAction to make sure function runs only every Xms
TimedAction task4 = TimedAction(5000, calltask4);            //initalize TimedAction to make sure function runs only every Xms
TimedAction task5 = TimedAction(100, calltask5);             //initalize TimedAction to make sure function runs only every Xms
TimedAction task6 = TimedAction(10000, calltask6);           //initalize TimedAction to make sure function runs only every Xms

#endif

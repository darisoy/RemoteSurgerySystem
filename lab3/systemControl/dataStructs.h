//System Control Subsystem Variables
#ifndef dataStructs                     //check to see if variables are defined elsewhere
#define dataStructs                     //assigns definiton to dataStructs
#include <stdbool.h>                    //import necessary files

enum _myBool { FALSE = 0, TRUE = 1 };   //define boolean values
typedef enum _myBool Bool;              //creates the boolean variable

unsigned int temperatureRawBuf[8];            //initializes the raw temperature variable
unsigned int bloodPressRawBuf[16];          //initializes the raw syst. press. variable
unsigned int pulseRateRaw[8];              //initializes the raw pulse rate variable

double tempCorrectedBuf[8];                   //initalizes the corrected temperature variable
double bloodPressCorrectedBuf[16];          //initalizes the corrected syst. press. variable
double pulseRateCorrectedBuf[8];              //initalizes the corrected pulse rate variable

unsigned short batteryState;            //initializes the battery state variable

bool tempGoodBool;                      //initialized the warning boolean for temperature
bool sysGoodBool;                       //initialized the warning boolean for systolic
bool diaGoodBool;                       //initialized the warning boolean for diastolic
bool prGoodBool;                        //initialized the warning boolean for pulse
bool batteryGoodBool;                   //initialized the warning boolean for battery

//Keypad values
unsigned int measurementSelection;
unsigned int alarmAcknowledge;
unsigned int functionSelect;

int timer;                              //initializes timer that will schedule when data will be requested
char dataTransfered[16];                //initializes 16 long character array that will hold read values on serial

int start0;                             //initialize start time for task0
int start1;                             //initialize start time for task1
int start2;                             //initialize start time for task2
int start3;                             //initialize start time for task3
int start4;                             //initialize start time for task4

struct controlMeasureData {             //create the MeasureData struct
    unsigned int* pTemperatureRawBuf[8];      //struct contains raw temp data
    unsigned int* pBloodPressRawBuf[16];    //struct contains raw syst. press. data
    unsigned int* pPulseRateRawBuf[8];        //struct contains raw pulse rate data
} MeasureData;                          //struct name

struct controlComputeData {             //create the controlComputeData struct
    unsigned int* pTemperatureRawBuf[8];      //struct contains raw temp data
    unsigned int* pBloodPressRawBuf[16];    //struct contains raw syst. press. data
    unsigned int* pPulseRateRawBuf[8];        //struct contains raw pulse rate data
    double* pTempCorrectedBuf[8];             //struct contains corrected temp data
    double* pBloodPressCorrectedBuf[16];    //struct contains corrected syst. press. data
    double* pPulseRateCorrectedBuf[8];        //struct contains corrected pulse rate data
} ComputeData;                          //struct name

struct controlDisplayData {             //create the controlDisplayData struct
    double* pTempCorrectedBuf[8];             //struct contains corrected temp data
    double* pBloodPressCorrectedBuf[16];    //struct contains corrected syst. press. data
    double* pPulseRateCorrectedBuf[8];        //struct contains corrected pulse rate data
    unsigned short* pBatteryState;      //struct contians battery data
} DisplayData;                          //struct name

struct controlWarningAlarmData {        //create the controlWarningAlarmData struct
    double* pTempCorrectedBuf[8];             //struct contains corrected temp data
    double* pBloodPressCorrectedBuf[16];    //struct contains corrected syst. press. data
    double* pPulseRateCorrectedBuf[8];        //struct contains corrected pulse rate data
    unsigned short* pBatteryState;      //struct contians battery data
} AlarmData;                            //struct name

struct controlStatus {                  //create the controlStatus struct
    unsigned short* pBatteryState;      //struct contains battery state data
} StatusData;                           //struct name

struct controlSchedulerData {           //create the controlSchedulerData struct
                                        //struct does not contian any variables
} SchedulerData;                        //struct name

struct controlTFTKeypadData {
    unsigned int* pMeasurementSelection;
    unsigned int* pAlarmAcknowledge;
} KeypadData;

struct controlCommunicationData {
    double* pTempCorrectedBuf[8];
    double* pBloodPressCorrectedBuf[16];
    double* pPulseRateCorrectedBuf[8];
} CommunicationData;

struct MyTCB {                          //create the task control block struct
  void (*functionPtr)(void*);           //struct contains a pointer to a function
  void* dataPtr;                        //struct contains a pointer
  struct MyTCB* next;
  struct MyTCB* prev;
} TCB;                                  //struct name

MyTCB measureT,
    computeT,
    statusT,
    keypadT,
    warningT,
    communicationT,
    displayT;

#endif

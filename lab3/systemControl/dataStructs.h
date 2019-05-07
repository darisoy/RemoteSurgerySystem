//System Control Subsystem Variables
#ifndef dataStructs                     //check to see if variables are defined elsewhere
#define dataStructs                     //assigns definiton to dataStructs
#include <stdbool.h>                    //import necessary files

enum _myBool { FALSE = 0, TRUE = 1 };   //define boolean values
typedef enum _myBool Bool;              //creates the boolean variable

//Character arrays for the buffers
double temperatureRawBuf[8];
double systolicRawBuf[8];
double diastolicRawBuf[8];
double bloodPressRawBuf[16];
double pulseRateRawBuf[8];

double tempCorrectedBuf[8];
double bloodPressCorrectedBuf[16];
double pulseRateCorrectedBuf[8];

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

struct BufferData {
    double * list;
    int front;
    int back;
    int size;
} Buffer;

BufferData temperatureRawBuffer;            //initializes the raw temperature variable
BufferData systolicRawBuffer;
BufferData diastolicRawBuffer;
BufferData bloodPressRawBuffer;          //initializes the raw syst. press. variable
BufferData pulseRateRawBuffer;              //initializes the raw pulse rate variable

BufferData tempCorrectedBuffer;                   //initalizes the corrected temperature variable
BufferData bloodPressCorrectedBuffer;              //initalizes the corrected syst. press. variable
BufferData pulseRateCorrectedBuffer;              //initalizes the corrected pulse rate variable

struct controlMeasureData {             //create the MeasureData struct
    BufferData* pTemperatureRawBuf;      //struct contains raw temp data
    BufferData* pSystolicRawBuf;
    BufferData* pDiastolicRawBuf;
    BufferData* pBloodPressRawBuf;    //struct contains raw syst. press. data
    BufferData* pPulseRateRawBuf;        //struct contains raw pulse rate data
} MeasureData;                          //struct name

struct controlComputeData {             //create the controlComputeData struct
    BufferData* pTemperatureRawBuf;      //struct contains raw temp data
    BufferData* pBloodPressRawBuf;    //struct contains raw syst. press. data
    BufferData* pPulseRateRawBuf;        //struct contains raw pulse rate data
    BufferData* pTempCorrectedBuf;             //struct contains corrected temp data
    BufferData* pBloodPressCorrectedBuf;    //struct contains corrected syst. press. data
    BufferData* pPulseRateCorrectedBuf;        //struct contains corrected pulse rate data
} ComputeData;                          //struct name

struct controlDisplayData {             //create the controlDisplayData struct
    BufferData* pTempCorrectedBuf;             //struct contains corrected temp data
    BufferData* pBloodPressCorrectedBuf;    //struct contains corrected syst. press. data
    BufferData* pPulseRateCorrectedBuf;        //struct contains corrected pulse rate data
    unsigned short* pBatteryState;      //struct contians battery data
} DisplayData;                          //struct name

struct controlWarningAlarmData {        //create the controlWarningAlarmData struct
    BufferData* pTempCorrectedBuf;             //struct contains corrected temp data
    BufferData* pBloodPressCorrectedBuf;    //struct contains corrected syst. press. data
    BufferData* pPulseRateCorrectedBuf;        //struct contains corrected pulse rate data
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
    BufferData* pTempCorrectedBuf;
    BufferData* pBloodPressCorrectedBuf;
    BufferData* pPulseRateCorrectedBuf;
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

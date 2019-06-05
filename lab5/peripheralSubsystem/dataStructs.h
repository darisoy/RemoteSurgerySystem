//Peripheral Subsystem Variables
#ifndef dataStructs                     //check to see if variables are defined elsewhere
#define dataStructs                     //assigns definiton to dataStructs
#include <stdbool.h>                    //import necessary files

enum _myBool { FALSE = 0, TRUE = 1 };   //define boolean values
typedef enum _myBool Bool;              //creates the boolean variable

unsigned int temperatureRaw;            //initializes temperature variable
unsigned int systolicPressRaw;          //initializes syst. press. variable
unsigned int diastolicPressRaw;         //initializes dias. press. variable
unsigned int pulseRateRaw;              //initializes pulse rate variable
unsigned int respRaw;
signed int EKGProcessedData[256];
signed int EKGRealData[256];
signed int EKGImagData[256];
int samplingFreq;
int EKGFrequency;

boolean pinHighPS;                      //initializes the boolean values for sending signal states
boolean pinHighNS;                      //initializes the boolean values for sending signal states

boolean megaAckowledge;

boolean b1HighPS;
boolean b1HighNS;
boolean b2HighPS;
boolean b2HighNS;

int tempBool = 0;                       //initialize temperature boolean to be 0
int pulseBool = 0;                      //initialize pulse boolean to be 0
int tempCount;                          //initialize the pointer to the temp counter
int sysCount;                           //initialize the pointer to the systolic counter
int diaCount;                           //initialize the pointer to the diastolic counter
int* pDiastolicFunction;                //initialize the pointer to the diastolic function
int* pSystolicFunction;                 //initialize the pointer to the systolic function

double pulseSum;                                             //initalize sum variable for frequency measurement
int pulseCount;                                              //intialize the count variable for frequency measurement
int countMillis;

int diastolicCount;
int systolicCount;
int frequency;

boolean respInputState;
boolean respLastState;
int respCount;
unsigned long respPrevCount;

struct controlMeasureData {             //create the MeasureData struct
    unsigned int* pTemperatureRaw;      //struct contains temp data
    unsigned int* pSystolicPressRaw;    //struct contains syst. press. data
    unsigned int* pDiastolicPressRaw;   //struct contains dia. press. data
    unsigned int* pPulseRateRaw;        //struct contains pulse rate data
    unsigned int* pRespRaw;
    int* pFrequency;
} MeasureData;                          //struct name

struct controlEKGData {
  signed int* EKGRealDataPtr[256];
  signed int* EKGImagDataPtr[256];
  int* samplingFrequencyPtr;
};
struct controlEKGData EKGData;
#endif

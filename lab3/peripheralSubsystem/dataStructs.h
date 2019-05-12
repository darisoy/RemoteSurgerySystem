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

boolean pinHighPS;
boolean pinHighNS;

int tempBool = 0;                       //initialize temperature boolean to be 0
int pulseBool = 0;                      //initialize pulse boolean to be 0
int tempCount;                        //initialize the pointer to the temp counter
int pulseCount;                       //initialize the pointer to the pulse counter
int sysCount;                         //initialize the pointer to the systolic counter
int diaCount;                         //initialize the pointer to the diastolic counter
int* pDiastolicFunction;                //initialize the pointer to the diastolic function
int* pSystolicFunction;                 //initialize the pointer to the systolic function

struct controlMeasureData {             //create the MeasureData struct
    unsigned int* pTemperatureRaw;      //struct contains temp data
    unsigned int* pSystolicPressRaw;    //struct contains syst. press. data
    unsigned int* pDiastolicPressRaw;   //struct contains dia. press. data
    unsigned int* pPulseRateRaw;        //struct contains pulse rate data
} MeasureData;                          //struct name
#endif

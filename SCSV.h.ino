//System Control Subsystem Variables
#ifndef SCSV_H
#define SCSV_H

                                          //creates the boolean variable
enum _myBool { FALSE = 0, TRUE = 1 };
typedef enum _myBool Bool;

                                          //initializes all variables needed for the system control
unsigned int temperatureRaw;
unsigned int systolicPressRaw;
unsigned int diastolicPressRaw;
unsigned int pulseRateRaw;

unsigned char* tempCorrected;
unsigned char* systolicPressCorrected;
unsigned char* diastolicPressCorrected;
unsigned char* pulseRateCorrected;

unsigned short batteryState;

unsigned char bpOutOfRange;
unsigned char tempOutOfRange;
unsigned char pulseOutOfRange;

struct MeasureData;
struct ComputeData;
struct DisplayData;
struct WarningAlarmData;
struct Status;
struct SchedulerData;

#endif 

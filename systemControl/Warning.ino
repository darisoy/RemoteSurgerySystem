#include "Warning.h"                                                                                 //import the header of this function
#include "dataStructs.h"                                                                             //import the variables
#include <stdio.h>                                                                                   //import necessary header files
#include <stdbool.h>                                                                                 //import necessary header files
#include <stddef.h>                                                                                  //import necessary header files

void alarmFunction(void* warningStruct){                                                             //function that checks if alarms should be going off, takes in the warning struct
  struct controlWarningAlarmData *wData = (struct controlWarningAlarmData*) warningStruct;           //deference the warning struct
  wData->pTempCorrected           = &tempCorrected;                                                  //assign corrected temp's address to corrected temp pointer from warning struct
  wData->pSystolicPressCorrected  = &systolicPressCorrected;                                         //assign corrected sys's address to corrected sys pointer from warning struct
  wData->pDiastolicPressCorrected = &diastolicPressCorrected;                                        //assign corrected fia's address to corrected dia pointer from warning struct
  wData->pPulseRateCorrected      = &pulseRateCorrected;                                             //assign corrected pulse's address to corrected pulse pointer from warning struct
  wData->pBatteryState            = &batteryState;                                                   //assign battery state's address to battery state pointer from warning struct

  tempGoodBool    = (*wData->pTempCorrected <= 37.8) && (*wData->pTempCorrected >= 36.1);            //if value of the corrected temp pointer is less than 37.8 and greater than 36.1, make the boolean true, otherwise false
  sysGoodBool     = (*wData->pSystolicPressCorrected == 120);                                        //if value of the corrected sys pointer is 120, make the boolean true, otherwise false
  diaGoodBool     = (*wData->pDiastolicPressCorrected == 80);                                        //if value of the corrected dia pointer is 80, make the boolean true, otherwise false
  prGoodBool      = (*wData->pPulseRateCorrected > 60.0) && (*wData->pPulseRateCorrected < 100.0);   //if value of the corrected pulse rate pointer is greater than 60 and less than 100, make the boolean true, otherwise false
  batteryGoodBool = (*wData->pBatteryState >= 40);                                                   //if value of the battery state pointer is greater than 40, make the boolean true, otherwise false
}

#include "status.h"                                         //import the header of this function
#include "dataStructs.h"                                    //import the variables
#include <stdio.h>                                          //import necessary header files
#include <stdbool.h>                                        //import necessary header files
#include <stddef.h>                                         //import necessary header files

void statusFunction(void* statusDataStruct){
  struct controlStatus *sData = (struct controlStatus*) statusDataStruct;
  sData->pBatteryState = &batteryState;

  (*sData->pBatteryState)--;
  if ((*sData->pBatteryState) <= 1) {
    (*sData->pBatteryState) = 200;
  }
}

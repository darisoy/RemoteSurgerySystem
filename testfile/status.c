#include <stdio.h>
#include "status.h"

void statusFunction(void* statusDataStruct){
  struct controlStatus *sData = (struct controlStatus) statusDataStruct;
  sData->pBatteryState = &batteryState;

  //What do we do in here?
}

#include <stdio.h>
#include "status.h"

void statusFunction(void* statusDataStruct){
  struct controlStatus *sData = (struct controlStatus*) statusDataStruct;
  sData->pBatteryState = &batteryState;

  (*sData->pBatteryState)--;
  if ((*sData->pBatteryState) <= 1) {
    (*sData->pBatteryState) = 200;
  }
}

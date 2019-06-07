#include "datastructs.h"
#include "traffic.h"

void trafficFunction(void* data) {
  struct controlTrafficData *tData = (struct controlTrafficData*) data;
  tData->pSwitch = &trafficSwitch;

  if (tData->pSwitch == true) {
    
  }
}

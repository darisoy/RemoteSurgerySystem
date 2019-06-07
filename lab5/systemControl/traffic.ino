#include "datastructs.h"

#include "traffic.h"

void trafficFunction(void* data) {
  struct controlTrafficData *tData = (struct controlTrafficData*) data;
  tData->pSwitch = &trafficSwitch;

  task1.check();
  task2.check();

  if (trafficSwitch){
    digitalWrite(BLUEPIN, HIGH);
    digitalWrite(REDPIN, HIGH);
    digitalWrite(WHITEPIN, HIGH);
  } else {
    digitalWrite(BLUEPIN, LOW);
    digitalWrite(REDPIN, LOW);
    digitalWrite(WHITEPIN, LOW);
  }
}

TimedAction task1 = TimedAction(500, blueOn);
TimedAction task2 = TimedAction(1000, redOn);

void blueOn(){
  digitalWrite(BLUEPIN, HIGH);
}

void redOn(){
  digitalWrite(REDPIN,HIGH);
}

void whiteOn(){
  digitalWrite(WHITEPIN, HIGH;)
}

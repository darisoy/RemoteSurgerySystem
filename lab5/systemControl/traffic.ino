#include "datastructs.h"
#include "traffic.h"

boolean red = false;
void redOn(){
    red = !red;
}

TimedAction taskR = TimedAction(100, redOn);

void trafficFunction(void* data) {
    struct controlTraffic *tData = (struct controlTraffic*) data;
    tData->pSwitch = &trafficSwitch;
    taskR.check();

    if (*tData->pSwitch == 1){
        if (red) {
            digitalWrite(REDPIN, HIGH);
            digitalWrite(BLUEPIN, LOW);
        } else {
            digitalWrite(REDPIN, LOW);
            digitalWrite(BLUEPIN, HIGH);
        }

        digitalWrite(WHITEPIN, HIGH);
    } else {
        digitalWrite(BLUEPIN, LOW);
        digitalWrite(REDPIN, LOW);
        digitalWrite(WHITEPIN, LOW);
    }
}

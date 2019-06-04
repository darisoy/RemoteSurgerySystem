#include "communicationFunction.h"            //import the header of this function
#include "dataStructs.h"                      //import the variables
#include <stdio.h>                            //import necessary header files
#include <stdbool.h>                          //import necessary header files
#include <stddef.h>                           //import necessary header files

void communicationFunction(void* data) {                //function that sends signal to uno to request data
    digitalWrite(UNOREQ, HIGH);                   //make pin 22 high
    Serial.print("in ");
    Serial.print("COMMUNI");
    Serial.println("CATIONS");
    digitalWrite(UNOREQ, LOW);                    //make pin 22 low
}

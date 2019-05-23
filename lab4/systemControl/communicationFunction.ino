#include "communicationFunction.h"            //import the header of this function
#include "dataStructs.h"                      //import the variables
#include <stdio.h>                            //import necessary header files
#include <stdbool.h>                          //import necessary header files
#include <stddef.h>                           //import necessary header files

void communicationFunction(void* data) {                //function that sends signal to uno to request data
    digitalWrite(22, HIGH);                   //make pin 22 high
    Serial.println("in COMMUNICATION");
    digitalWrite(22, LOW);                    //make pin 22 low
}

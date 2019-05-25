#include "status.h"                                                             //import the header of this function
#include "dataStructs.h"                                                        //import the variables
#include <stdio.h>                                                              //import necessary header files
#include <stdbool.h>                                                            //import necessary header files
#include <stddef.h>                                                             //import necessary header files

void statusFunction(void* statusDataStruct){                                    //function that calculates the battery of the system, takes status struct as input
    struct controlStatus *sData = (struct controlStatus*) statusDataStruct;     //deference the status struct
    sData->pBatteryState = &batteryState;                                       //assign battery's address to battery pointer from status struct
    (*sData->pBatteryState)--;                                                  //decrement the value of the battery pointer in the status struct by 1 in every cycle.
    if ((*sData->pBatteryState) <= 1) {                                         //if the value of the battery pointer in the status struct is less than 1
        (*sData->pBatteryState) = 200;                                          //set the value of the battery pointer in the status struct to 200
    }
}

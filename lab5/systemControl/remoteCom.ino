#include "remoteCom.h"                                                                            //import the header of this function
#include "dataStructs.h"                                                                        //import the variables
#include <stdio.h>                                                                              //import necessary header files
#include <stdbool.h>                                                                            //import necessary header files
#include <stddef.h>

void remoteComFunction(void* remoteData) {
    Serial.println("in REMOTECOM1");
    struct controlRemoteComData *rData = (struct controlRemoteComData*) remoteData;          //deference the display struct
    rData->pTemperatureRaw     = &tempRawData;                                               //assign raw temp's address to raw temp pointer from measure struct
    rData->pSystolicPressRaw   = &sysRawData;                                             //assign raw sys's address to raw sys pointer from measure struct
    rData->pDiastolicPressRaw  = &diaRawData;                                            //assign raw dia's address to raw dia pointer from measure struct
    rData->pPulseRateRaw       = &pulseRawData;
    rData->pRespRaw            = &respRawData;

    if (!pinHighPS && (digitalRead(WIFIREQ) == HIGH)) {         //check if the request pin turned high
        pinHighNS = true;                                   //if so, make the current state true
    } else if (pinHighPS && (digitalRead(WIFIREQ) == HIGH)) {   //if request pin is true and it has been true
        pinHighNS = true;                                   // keep the current state true
    } else {                                                //in any other case
        pinHighNS = false;                                    //make current case false
    }

    if (digitalRead(WIFIACK) == HIGH) {
        wifiAckowledge = true;
    }
    Serial.println(!pinHighPS && pinHighNS);
    if (!pinHighPS && pinHighNS && wifiAckowledge) {
        Serial.println("in here");
        Serial2.print("VT");                                 //print "VT" on the serial
        if ((int)rData->pTemperatureRaw->last() < 10) {            //if value for the raw temp. pointer is less than 10
            Serial2.print("00");                             //print "00" on the serial
        } else if ((int)rData->pTemperatureRaw->last() < 100) {    //if value for the raw temp. pointer is less than 100
            Serial2.print("0");                              //print "0" on the serial
        }
        Serial2.print((int)rData->pTemperatureRaw->last());         //print the value for the raw temp. pointer on the serial
        Serial2.print("S");                                  //print "VS" on the serial
        if ((int)rData->pSystolicPressRaw->last() < 10) {          //if value for the raw sys. pointer is less than 10
            Serial2.print("00");                             //print "00" on the serial
        } else if ((int)rData->pSystolicPressRaw->last() < 100) {  //if value for the raw sys. pointer is less than 100
            Serial2.print("0");                              //print "0" on the serial
        }
        Serial2.print((int)rData->pSystolicPressRaw->last());       //print the value for the raw sys. pointer on the serial
        Serial2.print("D");                                  //print "VD" on the serial
        if ((int)rData->pDiastolicPressRaw->last() < 10) {         //if value for the raw dia. pointer is less than 10
            Serial2.print("00");                             //print "00" on the serial
        } else if ((int)rData->pDiastolicPressRaw->last() < 100) { //if value for the raw dia. pointer is less than 100
            Serial2.print("0");                              //print "0" on the serial
        }
        Serial2.print((int)rData->pDiastolicPressRaw->last());      //print the value for the raw dia. pointer on the serial                    //call the pulseRateRawData function to generate pulse data
        Serial2.print("P");                                  //print "VP" on the serial
        if ((int)rData->pPulseRateRaw->last() < 10) {              //if value for the raw pulse. pointer is less than 10
            Serial2.print("00");                             //print "00" on the serial
        } else if ((int)rData->pPulseRateRaw->last() < 100) {      //if value for the raw pulse. pointer is less than 100
            Serial2.print("0");                              //print "0" on the serial
        }
        Serial2.print((int)rData->pPulseRateRaw->last());         //print the value for the raw pulse. pointer on the serial
        Serial2.print("R");                                  //print "VP" on the serial
        if ((int)rData->pRespRaw->last() < 10) {              //if value for the raw pulse. pointer is less than 10
            Serial2.print("00");                             //print "00" on the serial
        } else if ((int)rData->pRespRaw->last() < 100) {      //if value for the raw pulse. pointer is less than 100
            Serial2.print("0");                              //print "0" on the serial
        }
        Serial2.println((int)rData->pRespRaw->last());
        wifiAckowledge = false;


        ///test----------------
        Serial.print("TO THE WIFI BOARD: VT");                                 //print "VT" on the serial
        if ((int)rData->pTemperatureRaw->last() < 10) {            //if value for the raw temp. pointer is less than 10
            Serial.print("00");                             //print "00" on the serial
        } else if ((int)rData->pTemperatureRaw->last() < 100) {    //if value for the raw temp. pointer is less than 100
            Serial.print("0");                              //print "0" on the serial
        }
        Serial.print((int)rData->pTemperatureRaw->last());         //print the value for the raw temp. pointer on the serial
        Serial.print("S");                                  //print "VS" on the serial
        if ((int)rData->pSystolicPressRaw->last() < 10) {          //if value for the raw sys. pointer is less than 10
            Serial.print("00");                             //print "00" on the serial
        } else if ((int)rData->pSystolicPressRaw->last() < 100) {  //if value for the raw sys. pointer is less than 100
            Serial.print("0");                              //print "0" on the serial
        }
        Serial.print((int)rData->pSystolicPressRaw->last());       //print the value for the raw sys. pointer on the serial
        Serial.print("D");                                  //print "VD" on the serial
        if ((int)rData->pDiastolicPressRaw->last() < 10) {         //if value for the raw dia. pointer is less than 10
            Serial.print("00");                             //print "00" on the serial
        } else if ((int)rData->pDiastolicPressRaw->last() < 100) { //if value for the raw dia. pointer is less than 100
            Serial.print("0");                              //print "0" on the serial
        }
        Serial.print((int)rData->pDiastolicPressRaw->last());      //print the value for the raw dia. pointer on the serial                    //call the pulseRateRawData function to generate pulse data
        Serial.print("P");                                  //print "VP" on the serial
        if ((int)rData->pPulseRateRaw->last() < 10) {              //if value for the raw pulse. pointer is less than 10
            Serial.print("00");                             //print "00" on the serial
        } else if ((int)rData->pPulseRateRaw->last() < 100) {      //if value for the raw pulse. pointer is less than 100
            Serial.print("0");                              //print "0" on the serial
        }
        Serial.print((int)rData->pPulseRateRaw->last());         //print the value for the raw pulse. pointer on the serial
        Serial.print("R");                                  //print "VP" on the serial
        if ((int)rData->pRespRaw->last() < 10) {              //if value for the raw pulse. pointer is less than 10
            Serial.print("00");                             //print "00" on the serial
        } else if ((int)rData->pRespRaw->last() < 100) {      //if value for the raw pulse. pointer is less than 100
            Serial.print("0");                              //print "0" on the serial
        }
        Serial.println((int)rData->pRespRaw->last());

    }

    pinHighPS = pinHighNS;
}

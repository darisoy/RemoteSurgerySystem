void command() {
    if (digitalRead(DPIN) == HIGH) {
        Serial.println("D");
        displayEnabled = true;
    } else {
        displayEnabled = false;
    }

    if (digitalRead(WPIN) == HIGH) {
        Serial.println("W");
        int warningCount = 0;
        int alarmCount = 0;
        if (tempGoodBool == 1) {
            ++warningCount;
        } else if (tempGoodBool == 2) {
            ++alarmCount;
        }
        if (sysGoodBool == 1) {
            ++warningCount;
        } else if (sysGoodBool == 2) {
            ++alarmCount;
        }
        if (diaGoodBool == 1) {
            ++warningCount;
        } else if (diaGoodBool == 2) {
            ++alarmCount;
        }
        if (prGoodBool == 1) {
            ++warningCount;
        } else if (prGoodBool == 2) {
            ++alarmCount;
        }
        if (rrGoodBool == 1) {
            ++warningCount;
        } else if (rrGoodBool == 2) {
            ++alarmCount;
        }
        if (ekgGoodBool == 1) {
            ++warningCount;
        } else if (ekgGoodBool == 2) {
            ++alarmCount;
        }
        if (batteryGoodBool == 1) {
            ++warningCount;
        } else if (batteryGoodBool == 2) {
            ++alarmCount;
        }
        Serial2.print("VWARNINGS_");
        Serial2.print(warningCount);
        Serial2.print("_ALARMS_");
        Serial2.print(alarmCount);
        Serial2.println("__________");
        Serial.println("warning printed");
    }

    if (digitalRead(SPPIN) == HIGH) {
        collectData = true;
    } else {
        collectData = false;
    }
}

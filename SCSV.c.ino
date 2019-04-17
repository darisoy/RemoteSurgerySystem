//SCSH c file
//#include "SCSV.h"

struct MeasureData{
  void(*measure)(void*)
  unsigned int * pTemperatureRaw = &temperatureRaw;
  unsigned int * pSystolicPressRaw = &systolicPressRaw;
  unsigned int * pDiastolicPressRaw = &diastolicPressRaw;
  unsigned int * pPulseRateRaw = &pulseRateRaw;
};

struct ComputeData{
  unsigned int * pTemperatureRaw = &temperatureRaw;
  unsigned int * pSystolicPressRaw = &systolicPressRaw;
  unsigned int * pDiastolicPressRaw = &diastolicPressRaw;
  unsigned int * pPulseRateRaw = &pulseRateRaw;
  unsigned char * pTempCorrected = tempCorrected;                        //pointer to the first element in the array
  unsigned char * pSystolicPressCorrected = systolicPressCorrected;
  unsigned char * pDiasCorrected = diastolicPressCorrected;
  unsigned char * pPulseRateCorrected = pulseRateCorrected;
}

struct DisplayData{
  unsigned char * pTempCorrected = tempCorrected;                        //pointer to the first element in the array
  unsigned char * pSystolicPressCorrected = systolicPressCorrected;
  unsigned char * pDiasCorrected = diastolicPressCorrected;
  unsigned char * pPulseRateCorrected = pulseRateCorrected;
  unsigned short * pBatteryState = &batteryState;
}

struct WarningAlarmData{
  unsigned int * pTemperatureRaw = &temperatureRaw;
  unsigned int * pSystolicPressRaw = &systolicPressRaw;
  unsigned int * pDiastolicPressRaw = &diastolicPressRaw;
  unsigned int * pPulseRateRaw = &pulseRateRaw;
  unsigned short * pBatteryState = &batteryState;
}

struct Status{
  unsigned short * pBatteryState = &batteryState;
}

struct SchedulerData{
  
}

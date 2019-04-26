#include "Display.h"
#include "dataStructs.h"
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

void displayFunction(void* displayDataStruct){
  struct controlDisplayData *dData = (struct controlDisplayData*) displayDataStruct;
  dData->pTempCorrected = &tempCorrected;
  dData->pSystolicPressCorrected = &systolicPressCorrected;
  dData->pDiastolicPressCorrected = &diastolicPressCorrected;
  dData->pPulseRateCorrected = &pulseRateCorrected;
  dData->pBatteryState = &batteryState;

  tft.setCursor(0, 0);
  tft.setTextSize(2);

  tft.setTextColor(WHITE, BLACK);
  tft.println("results from patient");
  tft.print("Temp: ");
  if (tempGoodBool) {
      tft.setTextColor(GREEN, BLACK);
  } else {
      tft.setTextColor(RED, BLACK);
  }
  tft.print(*dData->pTempCorrected);
  tft.println(" C   ");

  tft.setTextColor(WHITE, BLACK);
  tft.print("Syst: ");
  if (sysGoodBool) {
      tft.setTextColor(GREEN, BLACK);
  } else {
      tft.setTextColor(RED, BLACK);
  }
  tft.print(*dData->pSystolicPressCorrected);
  tft.println(" mm Hg ");

  tft.setTextColor(WHITE, BLACK);
  tft.print("Dias: ");
  if (diaGoodBool) {
      tft.setTextColor(GREEN, BLACK);
  } else {
      tft.setTextColor(RED, BLACK);
  }
  tft.print(*dData->pDiastolicPressCorrected);
  tft.println(" mm Hg ");

  tft.setTextColor(WHITE, BLACK);
  tft.print("Puls: ");
  if (prGoodBool) {
      tft.setTextColor(GREEN, BLACK);
  } else {
      tft.setTextColor(RED, BLACK);
  }
  tft.print(*dData->pPulseRateCorrected);
  tft.println(" BPM ");

  tft.setTextColor(WHITE, BLACK);
  tft.print("Batt: ");
  if (batteryGoodBool) {
      tft.setTextColor(GREEN, BLACK);
  } else {
      tft.setTextColor(RED, BLACK);
  }
  int batteryPercentage = *dData->pBatteryState / 2;
  tft.print(batteryPercentage);
  tft.println("%      ");
  tft.println("                     ");
  tft.println("                     ");
  tft.println("                     ");
  tft.println("                     ");
}

#include "typewise-alert.h"
#include <stdio.h>
                            
int CoolTypeTempLimits[3][2] = {{0,35},{0,45},{0,40}};  //Temperature limits {lowerLimit, upperLimit}

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  else if(value > upperLimit) {
    return TOO_HIGH;
  }
  else
  {
    return NORMAL;
  }
 
}

BreachType classifyTemperatureBreach(
  CoolingType coolingType, double temperatureInC) {
    int lowerLimit = 0;
    int upperLimit = 0;

    lowerLimit = CoolTypeTempLimits[coolingType][0];
    upperLimit = CoolTypeTempLimits[coolingType][1];

  return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

void checkAndAlert(
  AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreach(
    batteryChar.coolingType, temperatureInC
  );

  if(alertTarget == TO_CONTROLLER)
  {
    sendToController(breachType);
  }
  else
  {
    sendToEmail(breachType);
  }
}


void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  switch(breachType) {
    case TOO_LOW:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too low\n");
      break;
    case TOO_HIGH:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too high\n");
      break;
  }
}

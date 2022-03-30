#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
  REQUIRE(inferBreach(50, 30, 40) == TOO_HIGH);
  REQUIRE(inferBreach(15, 10, 20) == NORMAL);
}

TEST_CASE("classifies the temperature breach according to the current temperature") {
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 20) == NORMAL);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 50) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, -5) == TOO_LOW);
}

TEST_CASE("Alert to controller/Mail based on temperature") {

  AlertTarget alerttarget;
  CoolingType coolingType;

  coolingType = MED_ACTIVE_COOLING;
  alerttarget = TO_CONTROLLER;
  checkAndAlert(alerttarget, coolingType, 45);

  coolingType = HI_ACTIVE_COOLING;
  alerttarget = TO_EMAIL;
  checkAndAlert(alerttarget, coolingType, 45);

  
}

TEST_CASE(" Sent to controller check") {

  BreachType Breachtype=TOO_HIGH;
  sendToController(Breachtype);

  Breachtype=TOO_LOW;
  sendToController(Breachtype);

  Breachtype=NORMAL;
  sendToController(Breachtype);
}

TEST_CASE(" Sent to Email check") {

  BreachType Breachtype=TOO_HIGH;
  sendToEmail(Breachtype);

  Breachtype=TOO_LOW;
  sendToEmail(Breachtype);

  Breachtype=NORMAL;
  sendToEmail(Breachtype);
}

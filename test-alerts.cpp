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
  BatteryCharacter batterychar;
  
  batterychar.coolingType = HI_ACTIVE_COOLING;
  alerttarget = TO_CONTROLLER;
  REQUIRE(alerttarget == TO_CONTROLLER);
  checkAndAlert(alerttarget, batterychar, 45);

  batterychar.coolingType = HI_ACTIVE_COOLING;
  alerttarget = TO_EMAIL;
  REQUIRE(alerttarget == TO_EMAIL);
  checkAndAlert(alerttarget, batterychar, 45);

  
}

TEST_CASE(" Sent to controller check") {

  BreachType Breachtype = TOO_HIGH;
  REQUIRE(Breachtype == TOO_HIGH);
  sendToController(Breachtype);

  Breachtype=TOO_LOW;
  REQUIRE(Breachtype == TOO_LOW);
  sendToController(Breachtype);

  Breachtype=NORMAL;
  REQUIRE(Breachtype == NORMAL);
  sendToController(Breachtype);
}

TEST_CASE(" Sent to Email check") {

  BreachType Breachtype=TOO_HIGH;
  REQUIRE(Breachtype == TOO_HIGH);
  sendToEmail(Breachtype);

  Breachtype=TOO_LOW;
  REQUIRE(Breachtype == TOO_LOW);
  sendToEmail(Breachtype);

  Breachtype=NORMAL;
  REQUIRE(Breachtype == NORMAL);
  sendToEmail(Breachtype);
}

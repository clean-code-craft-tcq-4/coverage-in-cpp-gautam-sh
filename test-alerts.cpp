#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
// #include "typewise-alert.h"
#include "include/alert.hpp"
#include <assert.h>
#include <iostream>

TEST_CASE("infers the breach according to limits") {
  REQUIRE(Breach::inferBreach(12, 20, 30) == Breach::BreachType::TOO_LOW);
}

TEST_CASE_METHOD(EmailAlerter, "classifies the breach type"){
  EmailAlerter test_email_alerter;
  test_email_alerter.brand = "brand_A";
  test_email_alerter.cooling_type = BatteryCharacter::HI_ACTIVE_COOLING;

  std::string test_low_breach_msg = "To: a.b@c.com\nHi, the temperature is too low";
  std::string test_high_breach_msg = "To: a.b@c.com\nHi, the temperature is too high";
  std::string test_no_breach_msg = "To: a.b@c.com\nHi, the temperature is normal";

  double test_temperature = 100;

  REQUIRE(test_email_alerter.classifyTemperatureBreach(test_temperature) == Breach::BreachType::TOO_HIGH);
  REQUIRE(test_email_alerter.sendAlert(Breach::TOO_HIGH) == test_high_breach_msg);
}



// int main() {
//   Breach test;

//   EmailAlerter test_email_alerter;
//   test_email_alerter.brand = "brand_A";
//   test_email_alerter.cooling_type = BatteryCharacter::HI_ACTIVE_COOLING;

//   std::string test_low_breach_msg = "To: a.b@c.com\nHi, the temperature is too low";
//   std::string test_high_breach_msg = "To: a.b@c.com\nHi, the temperature is too high";
//   std::string test_no_breach_msg = "To: a.b@c.com\nHi, the temperature is normal";

//   // Test inferBreach
//   assert(test.inferBreach(22.0,20.0,30.0) == Breach::BreachType::NORMAL);

//   // Test classifyTempBreach
//   double test_temp = 100;
//   assert(test_email_alerter.classifyTemperatureBreach(test_temp) == Breach::BreachType::TOO_HIGH);
  
//   // Test checkAndAlert
//   assert(test_email_alerter.sendAlert(Breach::TOO_HIGH) == test_high_breach_msg);

// }

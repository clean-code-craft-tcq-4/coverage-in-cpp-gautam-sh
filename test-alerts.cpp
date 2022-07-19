#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "include/alert.hpp"
#include <assert.h>
#include <iostream>

TEST_CASE("infers the breach according to limits") {
  REQUIRE(Breach::inferBreach(12, 20, 30) == Breach::BreachType::TOO_LOW);
}

TEST_CASE_METHOD(EmailAlerter, "classifies the breach type and sends email alert"){
  EmailAlerter test_email_alerter;
  test_email_alerter.brand = "brand_A";
  test_email_alerter.cooling_type = BatteryCharacter::HI_ACTIVE_COOLING;

  std::string test_low_breach_msg = "To: a.b@c.com\nHi, the temperature is too low";
  std::string test_high_breach_msg = "To: a.b@c.com\nHi, the temperature is too high";
  std::string test_no_breach_msg = "To: a.b@c.com\nHi, the temperature is normal";

  REQUIRE(test_email_alerter.classifyTemperatureBreach(100) == Breach::BreachType::TOO_HIGH);
  REQUIRE(test_email_alerter.classifyTemperatureBreach(-10) == Breach::BreachType::TOO_LOW);
  REQUIRE(test_email_alerter.classifyTemperatureBreach(22) == Breach::BreachType::NORMAL);

  REQUIRE(test_email_alerter.sendAlert(Breach::TOO_HIGH) == test_high_breach_msg);
  REQUIRE(test_email_alerter.sendAlert(Breach::TOO_LOW) == test_low_breach_msg);
  REQUIRE(test_email_alerter.sendAlert(Breach::NORMAL) == test_no_breach_msg);
}

TEST_CASE_METHOD(ControllerAlerter, "classifies the breach type and sends controller alert"){
  ControllerAlerter test_controller_alerter;
  test_controller_alerter.brand = "brand_A";
  test_controller_alerter.cooling_type = BatteryCharacter::HI_ACTIVE_COOLING;
  std::string test_controller_msg = "0xfeed : ";

  REQUIRE(test_controller_alerter.classifyTemperatureBreach(100) == Breach::BreachType::TOO_HIGH);
  REQUIRE(test_controller_alerter.classifyTemperatureBreach(-10) == Breach::BreachType::TOO_LOW);
  REQUIRE(test_controller_alerter.classifyTemperatureBreach(22) == Breach::BreachType::NORMAL);

  REQUIRE(test_controller_alerter.sendAlert(Breach::TOO_HIGH) == test_controller_msg + std::to_string(Breach::TOO_HIGH));
  REQUIRE(test_controller_alerter.sendAlert(Breach::TOO_LOW) == test_controller_msg + std::to_string(Breach::TOO_LOW));
  REQUIRE(test_controller_alerter.sendAlert(Breach::NORMAL) == test_controller_msg + std::to_string(Breach::NORMAL));

}

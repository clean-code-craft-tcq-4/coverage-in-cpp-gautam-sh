#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "include/alert.hpp"
#include <iostream>

TEST_CASE("infers the breach according to limits") {
  REQUIRE(Breach::inferBreach(12, 20, 30) == Breach::BreachType::TOO_LOW);
  REQUIRE(Breach::inferBreach(20, 20, 30) == Breach::BreachType::NORMAL);
  REQUIRE(Breach::inferBreach(25, 20, 30) == Breach::BreachType::NORMAL);
  REQUIRE(Breach::inferBreach(30, 20, 30) == Breach::BreachType::NORMAL);
  REQUIRE(Breach::inferBreach(31, 20, 30) == Breach::BreachType::TOO_HIGH);
}

TEST_CASE_METHOD(EmailAlerter, "classifies the breach type and sends email alert"){
  EmailAlerter test_email_alerter;
  std::string test_low_breach_msg = "To: a.b@c.com\nHi, the temperature is too low";
  std::string test_high_breach_msg = "To: a.b@c.com\nHi, the temperature is too high";
  std::string test_no_breach_msg = "To: a.b@c.com\nHi, the temperature is normal";

  REQUIRE(test_email_alerter.sendAlert(Breach::TOO_HIGH) == test_high_breach_msg);
  REQUIRE(test_email_alerter.sendAlert(Breach::TOO_LOW) == test_low_breach_msg);
  REQUIRE(test_email_alerter.sendAlert(Breach::NORMAL) == test_no_breach_msg);

  for(auto it : test_email_alerter.cooling_type_limits) {
    test_email_alerter.cooling_type = it.first;

    double test_temp_lower = it.second.first - 0.5;
    double test_temp_higher = it.second.second + 0.5;
    double test_temp_normal = (it.second.first + it.second.second)/2;

    REQUIRE(test_email_alerter.classifyTemperatureBreach(test_temp_higher) == Breach::BreachType::TOO_HIGH);
    REQUIRE(test_email_alerter.classifyTemperatureBreach(test_temp_lower) == Breach::BreachType::TOO_LOW);
    REQUIRE(test_email_alerter.classifyTemperatureBreach(test_temp_normal) == Breach::BreachType::NORMAL);
    REQUIRE(test_email_alerter.classifyTemperatureBreach(it.second.first) == Breach::BreachType::NORMAL);
    REQUIRE(test_email_alerter.classifyTemperatureBreach(it.second.second) == Breach::BreachType::NORMAL);

    test_email_alerter.checkAndAlert(test_temp_higher, false);
    REQUIRE(test_email_alerter.breachType == Breach::BreachType::TOO_HIGH);
    REQUIRE(test_email_alerter.alert_msg == test_high_breach_msg);

    test_email_alerter.checkAndAlert(test_temp_lower, false);
    REQUIRE(test_email_alerter.breachType == Breach::BreachType::TOO_LOW);
    REQUIRE(test_email_alerter.alert_msg == test_low_breach_msg);
    
    test_email_alerter.checkAndAlert(test_temp_normal, false);
    REQUIRE(test_email_alerter.breachType == Breach::BreachType::NORMAL);
    REQUIRE(test_email_alerter.alert_msg == test_no_breach_msg);
  }
}

TEST_CASE_METHOD(ControllerAlerter, "updates the breach limits and sends controller alert"){
  ControllerAlerter test_controller_alerter;
  std::string test_controller_msg = "0xfeed : ";

  for(auto it : test_controller_alerter.cooling_type_limits) {
    test_controller_alerter.updateLimits(it.first, -5, 200);
    REQUIRE(test_controller_alerter.cooling_type_limits[it.first].first == -5);
    REQUIRE(test_controller_alerter.cooling_type_limits[it.first].second == 200);

    REQUIRE(test_controller_alerter.sendAlert(Breach::TOO_HIGH) == test_controller_msg + std::to_string(Breach::TOO_HIGH));
    REQUIRE(test_controller_alerter.sendAlert(Breach::TOO_LOW) == test_controller_msg + std::to_string(Breach::TOO_LOW));
    REQUIRE(test_controller_alerter.sendAlert(Breach::NORMAL) == test_controller_msg + std::to_string(Breach::NORMAL));
  }
}


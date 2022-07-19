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
  }
  
  std::string test_low_breach_msg = "To: a.b@c.com\nHi, the temperature is too low";
  std::string test_high_breach_msg = "To: a.b@c.com\nHi, the temperature is too high";
  std::string test_no_breach_msg = "To: a.b@c.com\nHi, the temperature is normal";

  REQUIRE(test_email_alerter.sendAlert(Breach::TOO_HIGH) == test_high_breach_msg);
  REQUIRE(test_email_alerter.sendAlert(Breach::TOO_LOW) == test_low_breach_msg);
  REQUIRE(test_email_alerter.sendAlert(Breach::NORMAL) == test_no_breach_msg);
}

TEST_CASE_METHOD(ControllerAlerter, "updates the breach limits and sends controller alert"){
  ControllerAlerter test_controller_alerter;
  // test_controller_alerter.brand = "brand_A";

  // for(auto it : test_controller_alerter.cooling_type_limits) {
  //   test_controller_alerter.cooling_type = it.first;

  //   double test_temp_lower = it.second.first - 0.5;
  //   double test_temp_higher = it.second.second + 0.5;
  //   double test_temp_normal = (it.second.first + it.second.second)/2;

  //   REQUIRE(test_controller_alerter.classifyTemperatureBreach(test_temp_higher) == Breach::BreachType::TOO_HIGH);
  //   REQUIRE(test_controller_alerter.classifyTemperatureBreach(test_temp_lower) == Breach::BreachType::TOO_LOW);
  //   REQUIRE(test_controller_alerter.classifyTemperatureBreach(test_temp_normal) == Breach::BreachType::NORMAL);
  //   REQUIRE(test_controller_alerter.classifyTemperatureBreach(it.second.first) == Breach::BreachType::NORMAL);
  //   REQUIRE(test_controller_alerter.classifyTemperatureBreach(it.second.second) == Breach::BreachType::NORMAL);
  // }

  for(auto it : test_controller_alerter.cooling_type_limits) {
    test_controller_alerter.updateLimits(it.first, -5, 200);
    REQUIRE(test_controller_alerter.cooling_type_limits[it.first].first == -5);
    REQUIRE(test_controller_alerter.cooling_type_limits[it.first].second == 200);
  }

  std::string test_controller_msg = "0xfeed : ";

  REQUIRE(test_controller_alerter.sendAlert(Breach::TOO_HIGH) == test_controller_msg + std::to_string(Breach::TOO_HIGH));
  REQUIRE(test_controller_alerter.sendAlert(Breach::TOO_LOW) == test_controller_msg + std::to_string(Breach::TOO_LOW));
  REQUIRE(test_controller_alerter.sendAlert(Breach::NORMAL) == test_controller_msg + std::to_string(Breach::NORMAL));

}

// TEST_CASE("classifies the breach type"){
  // Alerter* test_controller_alerter;
  // EmailAlerter* test_email_alerter;

  // std::vector<Alerter*> test_alerter = {test_controller_alerter, test_email_alerter};

  // for(auto alert_it : test_alerter) {
    // for(auto it : alert_it->cooling_type_limits) {
  //       alert_it->cooling_type = it.first;

  //       double test_temp_lower = it.second.first - 0.5;
  //       double test_temp_higher = it.second.second + 0.5;
  //       double test_temp_normal = (it.second.first + it.second.second)/2;

        // REQUIRE(alert_it->classifyTemperatureBreach(test_temp_higher) == Breach::BreachType::TOO_HIGH);
        // REQUIRE(alert_it->classifyTemperatureBreach(test_temp_lower) == Breach::BreachType::TOO_LOW);
        // REQUIRE(alert_it->classifyTemperatureBreach(test_temp_normal) == Breach::BreachType::NORMAL);
        // REQUIRE(alert_it->classifyTemperatureBreach(it.second.first) == Breach::BreachType::NORMAL);
        // REQUIRE(alert_it->classifyTemperatureBreach(it.second.second) == Breach::BreachType::NORMAL);
      // }
  // }
// }


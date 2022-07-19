#include "battery_character.hpp"
#include <map>

class Alerter : public BatteryCharacter {
    public:

    enum AlertTarget {
    TO_CONTROLLER,
    TO_EMAIL
    };

    void checkAndAlert(double temperatureInC){

        Breach::BreachType breachType = BatteryCharacter::classifyTemperatureBreach(temperatureInC);
        AlertTarget test_alert;
        printMessage(sendAlert(breachType));
    }

    virtual std::string sendAlert(BreachType breachType) = 0;

    void printMessage(std::string msg) {
        std::cout << msg << std::endl;
    }
};

class EmailAlerter : public Alerter {
    public:
    std::string sendAlert(BreachType breachType){
    std::string recepient = "a.b@c.com";
    std::string low_breach_msg = "To: " + recepient + "\nHi, the temperature is too low";
    std::string high_breach_msg = "To: " + recepient + "\nHi, the temperature is too high";
    std::string no_breach_msg = "To: " + recepient + "\nHi, the temperature is normal";

    std::map<Breach::BreachType, std::string> breach_type_msgs = {
            {Breach::TOO_LOW,low_breach_msg},
            {Breach::TOO_HIGH,high_breach_msg},
            {Breach::NORMAL,no_breach_msg}};

    return breach_type_msgs[breachType];
    }
};

class ControllerAlerter : public Alerter {
    public:
    std::string sendAlert(BreachType breachType){
        std::string control_msg = "0xfeed : " + std::to_string(breachType);
        return control_msg;
  }
};
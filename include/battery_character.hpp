#include "breach.hpp"
#include <iostream>
#include <utility>
#include <map>

class BatteryCharacter : public Breach {

    public: 

    enum CoolingType {
        PASSIVE_COOLING,
        HI_ACTIVE_COOLING,
        MED_ACTIVE_COOLING
        };

    CoolingType cooling_type;
    std::string brand;

    std::map<BatteryCharacter::CoolingType, std::pair<double,double>> cooling_type_limits = {
        {PASSIVE_COOLING,std::make_pair(0,35)},
        {HI_ACTIVE_COOLING,std::make_pair(0,45)},
        {MED_ACTIVE_COOLING,std::make_pair(0,40)}};

    void updateLimits(CoolingType fcooling_type, double flower_limit, double fupper_limit) {
        cooling_type_limits[fcooling_type] = std::make_pair(flower_limit, fupper_limit);
    }

    BreachType classifyTemperatureBreach(double temperatureInC){
        return inferBreach(temperatureInC, cooling_type_limits[cooling_type].first, cooling_type_limits[cooling_type].second);
    }
};
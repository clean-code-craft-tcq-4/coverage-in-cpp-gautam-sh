#include <vector>
#include <algorithm>
#include <iostream>

class Breach {

    public:

    enum BreachType {
            TOO_LOW,
            NORMAL,
            TOO_HIGH
    };

    static BreachType inferBreach(double value, double lowerLimit, double upperLimit){

    std::vector<double> boundary = {lowerLimit, upperLimit};
    auto it = std::upper_bound(boundary.begin(), boundary.end(), value);
    if(value == upperLimit) --it;
    return BreachType(it -boundary.begin());
    }

};
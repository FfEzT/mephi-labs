#include "module/BasicSensor.h"

#include <stdexcept>

using namespace GameLogic;
using namespace module;

using namespace coord;

using std::unordered_set;

BasicSensor::BasicSensor(unsigned energy, unsigned priority,
    unsigned coast, float angle, Direction direct)
    : BasicModule(energy, priority, coast), angle_(angle),
      direct_( std::move(direct) )
{
    if (angle < 0)
        throw std::invalid_argument("Angle is negative number");
}

float BasicSensor::getAngle() const
{
    return angle_;
}

unsigned BasicSensor::getRadius() const
{
    return direct_.getSpeed();
}

const unordered_set<id_t>& BasicSensor::getEnvironmentInfo() const
{
    static const unordered_set<id_t> empty{};
    return isOn() ? surroundingObjects : empty;
}

void BasicSensor::setEnvironmentInfo(unordered_set<id_t> enviroment)
{
    surroundingObjects = std::move(enviroment);
}

const Direction& BasicSensor::getDirection() const
{
    return direct_;
}
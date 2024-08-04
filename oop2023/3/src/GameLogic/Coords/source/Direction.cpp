#include "coord/Direction.h"

#include <cmath>
#include <stdexcept>

using namespace GameLogic;
using namespace coord;

Direction::Direction(int xPos, int yPos)
    : speed(
        std::sqrt(xPos * xPos + yPos * yPos))
{
    if (xPos == 0 && yPos == 0)
        throw std::invalid_argument("NULL vector");

    int max = std::max(
        std::abs(xPos),
        std::abs(yPos)
    );

    x = std::round(
        (double)xPos / (double)max
    );

    y = std::round(
        (double)yPos / (double)max
    );
}

short Direction::getX() const
{
    return x;
}

short Direction::getY() const
{
    return y;
}

unsigned Direction::getSpeed() const
{
    return speed;
}

Direction& Direction::setSpeed(unsigned value)
{
    speed = value;
    return *this;
}

// TODO для поворота сенсора
Direction Direction::operator+(const Direction& right)
{
    return {};
}
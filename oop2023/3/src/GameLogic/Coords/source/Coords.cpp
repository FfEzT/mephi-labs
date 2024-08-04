#include "coord/Coords.h"

#include <cmath>
#include <tuple>

using namespace GameLogic;
using namespace coord;
using std::tie;

double Coords::distance(const Coords& lSide, const Coords& rSide)
{
    return sqrt(
        distanceSquared(lSide, rSide)
    );
}

unsigned Coords::distanceSquared(const Coords& lSide, const Coords& rSide)
{
    int xTmp = (int)lSide.x - (int)rSide.x;
    int yTmp = (int)lSide.y - (int)rSide.y;

    xTmp *= xTmp;
    yTmp *= yTmp;

    return xTmp + yTmp;
}

Coords Coords::operator+(const Coords& other) const
{
    return { x + other.x, y + other.y };
}
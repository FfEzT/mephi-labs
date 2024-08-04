#pragma once

#include <optional>
#include <queue>

#include "ISubject.h"
#include "coord/Direction.h"
#include "coord/Coords.h"

namespace GameLogic {
    namespace subject {
        using namespace coord;
        using std::optional;

        class IMoveable : public ISubject
        {
        public:
            virtual const Direction& getDirection() const = 0;

            virtual optional<Coords> getNextPosition() const = 0;
            virtual bool popNextPosition() = 0;

            virtual void addNextPositions(std::queue<Coords>) = 0;
            virtual void setNextPositions(std::queue<Coords>) = 0;

            virtual void setDirection(Direction) = 0;
        };
    }
}
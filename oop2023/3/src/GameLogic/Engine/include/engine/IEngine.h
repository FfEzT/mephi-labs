#pragma once

#include "coord/Coords.h"
#include "enviroment/Database.h"

namespace GameLogic {
    namespace engine {
        class IEngine
        {
        public:
            virtual ~IEngine() = default;
            
            virtual void init(coord::Coords fieldSize) = 0;

            virtual void findPointInterest(const Database&) = 0;
        };
    }
}
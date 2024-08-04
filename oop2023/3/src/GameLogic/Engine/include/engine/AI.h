#pragma once

#include "IEngine.h"

namespace GameLogic {
    namespace engine {
        class AI : public IEngine
        {
        public:
            void init(coord::Coords fieldSize) override;

            void findPointInterest(const Database& data) override;
        };
    }
}
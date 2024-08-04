#pragma once

#include "ISensor.h"
#include "BasicModule.h"
#include "coord/Direction.h"

namespace GameLogic {
    namespace module {
        class BasicSensor : public BasicModule<ISensor>
        {
        public:
            BasicSensor(unsigned energy, unsigned priority,
                unsigned coast, float angle,
                coord::Direction direct = coord::Direction());

            float getAngle() const override;

            unsigned getRadius() const override;

            const std::unordered_set<id_t>& getEnvironmentInfo() const override;

            void setEnvironmentInfo(std::unordered_set<id_t> enviroment) override;

            const coord::Direction& getDirection() const override;

        private:
            std::unordered_set<id_t> surroundingObjects;
            coord::Direction direct_;
            float angle_;
        };
    }
}
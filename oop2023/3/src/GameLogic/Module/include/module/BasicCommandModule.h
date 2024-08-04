#pragma once

#include <vector>

#include "BasicModule.h"
#include "ICommandModule.h"

namespace GameLogic {
    namespace module {
        class BasicCommandModule : public BasicModule<ICommandModule>
        {
        public:
            BasicCommandModule(unsigned energy, unsigned priority, unsigned coast, unsigned radius)
                : BasicModule(energy, priority, coast), radius_(radius)
            {}

            void setControlledRobot(std::unordered_set<id_t> controlledPlatforms) override
            {
                controlledPlatforms_ = std::move(controlledPlatforms);
            }

            const std::unordered_set<id_t>& getControlledRobot() const override
            {
                static const std::unordered_set<id_t> empty{};
                return isOn() ? controlledPlatforms_ : empty;
            }

            unsigned getRadius() const override
            {
                return radius_;
            }

        private:
            std::unordered_set<id_t> controlledPlatforms_;
            unsigned radius_;
        };
    }
}
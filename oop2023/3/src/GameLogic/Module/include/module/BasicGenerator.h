#pragma once

#include "BasicModule.h"
#include "IGenerator.h"

namespace GameLogic {
    namespace module {
        class BasicGenerator : public BasicModule<IGenerator>
        {
        public:
            BasicGenerator(unsigned energy, unsigned priority, unsigned coast)
                : BasicModule(energy, priority, coast)
            {}

            unsigned generate() const override
            {
                return isOn()? getEnergy() : 0;
            }
        };
    }
}
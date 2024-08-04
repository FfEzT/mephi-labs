#pragma once

#include "IModule.h"

namespace GameLogic {
    namespace module {
        template <typename Parent = IModule>
        class BasicModule : public Parent
        {
        public:
            BasicModule(unsigned energy, unsigned priority, unsigned coast)
                : energy_(energy), priority_(priority), coast_(coast), isOn_(true)
            {}

            unsigned getEnergy() const override
            {
                return energy_;
            }

            unsigned getPriority() const override
            {
                return priority_;
            }

            unsigned getCost() const override
            {
                return coast_;
            }

            bool isOn() const override
            {
                return isOn_;
            }

            void setIsOn(bool flag) override
            {
                isOn_ = flag;
            }

        private:
            unsigned energy_;
            unsigned priority_;
            unsigned coast_;
            bool isOn_;
        };
    }
}
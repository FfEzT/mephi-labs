#pragma once

#include "IModule.h"
#include "id_t.h"

namespace GameLogic {
    namespace module {
        class ICommandModule : public IModule
        {
        public:
            virtual unsigned getRadius() const = 0;

            virtual void setControlledRobot(std::unordered_set<id_t> platforms) = 0;

            virtual const std::unordered_set<id_t>& getControlledRobot() const = 0;
        };
    }
}
#pragma once

#include "IModule.h"

namespace GameLogic {
    namespace module {

        /**
         * @brief Interface for generators in the game.
         * method getEnergy will be ignored, so You can call getEnergy in generate
         */
        class IGenerator : public IModule {
        public:
            /**
             * @brief Generate a resource or value.
             * @return The generated value.
             */
            virtual unsigned generate() const = 0;
        };
    } // namespace module
} // namespace GameLogic

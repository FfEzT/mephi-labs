#pragma once

#include <unordered_set>
#include "IModule.h"
#include "id_t.h"
#include "coord/Direction.h"

namespace GameLogic {
    namespace module {

        /**
         * @brief Interface for sensors in the game.
         */
        class ISensor : public IModule {
        public:
            /**
             * @brief Get information about the environment sensed by the sensor.
             * @return A reference to an unordered set of object IDs.
             */
            virtual const std::unordered_set<id_t>& getEnvironmentInfo() const = 0;

            /**
             * @brief Set information about the environment sensed by the sensor.
             * @param environmentInfo An unordered set of object IDs.
             */
            virtual void setEnvironmentInfo(std::unordered_set<id_t> environmentInfo) = 0;

            /**
             * @brief Get the angle of the sensor.
             * @return The angle in radians.
             */
            virtual float getAngle() const = 0;

            /**
             * @brief Get the direction of the sensor.
             * @return A reference to the Direction sensor.
             */
            virtual const coord::Direction& getDirection() const = 0;

            /**
             * @brief Get the radius of the sensor's coverage.
             * @return The radius value.
             */
            virtual unsigned getRadius() const = 0;
        };
    } // namespace module
} // namespace GameLogic

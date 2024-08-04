#pragma once

namespace GameLogic {

    /**
     * @brief Namespace for module-related functionality.
     */
    namespace module {

        /**
         * @brief Interface for game modules.
         */
        class IModule {
        public:
            /**
             * @brief Virtual destructor for interface.
             */
            virtual ~IModule() = default;

            /**
             * @brief Get the energy level of the module.
             * @return The energy level.
             */
            virtual unsigned getEnergy() const = 0;

            /**
             * @brief Get the priority level of the module.
             * @return The priority level.
             */
            virtual unsigned getPriority() const = 0;

            /**
             * @brief Get the cost of the module.
             * @return The cost.
             */
            virtual unsigned getCost() const = 0;

            /**
             * @brief Check if the module is currently on.
             * @return True if the module is on, false otherwise.
             */
            virtual bool isOn() const = 0;

            /**
             * @brief Set the on/off state of the module.
             * @param on The new state (true for on, false for off).
             */
            virtual void setIsOn(bool on) = 0;
        };
    } // namespace module
} // namespace GameLogic

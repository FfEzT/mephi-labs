#pragma once

#include <string>
#include <memory>
#include <vector>
#include <unordered_set>
#include "IObject.h"
#include "module/ISensor.h"
#include "module/IGenerator.h"

namespace GameLogic {
    namespace object {
        using std::string;
        using std::shared_ptr;
        using std::unique_ptr;
        using std::vector;

        /**
         * @brief Represents a platform in the game.
         */
        class Platform : public IObject {
        public:
            /**
             * @brief Check if the platform is active.
             * @return True if active, false otherwise.
             */
            virtual bool isActive() const = 0;

            /**
             * @brief Check if the platform is under control.
             * @return True if under control, false otherwise.
             */
            virtual bool isUnderControl() const = 0;

            /**
             * @brief Set the under control state of the platform.
             * @param underControl The new state (true for under control, false otherwise).
             */
            virtual void setIsUnderControl(bool underControl) = 0;

            /**
             * @brief Get the energy level of the platform.
             * @return The energy level.
             */
            virtual unsigned getEnergy() const = 0;

            /**
             * @brief Get the sum of energy from all modules on the platform.
             * @return The sum of energy.
             */
            virtual unsigned getSumEnergy() const = 0;

            /**
             * @brief Get the cost of the platform.
             * @return The cost.
             */
            virtual unsigned getCost() const = 0;

            /**
             * @brief Get the maximum count of modules that can be added to the platform.
             * @return The maximum module count.
             */
            virtual size_t getMaxModuleCount() const = 0;

            /**
             * @brief Get the current count of modules on the platform.
             * @return The current module count.
             */
            virtual size_t getModuleCount() const = 0;

            /**
             * @brief Get the description of the platform.
             * @return The description.
             */
            virtual const string& getDescribe() const = 0;

            /**
             * @brief Add a module to the platform.
             * @param module The module to add.
             * @return A unique pointer to the added module.
             */
            virtual unique_ptr<module::IModule> setModule(unique_ptr<module::IModule> module);

            /**
             * @brief Get information about the environment sensed by the platform's sensors.
             * @return An unordered set of object IDs.
             */
            virtual std::unordered_set<id_t> getEnvironmentInfo() const = 0;

            /**
             * @brief Delete a sensor module from the platform.
             * @param element const_iterator pointing to the sensor module to delete.
             */
            virtual void deleteModule(vector<shared_ptr<module::ISensor>>::const_iterator element) = 0;

            /**
             * @brief Delete a generator module from the platform.
             * @param element const_iterator pointing to the generator module to delete.
             */
            virtual void deleteModule(vector<shared_ptr<module::IGenerator>>::const_iterator element) = 0;

            /**
             * @brief Turn on a sensor module on the platform.
             * @param element const_iterator pointing to the sensor module to turn on.
             */
            virtual void onModule(vector<shared_ptr<module::ISensor>>::const_iterator element) = 0;

            /**
             * @brief Turn on a generator module on the platform.
             * @param element const_iterator pointing to the generator module to turn on.
             */
            virtual void onModule(vector<shared_ptr<module::IGenerator>>::const_iterator element) = 0;

            /**
             * @brief Turn off a sensor module on the platform.
             * @param element const_iterator pointing to the sensor module to turn off.
             */
            virtual void offModule(vector<shared_ptr<module::ISensor>>::const_iterator element) = 0;

            /**
             * @brief Turn off a generator module on the platform.
             * @param element const_iterator pointing to the generator module to turn off.
             */
            virtual void offModule(vector<shared_ptr<module::IGenerator>>::const_iterator element) = 0;

            /**
             * @brief Get a reference to the vector of sensors on the platform.
             * @return A reference to the vector of sensors.
             */
            virtual const vector<shared_ptr<module::ISensor>>& getSensors() const = 0;

            /**
             * @brief Get a reference to the vector of generators on the platform.
             * @return A reference to the vector of generators.
             */
            virtual const vector<shared_ptr<module::IGenerator>>& getGenerators() const = 0;

        protected:
            /**
             * @brief Check if a new module can be added to the platform.
             * @return True if a new module can be added, false otherwise.
             */
            virtual bool canSetModule() const;

            /**
             * @brief Check and adjust the energy level of the platform based on module changes.
             */
            virtual void checkEnergy() = 0;

            /**
             * @brief Set a sensor module on the platform.
             * @param sensor The sensor module to set.
             */
            virtual void setModule_(shared_ptr<module::ISensor> sensor) = 0;

            /**
             * @brief Set a generator module on the platform.
             * @param generator The generator module to set.
             */
            virtual void setModule_(shared_ptr<module::IGenerator> generator) = 0;
        };
    } // namespace object
} // namespace GameLogic

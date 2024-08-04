#pragma once

#include <vector>
#include <memory>
#include <string>

#include "BasicPlatform.h"
#include "ICommandPlatform.h"

namespace GameLogic {
    namespace object {
        class BasicCommandPlatform : public BasicPlatform<ICommandPlatform>
        {
        public:
            BasicCommandPlatform(std::string describe, unsigned coast,
                unsigned energy, size_t maxModuleCount);

            bool isUnderControl() const override
            {
                return true;
            }

            virtual void setIsUnderControl(bool) override
            {}

            size_t getIdTexture() const override;

            size_t getModuleCount() const override;

            unsigned getSumEnergy() const override;

            std::unordered_set<id_t> getControlledPlatform() const override;

            const std::vector< std::shared_ptr<module::ICommandModule>>& getCommandModule() const override;

            void onModule(std::vector<std::shared_ptr<module::ICommandModule>>::const_iterator element) override;
            void offModule(std::vector<std::shared_ptr<module::ICommandModule>>::const_iterator element) override;
            void deleteModule(std::vector<std::shared_ptr<module::ICommandModule>>::const_iterator element) override;

        private:
            void setModule_(std::shared_ptr<module::ICommandModule> ptr) override;

            std::vector<std::weak_ptr<module::IModule>> getAllModules() const override;

            std::vector <std::shared_ptr<module::ICommandModule>> commandModules;
        };
    }
}

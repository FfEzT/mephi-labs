#pragma once

#include <vector>
#include <memory>

#include "IPlatform.h"
#include "module/allBasic.h"

namespace GameLogic {
    namespace object {
        class ICommandPlatform : public Platform
        {
        public:
            unique_ptr<module::IModule> setModule(unique_ptr<module::IModule> module) override;

            virtual std::unordered_set<id_t> getControlledPlatform() const = 0;

            virtual const vector< shared_ptr<module::ICommandModule> >& getCommandModule() const = 0;

            virtual void onModule(    vector<shared_ptr<module::ICommandModule>>::const_iterator element) = 0;
            virtual void offModule(   vector<shared_ptr<module::ICommandModule>>::const_iterator element) = 0;
            virtual void deleteModule(vector<shared_ptr<module::ICommandModule>>::const_iterator element) = 0;

        protected:
            virtual void setModule_(shared_ptr<module::ICommandModule>) = 0;
        };
    }
}

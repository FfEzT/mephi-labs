#include "object/IPlatform.h"

using namespace GameLogic;
using namespace object;
using namespace module;

using std::unique_ptr;
using std::shared_ptr;

unique_ptr<IModule> Platform::setModule(unique_ptr<IModule> module)
{
    if (!canSetModule())
        return module;

    IModule* ptr_ = module.get();

    if (ISensor* ptr = dynamic_cast<ISensor*>(ptr_); ptr) {
        setModule_(
            shared_ptr<ISensor>(ptr)
        );
    }
    else if (IGenerator* ptr = dynamic_cast<IGenerator*>(ptr_); ptr) {
        setModule_(
            shared_ptr<IGenerator>(ptr)
        );
    }
    else {
        return module;
    }

    checkEnergy();

    module.release();
    return nullptr;
}

bool Platform::canSetModule() const
{
    return getModuleCount() < getMaxModuleCount();
}
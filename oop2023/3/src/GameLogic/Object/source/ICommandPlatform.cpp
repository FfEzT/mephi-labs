#include "object/ICommandPlatform.h"

using namespace GameLogic;
using namespace object;
using namespace module;

using std::unique_ptr;
using std::shared_ptr;

unique_ptr<IModule> ICommandPlatform::setModule(unique_ptr<IModule> module)
{
    module = Platform::setModule(std::move(module));

    if (!module)
        return nullptr;
    if (!canSetModule())
        return module;

    IModule* ptr_ = module.get();

    if (ICommandModule* ptr = dynamic_cast<ICommandModule*>(ptr_); ptr) {
        setModule_(
            shared_ptr<ICommandModule>(ptr)
        );
    }
    else {
        return module;
    }

    module.release();
    return nullptr;
}

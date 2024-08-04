#pragma once

#include <memory>

#include "subject/ISubject.h"
#include "object/IObject.h"
#include "module/IModule.h"

namespace graphic {
    using namespace GameLogic::object;
    using namespace GameLogic::subject;
    using namespace GameLogic::module;

    using std::shared_ptr;
    using std::unique_ptr;

    class Builder {
    public:
        shared_ptr<ISubject> createInterest();

        shared_ptr<ISubject> createLet();

        shared_ptr<ISubject> createMovePlatform();

        shared_ptr<ISubject> createStaticPlatform();

        shared_ptr<ISubject> createMoveCommandPlatform();

        shared_ptr<ISubject> createStaticCommandPlatform();

    private:
        unique_ptr<IObject> makePlatform();

        unique_ptr<IObject> makeCommandPlatform();

        unique_ptr<IModule> makeSensor();

        unique_ptr<IModule> makeGenerator();

        unique_ptr<IModule> makeCommandModule();
    };
}
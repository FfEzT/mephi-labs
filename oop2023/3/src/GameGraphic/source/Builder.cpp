#include "Builder.h"

#include "subject/BasicSubject.h"
#include "subject/Moveable.h"
#include "object/BasicCommandPlatform.h"
#include "object/BasicPlatform.h"

using namespace graphic;
using namespace GameLogic::coord;
using std::make_unique;

shared_ptr<ISubject> Builder::createInterest()
{
    return shared_ptr<ISubject>(
        new BasicSubject<>(
            make_unique<IPointInterest>()
        )
    );
}

shared_ptr<ISubject> Builder::createLet()
{
    return shared_ptr<ISubject>(
        new BasicSubject<>(
            make_unique<ILet>()
        )
    );
}

shared_ptr<ISubject> Builder::createMovePlatform()
{
    return shared_ptr<ISubject>(
        new Moveable(
            Direction().setSpeed(0),
            makePlatform()
        )
    );
}

shared_ptr<ISubject> Builder::createStaticPlatform()
{
    return shared_ptr<ISubject>(
        new BasicSubject(
            makePlatform()
        )
    );
}

shared_ptr<ISubject> Builder::createMoveCommandPlatform()
{
    return shared_ptr<ISubject>(
        new Moveable(
            Direction().setSpeed(0),
            makeCommandPlatform()
        )
    );
}

shared_ptr<ISubject> Builder::createStaticCommandPlatform()
{
    return shared_ptr<ISubject>(
        new BasicSubject(
            makeCommandPlatform()
        )
    );
}

unique_ptr<IObject> Builder::makePlatform()
{
    auto platform = BasicPlatform("Platform", 100, 5, 5);

    platform.setModule(
        makeSensor()
    );
    platform.setModule(
        makeGenerator()
    );

    return unique_ptr<IObject>(
        new BasicPlatform(platform)
    );

}

unique_ptr<IObject> Builder::makeCommandPlatform()
{
    auto platform = BasicCommandPlatform("Command platform", 100, 5, 5);

    platform.setModule(
        makeSensor()
    );
    platform.setModule(
        makeGenerator()
    );
    platform.setModule(
        makeCommandModule()
    );

    return unique_ptr<IObject>(
        new BasicCommandPlatform(platform)
    );

}

unique_ptr<IModule> Builder::makeSensor() {
    return unique_ptr<IModule>(new BasicSensor(1, 0, 25, 90));
}

unique_ptr<IModule> Builder::makeGenerator() {
    return unique_ptr<IModule>(new BasicGenerator(10, 2, 50));
}

unique_ptr<IModule> Builder::makeCommandModule() {
    return unique_ptr<IModule>(new BasicCommandModule(1, 1, 75, 1));
}
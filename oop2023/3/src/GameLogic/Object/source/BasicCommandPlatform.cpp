#include "object/BasicCommandPlatform.h"

#include <algorithm>
#include <iterator>

using namespace GameLogic;
using namespace object;
using namespace module;

using std::string;
using std::vector;
using std::shared_ptr;
using std::weak_ptr;
using std::unordered_set;
using std::copy;
using std::unique;
using std::back_inserter;
using const_iterator = vector<std::shared_ptr<module::ICommandModule>>::const_iterator;

BasicCommandPlatform::BasicCommandPlatform(string describe, unsigned coast,
    unsigned energy, size_t maxModuleCount)
    : BasicPlatform(std::move(describe), coast, energy,
        maxModuleCount)
{}

size_t BasicCommandPlatform::getIdTexture() const
{
    return COMMAND_PLATFORM;
}

size_t BasicCommandPlatform::getModuleCount() const
{
    return BasicPlatform::getModuleCount() + commandModules.size();
}

unsigned BasicCommandPlatform::getSumEnergy() const
{
    unsigned res = BasicPlatform<ICommandPlatform>::getSumEnergy();

    for (auto command : commandModules) {
        res += command->getEnergy();
    }

    return res;
}

unordered_set<id_t> BasicCommandPlatform::getControlledPlatform() const
{
    const vector<shared_ptr<ICommandModule>>& mods = getCommandModule();
    unordered_set<id_t> res;

    for (auto& mod : mods) {
        const auto& robots = mod->getControlledRobot();

        for (auto& robot : robots)
            res.emplace(robot);
    }

    return res;
}

const vector<shared_ptr<ICommandModule>>& BasicCommandPlatform::getCommandModule() const
{
    return commandModules;
}

void BasicCommandPlatform::setModule_(std::shared_ptr<module::ICommandModule> ptr)
{
    commandModules.emplace_back(std::move(ptr));
}

void BasicCommandPlatform::onModule(const_iterator element)
{
    if (inVector(commandModules, element))
        (*element)->setIsOn(true);
}

void BasicCommandPlatform::offModule(const_iterator element)
{
    if (inVector(commandModules, element))
        (*element)->setIsOn(false);

}

void BasicCommandPlatform::deleteModule(const_iterator element)
{
    commandModules.erase(element);
}

vector<weak_ptr<IModule>> BasicCommandPlatform::getAllModules() const
{
    vector<weak_ptr<IModule>> res = BasicPlatform::getAllModules();

    copy(
        commandModules.begin(),
        commandModules.end(),
        back_inserter(res)
    );

    return res;

}
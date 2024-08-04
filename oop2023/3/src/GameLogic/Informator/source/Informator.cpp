#include "informator/Informator.h"

using namespace std;
using namespace GameLogic;
using namespace object;
using namespace coord;

namespace {
    unordered_set<id_t> getObjectsOnCoord(const Database& data, Coords position);

    unordered_set<id_t> getNoCommandPlatformOnCoord(const Database& data, Coords position);

    unordered_set<Coords, CoordsHasher> getCoordsAround(Coords center, unsigned radius);

    void nullUnderControlPlatforms(const Database& data);

    void informPlatformsSensors(const Database& data);

    void inform_platforms_command_modules_and_set_is_under_control(const Database& data);
}

void Informator::updateInfo(const Database& data) const
{
    nullUnderControlPlatforms(data);

    informPlatformsSensors(data);
    inform_platforms_command_modules_and_set_is_under_control(data);
}

#include <iostream>

namespace {
    unordered_set<id_t> getObjectsOnCoord(const Database& data, Coords position)
    {
        auto itPair = data.getIdsByCoords(std::move(position));

        unordered_set<id_t>res;
        for (auto it = itPair.first; it != itPair.second; ++it)
            res.emplace(it->second);

        return res;
    }

    unordered_set<id_t> getNoCommandPlatformOnCoord(const Database& data, Coords position)
    {
        unordered_set<id_t> res = getObjectsOnCoord(data, std::move(position));

        const unordered_set<id_t>& platforms = data.getPlatforms();
        const unordered_set<id_t>& commandPlatforms = data.getCommandPlatforms();
        erase_if(
            res,
            [&](id_t el) {
                return (platforms.find(el) == platforms.end())
                    || (commandPlatforms.find(el) != commandPlatforms.end());
            }
        );

        return res;
    }

    unordered_set<Coords, CoordsHasher> getCoordsAround(Coords center, unsigned radius)
    {
        if (radius == 0)
            return {};

        unordered_set<Coords, CoordsHasher> res;
        for (int x = center.x - static_cast<int>(radius); x <= center.x + static_cast<int>(radius); ++x) {
            // поиск вверх
            for (int y = center.y;
                Coords::distanceSquared(center, Coords(x, y)) <= std::pow(radius, 2);
                ++y)
            {
                res.emplace(x, y);
            }

            // поиск вниз
            for (
                int y = center.y - 1;
                Coords::distanceSquared(center, Coords(x, y)) <= std::pow(radius, 2);
                --y)
            {
                res.emplace(x, y);
            }
        }

        return res;
    }

    void nullUnderControlPlatforms(const Database& data)
    {
        auto& platforms = data.getPlatforms();

        for (auto& platform : platforms) {
            static_cast<object::Platform&>(data.getSubjectById(platform)->getObject()).setIsUnderControl(false);
        }
    }

    // TODO так ты получаешь целый круг вокруг сенсора, надо переписать с использованием углов
    void informPlatformsSensors(const Database& data)
    {
        for (auto id : data.getPlatforms()) {
            Coords position = data.getCoordsById(id);

            Platform& ptr = static_cast<Platform&>(
                data.getSubjectById(id)->getObject()
            );

            for (auto& ptrModule : ptr.getSensors()) {
                std::unordered_set<id_t> res;
                res.reserve(10);

                for (const auto& coord : getCoordsAround(
                    position, ptrModule->getRadius())
                    )
                {
                    res.merge(
                        getObjectsOnCoord(data, coord)
                    );
                }

                ptrModule->setEnvironmentInfo(
                    std::move(res)
                );
            }
        }
    }

    void inform_platforms_command_modules_and_set_is_under_control(const Database& data)
    {
        for (auto id : data.getCommandPlatforms()) {
            Coords position = data.getCoordsById(id);

            ICommandPlatform& ptr = static_cast<ICommandPlatform&>(
                data.getSubjectById(id)->getObject()
            );

            for (auto& ptrModule : ptr.getCommandModule()) {
                std::unordered_set<id_t> res;
                res.reserve(10);

                for (
                    const auto& coord : getCoordsAround(
                        position, ptrModule->getRadius()
                    ))
                {
                    res.merge(
                        getNoCommandPlatformOnCoord(data, coord)
                    );
                }

                for (auto r : res) {
                    static_cast<object::Platform&>(
                        data.getSubjectById(r)->getObject()
                        )
                        .setIsUnderControl(true);
                }

                ptrModule->setControlledRobot(
                    std::move(res)
                );
            }
        }
    }
}
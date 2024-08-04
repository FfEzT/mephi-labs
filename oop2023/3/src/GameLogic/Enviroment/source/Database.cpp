#include "enviroment/Database.h"

using namespace GameLogic;

const std::shared_ptr<subject::ISubject>& Database::getSubjectById(id_t id) const
{
    return idToObj.find(id)->second;
}

const std::unordered_map<id_t, coord::Coords>& Database::getIdToCoord() const
{
    return idToCoord;
}

const std::unordered_set<id_t>& Database::getMoveObjects() const
{
    return moveObjects;
}

const std::unordered_set<id_t>& Database::getPlatforms() const
{
    return platforms;
}

const std::unordered_set<id_t>& Database::getCommandPlatforms() const
{
    return commandPlatforms;
}

coord::Coords Database::getCoordsById(id_t id) const
{
    return idToCoord.find(id)->second;
}

void Database::deleteAtCoord(coord::Coords position)
{
    auto itPair = coordToId.equal_range(position);

    for (auto it = itPair.first; it != itPair.second; ++it) {
        idToCoord.erase(it->second);
        idToObj.erase(it->second);
    }

    coordToId.erase(position);
}

pair<multimapCoordToId::const_iterator, multimapCoordToId::const_iterator>
    Database::getIdsByCoords(coord::Coords position) const
{
    return coordToId.equal_range(std::move(position));
}

void Database::setCoordsById(id_t id, coord::Coords newCoord)
{
    using namespace std;

    // изменение в coordToId
    auto itPair = coordToId.equal_range(idToCoord[id]);
    auto it = itPair.first;
    for (; it != itPair.second; ++it) {
        if (it->second == id)
            break;
    }
    auto node = coordToId.extract(it);
    node.key() = newCoord;
    coordToId.insert(std::move(node));


    // изменение в idToCoord
    idToCoord[id] = std::move(newCoord);
}
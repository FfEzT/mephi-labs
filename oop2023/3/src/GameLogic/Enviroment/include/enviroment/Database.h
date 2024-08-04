#pragma once

#include <unordered_map>
#include <vector>
#include <memory>

#include "id_t.h"
#include "coord/Coords.h"
#include "coord/CoordHasher.h"

#include "object/BasicCommandPlatform.h"
#include "subject/ISubject.h"

#include "subject/BasicSubject.h"
#include "subject/Moveable.h"

namespace GameLogic {
    using std::pair;
    using std::shared_ptr;
    using subject::ISubject;
    using coord::Coords;
    using multimapCoordToId = std::unordered_multimap<coord::Coords, id_t, coord::CoordsHasher>;

    class Database
    {
    public:
        const std::shared_ptr<subject::ISubject>& getSubjectById(id_t id) const;

        const std::unordered_map<id_t, coord::Coords>& getIdToCoord() const;

        const std::unordered_set<id_t>& getMoveObjects() const;

        const std::unordered_set<id_t>& getPlatforms() const;

        const std::unordered_set<id_t>& getCommandPlatforms() const;

        Coords getCoordsById(id_t id) const;

        void deleteAtCoord(Coords position);

        pair<multimapCoordToId::const_iterator, multimapCoordToId::const_iterator> getIdsByCoords(coord::Coords position) const;

        void setCoordsById(id_t id, coord::Coords newCoord);

        id_t addSubject(shared_ptr<ISubject> subject, Coords position)
        {
            idToCoord.emplace(freeId, position);
            coordToId.emplace(position, freeId);

            idToObj.emplace(
                freeId,
                std::move(subject)
            );

            return freeId++;
        }
        
        void addMoveable(id_t id)
        {
            moveObjects.emplace(id);
        }

        void addCommand(id_t id)
        {
            commandPlatforms.emplace(id);
        }

        void addPlatform(id_t id)
        {
            platforms.emplace(id);
        }

    private:
        id_t freeId = 0;

        std::unordered_map<id_t, Coords> idToCoord;
        std::unordered_map<id_t, std::shared_ptr<ISubject>> idToObj;

        std::unordered_multimap<coord::Coords, id_t, coord::CoordsHasher> coordToId;

        std::unordered_set<id_t> platforms;
        std::unordered_set<id_t> commandPlatforms;
        std::unordered_set<id_t> moveObjects;
    };
}
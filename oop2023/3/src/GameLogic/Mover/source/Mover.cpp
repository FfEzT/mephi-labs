#include "mover/Mover.h"

using namespace GameLogic;
using namespace coord;
using namespace subject;
using std::shared_ptr;

namespace {
    bool isInterest(const Database& data, Coords position);

    bool isActivePlatformOrElse(const Database& data, const IMoveable& subject, id_t id);

    void moveObject(Database& data, const Coords& sizeEnviroment, id_t id);
}

void Mover::move(Database& data, const Coords& sizeEnviroment)
{
    const std::unordered_set<id_t>& moveable = data.getMoveObjects();

    for (id_t id : moveable) {
        moveObject(data, sizeEnviroment, id);
    }
}

bool GameLogic::canGo(const Database& data, Coords position)
{
    auto pairIt = data.getIdsByCoords(position);

    if (pairIt.first == pairIt.second)
        return true;

    for (auto it = pairIt.first; it != pairIt.second; ++it) {
        object::IObject& ptr = data.getSubjectById(it->second)->getObject();

        if (!dynamic_cast<object::IPointInterest*>(&ptr))
            return false;
    }
    return true;
}

bool GameLogic::inField(const Coords& size, const Coords& position)
{
    if (   position.x < size.x
        && position.y < size.y
        && position.x >= 0
        && position.y >= 0)
        return true;

    return false;
}

namespace {
    bool isInterest(const Database& data, Coords position)
    {
        auto pairIt = data.getIdsByCoords(position);
        if (pairIt.first == pairIt.second)
            return false;

        for (auto it = pairIt.first; it != pairIt.second; ++it) {
            object::IObject& ptr = data.getSubjectById(it->second)->getObject();

            if (!dynamic_cast<object::IPointInterest*>(&ptr))
                return false;
        }
        return true;
    }

    bool isActivePlatformOrElse(const Database& data, const IMoveable& subject, id_t id)
    {
        auto& platforms = data.getPlatforms();
        if (platforms.find(id) != platforms.end()) {
            const auto& platfrom = static_cast<const object::Platform&>(subject.getObject());

            if (!platfrom.isUnderControl() || !platfrom.isActive())
                return false;
        }
        return true;
    }

    void moveObject(Database& data, const Coords& sizeEnviroment, id_t id)
    {
        IMoveable& subject = static_cast<IMoveable&>(*data.getSubjectById(id).get());

        if (!isActivePlatformOrElse(data, subject, id))
            return;

        const Direction& direct = subject.getDirection();
        Coords currentPosition = data.getCoordsById(id);


        bool isChanged = false;
        // TODO объединить с else
        if (optional<Coords> nextPos = subject.getNextPosition(); nextPos) {
            int x = nextPos->x;
            int y = nextPos->y;

            if (inField(sizeEnviroment, Coords(x, y)))
            {
                if (
                    canGo(
                        data, Coords(x, y)
                    ))
                {
                    currentPosition = Coords(x, y);

                    if (isInterest(data, currentPosition))
                        data.deleteAtCoord(currentPosition);

                    isChanged = true;
                    subject.popNextPosition();
                }
            }
            else {
                subject.setDirection(Direction().setSpeed(0));
            }
        }
        else for (size_t i = 0; i < direct.getSpeed(); ++i) {
            int x = currentPosition.x + direct.getX();
            int y = currentPosition.y + direct.getY();

            if (inField(sizeEnviroment, Coords(x, y))
                && canGo(
                    data, Coords(x, y)
                ))
            {
                currentPosition = Coords(x,y);

                if ( isInterest(data, currentPosition) )
                    data.deleteAtCoord(currentPosition);

                isChanged = true;
            }
            else {
                subject.setDirection(Direction().setSpeed(0));
                break;
            }
        }

        if (isChanged)
            data.setCoordsById(id, std::move(currentPosition));
    }
}

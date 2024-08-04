#include <future>
#include <algorithm>
#include <stack>

#include "enviroment/Enviroment.h"
#include "coord/CoordHasher.h"

using namespace GameLogic;

using coord::Coords;
using engine::IEngine;
using std::unique_ptr;

namespace {
    struct CoordWeight {
        Coords position;
        unsigned weight;

        bool operator<(const CoordWeight& r) const
        {
            return weight > r.weight;
        }
    };

    using std::priority_queue;
    using std::unordered_map;
    using std::stack;
    using CoordsSet = std::unordered_set<Coords, coord::CoordsHasher>;

    std::queue<Coords> findPath(const Database& data, const Coords& size, const Coords& A, const Coords& B)
    {
        priority_queue<CoordWeight> queue;
        unordered_map<Coords, unsigned, coord::CoordsHasher> coordToWeight;

        queue.emplace(A, 0);

        while (!queue.empty()) {
            CoordWeight current = queue.top();
            queue.pop();

            const Coords& currentC = current.position;
            unsigned weight = current.weight;

            if (coordToWeight.find(currentC) != coordToWeight.end())
                continue;
            coordToWeight.emplace(currentC, weight);

            if (currentC == B)
                break;

            if (Coords check = currentC + Coords(1, 0); inField(size, check) && canGo(data, check)) {
                queue.emplace(check, weight + 1);
            }
            if (Coords check = currentC + Coords(0, -1); inField(size, check) && canGo(data, check)) {
                queue.emplace(check, weight + 1);
            }
            if (Coords check = currentC + Coords(-1, 0); inField(size, check) && canGo(data, check)) {
                queue.emplace(check, weight + 1);
            }
            if (Coords check = currentC + Coords(0, 1); inField(size, check) && canGo(data, check)) {
                queue.emplace(check, weight + 1);
            }
            /*if (Coords check = currentC + Coords(1, -1); inField(size, check) && canGo(data, check)) {
                queue.emplace(check, weight + 1);
            }
            if (Coords check = currentC + Coords(-1, -1); inField(size, check) && canGo(data, check)) {
                queue.emplace(check, weight + 1);
            }
            if (Coords check = currentC + Coords(-1, 1); inField(size, check) && canGo(data, check)) {
                queue.emplace(check, weight + 1);
            }
            if (Coords check = currentC + Coords(1, 1); inField(size, check) && canGo(data, check)) {
                queue.emplace(check, weight + 1);
            }*/

        }

        if (coordToWeight.find(B) == coordToWeight.end())
            return {};

        stack<Coords> reversePath;
        Coords current = B;
        unsigned currentW = coordToWeight.find(B)->second;
        reversePath.emplace(B);

        while (current != A) {
            if (auto it = coordToWeight.find(current + Coords(1, 0)); it != coordToWeight.end() && it->second == currentW - 1) {
                reversePath.emplace(it->first);
                current = it->first;
                --currentW;
            }
            else if (auto it = coordToWeight.find(current + Coords(0, -1)); it != coordToWeight.end() && it->second == currentW - 1) {
                reversePath.emplace(it->first);
                current = it->first;
                --currentW;
            }
            else if (auto it = coordToWeight.find(current + Coords(-1, 0)); it != coordToWeight.end() && it->second == currentW - 1) {
                reversePath.emplace(it->first);
                current = it->first;
                --currentW;
            }
            else if (auto it = coordToWeight.find(current + Coords(0, 1)); it != coordToWeight.end() && it->second == currentW - 1) {
                reversePath.emplace(it->first);
                current = it->first;
                --currentW;
            }
            else if (auto it = coordToWeight.find(current + Coords(1, -1)); it != coordToWeight.end() && it->second == currentW - 1) {
                reversePath.emplace(it->first);
                current = it->first;
                --currentW;
            }
            else if (auto it = coordToWeight.find(current + Coords(-1, -1)); it != coordToWeight.end() && it->second == currentW - 1) {
                reversePath.emplace(it->first);
                current = it->first;
                --currentW;
            }
            else if (auto it = coordToWeight.find(current + Coords(-1, 1)); it != coordToWeight.end() && it->second == currentW - 1) {
                reversePath.emplace(it->first);
                current = it->first;
                --currentW;
            }
            else if (auto it = coordToWeight.find(current + Coords(1, 1)); it != coordToWeight.end() && it->second == currentW - 1) {
                reversePath.emplace(it->first);
                current = it->first;
                --currentW;
            }
            else throw std::invalid_argument("error");
        }

        reversePath.pop();
        std::queue<Coords> res;
        while (!reversePath.empty()) {
            res.emplace(reversePath.top());
            reversePath.pop();
        }

        return res;
    }
}

Enviroment::Enviroment(unsigned xSize, unsigned ySize, unique_ptr<IEngine> engine)
    : size_{ static_cast<int>(xSize), static_cast<int>(ySize) }, engine_(std::move(engine))
{
    engine_->init(size_);
}

const Coords& Enviroment::getSize() const
{
    return size_;
}

void Enviroment::doTick()
{
    informator_.updateInfo(data);
    engine_->findPointInterest(data);
    mover_.move(data, size_);
}

const Database& Enviroment::getDatabase() const
{
    return data;
}

Database& Enviroment::getDatabase()
{
    return data;
}

const IEngine& Enviroment::getEngine() const
{
    return *engine_;
}

IEngine& Enviroment::getEngine()
{
    return *engine_;
}

bool Enviroment::addSubject(shared_ptr<ISubject> subject, Coords position)
{
    if (position.x < size_.x
        && position.y < size_.y
        && position.x >= 0
        && position.y >= 0)
    {
        id_t lastId = data.addSubject(subject, position);

        if (dynamic_cast<subject::IMoveable*>(subject.get()))
            data.addMoveable(lastId);

        if (dynamic_cast<object::Platform*>(&subject->getObject()))
            data.addPlatform(lastId);
        if (dynamic_cast<object::ICommandPlatform*>(&subject->getObject()))
            data.addCommand(lastId);

        return true;
    }

    return false;
}

// TODO если монетки уже нет, то ничего не делай
void Enviroment::sendRobotToInterest(const Coords& dist)
{
    using std::unordered_map;
    using std::queue;
    using std::future;
    using std::async;

    using queueCoords = queue<Coords>;
    using futureQueue = future<queueCoords>;

    const auto& commandPlatforms = data.getCommandPlatforms();
    auto                moveable = data.getMoveObjects();

    std::erase_if(
        moveable,
        [&commandPlatforms](id_t id) {
            return commandPlatforms.find(id) == commandPlatforms.end();
        }
    );

    if (moveable.empty())
        return;

    unordered_map<id_t, futureQueue> futures;
    futures.reserve(moveable.size());
    for (auto id : moveable) {
        futures.emplace(
            id,
            async(
                findPath,
                std::ref(data),
                std::ref(size_),
                data.getCoordsById(id),
                std::ref(dist)
            )
        );
    }

    unordered_map<id_t, queueCoords> queues;
    queues.reserve(moveable.size());

    for (auto& pair : futures) {
        auto path = pair.second.get();
        
        if (path.empty())
            continue;

        queues.emplace(
            pair.first,
            std::move(path)
        );
    }

    if (queues.empty())
        return;


    auto minPathIt = std::min_element(
        queues.begin(), queues.end(),
        [](const auto& a, const auto& b) {
            return a.second.size() < b.second.size();
        }
    );

    static_cast<IMoveable&>(*data.getSubjectById(minPathIt->first))
        .setNextPositions(
            std::move(minPathIt->second)
        );
}

#pragma once

#include "BasicSubject.h"
#include "IMoveable.h"

namespace GameLogic {
    namespace subject {
        class Moveable : public BasicSubject<IMoveable>
        {
        public:
            Moveable(coord::Direction direction, std::unique_ptr<object::IObject> object)
                : BasicSubject(std::move(object)), direction_(std::move(direction))
            {}

            const coord::Direction& getDirection() const override
            {
                return direction_;
            }

            void setDirection(coord::Direction direction) override
            {
                direction_ = std::move(direction);
            }

            optional<Coords> getNextPosition() const override
            {
                if (nextPositions.empty())
                    return std::nullopt;
                return nextPositions.front();
            }

            bool popNextPosition() override
            {
                if (nextPositions.empty())
                    return false;

                nextPositions.pop();
                return true;
            }

            void addNextPositions(std::queue<Coords> queue) override
            {
                while (!queue.empty()) {
                    nextPositions.push(std::move(queue.front()));
                    queue.pop();
                }
            }

            void setNextPositions(std::queue<Coords> queue) override
            {
                nextPositions = std::move(queue);
            }

        private:
            Direction direction_;
            std::queue<Coords> nextPositions;
        };
    }
}
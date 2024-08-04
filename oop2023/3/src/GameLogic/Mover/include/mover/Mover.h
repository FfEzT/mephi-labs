#pragma once

#include "coord/Coords.h"
#include "enviroment/Database.h"

namespace GameLogic {
    class Mover
    {
    public:
        void move(
            Database& data,
            const coord::Coords& sizeEnviroment);
    };

    bool canGo(const Database& data, Coords position);

    bool inField(const Coords& size, const Coords& position);
}
#pragma once

#include <stddef.h>

#include "Coords.h"

namespace GameLogic {
    namespace coord {
        struct CoordsHasher
        {
            inline size_t operator() (const Coords& coord) const
            {
                using std::hash;

                static constexpr hash<int> hasher;

                size_t hashX = hasher(coord.x);
                size_t hashY = hasher(coord.y);

                // Ax + B
                size_t x = 37;
                return (hashX * x + hashY);
            }
        };
    }
}
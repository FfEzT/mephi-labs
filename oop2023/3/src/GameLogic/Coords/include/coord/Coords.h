#pragma once

namespace GameLogic {
    namespace coord {
        struct Coords
        {
            int x;
            int y;

            static double distance(const Coords& lSide, const Coords& rSide);

            static unsigned distanceSquared(const Coords& lSide, const Coords& rSide);

            Coords operator+(const Coords& other) const;

            bool operator==(const Coords& rSide) const = default;
        };
    }
}
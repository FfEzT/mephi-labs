#ifndef _HashCard
#define _HashCard

#include <unordered_set>

#include "Card/card.h"

namespace prog2 {
    struct HashCard {
        inline size_t operator() (const Card& card) const
        {
            std::hash<char> hasherGroup;
            std::hash<unsigned> hasherRank;

            const auto& groupRank = card.getGroupRank();

            size_t hashGroup = hasherGroup(
                card.getCharByGroup(groupRank.first)
            );
            size_t hashRank = hasherRank(groupRank.second);

            // Ax + B
            size_t x = 37;
            return (hashGroup * x + hashRank);
        }
    };
}

#endif
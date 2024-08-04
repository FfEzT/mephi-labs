#ifndef _card
#define _card

#include <iostream>

namespace prog2 {
    class Card {
    public:
        enum class GROUP : char
        {
            HEART,
            DIAMOND,
            CLUB,
            SPADE
        };
        static constexpr int GROUP_COUNT = 4;
        static constexpr int RANK_COUNT = 13;

        Card(GROUP group, unsigned rank);
        Card(const Card& obj) = default;
        Card(Card&& obj) noexcept = default;

        Card& operator=(const Card& obj) = default;
        Card& operator=(Card&& obj) noexcept = default;

        std::strong_ordering operator<=>(const Card& other) const;
        bool operator==(const Card& other) const;

        static Card makeRandomCard();
        inline const auto& getGroupRank() const {return groupRank;}
        static GROUP getGroupByNumber(unsigned num);
        static char getCharByGroup(GROUP group);

    private:
        std::pair<GROUP, unsigned> groupRank;
    };

    std::ostream& operator<<(std::ostream& os, const Card& obj);
    std::istream& operator>>(std::istream& os, Card& obj);
}

#endif

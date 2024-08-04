#include <Card/card.h>

#include <utility>

#include <Utils/utils.h>

using namespace prog2;
using GROUP = Card::GROUP;

Card::Card(GROUP group, unsigned rank)
    : groupRank(group, rank)
{
    if (rank > RANK_COUNT || rank < 1)
        throw std::invalid_argument("incorrect rank");
}



std::strong_ordering Card::operator<=>(const Card& other) const
{
    if (groupRank.first != other.groupRank.first)
        throw std::invalid_argument("diffrent group");

    return groupRank <=> other.groupRank;
}

bool Card::operator==(const Card& other) const
{
    return groupRank == other.groupRank;
}



Card Card::makeRandomCard()
{
    unsigned randomNum = utils::getRandom();
    unsigned randomNum2 = utils::getRandom();

    unsigned group = randomNum % (GROUP_COUNT - 1);
    unsigned rank = 1 + randomNum2 % (RANK_COUNT - 1);

    return { Card::getGroupByNumber(group), rank };
}

GROUP Card::getGroupByNumber(unsigned num)
{
    switch (num) {
    case 0:
        return GROUP::HEART;
    case 1:
        return GROUP::DIAMOND;
    case 2:
        return GROUP::CLUB;
    case 3:
        return GROUP::SPADE;
    }

    throw std::invalid_argument("incorrect group number");
}

char Card::getCharByGroup(GROUP group)
{
    switch (group) {
    case GROUP::HEART:
        return 3;
    case GROUP::DIAMOND:
        return 4;
    case GROUP::CLUB:
        return 5;
    case GROUP::SPADE:
        return 6;
    }

    throw std::invalid_argument("hz");
}



std::ostream& prog2::operator<<(std::ostream& os, const Card& obj)
{
    char group = Card::getCharByGroup(
        obj.getGroupRank().first
    );

    os << group << obj.getGroupRank().second;

    return os;
}

std::istream& prog2::operator>>(std::istream& os, Card& obj)
{
    unsigned groupNum;
    unsigned rank;
    os >> groupNum >> rank;

    if (os.good()) {
        GROUP group = Card::getGroupByNumber(groupNum);
        obj = Card(group, rank);
    }
    else {
        os.setstate(std::ios::failbit);
    }


    return os;
}

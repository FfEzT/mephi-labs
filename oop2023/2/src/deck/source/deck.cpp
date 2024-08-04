#include "Deck/deck.h"

#include <set>
#include <iomanip>
#include <algorithm>

#include "Utils/utils.h"
#include "Card/hashCard.h"

using namespace prog2;
using GROUP = Card::GROUP;

namespace {
    std::unordered_map<
        GROUP,
        std::unordered_set<unsigned>
    > getAllAviableCard()
    {
        using vector_unsigned = std::unordered_set<unsigned>;

        std::unordered_map<
            GROUP, vector_unsigned
        > table;

        vector_unsigned temp;
        temp.reserve(Card::RANK_COUNT);

        for (unsigned i = 1; i <= Card::RANK_COUNT; ++i)
            temp.insert(i);

        /*for (auto& it : table) {
            it.second = temp;
        }*/
        table[GROUP::CLUB] = temp;
        table[GROUP::DIAMOND] = temp;
        table[GROUP::HEART] = temp;
        table[GROUP::SPADE] = temp;

        return table;
    }

    GROUP getRandomGroupByMap(
        const std::unordered_map<
        GROUP,
        std::unordered_set<unsigned>
        >& table
    )
    {
        unsigned groupNumeric = utils::getRandom() % table.size();

        auto itTmp = std::next(
            table.begin(),
            groupNumeric
        );

        return itTmp->first;
    }

    unsigned getRundomNumeric(size_t sizeOfSet) {
        if (!sizeOfSet)
            std::invalid_argument("size == 0");

        if (sizeOfSet == 1)
            return 0;

        return utils::getRandom() % (sizeOfSet - 1);
    }
}

int Deck::getNumericFirstCard() const
{
    if (deck.empty())
        throw std::invalid_argument("deck is empty");

    return deck.begin()->first;
}

Deck::Deck(size_t count)
{
    if (count > maxPossibleCardCount)
        throw std::invalid_argument("Very big count for those Cards");

    auto table = getAllAviableCard();

    for (int i = 0; i < count;) {
        GROUP group = getRandomGroupByMap(table);

        std::unordered_set<unsigned>& aviableRanks = table[group];

        if (aviableRanks.empty()) {
            table.erase(group);
            continue;
        }

        auto itRandomNumber = std::next(
            aviableRanks.begin(),
            getRundomNumeric(aviableRanks.size())
        );

        unsigned rank = *itRandomNumber;
        aviableRanks.erase(itRandomNumber);

        deck.emplace(
            i,
            Card(group, rank)
        );

        ++i;
    }
}



Deck Deck::operator+(const Deck& obj) const
{
    Deck res;

    int numeric = 0;
    for (auto it : deck) {
        res.deck.emplace(
            numeric++, it.second
        );
    }

    for (auto it : obj.deck) {
        res.deck.emplace(
            numeric++, it.second
        );
    }

    return res;
}

Deck& Deck::operator>>(Deck& obj)
{
    if (!deck.size())
        throw std::invalid_argument("Your deck is Empty");

    auto node = deck.extract(deck.begin());
    auto& numeric = node.key();

    try {
        numeric = obj.getNumericFirstCard() - 1;
    }
    catch (std::invalid_argument&) {
        numeric = 0;
    }

    obj.deck.insert(
        std::move(node)
    );

    return obj;
}

Card& Deck::operator[](size_t number)
{
    if (number >= deck.size())
        throw std::out_of_range("too big [number]");

    auto it = std::next(
        deck.begin(),
        number
    );

    return it->second;
}

const Card& Deck::operator[](size_t number) const
{
    if (number >= deck.size())
        throw std::out_of_range("too big [number]");

    auto it = std::next(
        deck.begin(),
        number
    );

    return it->second;
}



Deck& Deck::sort()
{
    std::set<
        std::pair<GROUP, unsigned>
    > set;

    for (auto& it : deck)
        set.emplace(it.second.getGroupRank());

    std::map<int, Card> newDeck;

    int i = 0;
    for (auto& it : set) {
        newDeck.emplace(
                i++,
                Card(it.first, it.second)
        );
    }

    deck = std::move(newDeck);

    return *this;
}

Deck& Deck::shuffle()
{
    std::unordered_multiset<Card, HashCard> a;

    for (auto& it : deck)
        a.emplace(it.second);

    deck.clear();

    int numeric = 0;
    while (a.size()) {
        size_t itNum = utils::getRandom() % a.size();

        auto it = std::next(
            a.begin(),
            itNum
        );

        auto node = a.extract(it);
        deck.emplace(
            numeric++, std::move(node.value())
        );
    }

    return *this;
}

Deck Deck::extractByGroup(Card::GROUP group)
{
    Deck res;
    std::map<int, Card> currentDeck;

    for (const auto& it : deck) {
        const Card& card = it.second;
        const GROUP& groupInDeck = card.getGroupRank().first;

        if (groupInDeck == group)
            res.deck.insert(it);
        else currentDeck.insert(it);
    }

    deck = currentDeck;

    return res;
}

Deck& Deck::deleteCard(size_t number)
{
    if (number >= deck.size())
        throw std::out_of_range("too big [number]");

    auto it = std::next(
        deck.begin(),
        number
    );

    deck.erase(it);

    return *this;
}

bool Deck::isAllUniqueCards() const
{
    std::unordered_set<Card, HashCard> set;

    for (auto it : deck) {
        const Card& card = it.second;
        auto findIt = set.find(card);

        if (findIt == set.end())
            set.emplace(card);
        else
            return false;
    }

    return true;
}

Deck& prog2::Deck::putCard(Card card)
{
    int numeric;
    try {
        numeric = getNumericFirstCard() - 1;
    }
    catch (std::invalid_argument&) {
        numeric = 0;
    }

    deck.emplace(numeric, std::move(card));

    return *this;
}

std::ostream& prog2::operator<<(std::ostream& os, const Deck& obj)
{
    bool isFirstPrint = true;
    size_t i = 0;

    for (auto& pair : obj.deck) {
        if (isFirstPrint) {
            isFirstPrint = false;
        }
        else os << '\n';

        os << std::setw(2) << i++ << ": " << pair.second;
    }

    return os;
}

std::istream& prog2::operator>>(std::istream& stream, Deck& obj)
{
    int size;
    stream >> size;

    if (stream.good()) {
        obj = Deck(size);
    }
    else {
        stream.setstate(std::ios::failbit);
    }

    return stream;
}
#ifndef _deck
#define _deck

#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <map>

#include "Card/card.h"

namespace prog2 {
    class Deck {
        using GROUP = Card::GROUP;

        // !int
        std::map<int, Card> deck;

        int getNumericFirstCard() const;

    public:
        constexpr static size_t maxPossibleCardCount = Card::GROUP_COUNT *
                                                   Card::RANK_COUNT;

        Deck() = default;
        Deck(const Deck&) = default;
        Deck(Deck&&) noexcept = default;
        Deck(size_t count);

        static Deck makeFullDeck() {return maxPossibleCardCount;}

        Deck& operator=(const Deck&) = default;
        Deck& operator=(Deck&&) = default;

        Deck operator+(const Deck& obj) const;
        Deck& operator>>(Deck& obj);
        Card& operator[](size_t number);
        const Card& operator[](size_t number) const;

        size_t size() const {return deck.size();}
        Deck& sort();
        Deck& shuffle();
        Deck extractByGroup(Card::GROUP group);
        Deck& deleteCard(size_t number);
        bool isAllUniqueCards() const;
        Deck& putCard(Card);

        friend std::ostream& operator<<(std::ostream& os, const Deck& obj);
        friend std::istream& operator>>(std::istream& os, Deck& obj);

    };
}

#endif
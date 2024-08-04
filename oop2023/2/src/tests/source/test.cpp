#include <gtest/gtest.h>

#include "Card/card.h"
#include "Deck/deck.h"

using namespace prog2;
using GROUP = Card::GROUP;

TEST(Card, constructor) {
    Card test(GROUP::CLUB, 13);
    const auto& pair = test.getGroupRank();

    EXPECT_EQ(pair.first, GROUP::CLUB);
    EXPECT_EQ(pair.second, 13);
}

TEST(Card, constructorException) {
    EXPECT_THROW(
        Card(GROUP::CLUB, 0),
        std::invalid_argument
    );
}

TEST(Card, operatorSpaceShip) {
    Card test(GROUP::CLUB, 12);
    Card test1(GROUP::CLUB, 13);

    EXPECT_TRUE(test < test1);
    EXPECT_TRUE(test <= test1);
    EXPECT_TRUE(test1 != test);

    EXPECT_FALSE(test > test1);
    EXPECT_FALSE(test >= test1);
    EXPECT_FALSE(test1 == test);
}

TEST(Card, operatorSpaceShipDiffrentGroup) {
    Card test(GROUP::CLUB, 12);
    Card test1(GROUP::DIAMOND, 10);

    EXPECT_THROW(
        test <=> test1,
        std::invalid_argument
    );
}

TEST(Card, getGroupByNumber) {
    EXPECT_EQ(
        GROUP::HEART, Card::getGroupByNumber(0)
    );
    EXPECT_EQ(
        GROUP::DIAMOND, Card::getGroupByNumber(1)
    );
    EXPECT_EQ(
        GROUP::CLUB, Card::getGroupByNumber(2)
    );
    EXPECT_EQ(
        GROUP::SPADE, Card::getGroupByNumber(3)
    );
}

TEST(Deck, constructorThrowEmpty)
{
    Deck test(0);

    EXPECT_THROW(
        test[0], std::out_of_range
    );
}

TEST(Deck, constructor)
{
    Deck test(5);

    EXPECT_NO_THROW(test[0]);
    EXPECT_NO_THROW(test[4]);
    EXPECT_THROW(
        test[5],
        std::out_of_range
    );
}

TEST(Deck, putCard)
{
    Card card = Card::makeRandomCard();
    Deck test;

    test.putCard(card);

    EXPECT_EQ(
        test[0], card
    );
}

TEST(Deck, isAllUniqueCard)
{
    Card card1(GROUP::DIAMOND, 10);
    Card card2(GROUP::HEART, 5);

    Deck test;
    test.putCard(card1).putCard(card2);

    EXPECT_TRUE(
        test.isAllUniqueCards()
    );
}

TEST(Deck, isAllUniqueFalse)
{
    Deck test = Deck::makeFullDeck().putCard(
        Card::makeRandomCard()
    );

    EXPECT_FALSE(
        test.isAllUniqueCards()
    );
}

TEST(Deck, isAllUniqueForFullDeck)
{
    Deck test = Deck::makeFullDeck();

    EXPECT_TRUE(
        test.isAllUniqueCards()
    );
}

TEST(Deck, operatorSum)
{
    Deck a(2);
    Deck b(1);

    Deck sum = a + b;

    EXPECT_EQ(a[0], sum[0]);
    EXPECT_EQ(a[1], sum[1]);
    EXPECT_EQ(b[0], sum[2]);
}

TEST(Deck, deleteCard) {
    Deck a(3);
    Deck test = a;

    test.deleteCard(1);
    EXPECT_EQ(a[2], test[1]);
}

TEST(Deck, deleteCardException) {
    Deck test(3);

    EXPECT_THROW(
        test.deleteCard(3),
        std::out_of_range
    );
}

TEST(Deck, deleteCardException_) {
    Deck test(0);

    EXPECT_THROW(
        test.deleteCard(0),
        std::out_of_range
    );
}

TEST(Deck, sort)
{
    Card card1(GROUP::DIAMOND, 10);
    Card card2(GROUP::DIAMOND, 7);
    Card card3(GROUP::DIAMOND, 8);

    Deck test;
    test.putCard(card1).putCard(card2).putCard(card3);

    test.sort();

    EXPECT_EQ(test[0], card2);
    EXPECT_EQ(test[1], card3);
    EXPECT_EQ(test[2], card1);
}

TEST(Deck, operatorRight)
{
    Deck a(3);
    Deck b(3);

    Deck cpy = a;
    
    a >> b;

    EXPECT_EQ(cpy[0], b[0]);
    EXPECT_EQ(cpy[1], a[0]);
}

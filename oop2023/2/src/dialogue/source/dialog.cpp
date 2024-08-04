#include "Dialogue/dialog.h"

#include <array>

using namespace prog2;
using namespace dialog;
using strings = std::vector<std::string>;

namespace {
    template <class T>
    T lol(size_t size)
    {
        return static_cast<T>(
            ShowMessageGetNumber<unsigned>(
                "Make a choice >> ",
                0,
                size - 1
            )
        );
    }

    void showStrings(const strings& strings)
    {
        size_t index = 0;

        for (const auto& string : strings)
            std::cout << index++ << ": " << string << '\n';
    }

    enum class OperationWithDeck {
        DELETE, SHOW, SWITCH, ADD_RANDOM_CARD, SHOW_CARD,
        DELETE_CARD, ADD_DECKS, SORT, SHUFFLE, EXCTRACT_GROUP
    };

    OperationWithDeck chooseOperationWithDeck()
    {
        strings select = {
            "delete", "show", "switch", "add random card",
            "show card", "delete card", "sum deck",
            "sort", "shuffle", "extract"
        };

        std::cout << '\n';
        showStrings(select);

        OperationWithDeck res = lol<OperationWithDeck>(select.size());

        std::cout << '\n';

        return res;
    }
}

namespace dialog {

    ChoiceCode getChoice(const std::vector<Deck>& decks)
    {
        strings select = {
            "exit",
            "make Full Deck",
            "make Deck",
            "choose Deck"
        };

        std::cout << '\n';
        showStrings(select);

        ChoiceCode res = lol<ChoiceCode>(select.size());

        std::cout << '\n';

        return res;
    };

    void makeFullDeck(std::vector<Deck>& decks)
    {
        decks.push_back(
            Deck::makeFullDeck()
        );
    }

    void makeDeck(std::vector<Deck>& decks)
    {
        unsigned size = ShowMessageGetNumber(
            "Size of new Deck >> ",
            0
        );

        decks.push_back(
            Deck(size)
        );
    }

    void chooseDeck(std::vector<Deck>& decks)
    {
        if (!decks.size()) {
            std::cout << "U haven't decks" << '\n';
            return;
        }

        std::cout << "U have " << decks.size() << " decks\n";
        std::cout << "Choose deck [0-" << decks.size() - 1 << "] >> ";

        size_t deckNum = lib_io::getNum<size_t>(0, decks.size() - 1);

        auto operation = chooseOperationWithDeck();
        switch (operation) {
        case OperationWithDeck::DELETE:
            decks.erase(
                decks.begin() + deckNum
            );
            break;

        case OperationWithDeck::SHOW:
            std::cout << decks[deckNum] << '\n';
            break;

        case OperationWithDeck::SWITCH:
        {
            std::cout << "To which Deck >> ";
            unsigned secondDeckNum = lib_io::getNum<unsigned>(0, decks.size() - 1);
            decks[deckNum] >> decks[secondDeckNum];
        }
            break;

        case OperationWithDeck::ADD_RANDOM_CARD:
            decks[deckNum].putCard(Card::makeRandomCard());
            break;

        case OperationWithDeck::SHOW_CARD:
        {
            std::cout << "[0-" << decks[deckNum].size() - 1 << "] >> ";
            unsigned cardNum = lib_io::getNum<unsigned>(0, decks[deckNum].size() - 1);
            std::cout << decks[deckNum][cardNum] << '\n';
        }
            break;

        case OperationWithDeck::DELETE_CARD:
        {
            std::cout << "[0-" << decks[deckNum].size() - 1 << "] >> ";
            unsigned cardNum = lib_io::getNum<unsigned>(0, decks[deckNum].size() - 1);
            decks[deckNum].deleteCard(cardNum);
        }
            break;

        case OperationWithDeck::ADD_DECKS:
        {
            std::cout << "With which Deck >> ";
            unsigned secondDeckNum = lib_io::getNum<unsigned>(0, decks.size() - 1);
            decks.push_back(
                decks[deckNum] + decks[secondDeckNum]
            );
        }
            break;

        case OperationWithDeck::SORT:
            decks[deckNum].sort();
            break;

        case OperationWithDeck::SHUFFLE:
            decks[deckNum].shuffle();
            break;

        case OperationWithDeck::EXCTRACT_GROUP:
            decks.push_back(
                decks[deckNum].shuffle()
            );
            break;
        }
    }
}

#ifndef _dialog
#define _dialog

#include <limits>
#include <string>
#include <vector>

#include "lib_io/lib_io.h"
#include "Deck/deck.h"

namespace dialog {
    enum class ChoiceCode {
        EXIT, MAKE_FULL_DECK, MAKE_DECK, CHOOSE_DECK
    };

    template <typename T>
    T ShowMessageGetNumber(std::string str,
        T min = std::numeric_limits<T>::min(),
        T max = std::numeric_limits<T>::max())
    {
        std::cout << str;
        return lib_io::getNum<T>(min, max);
    }

    ChoiceCode getChoice(const std::vector<prog2::Deck>&);

    void makeFullDeck(std::vector<prog2::Deck>& decks);
    void makeDeck(std::vector<prog2::Deck>& decks);
    void chooseDeck(std::vector<prog2::Deck>&decks);
}

#endif
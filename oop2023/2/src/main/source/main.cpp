#include <iostream>

#include "Dialogue/dialog.h"
#include "Card/card.h"
#include "Card/hashCard.h"
#include "Deck/deck.h"

int main()
{
    using namespace dialog;
    using namespace prog2;

    std::vector<Deck> decks;

    try {
        while (true) {
            ChoiceCode choice = getChoice(decks);
            if (choice == ChoiceCode::EXIT) break;

            try {
                switch (choice) {
                case ChoiceCode::MAKE_FULL_DECK:
                    makeFullDeck(decks);
                    break;

                case ChoiceCode::MAKE_DECK:
                    makeDeck(decks);
                    break;

                case ChoiceCode::CHOOSE_DECK:
                    chooseDeck(decks);
                    break;

                default:
                    throw std::invalid_argument("Unknown ChoiceCode");
                }
            }
            catch (std::invalid_argument& err) {
                std::cout << err.what() << '\n';
            }
        }
    }
    catch (const std::bad_alloc&) {
        std::cerr << "Not enough memory" << std::endl;
        return 1;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "ERRRRORRR" << std::endl;
    }

    return 0;
}


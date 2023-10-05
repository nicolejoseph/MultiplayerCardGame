#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <vector>

class Deck {
private:
    std::vector<Card> cards; // use vector for easy expansion or reduction of deck size if game rules change

public:
    Deck(); // constructor
    Card dealCard(); // this function returns a Card object
};

#endif 
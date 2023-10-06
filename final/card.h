#ifndef CARD_H
#define CARD_H

#include <string>

class Card {
public:
    int value; // card's numeric value (1-13) 
    std::string suite; // card's suite: (Spades, Hearts, Diamonds, Clubs)
    
    Card(); 
    Card(int val, const std::string& suit);
};

#endif 
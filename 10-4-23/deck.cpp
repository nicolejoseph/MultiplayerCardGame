#include "deck.h"
// for shuffling:
#include <algorithm>  
#include <random>     

Deck::Deck() {
    // Initialize the deck with 52 cards
    std::string suits[] = {"Spades", "Hearts", "Diamonds", "Clubs"};
    for (int suitIndex = 0; suitIndex < 4; ++suitIndex) {
        for (int value = 1; value <= 13; ++value) {
            cards.push_back(Card(value, suits[suitIndex]));
        }
    }

    // Shuffle the deck: https://www.youtube.com/watch?v=f5vvgHX9coI at 29:39
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::shuffle(cards.begin(), cards.end(), rng);
}

Card Deck::dealCard() {
    if (!cards.empty()) {
        // Deal a card from the deck
        Card dealtCard = cards.back();
        cards.pop_back();
        return dealtCard;
    } else {
        // Handle no cards left in the deck -- GO BACK TO THIS! if it's empty then the game starts over
        return Card(0, "Empty");
    }
}
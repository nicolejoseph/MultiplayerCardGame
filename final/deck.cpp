#include "deck.h"
// for shuffling:
#include <algorithm>  
#include <random>   

int Deck::numberOfPlayers = 0;

Deck::Deck() {
    // Initialize the deck with 52 cards
    std::string suits[] = {"SPADES", "HEARTS", "DIAMONDS", "CLUBS"};
    // use nested loop: for each suit, values from 1 to 13 are looped over
    for (int suitIndex = 0; suitIndex < 4; ++suitIndex) { 
        for (int value = 1; value <= 13; ++value) {
            // for each combination of suit and value, create a Card object using the Card constructor and add it to the cards vector
            cards.push_back(Card(value, suits[suitIndex]));
        }
    }

    // Shuffle the deck: https://www.youtube.com/watch?v=f5vvgHX9coI at 29:39
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::shuffle(cards.begin(), cards.end(), rng);
}

Card Deck::dealCard() {
    // deal cards as long as the deck is not empty and there are enough cards to be dealt to all players
    if (!cards.empty() && static_cast<int>(cards.size()) >= numberOfPlayers) { 
        Card dealtCard = cards.back(); // retrieve the last card in the vector (representing the topmost card in the deck)
        cards.pop_back(); // pop the last/topmost card
        return dealtCard;
    } else {
        // Handle no cards left in the deck -- for now, this means game over
        return Card(0, "Empty deck.");
    }
}

// Set the number of players
void Deck::setNumberOfPlayers(int numPlayers) {
    numberOfPlayers = numPlayers;
}

// Get the number of players
int Deck::getNumberOfPlayers() {
    return numberOfPlayers;
}

int Deck::getDeckSize() {
    return cards.size(); // Return the size of the cards vector
}
#include <iostream>
#include "player.h"
#include "deck.h"
#include <thread>  
#include <chrono>

// void comparePlayers(std::vector<Player> &players)
// {
//     Player& player = players[i];
//     player.m_card; // is a Card
//     player.m_card.value
//     // fill this in later
// }

void playOneRound(int numberOfPlayers, std::vector<Player> &players, Deck& deck)
{
    for (int i = 0; i < numberOfPlayers; i++)
    {
        Player& player = players[i];

        // https://stackoverflow.com/questions/10673585/start-thread-with-member-function

        if (i == 0) {
            std::cout << "Welcome " << player.getUsername() << std::endl;
            std::cout << "You have 15 seconds to enter a number (1-9) to draw a card." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::thread first(&Player::startCountdown, std::ref(player));
            std::thread second(&Player::drawCard, std::ref(player));
            // player.drawCard();

            // std::thread third (dummy); // used this to ensure that threads were working
            first.join();               
            second.join();
        }
        else {
            // Make the other players draw a card by default
            player.drawnCard = 1;
        }

        if (player.drawnCard > 0) {
            std::cout << "\nDealing a card to " << player.getUsername() << "...\n";
            Card dealtCard = deck.dealCard(); 
            player.receiveCard(dealtCard);  
        }  
    }

    // comparePlayers(players);
}

int main() {
    int numberOfPlayers;
    while (true) {
        std::cout << "Enter the number of players: ";
        std::cin >> numberOfPlayers;
        if (numberOfPlayers >= 2 && numberOfPlayers <= 5) {
            break;
        } else {
            std::cout << "Invalid number of players. Please try again." << std::endl;
        }
    }

    // set number of players so it is available to the Deck class
    Deck::setNumberOfPlayers(numberOfPlayers);

    // Create the Players
    std::vector<Player> players;
    for (int i = 1; i <= numberOfPlayers; i++)
    {
        std::string playerName;
        std::cout << "Enter username for player " << i << ": ";
        std::cin >> playerName;
        // Create a default Card object with value 0 and suite "INVALID"
        Card defaultCard;
        players.push_back(Player(playerName, defaultCard));
    }

    // players[i] is a Player object

    Deck deck; // Create a deck of cards

    // while the size of cards >= numberOfPlayers
    while (deck.getDeckSize() >= numberOfPlayers) {
        playOneRound(numberOfPlayers, players, deck);
    }

    std::cout << "Not enough cards to continue the game. Game over." << std::endl;

    return 0;
}
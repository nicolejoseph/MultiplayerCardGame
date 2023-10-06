#include <iostream>
#include "player.h"
#include "deck.h"
#include <thread>  
#include <chrono>


void determineOutcome(std::vector<Player> &players) {
    // Player& player = players[i];
    // player.m_card; // is a Card object
    // player.m_card.value // is the card's value

    int highestValue = 0;
    std::string highestSuit = "";
    Player* winner = nullptr;

    for (Player& player : players) {
        // Skip players who did not draw a card (they failed to enter a number 1-9)
        // std::cout << player.drawnCard; // for testing purpose
        if (player.drawnCard == 0) {     // this still needs to be debugged
            continue;
        }

        // Check if the current player's card is higher
        if (player.m_card.value > highestValue ||
            (player.m_card.value == highestValue && player.m_card.suite > highestSuit)) {
            highestValue = player.m_card.value;
            highestSuit = player.m_card.suite;
            winner = &player;
        }
    }

    if (winner != nullptr) {
        std::cout << "\nPlayer " << winner->getUsername() << " wins this round with ";
        switch (winner->m_card.value) {
            case 1:
                std::cout << "ACE";
                break;
            case 11:
                std::cout << "JACK";
                break;
            case 12:
                std::cout << "QUEEN";
                break;
            case 13:
                std::cout << "KING";
                break;
            default:
                std::cout << winner->m_card.value;
                break;
        }
        std::cout << " of " << winner->m_card.suite << "!" << std::endl;
    } else {
        std::cout << "No valid winner in this round." << std::endl;
    }
}


void playOneRound(int numberOfPlayers, std::vector<Player> &players, Deck& deck)
{
    for (int i = 0; i < numberOfPlayers; i++)
    {
        Player& player = players[i];

        // Reference: https://stackoverflow.com/questions/10673585/start-thread-with-member-function
        if (i == 0) {
            std::cout << "Hey player " << player.getUsername() << "!" << std::endl;
            std::cout << "\nYou have 15 seconds to to draw a card. Enter a number (1-9)" << std::endl;

            std::this_thread::sleep_for(std::chrono::seconds(1));

            std::thread first(&Player::startCountdown, std::ref(player));
            std::thread second(&Player::drawCard, std::ref(player));

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

    determineOutcome(players);

    char temp;
    std::cout << "Enter Y to continue to the next round: ";
    std::cin >> temp;
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
        Card defaultCard; // Create a default Card object with value 0 and suite "INVALID"
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
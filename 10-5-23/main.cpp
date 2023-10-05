// g++ -o MyProgram player.cpp playerTest.cpp
// ./MyProgram

#include <iostream>
#include "player.h"
#include "deck.h"
#include <thread>  
#include <chrono>

// void dummy() {
// }

int main() {
    std::string playerName;
    std::cout << "Enter your username for this game: ";
    std::cin >> playerName;

    Player player(playerName);
    std::cout << "Welcome " << player.getUsername() << std::endl;
    std::cout << "You have 15 seconds to enter a number (1-52) to draw a card." << std::endl;
    // std::cout << "If the countdown ends, enter 0 to continue." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // player.drawCard();
    // player.startCountdown();

    // https://stackoverflow.com/questions/10673585/start-thread-with-member-function
    
    // std::thread first (&Player::drawCard, player);    
    // std::thread second (&Player::startCountdown, std::ref(player));
    // std::thread second (&Player::startCountdown, std::ref(player), std::ref(player.drawnCard));
    std::thread first(&Player::drawCard, std::ref(player));
    std::thread second(&Player::startCountdown, std::ref(player));

    // std::thread third (dummy); // used this to ensure that threads were working
    first.join();               
    second.join();

    Deck deck; // Create a deck of cards
    std::cout << "\nDealing a card to " << player.getUsername() << "...\n";
    Card dealtCard = deck.dealCard(); 
    player.receiveCard(dealtCard);    
    
    // I used this to check if dealing cards from the Deck worked
    // for (int i = 0; i < 52; ++i) {
    //     std::this_thread::sleep_for(std::chrono::seconds(1)); 
    //     Card dealtCard = deck.dealCard();
    //     player.receiveCard(dealtCard);    
    // }

    // player.displayOutcome(true); 

    return 0;
}
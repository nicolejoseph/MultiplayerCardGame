// g++ -o MyProgram player.cpp playerTest.cpp
// ./MyProgram


#include <iostream>
#include "player.h"
#include <thread>  

// void dummy() {
// }

int main() {
    std::string playerName;
    std::cout << "Enter your username for this game: ";
    std::cin >> playerName;

    Player player(playerName);
    std::cout << "Welcome " << player.getUsername() << std::endl;

    std::cout << "\nYou have 15 seconds to enter a number (1-52) to draw a card:\n";
    // player.drawCard();
    // player.startCountdown();

    // https://stackoverflow.com/questions/10673585/start-thread-with-member-function
    
    // std::thread first (&Player::drawCard, player);    
    // std::thread second (&Player::startCountdown, std::ref(player));
    // std::thread second (&Player::startCountdown, std::ref(player), std::ref(player.drawnCard));
    std::thread first(&Player::drawCard, std::ref(player));
    std::thread second(&Player::startCountdown, std::ref(player));


    // std::thread third (dummy);
    first.join();               
    second.join();
    
    player.displayOutcome(true); // Assume player wins for testing purposes lol

    return 0;
}



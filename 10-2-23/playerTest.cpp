// g++ -o MyProgram Player.cpp TestPlayer.cpp
// ./MyProgram


#include <iostream>
#include "player.h"

int main() {
    std::string playerName;
    std::cout << "Enter your username for this game: ";
    std::cin >> playerName;

    Player player(playerName);
    std::cout << "Welcome " << player.getUsername() << std::endl;

    std::cout << "\nYou have 15 seconds to enter a number (1-52) to draw a card: ";
    player.startCountdown(); 
    int drawnCard;
    std::cin >> drawnCard;

    player.displayOutcome(true); // Assume player wins for testing purposes lol

    return 0;
}

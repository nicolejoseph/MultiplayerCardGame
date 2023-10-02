
// to compile:
// g++ -o <name-you-want-to-give> source.cpp
// to run:
// ./myprogram

#include "player.h"
#include <iostream>
#include <Windows.h>
using namespace std;

// Constructor that initializes playerName and countdown timer
Player::Player(const std::string& playerName) : username(playerName), countdownTimer(15) {
}

const std::string& Player::getUsername() const {
    // cout << "Please enter a username for this game\n";
    // cin >> username;
    return username;
}

void Player::startCountdown() {
    // reference for setting up the countdown timer: https://stackoverflow.com/questions/54019545/making-a-countdown-timer-in-c
    int counter = countdownTimer;
    while (counter >= 1)
    {
        cout << "\rTime remaining to draw card: " << counter << flush;
        Sleep(1000);
        counter--;
        // if the player draws a card, this startCountdown() function will end
        if (drawnCard > 0) {
            break;
        }
    }
    if (drawnCard == 0) {
        cout << "Player " << username << " did not draw a card in time. Automatic loss." << endl;
    }
    cout << endl;
}

void Player::drawCard(int drawnCard) {

}

void Player::displayOutcome(bool isWinner) {
    // Display the outcome of the round (win/loss) for this player
    if (isWinner) {
        std::cout << "Player " << username << " wins this round!" << std::endl;
    } else {
        std::cout << "Player " << username << " loses this round." << std::endl;
    }
}

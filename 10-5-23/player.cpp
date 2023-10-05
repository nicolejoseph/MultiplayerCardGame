// to compile:
// g++ -o <name-you-want-to-give> source.cpp
// to run:
// ./myprogram

#include "player.h"
#include <iostream>
#include <Windows.h>
#include <thread>
#include <cstdlib>
using namespace std;

// Constructor that initializes playerName and countdown timer
Player::Player(const std::string& playerName) : username(playerName), countdownTimer(15), drawnCard(0) {
}

const std::string& Player::getUsername() const {
    // cout << "Please enter a username for this game\n";
    // cin >> username;
    return username;
}

void Player::startCountdown() {
    int x;
    // reference for setting up the countdown timer: https://stackoverflow.com/questions/54019545/making-a-countdown-timer-in-c
    int counter = countdownTimer;
    while (counter >= 0)
    {
        cout << "\rTime remaining to draw card: " << counter << endl;
        std::this_thread::sleep_for(1000ms);
        counter--;
        // if the player draws a card, this startCountdown() function will end
        if (drawnCard > 0) {
            break;
        }
    }
    cout << "\nCountdown Ended. Press Y to continue.";
    std::cin >> x;

    std::lock_guard<std::mutex> lock(cardMutex);
    if (drawnCard == 0) {
        cout << "\nAutomatic loss. Player " << username << " did not draw a card in time." << endl;
    }
    cout << endl;
}

int Player::drawCard() {
    std::lock_guard<std::mutex> lock(cardMutex);
    std::cin >> drawnCard;
    cout << "Your card's value is:" << drawnCard; // ensure that if no card is drawn before the timer ends, drawnCard = 0
    return drawnCard;
}

void Player::receiveCard(const Card& card) {
    std::lock_guard<std::mutex> lock(cardMutex);
    // Display the card's value and suite. Handle special cases of Ace, Jack, Queen, and King
    std::string cardValue;
    switch (card.value) {
        case 1:
            cardValue = "ACE";
            break;
        case 11:
            cardValue = "JACK";
            break;
        case 12:
            cardValue = "QUEEN";
            break;
        case 13:
            cardValue = "KING";
            break;
        default:
            cardValue = std::to_string(card.value);
            break;
    }
    std::cout << "You received: " << cardValue << " of " << card.suite << std::endl;
}


void Player::displayOutcome(bool isWinner) {
    // Display the outcome of the round (win/loss) for this player
    if (isWinner) {
        std::cout << "Player " << username << " wins this round!" << std::endl;
    } else {
        std::cout << "Player " << username << " loses this round." << std::endl;
    }
}
#include "player.h"
#include <iostream>
#include <Windows.h>
#include <thread>
#include <cstdlib>
using namespace std;

// Constructor that initializes playerName, countdownTimer, drawnCard, and a card object m_card
Player::Player(const std::string& playerName, const Card& card) : username(playerName), countdownTimer(15), drawnCard(0), m_card(card) {
}

// I added extra constructors for the players vector to work 
Player::Player(Player& otherPlayer)
{
    username = otherPlayer.username;
    countdownTimer = otherPlayer.countdownTimer;
    drawnCard = otherPlayer.drawnCard;
    // cardMutex = std::move(otherPlayer.cardMutex);
}

Player::Player(const Player& otherPlayer)
{
    username = otherPlayer.username;
    countdownTimer = otherPlayer.countdownTimer;
    drawnCard = otherPlayer.drawnCard;
}

const std::string& Player::getUsername() const {
    return username;
}

void Player::startCountdown() {
    char x;
    // reference for setting up the countdown timer: https://stackoverflow.com/questions/54019545/making-a-countdown-timer-in-c
    int counter = countdownTimer;
    drawnCard = 0;
    // cout << " drawnCard = " << drawnCard << endl; // for testing purposes
    while (counter >= 0)
    {
        cout << "\rTime remaining to draw card: " << counter << endl;
        std::this_thread::sleep_for(1000ms);
        counter--;

        // if the player draws a card successfully, this startCountdown() function will end
        if (drawnCard > 0) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear input buffer
            break;
        }
    }
    std::lock_guard<std::mutex> lock(cardMutex);
    cout << "\nCountdown Ended. Enter Y to continue." << std::flush;
    std::cin >> x;

    if (drawnCard == 0) {
        cout << "\nAutomatic loss. Player " << username << " did not draw a card in time." << endl;
    }
    cout << endl;
}


int Player::drawCard() {
    std::lock_guard<std::mutex> lock(cardMutex);
    // Reset drawnCard to 0 before reading input
    drawnCard = 0;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear input buffer

    std::string input;
    while (true) {
        std::cin >> input;
        
        // Check if the input is a valid integer
        try {
            drawnCard = std::stoi(input);
        } catch (const std::invalid_argument& e) {
            std::cout << "Invalid input. Please enter a number between 1 and 9." << std::endl;
            std::cin.clear();  // Clear the error flag on cin
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Discard invalid input
            continue;  // Ask for input again
        }

        // Check if the input is within the valid range
        if (drawnCard >= 1 && drawnCard <= 9) {
            break;  // Valid input, exit the loop
        } else {
            // NOTE: still need to debug this part because it's not working as intended
            std::cout << "Invalid input. Please enter a number between 1 and 9." << std::endl;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear input buffer
        break;
    }

    // std::cout << "Your card's value is: " << drawnCard << std::endl; // for testing purposes
    return drawnCard;
}


void Player::receiveCard(const Card& card) {
    // std::lock_guard<std::mutex> lock(cardMutex);
    // Display the card's value and suite. Handle special cases of Ace, Jack, Queen, and King
    m_card = card;  // save the card
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
    std::cout << username << " received: " << cardValue << " of " << card.suite << std::endl;
}


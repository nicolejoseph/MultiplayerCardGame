#include "player.h"
#include <iostream>
#include <Windows.h>
#include <thread>
#include <cstdlib>
using namespace std;

// Constructor that initializes playerName and countdown timer
Player::Player(const std::string& playerName, const Card& card) : username(playerName), countdownTimer(15), drawnCard(0), m_card(card) {
}

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
    // cout << "Please enter a username for this game\n";
    // cin >> username;
    return username;
}

void Player::startCountdown() {
    int x;
    // reference for setting up the countdown timer: https://stackoverflow.com/questions/54019545/making-a-countdown-timer-in-c
    int counter = countdownTimer;

    drawnCard = 0;
    cout << " drawnCard = " << drawnCard << endl;

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
    std::lock_guard<std::mutex> lock(cardMutex);
    cout << "\nCountdown Ended. Enter Y to continue.";
    std::cin >> x;

    if (drawnCard == 0) {
        drawnCard = 1; // just to allow the game to continue
        cout << "\nAutomatic loss. Player " << username << " did not draw a card in time." << endl;
    }
    cout << endl;
}

int Player::drawCard() {
    std::lock_guard<std::mutex> lock(cardMutex);
    drawnCard = 0; // Reset drawnCard to 0 before reading input
    // Clear the input buffer to prevent the \n from being interpreted as user input
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin >> drawnCard;
    cout << "Your card's value is:" << drawnCard; // ensure that if no card is drawn before the timer ends, drawnCard = 0
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


void Player::displayOutcome(bool isWinner) {
    // Display the outcome of the round (win/loss) for this player
    if (isWinner) {
        std::cout << "Player " << username << " wins this round!" << std::endl;
    } else {
        std::cout << "Player " << username << " loses this round." << std::endl;
    }
}
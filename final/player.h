#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <thread>
#include <mutex>
#include "card.h"

#include <condition_variable>

class Player{
private: // protect these from direct external access
    std::string username;
    int countdownTimer; 
    std::mutex cardMutex;

    std::condition_variable cv; // Condition variable to synchronize threads
    bool countdownEnded; // Flag indicating whether the countdown has ended

public:
    Player(const std::string& playerName, const Card& card);

    // I added other constructors for the players vector to work 
    Player(Player&);
    Player(const Player& otherPlayer);

    const std::string& getUsername() const; // this returns playerName
    void startCountdown(); // displays the countdown
    int drawCard(); // prompts user to "draw card" before timer ends 
    void receiveCard(const Card& card);      // Display the received card from deck

    int drawnCard;
    Card m_card;

};

#endif
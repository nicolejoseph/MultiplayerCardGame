// player class declarations - header file

#ifndef PLAYER_H
#define PLAYER_H
#include <string>

class Player{
private: // protect these from direct external access
    std::string username;
    int countdownTimer; 
    int drawnCard; 

public:
    // create a Player object and pass playerName value to this. The username above will be set to this name
    Player(const std::string& playerName); 
    const std::string& getUsername() const; // this returns playerName
    void startCountdown(); // displays the countdown
    void drawCard(int drawnCard); // draw card before timer ends and show player what card they have drawn
    void displayOutcome(bool isWinner); // display outcome of round

};

#endif
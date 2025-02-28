#ifndef NUMBER_GUESSING_GAME_H
#define NUMBER_GUESSING_GAME_H

#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

class NumberGuessingGame : public Game{     //creating a derived class of this game from the Game.h file
public:
    NumberGuessingGame();   //Constructor
    void play() override;   //With override, we will skip the play() function from the base class (Game)
private:
    int rand_num;
    void generate_random_number();
};

#endif NUMBER_GUESSING_GAME_H
#ifndef GAME_H
#define GAME_H

#include <iostream>

//Adding a Abstract Base class to act as an interface for all the games
class Game{
public:
   virtual void play() = 0;
   virtual ~Game() {} 
};

#endif GAME_H


// Game is an abstract base class that other games will inherit from.
// play() is a pure virtual function, meaning every game must implement it.
// ~Game() is a virtual destructor to ensure proper cleanup when deleting derived objects.
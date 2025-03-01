#include <iostream>
#include "Game.h"
#include "NumberGuessingGame.h"

void ShowMenu(){
    std::cout<<"Welcome to the mini-game collection, user!"<<std::endl;
    std::cout<<"***********LIST OF AVAILABLE GAMES*************"<<std::endl;
    std::cout<<"1. Number Guessing Game\n2. Exit\n";
    std::cout<<"Choose your game!: "<<std::endl;
}

int main(){
    int choice_of_game;
    while (true){
        ShowMenu();
        std::cin>>choice_of_game;

        if (choice_of_game == 2){
            std::cout<<"Sad to see you go! Exiting the game console...\n";
            break;
        }
        
        if (choice_of_game == 1){
            std::cout<<"You chose Number Guessing Game? Alright, let's dive into a game of pure luck!\n";
            NumberGuessingGame game;
            game.play();
        }
        else{
            std::cout<<"Invalid output\n";
        }

        std::cout<<"Your game will now start!\n";     //This message prints after the user has entered their choice other than the exit option
    }
    return 0;
}
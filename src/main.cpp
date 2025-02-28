#include <iostream>
#include <Game.h>


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

        if (choice_of_game = 2){
            std::cout<<"Sad to see you go! Exiting the game console..."<<std::endl;
        }
        
        std::cout<<"Your game will now start!"<<std::endl;      //This message prints after the user has entered their choice other than the exit option
    }
    return 0;
}
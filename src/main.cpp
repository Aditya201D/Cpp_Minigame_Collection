#include <iostream>
#include "Game.h"
#include "NumberGuessingGame.h"
#include "WordSearchGame.h"
#include <string>
#include <vector>
#include <algorithm>

void ShowMenu(){
    std::cout<<"Welcome to the mini-game collection, user!"<<std::endl;
    std::cout<<"***********LIST OF AVAILABLE GAMES*************"<<std::endl;
    std::cout<<"1. Number Guessing Game\n2. Word Search Game\n3. Exit\n";
    std::cout<<"Choose your game!: "<<std::endl;
}

int main(){
    int choice_of_game;
    int rows,cols;
    std::vector<std::string> defaultWords = {
        "COMPUTER", "PROGRAM", "CODING", "ALGORITHM",
        "FUNCTION", "VARIABLE", "CLASS", "OBJECT"
    };
    while (true){
        ShowMenu();
        std::cin>>choice_of_game;

        if (choice_of_game == 3){
            std::cout<<"Sad to see you go! Exiting the game console...\n";
            break;
        }
        
        if (choice_of_game == 1){
            std::cout<<"You chose Number Guessing Game? Alright, let's dive into a game of pure luck!\n";
            NumberGuessingGame game;
            game.play();
        }
        

        if (choice_of_game == 2){
            
            std::cout<<"Entering Word Search game!\n";
            std::cout<<"Enter the grid size (rows, cols):: ";
            std::cin >> rows;
            std::cin >> cols;
            
            WordSearch game(rows, cols);
            char choice;

            std::cout<<"a. Use default word list\n";
            std::cout<<"b. Enter custom words\n";
            std::cin>>choice;
            if (choice == 'a'){
                for (const auto& word : defaultWords){
                    game.addWord(word);
                }
            }
            else{
                std::cout<<"Enter the number of words: ";
                int numWords;
                std::cin >> numWords;
                std::cin.ignore();

                for (int i = 0; i < numWords; i++) {
                    std::string word;
                    std::cout << "Enter word " << (i + 1) << ": ";
                    std::getline(std::cin, word);
                    
                    // Remove spaces and convert to uppercase
                    word.erase(std::remove_if(word.begin(), word.end(), ::isspace), word.end());
                    std::transform(word.begin(), word.end(), word.begin(), ::toupper);
                    
                    if (!word.empty()) {
                        game.addWord(word);
                    }
            }
        }

        std::cout<<"Generating the puzzle...\n";
        game.generatePuzzle();
        std::cout<<"Your game will now start!\n"; 
        game.play();
            //This message prints after the user has entered their choice other than the exit option
    }
    return 0;
}
}
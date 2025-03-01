#include "NumberGuessingGame.h"

NumberGuessingGame :: NumberGuessingGame(){
    srand(time(NULL));      //This statement will generate a random number (or time seed, to be specific)
    generate_random_number();    
}

void NumberGuessingGame :: generate_random_number(){
    rand_num = (rand () % 10) + 1;
}

void NumberGuessingGame :: play(){
    int guess, tries = 0;
    std::cout<<"\n**************NUMBER GUESSING GAME*******************\n";
    std::cout<<"Details for the game: \n";
    std::cout<<"(a) Guess any randome integer from 1 to 10.\n";
    std::cout<<"(b) If your choice matches with the computer's choice, you win!\n";
    std::cout<<"(c) You get 3 chances only!"<<std::endl;
    while (tries<3){
        std::cout << "Enter a random number between (1-10): ";
        std::cin >> guess;

        if (guess <= 0 || guess > 10) {
            std::cout << "Invalid input!\n";
            return;
        }
        if (rand_num == guess) {
            std::cout << "Correct guess! Congratulations!\n";
            return;
        } else {
            std::cout << "Wrong guess. Try again.\n";
        }
        tries++;
    }

    std::cout << "You failed to guess correctly. Try again.\n";
}

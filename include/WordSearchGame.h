#ifndef WORD_SEARCH_GAME_H
#define WORD_SEARCH_GAME_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <unordered_map>

// Grid class handles the puzzle board representation and word placement
class Grid {
private:
    std::vector<std::vector<char>> board;
    int rows;
    int cols;
    std::mt19937 rng;  // Mersenne Twister random number generator

public:
    // Constructor - initialize an empty grid
    Grid(int rows, int cols);
    
    // Display the grid with coordinates
    void display() const;
    
    // Get character at position (with bounds checking)
    char getCharAt(int row, int col) const;
    
    // Set character at position (with bounds checking)
    void setCharAt(int row, int col, char c);
    
    // Fill empty spaces with random letters
    void fillRandom();
    
    // Check if word can be placed at specified position and direction
    bool canPlaceWord(const std::string& word, int row, int col, int rowDir, int colDir) const;
    
    // Place word at specified position and direction
    bool placeWord(const std::string& word, int row, int col, int rowDir, int colDir);
    
    // Get dimensions
    int getRows() const;
    int getCols() const;
    
    // Try to place a word in a random position and direction
    bool placeWordRandomly(const std::string& word);
    
    // Create a copy of the grid (useful for testing placements)
    Grid copy() const;
};

// WordSearch class manages the game logic
class WordSearch {
private:
    Grid grid;
    std::vector<std::string> wordList;
    std::unordered_map<std::string, bool> wordFound;
    int attempts;     // Number of attempts to place words
    
public:
    // Constructor
    WordSearch(int rows, int cols);
    
    // Add a word to the puzzle
    bool addWord(const std::string& word);
    
    // Generate the puzzle with all words
    void generatePuzzle();
    
    // Check if the word is found based on start and end coordinates
    bool checkWordFound(const std::string& word, int startRow, int startCol, int endRow, int endCol);
    
    // Mark a word as found
    void markWordAsFound(const std::string& word);
    
    // Check if all words have been found
    bool allWordsFound() const;
    
    // Display the puzzle and word list
    void displayGame() const;
    
    // Run the game loop
    void play();
};

#endif // WORD_SEARCH_GAME_H
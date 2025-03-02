#include "WordSearchGame.h"

// ===== Grid Class Implementation =====

// Constructor - initialize an empty grid
Grid::Grid(int rows, int cols) : rows(rows), cols(cols) {
    // Seed the random number generator
    rng.seed(std::random_device()());
    
    // Initialize the board with spaces
    board.resize(rows, std::vector<char>(cols, ' '));
}

// Display the grid with coordinates
void Grid::display() const {
    // Print column numbers
    std::cout << "  ";
    for (int j = 0; j < cols; j++) {
        std::cout << j % 10 << " ";
    }
    std::cout << std::endl;
    
    // Print the grid with row numbers
    for (int i = 0; i < rows; i++) {
        std::cout << i % 10 << " ";
        for (int j = 0; j < cols; j++) {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Get character at position (with bounds checking)
char Grid::getCharAt(int row, int col) const {
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        return board[row][col];
    }
    return '\0';  // Return null character for out of bounds
}

// Set character at position (with bounds checking)
void Grid::setCharAt(int row, int col, char c) {
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        board[row][col] = c;
    }
}

// Fill empty spaces with random letters
void Grid::fillRandom() {
    std::uniform_int_distribution<int> dist(0, 25);  // A-Z (0-25)
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'A' + dist(rng);  // Convert 0-25 to A-Z
            }
        }
    }
}

// Check if word can be placed at specified position and direction
bool Grid::canPlaceWord(const std::string& word, int row, int col, int rowDir, int colDir) const {
    int len = word.length();
    
    // Check if word would go out of bounds
    if (row + (len - 1) * rowDir < 0 || row + (len - 1) * rowDir >= rows ||
        col + (len - 1) * colDir < 0 || col + (len - 1) * colDir >= cols) {
        return false;
    }
    
    // Check if the word can be placed without conflicts
    for (int i = 0; i < len; i++) {
        int r = row + i * rowDir;
        int c = col + i * colDir;
        
        // If the cell is not empty, it must match the letter we want to place
        if (board[r][c] != ' ' && board[r][c] != word[i]) {
            return false;
        }
    }
    
    return true;
}

// Place word at specified position and direction
bool Grid::placeWord(const std::string& word, int row, int col, int rowDir, int colDir) {
    if (!canPlaceWord(word, row, col, rowDir, colDir)) {
        return false;
    }
    
    // Place the word
    for (int i = 0; i < word.length(); i++) {
        int r = row + i * rowDir;
        int c = col + i * colDir;
        board[r][c] = word[i];
    }
    
    return true;
}

// Get dimensions
int Grid::getRows() const { return rows; }
int Grid::getCols() const { return cols; }

// Try to place a word in a random position and direction
bool Grid::placeWordRandomly(const std::string& word) {
    // Possible directions (row direction, column direction):
    // (0,1)=right, (1,0)=down, (1,1)=diagonal right-down, 
    // (-1,0)=up, (0,-1)=left, (-1,-1)=diagonal left-up,
    // (1,-1)=diagonal left-down, (-1,1)=diagonal right-up
    std::vector<std::pair<int, int>> directions = {
        {0, 1}, {1, 0}, {1, 1}, {-1, 0}, 
        {0, -1}, {-1, -1}, {1, -1}, {-1, 1}
    };
    
    // Shuffle directions for more randomness
    std::shuffle(directions.begin(), directions.end(), rng);
    
    // Get a list of all possible starting positions
    std::vector<std::pair<int, int>> positions;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            positions.push_back({i, j});
        }
    }
    
    // Shuffle positions for more randomness
    std::shuffle(positions.begin(), positions.end(), rng);
    
    // Try each position and direction until we find a valid placement
    for (const auto& pos : positions) {
        for (const auto& dir : directions) {
            if (placeWord(word, pos.first, pos.second, dir.first, dir.second)) {
                return true;
            }
        }
    }
    
    return false;  // Could not place the word
}

// Create a copy of the grid (useful for testing placements)
Grid Grid::copy() const {
    Grid newGrid(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            newGrid.setCharAt(i, j, board[i][j]);
        }
    }
    return newGrid;
}

// ===== WordSearch Class Implementation =====

// Constructor
WordSearch::WordSearch(int rows, int cols) : grid(rows, cols), attempts(100) {
}

// Add a word to the puzzle
bool WordSearch::addWord(const std::string& word) {
    std::string upperWord = word;
    // Convert word to uppercase
    std::transform(upperWord.begin(), upperWord.end(), upperWord.begin(), ::toupper);
    
    // Check if the word is already in the list
    if (std::find(wordList.begin(), wordList.end(), upperWord) != wordList.end()) {
        return false;
    }
    
    wordList.push_back(upperWord);
    wordFound[upperWord] = false;
    return true;
}

// Generate the puzzle with all words
void WordSearch::generatePuzzle() {
    // Sort words by length (longest first) for better placement
    std::sort(wordList.begin(), wordList.end(), 
        [](const std::string& a, const std::string& b) {
            return a.length() > b.length();
        });
        
    // Try to place each word
    for (const auto& word : wordList) {
        bool placed = false;
        
        // Make multiple attempts to place the word
        for (int i = 0; i < attempts && !placed; i++) {
            placed = grid.placeWordRandomly(word);
        }
        
        if (!placed) {
            std::cout << "Warning: Could not place word: " << word << std::endl;
        }
    }
    
    // Fill the rest with random letters
    grid.fillRandom();
}

// Check if the word is found based on start and end coordinates
bool WordSearch::checkWordFound(const std::string& word, int startRow, int startCol, int endRow, int endCol) {
    std::string upperWord = word;
    std::transform(upperWord.begin(), upperWord.end(), upperWord.begin(), ::toupper);
    
    // Check if the word is in the list
    if (wordFound.find(upperWord) == wordFound.end()) {
        return false;
    }
    
    // If the word is already found, no need to check again
    if (wordFound[upperWord]) {
        return true;
    }
    
    // Calculate direction
    int rowDiff = endRow - startRow;
    int colDiff = endCol - startCol;
    int wordLen = upperWord.length();
    
    // Check if the coordinates match the word length
    int steps = std::max(abs(rowDiff), abs(colDiff)) + 1;
    if (steps != wordLen) {
        return false;
    }
    
    // Normalize direction
    int rowDir = (rowDiff == 0) ? 0 : rowDiff / abs(rowDiff);
    int colDir = (colDiff == 0) ? 0 : colDiff / abs(colDiff);
    
    // Extract the word from the grid
    std::string extractedWord;
    for (int i = 0; i < steps; i++) {
        int r = startRow + i * rowDir;
        int c = startCol + i * colDir;
        extractedWord += grid.getCharAt(r, c);
    }
    
    // Check if the extracted word matches
    if (extractedWord == upperWord) {
        wordFound[upperWord] = true;
        return true;
    }
    
    return false;
}

// Mark a word as found
void WordSearch::markWordAsFound(const std::string& word) {
    std::string upperWord = word;
    std::transform(upperWord.begin(), upperWord.end(), upperWord.begin(), ::toupper);
    
    if (wordFound.find(upperWord) != wordFound.end()) {
        wordFound[upperWord] = true;
    }
}

// Check if all words have been found
bool WordSearch::allWordsFound() const {
    for (const auto& pair : wordFound) {
        if (!pair.second) {
            return false;
        }
    }
    return true;
}

// Display the puzzle and word list
void WordSearch::displayGame() const {
    std::cout << "\n=== WORD SEARCH PUZZLE ===" << std::endl;
    grid.display();
    
    std::cout << "\nWords to find:" << std::endl;
    for (const auto& word : wordList) {
        std::cout << (wordFound.at(word) ? "[X] " : "[ ] ") << word << std::endl;
    }
    std::cout << std::endl;
}

// Run the game loop
void WordSearch::play() {
    std::cout << "Welcome to Word Search!\n";
    std::cout << "Find all the words in the grid.\n";
    std::cout << "To find a word, enter the starting and ending coordinates (row col).\n\n";
    
    while (!allWordsFound()) {
        displayGame();
        
        // Get user input
        int startRow, startCol, endRow, endCol;
        std::cout << "Enter starting position (row col): ";
        std::cin >> startRow >> startCol;
        std::cout << "Enter ending position (row col): ";
        std::cin >> endRow >> endCol;
        
        // Check if the input is valid
        if (startRow < 0 || startRow >= grid.getRows() ||
            startCol < 0 || startCol >= grid.getCols() ||
            endRow < 0 || endRow >= grid.getRows() ||
            endCol < 0 || endCol >= grid.getCols()) {
            std::cout << "Invalid coordinates. Try again.\n";
            continue;
        }
        
        // Extract the word from the grid based on coordinates
        std::string extractedWord;
        int rowDiff = endRow - startRow;
        int colDiff = endCol - startCol;
        int steps = std::max(abs(rowDiff), abs(colDiff)) + 1;
        int rowDir = (rowDiff == 0) ? 0 : rowDiff / abs(rowDiff);
        int colDir = (colDiff == 0) ? 0 : colDiff / abs(colDiff);
        
        for (int i = 0; i < steps; i++) {
            int r = startRow + i * rowDir;
            int c = startCol + i * colDir;
            extractedWord += grid.getCharAt(r, c);
        }
        
        // Check if the extracted word is in our list
        bool found = false;
        for (const auto& word : wordList) {
            if (word == extractedWord && !wordFound[word]) {
                std::cout << "You found the word: " << word << "!\n";
                wordFound[word] = true;
                found = true;
                break;
            }
        }
        
        if (!found) {
            std::cout << "No word found at those coordinates. Try again.\n";
        }
        
        std::cout << std::endl;
    }
    
    std::cout << "Congratulations! You found all the words!\n";
    displayGame();
}
#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

class TicTacToe {
private:
    char board[3][3];
    char currentPlayer;
    string player1;
    string player2;
    int moves;

public:
    // Constructor
    TicTacToe() {
        initializeBoard();
        currentPlayer = 'X';
        moves = 0;
    }

    // Initialize the board with empty spaces
    void initializeBoard() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                board[i][j] = ' ';
            }
        }
    }

    // Display the board
    void displayBoard() {
        cout << "\n";
        cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
        cout << "-----------" << endl;
        cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
        cout << "-----------" << endl;
        cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl;
        cout << "\n";
    }

    // Switch players
    void switchPlayer() {
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    // Make a move
    bool makeMove(int row, int col) {
        if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != ' ') {
            return false;
        }
        board[row][col] = currentPlayer;
        moves++;
        return true;
    }

    // Check for a win
    bool checkWin() {
        // Check rows
        for (int i = 0; i < 3; i++) {
            if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
                return true;
            }
        }

        // Check columns
        for (int j = 0; j < 3; j++) {
            if (board[0][j] != ' ' && board[0][j] == board[1][j] && board[1][j] == board[2][j]) {
                return true;
            }
        }

        // Check diagonals
        if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
            return true;
        }
        if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
            return true;
        }

        return false;
    }

    // Check for a draw
    bool checkDraw() {
        return moves >= 9;
    }

    // Get current player
    char getCurrentPlayer() {
        return currentPlayer;
    }

    // Set player names
    void setPlayerNames(string p1, string p2) {
        player1 = p1;
        player2 = p2;
    }

    // Get player name based on symbol
    string getPlayerName(char symbol) {
        return (symbol == 'X') ? player1 : player2;
    }

    // Save game to file
    void saveGame(const string& filename) {
        ofstream outFile(filename);
        if (!outFile) {
            cerr << "Error: Could not open file for saving." << endl;
            return;
        }

        // Save player names
        outFile << player1 << endl;
        outFile << player2 << endl;

        // Save current player
        outFile << currentPlayer << endl;

        // Save moves count
        outFile << moves << endl;

        // Save board state
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                outFile << board[i][j] << " ";
            }
            outFile << endl;
        }

        outFile.close();
        cout << "Game saved successfully to " << filename << endl;
    }

    // Load game from file
    bool loadGame(const string& filename) {
        ifstream inFile(filename);
        if (!inFile) {
            cerr << "Error: Could not open file for loading." << endl;
            return false;
        }

        // Load player names
        getline(inFile, player1);
        getline(inFile, player2);

        // Load current player
        inFile >> currentPlayer;
        inFile.ignore();

        // Load moves count
        inFile >> moves;
        inFile.ignore();

        // Load board state
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                inFile >> board[i][j];
            }
        }

        inFile.close();
        cout << "Game loaded successfully from " << filename << endl;
        return true;
    }
};

// Function to get valid integer input
int getValidInput(const string& prompt, int min, int max) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value < min || value > max) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between " << min << " and " << max << "." << endl;
        } else {
            cin.ignore();
            break;
        }
    }
    return value;
}

int main() {
    TicTacToe game;
    string player1, player2;
    int choice;

    cout << "Welcome to Tic Tac Toe!" << endl;
    cout << "1. New Game" << endl;
    cout << "2. Load Game" << endl;
    choice = getValidInput("Enter your choice (1-2): ", 1, 2);

    if (choice == 1) {
        cout << "Enter Player 1 name (X): ";
        getline(cin, player1);
        cout << "Enter Player 2 name (O): ";
        getline(cin, player2);
        game.setPlayerNames(player1, player2);
    } else {
        string filename;
        cout << "Enter filename to load: ";
        getline(cin, filename);
        if (!game.loadGame(filename)) {
            cout << "Starting a new game instead." << endl;
            cout << "Enter Player 1 name (X): ";
            getline(cin, player1);
            cout << "Enter Player 2 name (O): ";
            getline(cin, player2);
            game.setPlayerNames(player1, player2);
        }
    }

    while (true) {
        game.displayBoard();
        char currentPlayer = game.getCurrentPlayer();
        string currentPlayerName = game.getPlayerName(currentPlayer);

        cout << currentPlayerName << "'s turn (" << currentPlayer << ")" << endl;

        int row, col;
        cout << "Enter row (0-2) and column (0-2), or -1 to save and quit: ";
        row = getValidInput("Row (0-2 or -1 to save): ", -1, 2);

        if (row == -1) {
            string filename;
            cout << "Enter filename to save: ";
            getline(cin, filename);
            game.saveGame(filename);
            cout << "Game saved. Goodbye!" << endl;
            break;
        }

        col = getValidInput("Column (0-2): ", 0, 2);

        if (!game.makeMove(row, col)) {
            cout << "Invalid move. Try again." << endl;
            continue;
        }

        if (game.checkWin()) {
            game.displayBoard();
            cout << "Congratulations " << currentPlayerName << "! You won!" << endl;
            break;
        }

        if (game.checkDraw()) {
            game.displayBoard();
            cout << "It's a draw!" << endl;
            break;
        }

        game.switchPlayer();
    }

    return 0;
}

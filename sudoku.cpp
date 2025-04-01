#include <iostream>
#include <fstream>
using namespace std;

class Sudoku {
private:
    int board[9][9];

public:
    Sudoku() {
        initializeBoard();
    }


   void initializeBoard() {
    // Example board initialization
    int tempBoard[9][9] = {
        {0, 0, 8, 0, 0, 0, 0, 0, 0},
        {4, 9, 0, 1, 5, 7, 0, 0, 2},
        {0, 0, 0, 0, 3, 0, 4, 1, 9},
        {0, 1, 8, 5, 0, 6, 0, 0, 2},
        {0, 0, 0, 0, 2, 0, 0, 6, 0},
        {9, 6, 0, 4, 0, 5, 3, 0, 0},
        {0, 0, 0, 3, 0, 0, 7, 2, 0},
        {0, 4, 9, 0, 0, 3, 0, 5, 7},
        {8, 2, 7, 0, 0, 9, 1, 3, 0}
    };

    // Copy the temp board to the actual board
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            board[i][j] = tempBoard[i][j];
        }
    }


}



    void displayBoard() {
        cout << "\nSudoku Board:\n";
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
               if (board[i][j] == 0) {
    cout << ". ";
} else {
    cout << board[i][j] << " ";
}
            }
            cout << endl;
        }
    }

    bool isValidMove(int row, int col, int num) {
        for (int i = 0; i < 9; i++) {
            if (board[row][i] == num || board[i][col] == num)
                return false;
        }
        int startRow = (row / 3) * 3;
        int startCol = (col / 3) * 3;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[startRow + i][startCol + j] == num)
                    return false;
            }
        }
        return true;
    }

    void makeMove(int row, int col, int num) {
        if (isValidMove(row, col, num)) {
            board[row][col] = num;
        } else {
            cout << "Invalid move! Try again.\n";
        }
    }

    void saveProgress() {
        ofstream file("sudoku_save.txt");
        if (file.is_open()) {
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    file << board[i][j] << " ";
                }
                file << endl;
            }
            file.close();
            cout << "Game saved successfully!\n";
        } else {
            cout << "Error saving the game.\n";
        }
    }

    void loadProgress() {
    ifstream file("sudoku_save.txt");
    if (file.is_open()) {
        cout << "Loading saved game...\n";
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (!(file >> board[i][j])) { // Check if reading failed
                    cout << "Error reading file! Resetting board.\n";
                    initializeBoard(); // Reset board if file is corrupted
                    return;
                }
            }
        }
        file.close();
        cout << "Game loaded successfully!\n";
    } else {
        cout << "No saved game found. Using default board.\n";
        initializeBoard();
    }
}

};

int main() {
    Sudoku game;
    int choice, row, col, num;

    game.loadProgress();

    while (true) {
        game.displayBoard();
        cout << "\n1. Make a move\n2. Save Progress\n3. Load Progress\n4. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter row (0-8), column (0-8), and number (1-9): ";
               if (!(cin >> row >> col >> num)) {
    cout << "Invalid input! Please enter three integers.\n";
    cin.clear();  // Clear the error flag
    cin.ignore(10000, '\n');  // Ignore any remaining input in the buffer
    continue;  // Restart loop
}

                game.makeMove(row, col, num);
                break;
            case 2:
                game.saveProgress();
                break;
            case 3:
                game.loadProgress();
                break;
            case 4:
                cout << "Exiting game.\n";
                return 0;
            default:
                cout << "Invalid choice. Try again!\n";
        }
    }
    return 0;
}
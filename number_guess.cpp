#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

class NumberGuessingGame {
private:
    int number, guess, attempts, maxAttempts, score;
    int lowerBound, upperBound;
    bool isLimitedAttempts;

public:
    NumberGuessingGame() {
        srand(time(0));  // Seed for random number generation
    }

    void setDifficulty() {
        int choice;
        cout << "\nChoose Difficulty Level:\n";
        cout << "1. Easy (1-50, Unlimited Attempts)\n";
        cout << "2. Medium (1-100, Max 10 Attempts)\n";
        cout << "3. Hard (1-200, Max 7 Attempts)\n";
        cout << "Enter your choice (1-3): ";

        while (!(cin >> choice) || choice < 1 || choice > 3) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter 1, 2, or 3: ";
        }

        switch (choice) {
            case 1:
                lowerBound = 1; upperBound = 50;
                maxAttempts = -1;  // Unlimited attempts
                break;
            case 2:
                lowerBound = 1; upperBound = 100;
                maxAttempts = 10;
                break;
            case 3:
                lowerBound = 1; upperBound = 200;
                maxAttempts = 7;
                break;
        }

        isLimitedAttempts = (maxAttempts != -1);
        number = rand() % (upperBound - lowerBound + 1) + lowerBound;
        attempts = 0;
        score = 100;  // Start with full score
    }

    void userGuesses() {
        cout << "\nI have chosen a number between " << lowerBound << " and " << upperBound << ". Try to guess it!\n";

        while (true) {
            cout << "\nEnter your guess: ";
            
            while (!(cin >> guess)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter a number: ";
            }

            attempts++;
            if (isLimitedAttempts) score -= 10;  // Reduce score per attempt in limited mode

            if (guess == number) {
                cout << "🎉 Congratulations! You guessed the correct number in " << attempts << " attempts.\n";
                cout << "🎯 Your Score: " << score << "\n";
                break;
            } else if (guess < number) {
                cout << "🔼 Too low! Try again.";
            } else {
                cout << "🔽 Too high! Try again.";
            }

            if (isLimitedAttempts && attempts >= maxAttempts) {
                cout << "\n❌ You've reached the maximum attempts! The number was " << number << ".\n";
                cout << "🏆 Final Score: " << score << "\n";
                break;
            }
        }
    }

    void setComputerDifficulty(int &low, int &high, int &compMaxAttempts, string &modeName) {
        int choice;
        cout << "\nChoose Computer's Guessing Difficulty:\n";
        cout << "1. Easy (Random guessing)\n";
        cout << "2. Medium (Random + Logic)\n";
        cout << "3. Hard (Binary Search)\n";
        cout << "Enter your choice (1-3): ";

        while (!(cin >> choice) || choice < 1 || choice > 3) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter 1, 2, or 3: ";
        }

        switch (choice) {
            case 1:
                modeName = "Easy";
                compMaxAttempts = 20;  // Random guessing can take longer
                break;
            case 2:
                modeName = "Medium";
                compMaxAttempts = 12;  // Mix of random and logic
                break;
            case 3:
                modeName = "Hard";
                compMaxAttempts = 8;  // Efficient Binary Search
                break;
        }
    }

    void computerGuesses() {
        int userNumber;
        cout << "\nThink of a number between 1 and 200 and let the computer guess it!\n";
        cout << "Enter the number for reference (don't let the computer see it 😉): ";

        while (!(cin >> userNumber) || userNumber < 1 || userNumber > 200) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Enter a number between 1 and 200: ";
        }

        int low = 1, high = 200, compGuess, compAttempts = 0, compMaxAttempts;
        string modeName;
        setComputerDifficulty(low, high, compMaxAttempts, modeName);

        cout << "\nComputer is guessing in **" << modeName << "** mode...\n";

        while (low <= high) {
            if (modeName == "Easy") {
                compGuess = rand() % (high - low + 1) + low;  // Random guessing
            } else if (modeName == "Medium") {
                if (compAttempts % 2 == 0) {  // Every other guess is random
                    compGuess = rand() % (high - low + 1) + low;
                } else {
                    compGuess = (low + high) / 2;  // Some logic-based guessing
                }
            } else {  // Hard Mode (Binary Search)
                compGuess = (low + high) / 2;
            }

            compAttempts++;

            cout << "Is it " << compGuess << "? (h = too high, l = too low, c = correct): ";
            char response;
            cin >> response;

            if (response == 'c') {
                cout << "🎉 Computer guessed your number in " << compAttempts << " attempts!\n";
                break;
            } else if (response == 'h') {
                high = compGuess - 1;
            } else if (response == 'l') {
                low = compGuess + 1;
            } else {
                cout << "Invalid input! Please enter 'h', 'l', or 'c'.\n";
            }

            if (compAttempts >= compMaxAttempts) {
                cout << "\n❌ Computer couldn't guess your number in time!\n";
                break;
            }
        }
    }

    bool playAgain() {
        char choice;
        cout << "\nDo you want to play again? (y/n): ";
        cin >> choice;
        return (choice == 'y' || choice == 'Y');
    }
};

int main() {
    NumberGuessingGame game;
    
    do {
        int mode;
        cout << "\nSelect Game Mode:\n";
        cout << "1. You guess the number\n";
        cout << "2. Computer guesses your number\n";
        cout << "Enter your choice (1 or 2): ";
        
        while (!(cin >> mode) || (mode != 1 && mode != 2)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice! Enter 1 or 2: ";
        }

        if (mode == 1) {
            game.setDifficulty();
            game.userGuesses();
        } else {
            game.computerGuesses();
        }
    } while (game.playAgain());

    cout << "\nThanks for playing! 🎮\n";
    return 0;
}

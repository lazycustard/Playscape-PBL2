#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <tuple>
#include <random>
#include <limits>
#include <cctype>

using namespace std;

class WordScramble {
private:
    vector<tuple<string, string, string>> words; // word, category, hint
    string originalWord;
    string scrambledWord;
    string categoryHint;
    string descriptionHint;
    int hintCount;

    string normalizeInput(const string& input) {
        string normalized;
        bool lastWasSpace = false;
        for (char c : input) {
            if (isspace(c)) {
                if (!lastWasSpace) {
                    normalized += ' ';
                    lastWasSpace = true;
                }
            } else {
                normalized += tolower(c);
                lastWasSpace = false;
            }
        }
        return normalized;
    }

public:
    WordScramble() {
        loadWordsFromFile("C:\\Users\\Amit Gupta\\Desktop\\PBLSDF2\\wordsfileh.txt");
        srand(static_cast<unsigned int>(time(0))); // Seed random number generator
    }

    void loadWordsFromFile(const string& filename) 
    {
        ifstream file(filename);
        if (!file) {
            cerr << "Error opening file: " << filename << endl;
            system("pause");  
            exit(1);
        }

        string line, word, category, hint;

        while (getline(file, line)) {
            stringstream ss(line);
            getline(ss, word, ',');
            getline(ss, category, ',');
            getline(ss, hint, ',');

            words.emplace_back(word, category, hint);
        }
        file.close();
    }

    void selectWord() {
        int index = rand() % words.size();
        originalWord = get<0>(words[index]);
        categoryHint = get<1>(words[index]);
        descriptionHint = get<2>(words[index]);
        scrambledWord = originalWord;
        random_shuffle(scrambledWord.begin(), scrambledWord.end());
        hintCount = 0;
    }

    void displayScrambledWord() {
        for (char c : scrambledWord) {
            cout << c << " ";
        }
        cout << "\n";
    }

    void playGame() {
        char hintChoice;
        do {
            selectWord();
            string userGuess;
                cout << "#########################################\n";
    cout << "#                                       #\n";
    cout << "#          | WORD SCRAMBLE |            #\n";
    cout << "#                                       #\n";
    cout << "#########################################\n";
    cout << "#                                       #\n";
    cout << "#   HOW TO PLAY:                        #\n";
    cout << "#  -> Unscramble the jumbled letters    #\n";
    cout << "#  -> Type your guess and press Enter   #\n";
    cout << "#  -> Type 'h' for a hint (Max 2 hints) #\n";
    cout << "#  -> If stuck, type 'dontknow'         #\n";
    cout << "#  -> Play again to challenge yourself! #\n";
    cout << "#                                       #\n";
    cout << "#########################################\n";
    cout << "#   Press any key to start unscrambling #\n";
    cout << "#########################################\n";

            displayScrambledWord();
            
            while (true) {
                
                cout << "Enter your guess (or type 'h' for hint): ";
                cin >> userGuess;
                
                if (userGuess == "h") {
                    if (hintCount == 0) {
                        cout<<"_____________________________________________________________________"<<endl,
                        cout << "Hint: This word belongs to the category - " << categoryHint << "\n";
                    } else if (hintCount == 1) {
                        cout<<"_____________________________________________________________________"<<endl,
                        cout << "Hint: " << descriptionHint << "\n";
                    } else {
                        cout<<"_____________________________________________________________________"<<endl,
                        cout << "No more hints available! If you don't know, type 'dontknow'.\n";
                    }
                    hintCount++;
                } else if (userGuess == "dontknow") {
                    cout<<"_____________________________________________________________________"<<endl,
                    cout << "The correct answer was: " << originalWord << "\n";
                    break;
                } else if (userGuess == originalWord) {
                    cout<<"_____________________________________________________________________"<<endl,
                    cout << "Congratulations! You guessed it right!\n";
                    break;
                } else {
                    cout<<"_____________________________________________________________________"<<endl,
                    cout << "Try again!\n";
                }
            }
            cout<<"_____________________________________________________________________"<<endl,
            cout << "Do you want to play again? (y/n): ";
            cin >> hintChoice;
        } while (hintChoice == 'y');
    }
};

int main() {
    WordScramble game;
    game.playGame();
    cin.get();  
    return 0;
}

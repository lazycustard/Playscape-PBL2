#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <chrono>
#include <algorithm>
using namespace std;
using namespace chrono;

vector<string> words = {"programming", "challenge", "keyboard", "developer", "speed", "accuracy", "practice", "language", "computer", "typing", "algorithm", "efficiency", "hardware", "software", "debugging", "syntax", "variable", "function", "loop", "recursion"};

void shuffleWords() {
    srand(time(0));
    random_shuffle(words.begin(), words.end());
}

int main() {
    int difficulty;
    cout << "Select difficulty level:\n";
    cout << "1. Easy (5 words)\n";
    cout << "2. Medium (10 words)\n";
    cout << "3. Hard (15 words)\n";
    cout << "Enter choice: ";
    cin >> difficulty;
    
    int wordCount;
    if (difficulty == 1) {
        wordCount = 5;
    } else if (difficulty == 2) {
        wordCount = 10;
    } else {
        wordCount = 15;
    }
    
    string userInput;
    cout << "\nTyping Speed Test! Type the following words as fast as you can:\n";
    shuffleWords();
    
    for (int i = 0; i < wordCount; i++) {
        cout << words[i] << " ";
    }
    cout << "\nPress ENTER when ready...";
    cin.ignore();
    cin.get();
    
    auto start = high_resolution_clock::now();
    
    int correctWords = 0;
    for (int i = 0; i < wordCount; i++) {
        cout << "Type: " << words[i] << " -> ";
        cin >> userInput;
        if (userInput == words[i]) {
            correctWords++;
        }
    }
    
    auto end = high_resolution_clock::now();
    duration<double> elapsed = end - start;
    
    cout << "\nResults:\n";
    cout << "Correct words: " << correctWords << "/" << wordCount << "\n";
    cout << "Time taken: " << elapsed.count() << " seconds\n";
    double wpm = (correctWords / elapsed.count()) * 60;
    cout << "Typing Speed: " << wpm << " words per minute (WPM)\n";
    
    return 0;
}
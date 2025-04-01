#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>

using namespace std;

const int WIDTH = 45;
const int HEIGHT = 15; 

class Snake
{
    vector<pair<int, int>> body;
    pair<int, int> direction;
    int score;

public:
    Snake() : direction({0, 1}), score(0)
     { body.push_back({HEIGHT / 2, WIDTH / 2}); }
    void move(bool grow = false)
     {
        pair<int, int> newPos = {body[0].first + direction.first, body[0].second + direction.second};
        body.insert(body.begin(), newPos);
        if (!grow) body.pop_back();
        else score++;
    }
    void grow() { move(true); } 
    bool checkCollision() 
    {
        for (size_t i = 1; i < body.size(); ++i)
            if (body[i] == body[0]) return true;
        return body[0].first < 0 || body[0].first >= HEIGHT || body[0].second < 0 || body[0].second >= WIDTH;
    }
    void changeDirection(char input)
     {
        if (input == 'w' && direction != make_pair(1, 0)) direction = {-1, 0};
        if (input == 's' && direction != make_pair(-1, 0)) direction = {1, 0};
        if (input == 'a' && direction != make_pair(0, 1)) direction = {0, -1};
        if (input == 'd' && direction != make_pair(0, -1)) direction = {0, 1};
    }
    void draw(vector<vector<char>> &grid) {
        for (auto &part : body) grid[part.first][part.second] = 'O';
    }
    int getScore() { return score; }
    pair<int, int> getHeadPosition() { return body[0]; }
};

class Food
{
    pair<int, int> position;
public:
    Food() { spawn(); }

    void spawn() { position = {rand() % HEIGHT, rand() % WIDTH}; }

    void draw(vector<vector<char>> &grid) { grid[position.first][position.second] = 'X'; }
    pair<int, int> getPosition() { return position; }
};

void startScreen() {

    system("cls");

    cout << "#########################################\n";
    cout << "#                                       #\n";
    cout << "#             |SNAKE GAME|              #\n";
    cout << "#                                       #\n";
    cout << "#########################################\n";
    cout << "#                                       #\n";
    cout << "#   HOW TO PLAY:                        #\n";
    cout << "#  -> Use W A S D to slither around     #\n";
    cout << "#  -> Eat 'X' to grow and flex          #\n";
    cout << "#  -> Don't crash, or it's game over!   #\n";
    cout << "#  -> Press 'P' to pause/resume         #\n";
    cout << "#                                       #\n";
    cout << "#########################################\n";
    cout << "#   Press any key to vibe and start     #\n";
    cout << "#########################################\n";

    _getch();
}

bool endScreen(int score) {

    system("cls");
    cout << "\n\n  GAME OVER!  \n\n";
    cout << "Final Score: " << score << "\n";
    cout << "Press R to restart or any other key to exit...";

    char choice = _getch();
    return (choice == 'r' || choice == 'R');
}

void drawGame(Snake &snake, Food &food)
{
    vector<vector<char>> grid(HEIGHT, vector<char>(WIDTH, ' '));

    food.draw(grid);
    snake.draw(grid);
    system("cls");

    // Top border
    cout << " ";
    for (int i = 0; i < WIDTH; i++) cout << "_";
    cout << "\n";

    // Middle section
    for (int i = 0; i < HEIGHT; i++) {
        cout << "|";
        for (int j = 0; j < WIDTH; j++) cout << grid[i][j];
        cout << "|\n";
    }

    // Bottom border
    cout << "|";
    for (int i = 0; i < WIDTH; i++) cout << "_";
    cout << "|\n";

    cout << "\nScore: " << snake.getScore() << "\n";
}

int main() 
{
    while (true) {
        startScreen();
        Snake snake;
        Food food;
        int speed = 200; // Slower speed at the beginning
        bool paused = false;
        while (true) {
            if (_kbhit()) {
                char key = _getch();
                if (key == 'p') {
                    paused = !paused;
                    if (paused) cout << "\nGame Paused. Press 'P' to Resume...\n";
                } else {
                    snake.changeDirection(key);
                }
            }
            if (paused) {
                Sleep(100);
                continue;
            }
            if (snake.getHeadPosition() == food.getPosition()) { 
                snake.grow(); 
                food.spawn();
                if (speed > 50) speed -= 10; // Increase speed gradually
            } else {
                snake.move();
            }
            if (snake.checkCollision()) break;
            drawGame(snake, food);
            Sleep(speed);
        }
        if (!endScreen(snake.getScore())) break;
    }
    return 0;
}

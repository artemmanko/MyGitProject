#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <chrono>

using namespace std;
using namespace std::chrono;

// ANSI-коды для цветов
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

const int SIZE = 10; // Размер игрового поля
const int MINES = 10; // Количество мин

vector<vector<char>> board(SIZE, vector<char>(SIZE, '#')); // Игровое поле
vector<vector<bool>> mines(SIZE, vector<bool>(SIZE, false)); // Поле с минами
auto startTime = high_resolution_clock::now(); // Таймер

// Инициализация игрового поля и расстановка мин
void initBoard() {
    srand(time(0));
    for (int i = 0; i < MINES; ++i) {
        int x = rand() % SIZE;
        int y = rand() % SIZE;
        if (!mines[x][y]) {
            mines[x][y] = true;
        } else {
            --i;
        }
    }
}

// Вывод игрового поля на экран
void printBoard() {
    cout << "   ";
    for (int i = 0; i < SIZE; ++i) cout << "  " << i << " ";
    cout << "\n";
    cout << "   +";
    for (int i = 0; i < SIZE; ++i) cout << "---+";
    cout << "\n";

    for (int i = 0; i < SIZE; ++i) {
        cout << " " << i << " |";
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == '#') {
                cout << CYAN << " " << board[i][j] << " " << RESET << "|";
            } else if (board[i][j] == '0') {
                cout << " " << board[i][j] << " " << "|";
            } else if (board[i][j] == '*') {
                cout << RED << " " << board[i][j] << " " << RESET << "|";
            } else if (board[i][j] == 'F') {
                cout << MAGENTA << " " << board[i][j] << " " << RESET << "|";
            } else {
                cout << YELLOW << " " << board[i][j] << " " << RESET << "|";
            }
        }
        cout << "\n";
        cout << "   +";
        for (int j = 0; j < SIZE; ++j) cout << "---+";
        cout << "\n";
    }
}

// Проверка, находятся ли координаты в пределах поля
bool isValid(int x, int y) {
    return x >= 0 && x < SIZE && y >= 0 && y < SIZE;
}

// Подсчет мин вокруг клетки
int countMines(int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (isValid(x + i, y + j) && mines[x + i][y + j]) {
                ++count;
            }
        }
    }
    return count;
}

// Открытие клетки
void reveal(int x, int y) {
    if (!isValid(x, y)) return;
    if (board[x][y] != '#') return;
    if (mines[x][y]) {
        board[x][y] = '*';
        printBoard();
        cout << RED << "Game Over! You hit a mine.\n" << RESET;
        exit(0);
    }
    int minesCount = countMines(x, y);
    board[x][y] = minesCount + '0';
    if (minesCount == 0) {
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                reveal(x + i, y + j);
            }
        }
    }
}

// Проверка победы
bool checkWin() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == '#' && !mines[i][j]) {
                return false;
            }
        }
    }
    return true;
}

// Постановка/снятие флажка
void toggleFlag(int x, int y) {
    if (!isValid(x, y)) return;
    if (board[x][y] == '#') {
        board[x][y] = 'F';
    } else if (board[x][y] == 'F') {
        board[x][y] = '#';
    }
}

// Вывод времени
void printTime() {
    auto now = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(now - startTime).count();
    cout << "Time: " << duration << "s\n";
}

// Меню
void showMenu() {
    cout << "1. New Game\n";
    cout << "2. Exit\n";
    cout << "Choose an option: ";
}

// Сброс игры
void resetGame() {
    board = vector<vector<char>>(SIZE, vector<char>(SIZE, '#'));
    mines = vector<vector<bool>>(SIZE, vector<bool>(SIZE, false));
    initBoard();
    startTime = high_resolution_clock::now();
}

int main() {
    while (true) {
        showMenu();
        int choice;
        cin >> choice;
        if (choice == 1) {
            resetGame();
            while (true) {
                printBoard();
                printTime();
                string command;
                cout << "Enter command (f x y to flag, x y to reveal): ";
                cin >> command;
                if (command == "f") {
                    int x, y;
                    cin >> x >> y;
                    toggleFlag(x, y);
                } else {
                    int x = stoi(command);
                    int y;
                    cin >> y;
                    reveal(x, y);
                }
                if (checkWin()) {
                    printBoard();
                    cout << GREEN << "Congratulations! You won the game!\n" << RESET;
                    break;
                }
            }
        } else if (choice == 2) {
            break;
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    }
    return 0;
}

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

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

vector<vector<char>> board(SIZE, vector<char>(SIZE, '#')); // Игровое поле (закрытые клетки обозначены '#')
vector<vector<bool>> mines(SIZE, vector<bool>(SIZE, false)); // Поле с минами

// Инициализация игрового поля и расстановка мин
void initBoard() {
    srand(time(0)); // Инициализация генератора случайных чисел
    for (int i = 0; i < MINES; ++i) {
        int x = rand() % SIZE;
        int y = rand() % SIZE;
        if (!mines[x][y]) {
            mines[x][y] = true; // Установка мины
        } else {
            --i; // Если мина уже есть, повторяем попытку
        }
    }
}

// Вывод игрового поля на экран
void printBoard() {
    // Верхняя граница поля
    cout << "   ";
    for (int i = 0; i < SIZE; ++i) cout << "  " << i << " ";
    cout << "\n";
    cout << "   +";
    for (int i = 0; i < SIZE; ++i) cout << "---+";
    cout << "\n";

    // Само поле
    for (int i = 0; i < SIZE; ++i) {
        cout << " " << i << " |";
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == '#') {
                cout << CYAN << " " << board[i][j] << " " << RESET << "|"; // Закрытые клетки
            } else if (board[i][j] == '0') {
                cout << " " << board[i][j] << " " << "|"; // Пустые клетки
            } else if (board[i][j] == '*') {
                cout << RED << " " << board[i][j] << " " << RESET << "|"; // Мины
            } else {
                cout << GREEN << " " << board[i][j] << " " << RESET << "|"; // Числа мин вокруг
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
    if (!isValid(x, y)) return; // Проверка на выход за границы поля
    if (board[x][y] != '#') return; // Если клетка уже открыта, ничего не делаем
    if (mines[x][y]) { // Если нашли мину
        board[x][y] = '*'; // Обозначаем мину
        printBoard(); // Показываем поле с миной
        cout << RED << "Game Over! You hit a mine.\n" << RESET;
        exit(0); // Завершаем игру
    }
    int minesCount = countMines(x, y); // Подсчет мин вокруг
    board[x][y] = minesCount + '0'; // Отображаем количество мин
    if (minesCount == 0) { // Если мин нет, открываем соседние клетки
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                reveal(x + i, y + j);
            }
        }
    }
}

int main() {
    initBoard(); // Инициализация поля
    while (true) {
        printBoard(); // Вывод поля
        int x, y;
        cout << "Enter coordinates (x y): ";
        cin >> x >> y; // Ввод координат
        reveal(x, y); // Открытие клетки
    }
    return 0;
}

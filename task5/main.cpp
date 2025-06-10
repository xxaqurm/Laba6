#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>

using namespace std;

const char ONE = '1';   // Орёл
const char ZERO = '0';   // Решка

// Генерация случайной доски
vector<vector<char>> generateBoard(int n, int m) {
    vector<vector<char>> board(n, vector<char>(m));
    mt19937 rng(time(0));
    uniform_int_distribution<int> dist(0, 1);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            board[i][j] = dist(rng) ? ONE : ZERO;

    return board;
}

// Генерация одной из двух шахматных масок
vector<vector<char>> createChessPattern(int n, int m, bool startWithEagle) {
    vector<vector<char>> pattern(n, vector<char>(m));
    char first = startWithEagle ? ONE : ZERO;
    char second = startWithEagle ? ZERO : ONE;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            pattern[i][j] = ((i + j) % 2 == 0) ? first : second;

    return pattern;
}

// Подсчёт количества несовпадающих клеток
int countDifferences(const vector<vector<char>>& board, const vector<vector<char>>& pattern) {
    int diff = 0;
    int n = board.size(), m = board[0].size();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (board[i][j] != pattern[i][j])
                ++diff;
    return diff;
}

// Печать доски
void printBoard(const vector<vector<char>>& board) {
    for (auto& row : board) {
        for (char c : row)
            cout << c << ' ';
        cout << endl;
    }
}

int main() {
    int n = 5, m = 6; // Размеры доски (можно заменить на ввод с клавиатуры)

    auto board = generateBoard(n, m);

    cout << "Исходная доска:\n";
    printBoard(board);

    auto pattern1 = createChessPattern(n, m, true);
    auto pattern2 = createChessPattern(n, m, false);

    int diff1 = countDifferences(board, pattern1);
    int diff2 = countDifferences(board, pattern2);

    // Если кол-во несовпадений нечётное, то невозможно, потому что один ход меняет два состояния
    int res = -1;
    if (diff1 % 2 == 0 || diff2 % 2 == 0)
        res = min(diff1 % 2 == 0 ? diff1 / 2 : INT32_MAX,
                  diff2 % 2 == 0 ? diff2 / 2 : INT32_MAX);

    if (res == -1)
        cout << "Невозможно достичь шахматного узора." << endl;
    else
        cout << "Минимальное количество ходов: " << res << endl;

    return 0;
}

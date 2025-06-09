#include <iostream>
#include <vector>
#include <stdexcept>
#include <limits>
#include <random>
#include <iomanip>

#include "subtasks.h"

using namespace std;

void row_negative_counter() {
    cin.exceptions(ios::failbit);
    cout << "Введите свои m и n (m > 7, n > 5): ";
    
    int m = 8, n = 6;
    while (true) {
        try {
            cin >> m >> n;
            if (m < 8 || n < 6) {
                throw invalid_argument("invalid_args");
            }
            break;
        } catch (const ios::failure& e) {
            cout << ">>> Ошибка (" << e.what() << "): Введите целые числа. Попробуйте еще раз: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } catch (const exception& e) {
            cout << ">>> Ошибка (" << e.what() << "): m должно быть больше 7, а n должно быть больше 5. Попробуйте еще раз: ";
        }
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(-9, 9);
    
    vector<vector<int>> matrix(m, vector<int>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = dist(gen);
        }
    }

    cout << "Матрица:" << endl;
    for (auto& row : matrix) {
        for (auto& clmn : row) {
            cout << setw(2) << clmn << " ";
        }
        cout << endl;
    }

    int bstRow = 0;
    int bstNegativeNum = 0;
    for (int i = 0; i < m; i++) {
        int nowNegativeNum = 0;
        for (int j = 0; j < n; j++) {
            nowNegativeNum = matrix[i][j] < 0 ? nowNegativeNum + 1 : nowNegativeNum;
        }
        if (nowNegativeNum > bstNegativeNum) {
            bstNegativeNum = nowNegativeNum;
            bstRow = i;
        }
    }

    vector<int> result;
    for (int i = 0; i < n; i++) {
        result.push_back(matrix[bstRow][i]);
    }

    cout << "Номер найденной строки: " << bstRow + 1 << endl;
    cout << "Найденная строка: ";
    for (auto& elm : result) cout << elm << " ";
    cout << endl;
}

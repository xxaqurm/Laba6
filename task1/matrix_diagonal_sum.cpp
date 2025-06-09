#include <iostream>
#include <stdexcept>
#include <vector>
#include <limits>
#include <random>
#include <iomanip>
#include <algorithm>

#include "subtasks.h"

using namespace std;

int changeNum(int num) {
    vector<int> digits;
    while (num > 0) {
        digits.push_back(num % 10);
        num /= 10;
    }

    sort(digits.begin(), digits.end(), greater<int>());
    
    int res = 0;
    for (auto& elm : digits) {
        res = res * 10 + elm;
    }

    return res;
}

void matrix_diagonal_sum() {
    cin.exceptions(ios::failbit);
    cout << "Введите свое m (m > 5): ";

    int m = 6;
    while (true) {
        try {
            cin >> m;
            if (m < 6) {
                throw invalid_argument("invalid_arg");
            }
            break;
        } catch (const ios::failure& e) {
            cout << ">>> Ошибка (" << e.what() << "): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } catch (const exception& e) {
            cout << ">>> Ошибка (" << e.what() << "): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << "Введите целое число, большее 5: ";
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(10, 100);

    vector<vector<int>> matrix(m, vector<int>(m));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            matrix[i][j] = dist(gen);
        }
    }

    cout << "Матрица:" << endl;
    for (auto& row : matrix) {
        for (auto& clmn : row) {
            cout << setw(3) << clmn << " ";
        }
        cout << endl;
    }

    vector<int> mainDiagonal;
    vector<int> secondaryDiagonal;
    for (int i = 0; i < m; i++) {
        mainDiagonal.push_back(matrix[i][i]);
        secondaryDiagonal.push_back(matrix[i][m - i - 1]);
    }

    cout << "\nMain diagonal: ";
    for (auto& elm : mainDiagonal) cout << elm << " ";
    cout << endl;

    cout << "Secondary diagonal: ";
    for (auto& elm : secondaryDiagonal) cout << elm << " ";
    cout << endl;

    int sumMainDiagonal = 0;
    int sumSecondaryDiagonal = 0;
    for (int i = 0; i < m; i++) {
        sumMainDiagonal += changeNum(mainDiagonal[i]);
        sumSecondaryDiagonal += changeNum(secondaryDiagonal[i]);
    }

    cout << "Sum main diagonal: " << sumMainDiagonal << endl;
    cout << "Sum secondary diagonal: " << sumSecondaryDiagonal << endl << endl;

    if (sumMainDiagonal > sumSecondaryDiagonal) {
        cout << "Сумма основной диагонали больше!" << endl;
    } else if (sumMainDiagonal < sumSecondaryDiagonal) {
        cout << "Сумма побочной диагонали больше!" << endl;
    } else {
        cout << "Суммы совпадают!" << endl;
    }
}

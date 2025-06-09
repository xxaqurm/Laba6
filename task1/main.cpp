/* Вариант 7 */
#include <iostream>
#include <limits>

#include "subtasks.h"

using namespace std;

int main() {
    cin.exceptions(ios::failbit);
    
    cout << "Выберите программу:\n";
    cout << "0. Выход из программы\n";
    cout << "1. Программа №1\n";
    cout << "2. Программа №2\n";
    cout << "3. Программа №3\n";
    cout << "Введите номер программы (0-3): ";

    int choice = -1;
    while (true) {
        try {
            cin >> choice;
            if (choice < 0 || choice > 3) {
                throw invalid_argument("invalid_choice");
            }
            break;
        } catch (const ios::failure& e) {
            cout << ">>> Ошибка (" << e.what() << "): Введите целое число от 0 до 3: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } catch (const exception& e) {
            cout << ">>> Ошибка (" << e.what() << "): Введите целое число от 0 до 3: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    Tasks problem = (Tasks)choice;
    switch (problem) {
        case Tasks::ExitProgram:
            return 0;
        case Tasks::RowNegativeCounter:
            row_negative_counter();
            break;
        case Tasks::MatrixDiagonalSum:
            matrix_diagonal_sum();
            break;
        case Tasks::BattleshipCounter:
            battleship_counter();
            break;
    }
}
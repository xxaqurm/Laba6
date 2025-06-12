#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <limits>
#include <vector>

#include "subtasks.h"

using namespace std;

void battleship_counter() {
    int m = 4, n = 4;
    vector<vector<char>> field = {
        {'.', '.', 'X', 'X'},
        {'X', 'X', '.', 'X'},
        {'.', '.', '.', 'X'},
        {'.', 'X', '.', 'X'}
    };

    cout << "Игровое поле:" << endl;
    for (auto& row : field) {
        for (auto& clmn : row) {
            cout << clmn << " ";
        }
        cout << endl;
    }

    int cntShips = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (field[i][j] == 'X') {
                bool isStart = true;
                if (i > 0 && field[i-1][j] == 'X') isStart = false;
                if (j > 0 && field[i][j-1] == 'X') isStart = false;
                if ((i > 0 && field[i-1][j] == 'X') && (j > 0 && field[i][j-1] == 'X')) {
                    cout << "ERROR" << endl;
                    return;
                }
                
                if (isStart) {
                    cntShips++;
                }
            }
        }
    }

    cout << "Количество кораблей: " << cntShips << endl;
}
/* Вариант 6           e = 10^(-3)*/
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

vector<double> method_gauss(vector<vector<double>> A, vector<double> b) {
    double eps = 0.001;
    int n = A.size();

    for (int i = 0; i < n; i++) {
        int maxRow = i;
        for (int k = i + 1; k < n; k++) {  // ищем максимальный элемент в колонке i
            if (abs(A[k][i]) > abs(A[maxRow][i])) {
                maxRow = k;
            }
        }
        
        swap(A[i], A[maxRow]);
        swap(b[i], b[maxRow]);

        // Проверка на нулевой элемент
        if (abs(A[i][i]) < eps) {
            cerr << "Нет уникального решения (нулевой элемент на диагонали)." << endl;
            return {};
        }

        for (int j = i + 1; j < n; j++) {  // приводим к верхнетреугольной матрице
            double factor = A[j][i] / A[i][i];
            for (int k = i; k < n; k++)
                A[j][k] -= factor * A[i][k];
            b[j] -= factor * b[i];
        }
    }

    vector<double> x(n);
    for (int i = n - 1; i >= 0; i--) {
        x[i] = b[i];
        for (int j = i + 1; j < n; j++)
            x[i] -= A[i][j] * x[j];
        x[i] /= A[i][i];
    }

    return x;
}

int main() {
    vector<vector<double>> A = {
        {0.79, -0.04, 0.21, -18},
        {0.25, -1.23, 0.18, -0.09},
        {-0.21, 0.18, 0.8, -0.13},
        {0.15, -1.31, 0.06, -0.86}
    };
    vector<double> b = {-1.24, -0.86, 2.56, 0.79};

    vector<double> result = method_gauss(A, b);

    cout << "Решение:" << endl;
    for (size_t i = 0; i < result.size(); i++)
        cout << "x" << i + 1 << " = " << fixed << setprecision(4) << result[i] << endl;

    return 0;
}

/* Вариант 6 */
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

const double EPS = 0.001;

bool isConvergent(const vector<vector<double>> A) {
    /* Проверка сходимости */
    int n = A.size();
    for (int i = 0; i < n; ++i) {
        double sum = 0;
        for (int j = 0; j < n; ++j) {
            if (i != j) sum += abs(A[i][j]);
        }
        if (abs(A[i][i]) <= sum) return false;
    }
    return true;
}

vector<double> method_simple_iters(vector<vector<double>> A, vector<double> b) {
    int n = A.size();
    vector<vector<double>> B(n, vector<double>(n));
    vector<double> c(n);

    for (int i = 0; i < n; ++i) {  // Приведение к каноническому виду
        if (abs(A[i][i]) < EPS) {
            cout << "Нулевой диагональный элемент, метод невозможен." << endl;
            return {};
        }
        for (int j = 0; j < n; ++j) {
            if (i != j)
                B[i][j] = -A[i][j] / A[i][i];
            else
                B[i][j] = 0.0;
        }
        c[i] = b[i] / A[i][i];
    }

    if (!isConvergent(A)) {
        cout << "Не выполнено условие сходимости (не диагональное преобладание)" << endl;
        return {};
    }

    vector<double> x(n, 0.0);
    vector<double> x_new(n);
    double err;
    int iters = 0;

    do {
        err = 0;
        for (int i = 0; i < n; ++i) {
            x_new[i] = c[i];
            for (int j = 0; j < n; ++j) {
                x_new[i] += B[i][j] * x[j];
            }
            err = max(err, abs(x_new[i] - x[i]));
        }

        x = x_new;
        ++iters;

        cout << "Итерация " << iters << ": ";
        for (double val : x)
            cout << fixed << setprecision(4) << val << " ";
        cout << endl;

    } while (err > EPS && iters < 1000);

    return x;
}

vector<double> method_gauss(vector<vector<double>> A, vector<double> b) {
    /* Решение СЛАУ с помощью Гаусса */
    int n = A.size();

    for (int i = 0; i < n; i++) {
        int maxRow = i;
        for (int k = i + 1; k < n; k++) {
            if (abs(A[k][i]) > abs(A[maxRow][i])) {
                maxRow = k;
            }
        }
        
        swap(A[i], A[maxRow]);
        swap(b[i], b[maxRow]);

        if (abs(A[i][i]) < EPS) {  // нулевой элемент
            cerr << "Нет уникального решения (нулевой элемент на диагонали)." << endl;
            return {};
        }

        for (int j = i + 1; j < n; j++) {  // верхнетреугольная матрица
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

    cout << "Решение по Гауссу:" << endl;
    for (size_t i = 0; i < result.size(); i++)
        cout << "x" << i + 1 << " = " << fixed << setprecision(4) << result[i] << endl;
    cout << endl;

    result.clear();
    result = method_simple_iters(A, b);
    
    if (result.empty()) {
        cout << "По методу простых итераций решений не найдено" << endl;
        return 0;
    }
    cout << "\nРешение методом простых итераций:" << endl;
    for (size_t i = 0; i < result.size(); i++)
        cout << "x" << i + 1 << " = " << fixed << setprecision(4) << result[i] << endl;

    return 0;
}

#include <iostream>
#include <cmath>

double* gauss_elimination(double** matrix, int n) {
    // Eliminacja Gaussa
    for (int i = 0; i < n; ++i) {
        // Znajdź największy element w kolumnie i
        double maxEl = std::abs(matrix[i][i]);
        int maxRow = i;
        for (int k = i + 1; k < n; ++k) {
            if (std::abs(matrix[k][i]) > maxEl) {
                maxEl = std::abs(matrix[k][i]);
                maxRow = k;
            }
        }

        // Zamień wiersze
        for (int k = i; k <= n; ++k) {
            std::swap(matrix[maxRow][k], matrix[i][k]);
        }

        // Eliminacja
        for (int k = i + 1; k < n; ++k) {
            double coeff = -matrix[k][i] / matrix[i][i];
            for (int j = i; j <= n; ++j) {
                if (i == j) {
                    matrix[k][j] = 0;
                } else {
                    matrix[k][j] += coeff * matrix[i][j];
                }
            }
        }
    }

    // Podstawianie wsteczne
    double* result = new double[n];
    for (int i = n - 1; i >= 0; --i) {
        result[i] = matrix[i][n] / matrix[i][i];
        for (int k = i - 1; k >= 0; --k) {
            matrix[k][n] -= matrix[k][i] * result[i];
        }
    }

    return result;
}

int main() {
    const int n = 4;
    double** matrix = new double*[n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new double[n + 1];
    }

    // Przykład układu równań:
    // 2x + 3y - z + 2w = 5
    // 4x + y + 5z - 3w = 6
    // -2x + 5y + 2z + w = 7
    // x - y + 3z + 2w = 4
    double data[n][n+1] = {
        {2, 3, -1, 2, 5},
        {4, 1, 5, -3, 6},
        {-2, 5, 2, 1, 7},
        {1, -1, 3, 2, 4}
    };

    // Wypełnienie dynamicznej macierzy
    for (int i = 0; i < n; ++i)
        for (int j = 0; j <= n; ++j)
            matrix[i][j] = data[i][j];

    double* solution = gauss_elimination(matrix, n);


    
    std::cout << "Rozwiązanie układu:\n";
    for (int i = 0; i < n; ++i) {
        std::cout << "x" << i + 1 << " = " << solution[i] << std::endl;
    }

    delete[] solution;
    for (int i = 0; i < n; ++i)
        delete[] matrix[i];
    delete[] matrix;

    return 0;
}

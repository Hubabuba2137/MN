#include <iostream>
#include <vector>

double lagrangeInterpolation(const double* x, const double* y, int size, double val) {
    double result = 0.0;
    
    for (int i = 0; i < size; ++i) {
        double term = y[i];
        for (int j = 0; j < size; ++j) {
            if (i != j) {
                term *= (val - x[j]) / (x[i] - x[j]);
            }
        }
        result += term;
    }
    return result;
}

void dividedDifferences(double* x, double* y, double** table, int size) {
    for (int i = 0; i < size; ++i) {
        table[i][0] = y[i];
    }
    
    for (int j = 1; j < size; ++j) {
        for (int i = 0; i < size - j; ++i) {
            table[i][j] = (table[i + 1][j - 1] - table[i][j - 1]) / (x[i + j] - x[i]);
        }
    }
}

int main() {
    double x[] = {1, 2, 3};
    double y[] = {2, 3, 5};
    int size = sizeof(x) / sizeof(x[0]);
    double val = 2.5;
    std::cout << "Interpolacja Lagrange’a dla x=" << val << " wynosi " << lagrangeInterpolation(x, y, size, val) << std::endl;
    
    double** table = new double*[size];
    for (int i = 0; i < size; ++i) {
        table[i] = new double[size];
    }
    dividedDifferences(x, y, table, size);
    
    std::cout << "Ilorazy różnicowe: ";
    for (int i = 0; i < size; ++i) {
        std::cout << table[0][i] << " ";
    }
    std::cout << std::endl;
    
    for (int i = 0; i < size; ++i) {
        delete[] table[i];
    }
    delete[] table;
    
    return 0;
}

#include <iostream>

double horner(const double* coeffs, int size, double x) {
    double result = coeffs[size - 1];
    for (int i = size - 2; i >= 0; --i) {
        result = result * x + coeffs[i];
    }
    return result;
}

double newtonHorner(const double* a, const double* x, int size, double val) {
    double result = a[size - 1];
    for (int i = size - 2; i >= 0; --i) {
        result = result * (val - x[i]) + a[i];
    }
    return result;
}

void newtonToNatural(const double* a, const double* x, int size, double* coeffs) {
    for (int i = 0; i < size; ++i) {
        coeffs[i] = 0;
    }
    
    coeffs[0] = a[0];
    for (int i = 1; i < size; ++i) {
        for (int j = i; j > 0; --j) {
            coeffs[j] = coeffs[j - 1] - x[i - 1] * coeffs[j];
        }
        coeffs[0] = -x[i - 1] * coeffs[0] + a[i];
    }
}

int main() {
    double coeffs[] = {2, -3, 1}; // W(x) = x^2 - 3x + 2
    int size = sizeof(coeffs) / sizeof(coeffs[0]);
    double x = 3;
    std::cout << "Horner wynik: " << horner(coeffs, size, x) << std::endl;
    
    double a[] = {2, -1, 1}; // W(x) w postaci Newtona
    double x_vals[] = {1, 2};
    int size_a = sizeof(a) / sizeof(a[0]);
    std::cout << "Newton-Horner wynik: " << newtonHorner(a, x_vals, size_a, x) << std::endl;
    
    double naturalCoeffs[size_a] = {0};
    newtonToNatural(a, x_vals, size_a, naturalCoeffs);
    std::cout << "Wspolczynniki w postaci naturalnej: ";
    for (int i = 0; i < size_a; ++i) std::cout << naturalCoeffs[i] << " ";
    std::cout << std::endl;
    
    return 0;
}

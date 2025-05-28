#include <iostream>
#include <cmath>
#include <iomanip>

//f(x) = sin(-x) + e^-x - x^3
//x -> <-1,1>
double func(double x){
    return sin(-x) + exp(-x) - x*x*x;
}

double base_func(double x, int i){
    return pow(x, i);
}

double quad_trap(double (*f)(double), double a, double b, double dx){
    double sum = 0;
    
    double min_v = std::min(a,b);
    double max_v = std::max(a,b);
    
    for(double i=min_v; i<max_v; i+=dx){
        sum += ((f(i) + f(i+dx))*dx)/2;
    }
    
    return sum;
}

void lu(double **A, double **L, double **U, int n){
    //A to macierz do rozkładu
    
    for(int i=0; i<n; i++){
        for(int j=0; j<n;j++){
            L[i][j] = 0;
        }
    }
    
    for(int i=0; i<n; i++){
        for(int j=0; j<n;j++){
            U[i][j] = 0;
        }
    }
    
    for(int i = 0; i<n; i++){
        for(int k=i; k<n; k++){
            double s = 0;
            for(int j = 0; j<i; j++){
                s += (L[i][j]*U[j][k]);
            }
            
            U[i][k] = A[i][k] - s;
        }        
        
        for(int k= i; k < n; k++){
            if(i == k){
                L[i][i] = 1;
            }
            else{
                double s = 0;
                for(int j = 0; j<i; j++){
                    s += (L[k][j] * U[j][i]);
                }
                
                L[k][i] = (A[k][i] - s)/U[i][i];
            }
        }
    }
}

void solve_L(double **L, double *y, double *b, int n){
    for(int i = 0; i < n; i++){
        double sum = 0;
        for(int j = 0; j < i; j++){
            sum += L[i][j] * y[j];
        }
        y[i] = (b[i] - sum) / L[i][i];
    }
}

void solve_U(double **U, double *x, double *y, int n){
    for(int i = n-1; i >= 0; i--){
        double sum = 0;
        for(int j = i+1; j < n; j++){
            sum += U[i][j] * x[j];
        }
        x[i] = (y[i] - sum) / U[i][i];
    }
}

double skal(double (*f)(double), int base_i, int base_j){
    double dx = 0.001;
    double a = -1;
    double b = 1;
    
    double sum = 0;
    
    for(double x = a; x < b; x += dx){
        double val1 = base_func(x, base_i) * base_func(x, base_j);
        double val2 = base_func(x + dx, base_i) * base_func(x + dx, base_j);
        sum += ((val1 + val2) * dx) / 2;
    }
    
    return sum;
}

double skal_f_base(double (*f)(double), int base_i){
    double dx = 0.001;
    double a = -1;
    double b = 1;
    
    double sum = 0;
    
    for(double x = a; x < b; x += dx){
        double val1 = f(x) * base_func(x, base_i);
        double val2 = f(x + dx) * base_func(x + dx, base_i);
        sum += ((val1 + val2) * dx) / 2;
    }
    
    return sum;
}

int main()
{
    int n = 6;
    
    double ** A = new double*[n];
    for(int i=0; i<n; i++){
        A[i] = new double[n];
    }
    
    double ** L = new double*[n];
    double ** U = new double*[n];
    for(int i=0; i<n; i++){
        L[i] = new double[n];
        U[i] = new double[n];
    }
    
    double * a = new double[n];
    double * b = new double[n];
    double * y = new double[n];
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            A[i][j] = skal(func, i, j);
        }
    }
    
    for(int i = 0; i < n; i++){
        b[i] = skal_f_base(func, i);
    }
    
    std::cout << "\nMacierz A:\n";
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            std::cout << std::setw(10) << std::fixed << std::setprecision(6) << A[i][j] << " ";
        }
        std::cout << "\n";
    }
    
    std::cout << "\nWektor b:\n";
    for(int i = 0; i < n; i++){
        std::cout << std::setw(10) << std::fixed << std::setprecision(6) << b[i] << "\n";
    }
    
    lu(A, L, U, n);
    
    solve_L(L, y, b, n);
    solve_U(U, a, y, n);
    
    std::cout << "\nWspółczynniki aproksymacji:\n";
    for(int i = 0; i < n; i++){
        std::cout << "a[" << i << "] = " << a[i] << "\n";
    }
    
    std::cout << "\nWielomian aproksymujący:\n";
    std::cout << "P(x) = ";
    std::cout << a[0];
    for(int i = 1; i < n; i++){
        std::cout<<" + "<<a[i]<<"*x^"<<i;
    }
    
    for(int i = 0; i < n; i++){
        delete[] A[i];
        delete[] L[i];
        delete[] U[i];
    }
    delete[] A;
    delete[] L;
    delete[] U;
    delete[] a;
    delete[] b;
    delete[] y;
    
    return 0;
}

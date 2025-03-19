#include <iostream>
#include "matrix.cpp" //dynamiczna klasa macierzy
#include <fstream>

std::vector<double> gauss(Matrix mat){
    if(!mat.rows+1 >= mat.cols){
        throw invalid_argument("Nie da się wyznaczyć rozwiązań");
    }
    std::vector<double> res;
    res.resize(mat.rows); //inicjujemy wektor z odpowiedziami
    
    Matrix A=mat;
    
    for(int p = 0; p < A.rows - 1; p++){
        for(int i = p + 1; i < A.rows; i++){
            double factor = A[i][p] / A[p][p];
            for(int j = p; j < A.cols; j++){
                A[i][j] -= factor * A[p][j];
            }
        }
    }

    //std::cout<<A<<"\n";

    double xn = A[A.rows-1][A.rows]/A[A.rows-1][A.rows-1]; // -7/-5
    
    res[A.rows-1]=xn;

    for(int i = A.rows - 2; i >= 0; i--){
        double sum_ax = 0.0;
        for(int j = i + 1; j < A.rows; j++){
            sum_ax += A[i][j] * res[j];
        }
        res[i] = (A[i][A.cols - 1] - sum_ax) / A[i][i];
    }

    return res;

}

int main(){
    /*
    std::fstream plik;
    plik.open("D:/studia/S4/Metody Numeryczne/Kody/macierz.txt");
    if(!plik.good()){
        std::cout<<"error\n";
    }
    int rows = 0, cols = 0;
    plik >> rows;
    plik >> cols;

    Matrix mat(rows, cols);

    for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			plik>> mat[i][j];
		}
	}

    plik.close();
    */
    /*
    2 4 2 1
    2 2 3 3
    4 2 2 1
    */
    Matrix mat(3,4);
    mat[0][0] = 2;
    mat[0][1] = 4;
    mat[0][2] = 2;
    mat[0][3] = 1;

    mat[1][0] = 2;
    mat[1][1] = 2;
    mat[1][2] = 3;
    mat[1][3] = 3;

    mat[2][0] = 4;
    mat[2][1] = 2;
    mat[2][2] = 2;
    mat[2][3] = 1;


    std::cout<<mat<<"\n";

    std::vector<double> X_res = gauss(mat);
    for(auto it:X_res){
        std::cout<<it<<"\n";
    }

    return 0;
}
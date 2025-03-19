#include <vector>
#include <iostream>
#include <stdexcept>
#include <math.h>

using namespace std;

struct Matrix {
    vector<vector<double>> data;
    int rows;
    int cols;

    //Constructor
    Matrix(int r, int c) : rows(r), cols(c) {
        if (r <= 0 || c <= 0) {
            throw invalid_argument("Dimensions must be positive integers.");
        }
        data.resize(r, vector<double>(c, 0.0));
    }

    //Constructor with initializing values
    Matrix(int r, int c, const vector<vector<double>>& init_data) : rows(r), cols(c) {
        if (r <= 0 || c <= 0) {
            throw invalid_argument("Dimensions must be positive integers.");
        }
        if (init_data.size() != r || init_data[0].size() != c) {
            throw invalid_argument("Initial data dimensions do not match specified dimensions.");
        }
        data = init_data;
    }

    int getRows() const{
        return rows; 
    }

    int getCols() { 
        return cols; 
    }

    vector<double>& operator[](int index) {
        if (index < 0 || index >= rows) {
            throw out_of_range("Row index out of bounds.");
        }
        return data[index];
    }

    //Matrix addition
    Matrix operator+(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw invalid_argument("Matrices must have the same dimensions for addition.");
        }

        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    //Matrix subtraction
    Matrix operator-(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw invalid_argument("Matrices must have the same dimensions for subtraction.");
        }

        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    //Matrix multiplication
    Matrix operator*(const Matrix& other) const {
        if (cols != other.rows) {
            throw invalid_argument("Matrices cannot be multiplied. Columns of first matrix must match rows of second.");
        }

        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < other.cols; ++j) {
                double sum = 0;
                for (int k = 0; k < cols; ++k) {
                    sum += data[i][k] * other.data[k][j];
                }
                result[i][j] = sum;
            }
        }
        return result;
    }

    double determinant() const {
        if (!isSquare()) {
            throw invalid_argument("Determinant can only be calculated for square matrices.");
        }

        if (rows == 1) {
            return data[0][0];
        } else if (rows == 2) {
            return data[0][0] * data[1][1] - data[0][1] * data[1][0];
        } else {
            double det = 0;
            for (int col = 0; col < cols; ++col) {
                Matrix minor = getMinor(0, col);
                det += pow(-1, col) * data[0][col] * minor.determinant();
            }
            return det;
        }
    }

    // Transpose the matrix
    Matrix transpose() const {
        Matrix result(cols, rows);
        for (int i = 0; i < cols; ++i) {
            for (int j = 0; j < rows; ++j) {
                result[i][j] = data[j][i];
            }
        }
        return result;
    }

    bool isSquare() const { return rows == cols; }

    //Calculate sum of diagonal elements
    double trace() const {
        if (!isSquare()) {
            throw invalid_argument("Trace can only be calculated for square matrices.");
        }

        double sum = 0;
        for (int i = 0; i < rows; ++i) {
            sum += data[i][i];
        }
        return sum;
    }

    Matrix inverse() {
        // Check if the matrix is square and has non-zero determinant
        if (!this->isSquare()) {
            throw invalid_argument("Inverse only exists for square matrices.");
        }

        double det = this->determinant();
        if (det == 0.0) {
            throw invalid_argument("Matrix is singular; inverse does not exist.");
        }

        int size = this->getRows();
        vector<vector<double>> cofactors(size, vector<double>(size));

        // Calculate the cofactor matrix
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                // Compute minor by excluding row i and column j
                Matrix minor = this->getMinor(i, j);
                double minor_det = minor.determinant();
                cofactors[i][j] = pow(-1, i + j) * minor_det;
            }
        }

        // Transpose the cofactor matrix to get adjugate (adjoint)
        Matrix adjugate(size, size);
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                adjugate[j][i] = cofactors[i][j];
            }
        }

        // Multiply each element of the adjugate by 1/determinant
        Matrix inverse(size, size);
        double inv_det = 1.0 / det;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                inverse[i][j] = adjugate[i][j] * inv_det;
            }
        }

        return inverse;
    }

    //Helper function for greating aaaa minor
    Matrix getMinor(int row, int col) const {
        vector<vector<double>> minor_data;

        for (int i = 0; i < rows; ++i) {
            if (i == row) continue;
            vector<double> minor_row;
            for (int j = 0; j < cols; ++j) {
                if (j == col) continue;
                minor_row.push_back(data[i][j]);
            }
            minor_data.push_back(minor_row);
        }

        return Matrix(rows - 1, cols - 1, minor_data);
    }


};

// Overload << operator for output
ostream& operator<<(ostream& os, Matrix& mat) {
    for (int i = 0; i < mat.getRows(); ++i) {
        for (int j = 0; j < mat.getCols(); ++j) {
            os << mat.data[i][j] << "   ";
        }
        os << endl;
    }
    return os;
}

// Overload >> operator for input
istream& operator>>(istream& is, Matrix& mat) {
    for (int i = 0; i < mat.getRows(); ++i) {
        for (int j = 0; j < mat.getCols(); ++j) {
            is >> mat.data[i][j];
        }
    }
    return is;
}
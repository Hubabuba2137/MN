#include <iostream>
#include <cmath>

struct Vec {
    float x; //1
    float y; //x
    float z; //x^2

    Vec() : x(0), y(0), z(0) {}
    Vec(float a, float b, float c) : x(a), y(b), z(c) {}

    Vec operator +(const Vec &v) const {
        return Vec(x + v.x, y + v.y, z + v.z);
    }
    
    Vec operator -(const Vec &v) const {
        return Vec(x - v.x, y - v.y, z - v.z);
    }
    
    Vec operator *(const Vec &v) const {
        return Vec(x * v.x, y * v.y, z * v.z);
    }
};

Vec operator *(const double d, const Vec &v) {
    return Vec(v.x * d, v.y * d, v.z * d);
}

std::ostream & operator <<( std::ostream & os, const Vec & v ) {
    os << "<" << v.x << ", " << v.y << ", " << v.z << ">";
    return os;
}

double iloczyn_skal_wiel(Vec &v, Vec &w, double a, double b) {

    double I0 = (b - a);
    double I1 = (std::pow(b,2) - std::pow(a,2)) / 2.0;
    double I2 = (std::pow(b,3) - std::pow(a,3)) / 3.0;
    double I3 = (std::pow(b,4) - std::pow(a,4)) / 4.0;
    double I4 = (std::pow(b,5) - std::pow(a,5)) / 5.0;

    double v0 = v.x, v1 = v.y, v2 = v.z;
    double w0 = w.x, w1 = w.y, w2 = w.z;

    return   v0 * w0 * I0
           + (v0 * w1 + v1 * w0) * I1
           + (v0 * w2 + v1 * w1 + v2 * w0) * I2
           + (v1 * w2 + v2 * w1) * I3
           + v2 * w2 * I4;
}

Vec* gram_schmidt(int n, Vec f_i[], double a, double b) {
    Vec* g_i = new Vec[n];
    for (int i = 0; i < n; i++) {
        g_i[i] = f_i[i];
        for (int j = 0; j < i; j++) {
            double proj_coeff = iloczyn_skal_wiel(g_i[j], f_i[i], a, b) / iloczyn_skal_wiel(g_i[j], g_i[j], a, b);
            g_i[i] = g_i[i] - proj_coeff * g_i[j];
        }
    }
    return g_i;
}

int main() {
    double a = 0.0;
    double b = 1.0;
    
    int n = 3;
    Vec f_i[n];
    
    //baza standardowa
    f_i[0] = Vec(1, 0, 0);
    f_i[1] = Vec(0, 1, 0);
    f_i[2] = Vec(0, 0, 1);

    std::cout << "f_i:\n";
    for (int i = 0; i < n; i++) {
        std::cout << f_i[i] << "\n";
    }

    Vec* g_i = gram_schmidt(n, f_i, a, b);

    std::cout << "\ng_i[" << a << "," << b << "]\n";
    for (int i = 0; i < n; i++) {
        std::cout << g_i[i] << "\n";
    }

    delete[] g_i;
    return 0;
}
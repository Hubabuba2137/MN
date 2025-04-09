#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

double quad_trap(double (*f)(double), double a, double b, double dx){
    double sum = 0;
    
    double min_v = min(a,b);
    double max_v = max(a,b);
    
    for(double i=min_v; i<max_v; i+=dx){
        sum += ((f(i) + f(i+dx))*dx)/2;
    }
    
    return sum;
}

double quad_simp(double (*f)(double), double a, double b, double dx){
    double sum = 0;
    
    double min_v = min(a,b);
    double max_v = max(a,b);
    
    for(double i=min_v; i<max_v; i+=dx){
        sum += (f(i)+4*f((i+i+dx)/2)+f(i+dx))*((dx)/6);
    }
    
    return sum;
}

double func(double x){
    /*
    //x^2sin^3(x)
    return pow(sin(x),3)*x*x;
    */
    
    /*
    //exp(x^2)(x-1)
    return exp(x*x)*(x-1);
    */
    
    
    //sin(1/x)
    return sin(1/x);
    
    
}

double func_2(double x){
    if(x == 0.0){
        return 1.0;
    }
    else{
        return sin(x)/x;
    }
}


int main()
{
    cout<<"quad_trap"<<endl;
    for(int i=1; i<5;i++){
        cout<<"\t"<<quad_trap(func, 0.0, 1.0, pow(10, -i))<<endl;
    }
    
    cout<<"quad_simp"<<endl;
    for(int i=1; i<5;i++){
        cout<<"\t"<<quad_simp(func, 0.0, 1.0, pow(10, -i))<<endl;
    }
    
    return 0;
}

#include <iostream>
#include <math.h>

struct Data{
    double iteration;
    double begin;
    double end;

    Data(double iter, double beg, double ending){
        iteration = iter;
        begin = beg;
        end = ending;
    }
};

double func(double x){
    return x*x + 2*x+ 5;
}

double integrate_sq(Data pos){

    double s = (pos.end-pos.begin)/pos.iteration;
    double sum =0;
    double h=-s; //w pętli dodajemy s nawet w pierwszym kroku to tutaj odejmujemy żeby być na zero

    for(int i=0; i<pos.iteration;i++){
        h += func((pos.begin+s)+(s/2));
    }
    //std::cout<<h<<"\n";
    return s*h;
}

double integrate_trap(Data pos){
    double s = (pos.end-pos.begin)/pos.iteration; //step
    double sum = 0;
    double h=pos.begin;

    for(int i=0; i<pos.iteration;i++){
        sum += (func(h) + func(h+s))/2;
        h +=s;
    }
    return sum*s;
}

double integrate_simps(Data pos){
    double s = (pos.end-pos.begin)/pos.iteration;
    double sum = 0;
    double h = pos.begin;

    for(int i=0; i<pos.iteration;i++){
        sum += (func(h)+4*func((h+h+s)/2)+func(h+s))*((s)/6);
        h +=s;
    }

    return sum;
}

int main(){

    Data pos(4, 0.5, 2.5); 

    std::cout<<"Metody dla sin(x): \n\tMetoda kwadratów: "<<integrate_sq(pos)
    <<"\n\tMetoda trapezów: "<<integrate_trap(pos)<<"\n\tMetoda Simpsona: "<<integrate_simps(pos);



    return 0;
}
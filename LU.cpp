#include <iostream>

void lu(double **A, double **L, double **U, int n){
    /*
    for(int i=0; i<n; i++){
        for(int j=0; j<n;j++){
            std::cout<<A[i][j]<<" ";
        }
        std::cout<<"\n";
    }*/
    
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

int main() {
    int n=3;
    double **A = new double*[n];
    
    for(int i=0; i<n; i++){
        A[i] = new double[n];
    }
    
    double **L = new double*[n];
    
    for(int i=0; i<n; i++){
        L[i] = new double[n];
    }
    
    double **U = new double*[n];
    
    for(int i=0; i<n; i++){
        U[i] = new double[n];
    }
    
    /*
    double A_val[3][3] = {{60, 30, 20}
                        ,{30,20,15}
                        ,{20,15,12}};
    */
    
    double A_val[3][3] = {{3, 0, 1}
                        ,{0,-1,3}
                        ,{1,3,0}};
    
    
    /*
    double A_val[3][3] = {{2, 1, -2}
                        ,{4,2,-1}
                        ,{6,3,11}};
    */
                    
    for(int i=0; i<n; i++){
        for(int j=0; j<n;j++){
            A[i][j] = A_val[i][j];
        }
    }
    
    lu(A, L, U, n);
    std::cout<<"A:\n";
    
    for(int i=0; i<n; i++){
        for(int j=0; j<n;j++){
            std::cout<<A[i][j]<<" ";
        }
        std::cout<<"\n";
    }
    
    std::cout<<"\nU:\n";
    
    for(int i=0; i<n; i++){
        for(int j=0; j<n;j++){
            std::cout<<U[i][j]<<" ";
        }
        std::cout<<"\n";
    }
    std::cout<<"\nL:\n";
    
    for(int i=0; i<n; i++){
        for(int j=0; j<n;j++){
            std::cout<<L[i][j]<<" ";
        }
        std::cout<<"\n";
    }

    return 0;
}

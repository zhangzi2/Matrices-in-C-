//
//  main.cpp
//  matrix class
//
//  Created by Kevin Zhang on 12/11/18.
//  Copyright © 2018 Kevin Zhang. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <random>
#include <iterator>
#include <array>
using namespace std;


//prints matrix A
void print_matrix(const double * A, int rows, int cols){
    for (int i = 0; i < rows; ++i){
        for (int j = 0; j < cols; ++j){
            cout << A[i+j*rows] << " ";
        }
        cout << endl;
    }
}

//matrix addition, adds B to A (modifies A)
double * add_matrix(double * A, const double * B, int rows, int cols){
    for (int i = 0; i < rows; ++i){
        for (int j = 0; j < cols; ++j){
            A[i+j*rows] +=  B[i+j*rows];
        }
    }
    return A;
}


//scalar multiply matrix A by integer val, computes val*A
double * scalar_mult(double * A, int rows, int cols, double val){
    for (int i = 0; i < rows; ++i){
        for (int j = 0; j < cols; ++j){
            A[i+j*rows] = val*A[i+j*rows];
        }
    }
    return A;
}

//naive matrix matrix multiplication A is m x l, B is l x n
double *  dumb_multiply(const double * A, const double * B, double * C, int rows, int cols, int shared_dim){
    for (int i = 0; i < rows; ++i){
        for (int j = 0; j < cols; ++j){
            for (int k = 0; k < shared_dim; ++k){
                C[i+j*rows] += A[i+k*rows]*B[k+j*shared_dim];
            }
        }
    }
    return C;
}

//computes the transpose of B = A^T
double * transpose(double * A, double * B, int rows, int cols){
    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < cols; ++j){
            B[j+i*cols] = A[i+j*rows]; //switches from col-major to row-major
        }
    }
    return B;
}

//creates an rows x cols identity matrix
double *  identity(double * A, int rows, int cols){
    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < cols; ++j){
            if (i == j){
                A[i+j*rows] = 1;
            }
            else{
                A[i+j*rows] = 0;
            }
        }
    }
    return A;
}

//returns ij element of matrix A
double get_ij(const double * A, int i, int j, int rows){
    return A[i+j*rows];
}

//sets ij element to val
void set_ij(double * A, int i, int j, int rows, double val){
    A[i+j*rows] = val;
}

//returns the ith row of matrix A
double * extract_row(const double * A, double * v, int rows, int cols, int i){
    for (int j = 0; j < cols; ++j){
        v[j] = A[i+j*rows];
    }
    return v;
}

//returns the jth column of matrix A
double * extract_col(double * A, double * v, int rows, int cols, int j){
    for (int i = 0; i < rows; ++i){
        v[i] = A[i+j*rows];
    }
    return v;
}

//returns the dot product of vector a and b
double dot(double * a, double * b, int dim){
    double result = 0.0;
    for (int i = 0; i < dim; ++i){
        result += a[i]*b[i];
    }
    return result;
}
//returns 2 norm of vector a
double norm(double * a, int dim){
    double result = pow(dot(a,a,dim),0.5);
    return result;
}

//computes the QR decomposition of A via modified Gram Schmidt
void QR(double * A, double * Q, double * R, int rows, int cols){
    double * v = new double[rows*cols];
    double * q = new double[rows];
    double * v_i = new double[rows];
    double * v_j = new double[rows];
    fill_n(Q,rows*cols,0.0);
    fill_n(R,rows*cols,0.0);
    
    memcpy(v, A, rows*cols*sizeof(double)); //copy A into v
    for (int i = 0; i < cols; ++i){
        extract_col(v, v_i, rows, cols, i); //ith column of v
        R[i+i*rows] = norm(v_i, rows); //r_ii = ||v_i||
        memcpy(q, v_i, rows*sizeof(double)); //q_i = v_i
        scalar_mult(q, rows, 1, 1/norm(v_i, rows)); //q_i/r_ii

        //build Q col by col
        for (int k = 0; k < rows; ++k){
            Q[k+i*rows] = q[k];
        }
        
        for (int j = i+1; j < cols ; ++j){
            double * q_i = new double[rows];
            memcpy(q_i,q,rows*sizeof(double)); //this is necessary so that the columns of Q are not changed within the loop
            extract_col(v, v_j, rows, cols, j); //v_j
            R[i+j*rows] = dot(q_i,v_j,rows); //r_ij = q_i * v_j
            scalar_mult(q_i, rows, 1, -1*R[i+j*rows]); //-r_ij*q_i
            add_matrix(v_j, q_i, rows, 1); // v_j - r_ij*q_i
            for (int k = 0; k < rows; ++k){ //update the next column of v
                v[k+j*rows] = v_j[k];
            }
            delete [] q_i;
        }
    }
    cout << "Q = " << endl;
    print_matrix(Q, rows, cols);
    cout<<"\n"<<endl;
    cout << "R = " << endl;
    print_matrix(R, rows, cols);
    cout << "\n" << endl;
    
    double * q_0 = new double[rows];
    double * q_1 = new double[rows];
    
    extract_col(Q, q_0, rows, cols, 0);
    extract_col(Q, q_1, rows, cols, 1);
    cout << "are the columns orthogonal?"<<endl;
    cout << dot(q_0,q_1,rows) << endl;
    cout << "\n" << endl;
    
    cout << "are the columns normal?"<<endl;
    cout << dot(q_0,q_0,rows) << endl;
    cout << "\n" << endl;
    
    //de-allocate
    delete [] v;
    delete [] q;
    delete [] v_i;
    delete [] v_j;
    delete [] q_0;
    delete [] q_1;
}

int main() {
    int m = 5; //number of rows of A
    int l = 5; //number of cols of A and number of rows of B
    int n = 5; //number of cols of B
    //create matrices A and B dynamically
    double * A = new double[m*l];
    double * B = new double[l*n];
    //blank matrix C to store results
    double * C = new double[m*n];
    double * v = new double[3];
    double * w = new double[m];
    //initialize A and B with random integer entries from 0-10, note that this is column-major storage
    for (int i = 0; i < m; ++i){
        for (int j = 0; j < l; ++j){
            A[i+j*m] = rand() % 10;
        }
    }

    cout << "A = " << endl;
    print_matrix(A, m, l);
    cout << "\n";

    QR(A,B,C,m,l);
    
    //de-allocate
    delete [] A;
    delete [] B;
    delete [] C;
    delete [] v;
    delete [] w;
    return 0;
}


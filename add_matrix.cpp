//
//  main.cpp
//  matrix class
//
//  Created by Kevin Zhang on 12/11/18.
//  Copyright © 2018 Kevin Zhang. All rights reserved.
//

#include <iostream>
#include <vector>
#include <math.h>
#include <string>
using namespace std;
//adds two matrices A+B=C
int main() {
    int A[2][2], B[2][2], C[2][2];
    for (int i = 0; i < 2; ++i){
        for (int j = 0; j < 2; ++j){
            A[i][j] = (rand() % static_cast<int>(11));
            B[i][j] = (rand() % static_cast<int>(11));
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    cout << "A =" << endl;
    for (int i = 0; i < 2; ++i){
        for (int j = 0; j < 2; ++j){
            cout << A[i][j] << " ";
        }
        cout<<endl;
    }
    
    cout << "B =" << endl;
    for (int i = 0; i < 2; ++i){
        for (int j = 0; j < 2; ++j){
            cout << B[i][j] << " ";
        }
        cout<<endl;
    }
    
    cout << "C =" << endl;
    for (int i = 0; i < 2; ++i){
        for (int j = 0; j < 2; ++j){
            cout << C[i][j] << " ";
        }
        cout<<endl;
    }
    return 0;
}


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

//prints a m x n matrix with random entries from 0-10
void print_matrix(int m, int n){
    int mat[m][n];
    for (int i = 0; i < m; ++i){
        for (int j = 0; j < n; ++j){
            mat[i][j] =  (rand() % static_cast<int>(11));
        }
    }
    for (int i = 0; i < m; ++i){
        for (int j = 0; j < n; ++j){
            cout << mat[i][j] << " ";
        }
        cout<<endl;
    }
}


int main() {
    
    print_matrix(2,4);
    return 0;
    
}


#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <lapacke.h>
#include <cblas.h>
#include <chrono>
// #include "kim.h"
// #include "scheme4.h"
#include "scheme6.h"


void printMatrix(double* matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i * n + j] << "\t";  // Print each element followed by a tab for spacing
        }
        cout << endl;  // Move to the next line after printing a row
    }
}



int main() {
    int n = 20;  // Define the size of the matrix (change as needed)
    double h = 0.1;  // Example value for h (you can change this as needed)

    // Generate the matrices
    double* P = dP(n);
    double* Q = dQ(n, h);

    // Print the matrices
    cout << "Matrix P:" << endl;
    printMatrix(P, n);
    cout << endl;

    cout << "Matrix Q:" << endl;
    printMatrix(Q, n);
    cout << endl;

    // Free the allocated memory
    delete[] P;
    delete[] Q;

    return 0;
}

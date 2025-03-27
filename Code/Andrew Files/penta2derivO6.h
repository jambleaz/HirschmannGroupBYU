#include <cmath>
#include<iostream>

using namespace std;

double* dP(int n) {
    double alpha = 12.0 / 97.0;
    double beta =  - 1.0 / 194.0;

    double gamma01 = 11.0 / 2.0;
    double gamma02 =  - 131.0 / 4.0;

    // Create an nxn matrix with all elements initialized to zero
    double* P = new double[n * n]();

    // Set the diagonal values of the matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                // Main diagonal
                P[i * n + j] = 1;

            // UNCOMMENT FOR TRIDIAGONAL LHS
            } else if (i == j + 1 || i == j - 1) {
                // Adjacent diagonals
                P[i * n + j] = alpha;

            // UNCOMMENT FOR PENTADIAGONAL LHS
            } else if (i == j + 2 || i == j - 2) {
                // Adjacent super-diagonals
                P[i * n + j] = beta;
            } else {
                P[i * n + j] = 0;
            }
        }
    }

    P[0 * n + 1] = gamma01;
    P[0 * n + 2] = gamma02;

    P[(n - 1) * n + (n - 3)] = gamma02;
    P[(n - 1) * n + (n - 2)] = gamma01;

    return P;
}



double* dQ(int n, double h) {
    double a1 = 120.0 / 97.0;

    double a00 = 177.0 / 16.0;
    double a01 =  - 507.0 / 8.0;
    double a02 = 783.0 / 8.0;
    double a03 =  - 201.0 / 4.0;
    double a04 = 81.0 / 16.0;
    double a05 =  - 3.0 / 8.0;

    // Create an nxn matrix with all elements initialized to zero
    double* Q = new double[n * n]();

    // Set the diagonal values of the matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                // Main diagonal
                Q[i * n + j] = -2 * (a1);

            // UNCOMMENT FOR TRIDIAGONAL RHS
            } else if (i == j - 1) {
                // Adjacent diagonals
                Q[i * n + j] = a1 / 1.0;
            } else if (i == j + 1) {
                // Adjacent diagonals
                Q[i * n + j] = -a1 / 1.0;

            // UNCOMMENT FOR PENTADIAGONAL RHS
            // } else if (i == j - 2) {
            //     // Super diagonals on
            //     Q[i * n + j] = a2 / 4.0;
            // } else if (i == j + 2) {
            //     // Super diagonals on 
            //     Q[i * n + j] = -a2 / 4.0;

            // UNCOMMENT FOR SEPTADIAGONAL RHS
            // } else if (i == j - 3) {
            //     // Super +1 diagonals on 
            //     Q[i * n + j] = a3;
            // } else if (i == j + 3) {
            //     // Super +1 diagonals on 
            //     Q[i * n + j] = -a3;
            } else {
                Q[i * n + j] = 0.0;
            }
        }
    }

    Q[0 * n + 0] = a00;
    Q[0 * n + 1] = a01;
    Q[0 * n + 2] = a02;
    Q[0 * n + 3] = a03;
    Q[0 * n + 4] = a04;
    Q[0 * n + 5] = a05;

    Q[(n - 1) * n + (n - 6)] = -a05;
    Q[(n - 1) * n + (n - 5)] = -a04;
    Q[(n - 1) * n + (n - 4)] = -a03;
    Q[(n - 1) * n + (n - 3)] = -a02;
    Q[(n - 1) * n + (n - 2)] = -a01;
    Q[(n - 1) * n + (n - 1)] = -a00;



    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            Q[i * n + j] *= 1 / (h * h);
        }
    }
    return Q;
}
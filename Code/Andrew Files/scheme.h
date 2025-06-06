#include <cmath>
#include<iostream>

using namespace std;

double* dP(int n) {
    double alpha = 1.0 / 3.0;

    double gamma01 = 5.0;
    double gamma10 = 1.0 / 10.0;
    double gamma12 = 1.0;




    // Interior | O(h^4) | LHS
    // double alpha = 0.250000000000;

    // Interior | O(h^6) | LHS
    // double alpha = 0.333333333333;


    // MHat | O(h^4) | LHS
    /* Row 1 */
    // double beta01 = -3.384615384615;
    // double gamma02 = -1.307692307692;


    // MHat | O(h^6) | LHS
    // /* Row 1 */
    // double beta01 = 8.000000000000;
    // double gamma02 = 6.000000000000;


    // MBar | O(h^4) | LHS
    // /* Row 1 */
    // double beta01 = 3.000000000000;

    // /* Row 2 */
    // double alpha10 = 0.250000000000;
    // double alpha12 = 0.250000000000;


    // MBar | O(h^6) | LHS
    // /* Row 1 */
    // double beta01 = 5.000000000000;

    // /* Row 2 */
    // double alpha10 = 0.181818181818;
    // double alpha12 = 0.181818181818;


    // MAcute | O(h^4) | LHS
    // /* Row 1 */
    // double beta01 = 3.000000000000;

    // /* Row 2 */
    // double alpha10 = 0.250000000000;
    // double gamma12 = 0.250000000000;


    // MAcute | O(h^6) | LHS
    // /* Row 1 */
    // double beta01 = 5.000000000000;

    // /* Row 2 */
    // double alpha10 = 0.125000000000;
    // double gamma12 = 0.750000000000;


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
            // } else if (i == j + 2 || i == j - 2) {
            //     // Adjacent super-diagonals
            //     P[i * n + j] = beta;
            } else {
                P[i * n + j] = 0;
            }
        }
    }

    // Set MHat LHS Boundary
    /* Row 1 */
    P[0 * n + 1] = gamma01;

    P[1 * n + 0] = gamma10;
    P[1 * n + 2] = gamma12;

    /* Row k */
    P[(n - 2) * n + (n - 3)] = gamma12;
    P[(n - 2) * n + (n - 1)] = gamma10;

    P[(n - 1) * n + (n - 2)] = gamma01;


    // Set MBar LHS Boundary
    // /* Row 1 */
    // P[0 * n + 1] = beta01;

    // /* Row 2 */
    // P[1 * n + 0] = alpha10;
    // P[1 * n + 2] = alpha12;

    // /* Row k-1 */
    // P[(n - 2) * n + (n - 3)] = alpha12;
    // P[(n - 2) * n + (n - 1)] = alpha10;

    // /* Row k */
    // P[(n - 1) * n + (n - 2)] = beta01;


    // Set MAcute LHS Boundary
    // /* Row 1 */
    // P[0 * n + 1] = beta01;

    // /* Row 2 */
    // P[1 * n + 0] = alpha10;
    // P[1 * n + 2] = gamma12;

    // /* Row k-1 */
    // P[(n - 2) * n + (n - 3)] = gamma12;
    // P[(n - 2) * n + (n - 1)] = alpha10;

    // /* Row k */
    // P[(n - 1) * n + (n - 2)] = beta01;



    return P;
}



double* dQ(int n, double h) {
    double a1 = 14.0 / 9.0;
    double a2 = 1.0 / 9.0;

    double a00 =  - 197.0 / 60.0;
    double a01 =  - 5.0 / 12.0;
    double a02 = 5.0;
    double a03 =  - 5.0 / 3.0;
    double a04 = 5.0 / 12.0;
    double a05 =  - 1.0 / 20.0;
    double a10 =  - 227.0 / 600.0;
    double a11 =  - 13.0 / 12.0;
    double a12 = 7.0 / 6.0;
    double a13 = 1.0 / 3.0;
    double a14 =  - 1.0 / 24.0;
    double a15 = 1.0 / 300.0;


    // Interior | O(h^4) | RHS
    // double a1 = 1.500000000000;

    // Interior | O(h^6) | RHS
    // double a1 = 1.555555555555;
    // double a2 = 0.111111111111;
    /* REF: Jonathan Tyler pg 32 */
    // double a1 = 0.777777777777; // 14/18
    // double a2 = 0.027777777777; // 1/36


    // MHat | O(h^4) | RHS
    /* Row 1 */
    // double a00 = 0.000000000000;
    // double a01 = 3.692307692307;
    // double a02 = -3.692307692307;


    // MHat | O(h^6) | RHS
    // /* Row 1 */
    // double a00 = -3.583333333333;
    // double a01 = -6.666666666666;
    // double a02 = 9.000000000000;
    // double a03 = 1.333333333333;
    // double a04 = -0.083333333333;


    // MBar | O(h^4) | RHS
    // /* Row 1 */
    // double a00 = -2.833333333333;
    // double a01 = 1.500000000000;
    // double a02 = 1.500000000000;
    // double a03 = -0.166666666666;

    // /* Row 2 */
    // double a10 = -0.750000000000;
    // double a11 = 0.000000000000;
    // double a12 = 0.750000000000;
    // double a13 = 0.000000000000;


    // MBar | O(h^6) | RHS
    // /* Row 1 */
    // double a00 = -3.283333333333;
    // double a01 = -0.416666666666;
    // double a02 = 5.000000000000;
    // double a03 = -1.666666666666;
    // double a04 = 0.416666666666;
    // double a05 = -0.050000000000;

    // /* Row 2 */
    // double a10 = -0.606060606060;
    // double a11 = -0.265151515151;
    // double a12 = 1.030303030303;
    // double a13 = -0.212121212121;
    // double a14 = 0.060606060606;
    // double a15 = -0.007575757575;


    // MAcute | O(h^4) | RHS
    // /* Row 1 */
    // double a00 = -2.833333333333;
    // double a01 = 1.500000000000;
    // double a02 = 1.500000000000;
    // double a03 = -0.166666666666;

    // /* Row 2 */
    // double a10 = -0.750000000000;
    // double a11 = 0.000000000000;
    // double a12 = 0.750000000000;


    // MAcute | O(h^6) | RHS
    // /* Row 1 */
    // double a00 = -3.283333333333;
    // double a01 = -0.416666666666;
    // double a02 = 5.000000000000;
    // double a03 = -1.666666666666;
    // double a04 = 0.416666666666;
    // double a05 = -0.050000000000;

    // /* Row 2 */
    // double a10 = -0.447916666666;
    // double a11 = -0.833333333333;
    // double a12 = 1.125000000000;
    // double a13 = 0.166666666666;
    // double a14 = -0.010416666666;


    // Create an nxn matrix with all elements initialized to zero
    double* Q = new double[n * n]();

    // Set the diagonal values of the matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                // Main diagonal
                Q[i * n + j] = 0.0;

            // UNCOMMENT FOR TRIDIAGONAL RHS
            } else if (i == j - 1) {
                // Adjacent diagonals
                Q[i * n + j] = a1;
            } else if (i == j + 1) {
                // Adjacent diagonals
                Q[i * n + j] = -a1;

            // UNCOMMENT FOR PENTADIAGONAL RHS
            } else if (i == j - 2) {
                // Super diagonals on
                Q[i * n + j] = a2;
            } else if (i == j + 2) {
                // Super diagonals on 
                Q[i * n + j] = -a2;

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

    // Set MHat RHS Boundary
    // /* Row 1 */
    // O(h^4)
    Q[0 * n + 0] = a00;
    Q[0 * n + 1] = a01;
    Q[0 * n + 2] = a02;
    Q[0 * n + 3] = a03;
    Q[0 * n + 4] = a04;
    Q[0 * n + 5] = a05;

    Q[1 * n + 0] = a10;
    Q[1 * n + 1] = a11;
    Q[1 * n + 2] = a12;
    Q[1 * n + 3] = a13;
    Q[1 * n + 4] = a14;
    Q[1 * n + 5] = a15;
    // // O(h^6)
    // Q[0 * n + 3] = a03;
    // Q[0 * n + 4] = a04;

    // /* Row k */
    // // O(h^6)
    // Q[(n - 1) * n + (n - 5)] = -a04;
    // Q[(n - 1) * n + (n - 4)] = -a03;
    // O(h^4)

    Q[(n - 2) * n + (n - 6)] = -a15;
    Q[(n - 2) * n + (n - 5)] = -a14;
    Q[(n - 2) * n + (n - 4)] = -a13;
    Q[(n - 2) * n + (n - 3)] = -a12;
    Q[(n - 2) * n + (n - 2)] = -a11;
    Q[(n - 2) * n + (n - 1)] = -a10;

    Q[(n - 1) * n + (n - 6)] = -a05;
    Q[(n - 1) * n + (n - 5)] = -a04;
    Q[(n - 1) * n + (n - 4)] = -a03;
    Q[(n - 1) * n + (n - 3)] = -a02;
    Q[(n - 1) * n + (n - 2)] = -a01;
    Q[(n - 1) * n + (n - 1)] = -a00;


    // Set MBar RHS Boundary
    // /* Row 1 */
    // // O(h^4)
    // Q[0 * n + 0] = a00;
    // Q[0 * n + 1] = a01;
    // Q[0 * n + 2] = a02;
    // Q[0 * n + 3] = a03;
    // // O(h^6)
    // Q[0 * n + 4] = a04;
    // Q[0 * n + 5] = a05;

    /* Row 2 */
    // // O(h^4)
    // Q[1 * n + 0] = a10;
    // Q[1 * n + 1] = a11;
    // Q[1 * n + 2] = a12;
    // Q[1 * n + 3] = a13;
    // // O(h^6)
    // Q[1 * n + 4] = a14;
    // Q[1 * n + 5] = a15;

    /* Row k-1 */
    // // O(h^6)
    // Q[(n - 1) * n + (n - 6)] = -a15;
    // Q[(n - 1) * n + (n - 5)] = -a14;
    // // O(h^4)
    // Q[(n - 1) * n + (n - 4)] = -a13;
    // Q[(n - 1) * n + (n - 3)] = -a12;
    // Q[(n - 1) * n + (n - 2)] = -a11;
    // Q[(n - 1) * n + (n - 1)] = -a10;

    /* Row k */
    // // O(h^6)
    // Q[(n - 2) * n + (n - 6)] = -a05;
    // Q[(n - 2) * n + (n - 5)] = -a04;
    // // O(h^4)
    // Q[(n - 2) * n + (n - 4)] = -a03;
    // Q[(n - 2) * n + (n - 3)] = -a02;
    // Q[(n - 2) * n + (n - 2)] = -a01;
    // Q[(n - 2) * n + (n - 1)] = -a00;


    // Set MAcute RHS Boundary
    /* Row 1 */
    // // O(h^4)
    // Q[0 * n + 0] = a00;
    // Q[0 * n + 1] = a01;
    // Q[0 * n + 2] = a02;
    // Q[0 * n + 3] = a03;
    // // O(h^6)
    // Q[0 * n + 4] = a04;
    // Q[0 * n + 5] = a05;

    /* Row 2 */
    // // O(h^4)
    // Q[1 * n + 0] = a10;
    // Q[1 * n + 1] = a11;
    // Q[1 * n + 2] = a12;
    // // O(h^6)
    // Q[1 * n + 3] = a13;
    // Q[1 * n + 4] = a14;

    /* Row k-1 */
    // // O(h^6)
    // Q[(n - 2) * n + (n - 5)] = -a14;
    // Q[(n - 2) * n + (n - 4)] = -a13;
    // // O(h^4)
    // Q[(n - 2) * n + (n - 3)] = -a12;
    // Q[(n - 2) * n + (n - 2)] = -a11;
    // Q[(n - 2) * n + (n - 1)] = -a10;

    /* Row k */
    // O(h^6)
    // Q[(n - 1) * n + (n - 6)] = -a05;
    // Q[(n - 1) * n + (n - 5)] = -a04;
    // // O(h^4)
    // Q[(n - 1) * n + (n - 4)] = -a03;
    // Q[(n - 1) * n + (n - 3)] = -a02;
    // Q[(n - 1) * n + (n - 2)] = -a01;
    // Q[(n - 1) * n + (n - 1)] = -a00;



    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            Q[i * n + j] *= 1/(2*h);
        }
    }
    return Q;
}
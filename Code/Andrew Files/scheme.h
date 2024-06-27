#include <cmath>
#include<iostream>

using namespace std;

double* dP(int n) {
    //defining the constants
    // double g10 = 0.11737546726594537;
    // double g20 = -0.067477420334188354;
    // double g01 = 9.279310823736082;
    // double g21 = -0.1945509344676567;
    // double g02 = 9.8711877434133051;
    // double g12 = 0.92895849448052303;
    // double g13 = -0.067839996199150834;
    // double g23 = 1.279565347145571;
    // double g24 = 0.20842348769505742;

    // Pentadiagonal on LHS - from Kim-parallel
    // double alpha = 0.5862704032801503;
    // double beta = 0.09549533555017055;

    // Tridiagonal Interior on LHS - from Me
    double alpha = 0.250;

    // MHat | O(h^4) | LHS
    // double beta01 = 4.000;
    // double gamma02 = 1.000;

    // MBar | O(h^4) | LHS
    double beta01 = 3.000;

    double alpha10 = 0.250;
    double alpha12 = 0.250;

    // MAcute | O(h^4) | LHS
    // double beta01 = 3.000;

    // double alpha10 = 0.250;
    // double gamma12 = 0.250;

    // Create an nxn matrix with all elements initialized to zero
    double* P = new double[n * n]();

    // Set the diagonal values of the matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                // Main diagonal
                P[i * n + j] = 1;
            } else if (i == j + 1 || i == j - 1) {
                // Adjacent diagonals
                P[i * n + j] = alpha;
            // } else if (i == j + 2 || i == j - 2) {
            //     // Adjacent super-diagonals
            //     P[i * n + j] = beta;
            } else {
                P[i * n + j] = 0;
            }
        }
    }

    // Boundary Coefficients - from Kim
    // P[0 * n + 1] = g01;
    // P[0 * n + 2] = g02;

    // P[1 * n + 0] = g10;
    // P[1 * n + 2] = g12;
    // P[1 * n + 3] = g13;

    // P[2 * n + 0] = g20;
    // P[2 * n + 1] = g21;
    // P[2 * n + 3] = g23;
    // P[2 * n + 4] = g24;

    // P[(n - 3) * n + (n - 5)] = g24;
    // P[(n - 3) * n + (n - 4)] = g23;
    // P[(n - 3) * n + (n - 2)] = g21;
    // P[(n - 3) * n + (n - 1)] = g20;

    // P[(n - 2) * n + (n - 4)] = g13;
    // P[(n - 2) * n + (n - 3)] = g12;
    // P[(n - 2) * n + (n - 1)] = g10;

    // P[(n - 1) * n + (n - 3)] = g02;
    // P[(n - 1) * n + (n - 2)] = g01;

    // Set MHat LHS Boundary
    // P[0 * n + 1] = beta01;
    // P[0 * n + 2] = gamma02;

    // P[(n - 1) * n + (n - 3)] = gamma02;
    // P[(n - 1) * n + (n - 2)] = beta01;

    // Set MBar LHS Boundary
    P[0 * n + 1] = beta01;

    P[1 * n + 0] = alpha10;
    P[1 * n + 2] = alpha12;

    P[(n - 2) * n + (n - 3)] = alpha12;
    P[(n - 2) * n + (n - 1)] = alpha10;

    P[(n - 1) * n + (n - 2)] = beta01;

    // Set MAcute LHS Boundary
    // P[0 * n + 1] = beta01;

    // P[1 * n + 0] = alpha10;
    // P[1 * n + 2] = gamma12;

    // P[(n - 2) * n + (n - 3)] = gamma12;
    // P[(n - 2) * n + (n - 1)] = alpha10;

    // P[(n - 1) * n + (n - 2)] = beta01;



    return P;
}

double* dQ(int n, double h) {
    //defining some important variables 
    // double b10 = -0.4197688256685424;
    // double b20 = 0.20875393530974462;

    // double b01 = -9.9196421679170452;
    // double b21 = -0.36722447739446801;

    // double b02 = 10.088151775649886;
    // double b12 = 1.1593253854830003;

    // double b03 = 4.1769460418803268;
    // double b13 = 0.31685797023808876;
    // double b23 = 0.98917602108458036;

    // double b04 = -0.82222305192207212;
    // double b14 = -0.096453054902842381;
    // double b24 = 0.63518969715000262;

    // double b05 = 0.14757709267988142;
    // double b15 = 0.015579947274307879;
    // double b25 = 0.0042145635666246068;

    // double b06 = -0.014332365879513103;
    // double b16 = -0.0014553614585464077;
    // double b26 = 0.0010111910030585999;

    // Septadiagonal on RHS - from Kim-parallel
    // double a1 = 0.6431406736919156;
    // double a2 = 0.2586011023495066;
    // double a3 = 0.007140953479797375;

    // Tridiagonal Interior on RHS - from Me
    double a = 1.500;

    // MHat | O(h^4) | RHS
    // double a00 = -3.000;
    // double a01 = 0.000;
    // double a02 = 3.000;

    // MBar | O(h^4) | RHS
    double a00 = -2.833333333333333333;
    double a01 = 1.500;
    double a02 = 1.500;
    double a03 = -0.166666666666666666;

    double a10 = -0.750;
    double a11 = 0.000;
    double a12 = 0.750;
    double a13 = 0.000;

    // MAcute | O(h^4) | RHS
    // double a00 = -2.833333333333333333;
    // double a01 = 1.500;
    // double a02 = 1.500;
    // double a03 = -0.166666666666666666;

    // double a10 = -0.750;
    // double a11 = 0.000;
    // double a12 = 0.750;

    // double b00 = -(b01 + b02 + b03 + b04 + b05 + b06);
    // double b11 = -(b10 + b12 + b13 + b14 + b15 + b16);
    // double b22 = -(b20 + b21 + b23 + b24 + b25 + b26);
        double* Q = new double[n * n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                // Main diagonal
                Q[i * n + j] = 0.0;
            } else if (i == j - 1) {
                // Adjacent diagonals 
                // Q[i * n + j] = a1;
                Q[i * n + j] = a;
            } else if (i == j + 1) {
                // Adjacent diagonals 
                // Q[i * n + j] = -a1;
                Q[i * n + j] = -a;
            // } else if (i == j - 2) {
            //     // Super diagonals 
            //     Q[i * n + j] = a2;
            // } else if (i == j + 2) {
            //     // Super diagonals on 
            //     Q[i * n + j] = -a2;
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

    // Boundary Coefficients - from Kim
    // Q[0 * n + 0] = b00;
    // Q[0 * n + 1] = b01;
    // Q[0 * n + 2] = b02;
    // Q[0 * n + 3] = b03;
    // Q[0 * n + 4] = b04;
    // Q[0 * n + 5] = b05;
    // Q[0 * n + 6] = b06;

    // Q[1 * n + 0] = b10;
    // Q[1 * n + 1] = b11;
    // Q[1 * n + 2] = b12;
    // Q[1 * n + 3] = b13;
    // Q[1 * n + 4] = b14;
    // Q[1 * n + 5] = b15;
    // Q[1 * n + 6] = b16;

    // Q[2 * n + 0] = b20;
    // Q[2 * n + 1] = b21;
    // Q[2 * n + 2] = b22;
    // Q[2 * n + 3] = b23;
    // Q[2 * n + 4] = b24;
    // Q[2 * n + 5] = b25;
    // Q[2 * n + 6] = b26;

    // Q[(n - 3) * n + (n - 7)] = -b26;
    // Q[(n - 3) * n + (n - 6)] = -b25;
    // Q[(n - 3) * n + (n - 5)] = -b24;
    // Q[(n - 3) * n + (n - 4)] = -b23;
    // Q[(n - 3) * n + (n - 3)] = -b22;
    // Q[(n - 3) * n + (n - 2)] = -b21;
    // Q[(n - 3) * n + (n - 1)] = -b20;

    // Q[(n - 2) * n + (n - 7)] = -b16;
    // Q[(n - 2) * n + (n - 6)] = -b15;
    // Q[(n - 2) * n + (n - 5)] = -b14;
    // Q[(n - 2) * n + (n - 4)] = -b13;
    // Q[(n - 2) * n + (n - 3)] = -b12;
    // Q[(n - 2) * n + (n - 2)] = -b11;
    // Q[(n - 2) * n + (n - 1)] = -b10;

    // Q[(n - 1) * n + (n - 7)] = -b06;
    // Q[(n - 1) * n + (n - 6)] = -b05;
    // Q[(n - 1) * n + (n - 5)] = -b04;
    // Q[(n - 1) * n + (n - 4)] = -b03;
    // Q[(n - 1) * n + (n - 3)] = -b02;
    // Q[(n - 1) * n + (n - 2)] = -b01;
    // Q[(n - 1) * n + (n - 1)] = -b00;

    // Set MHat RHS Boundary
    // Q[0 * n + 0] = a00;
    // Q[0 * n + 1] = a01;
    // Q[0 * n + 2] = a02;

    // Q[(n - 1) * n + (n - 3)] = a02;
    // Q[(n - 1) * n + (n - 2)] = a01;
    // Q[(n - 1) * n + (n - 1)] = a00;

    // Set MBar RHS Boundary
    Q[0 * n + 0] = a00;
    Q[0 * n + 1] = a01;
    Q[0 * n + 2] = a02;
    Q[0 * n + 3] = a03;

    Q[1 * n + 0] = a10;
    Q[1 * n + 1] = a11;
    Q[1 * n + 2] = a12;
    Q[1 * n + 3] = a13;

    Q[(n - 2) * n + (n - 4)] = -a03;
    Q[(n - 2) * n + (n - 3)] = -a02;
    Q[(n - 2) * n + (n - 2)] = -a01;
    Q[(n - 2) * n + (n - 1)] = -a00;

    Q[(n - 1) * n + (n - 4)] = -a13;
    Q[(n - 1) * n + (n - 3)] = -a12;
    Q[(n - 1) * n + (n - 2)] = -a11;
    Q[(n - 1) * n + (n - 1)] = -a10;

    // Set MAcute RHS Boundary
    // Q[0 * n + 0] = a00;
    // Q[0 * n + 1] = a01;
    // Q[0 * n + 2] = a02;
    // Q[0 * n + 3] = a03;

    // Q[1 * n + 0] = a10;
    // Q[1 * n + 1] = a11;
    // Q[1 * n + 2] = a12;

    // Q[(n - 2) * n + (n - 3)] = a12;
    // Q[(n - 2) * n + (n - 2)] = a11;
    // Q[(n - 2) * n + (n - 1)] = a10;

    // Q[(n - 1) * n + (n - 4)] = a03;
    // Q[(n - 1) * n + (n - 3)] = a02;
    // Q[(n - 1) * n + (n - 2)] = a01;
    // Q[(n - 1) * n + (n - 1)] = a00;



    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            Q[i * n + j] *= 1/(2*h);
        }
    }
    return Q;
}
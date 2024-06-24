#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <lapacke.h>
#include <cblas.h>
#include <chrono>
#include "kim.h"  // Ensure this header defines the functions dP(n) and dQ(n, h)

int main() {
    // Sizes for the matrices
    int sizes[] = {20, 40, 80, 160};
    std::ofstream timingFile("timing.dat");

    // Iterate over the different sizes
    for (int s = 0; s < 4; ++s) {
        int n = sizes[s];
        const double x_min = 0.0;
        const double x_max = 1.0;
        const double h = (x_max - x_min) / (n - 1);

        // Measure the execution time
        auto start = std::chrono::high_resolution_clock::now();

        double *P = dP(n); // Define the matrix P using the function provided in kim.h
        double *Q = dQ(n, h); // Define the matrix Q

        // Compute the LU decomposition of the matrix P
        int *ipiv = new int[n];
        int info = LAPACKE_dgetrf(LAPACK_ROW_MAJOR, n, n, P, n, ipiv);

        if (info != 0) {
            std::cerr << "LU factorization failed for size " << n << ": " << info << std::endl;
            delete[] P;
            delete[] Q;
            delete[] ipiv;
            continue;  // Skip this size and proceed to the next one
        }

        // Compute the inverse of the matrix P
        double *Pinv = new double[n * n];
        std::memcpy(Pinv, P, n * n * sizeof(double));
        info = LAPACKE_dgetri(LAPACK_ROW_MAJOR, n, Pinv, n, ipiv);

        if (info != 0) {
            std::cerr << "Matrix inversion failed for size " << n << ": " << info << std::endl;
            delete[] P;
            delete[] Q;
            delete[] ipiv;
            delete[] Pinv;
            continue;  // Skip this size and proceed to the next one
        }

        // Compute the product of the inverted matrix Pinv and matrix Q
        double *R = new double[n * n];
        double alpha = 1.0;
        double beta = 0.0;
        cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, n, n, n, alpha, Pinv, n, Q, n, beta, R, n);

        // Define the input array x and encode sin(2*pi*x)
        double *x = new double[n];
        double w = 2.0 * M_PI;
        for (int i = 0; i < n; i++) {
            x[i] = i * h; // x ranges from 0 to 1
        }
        double *f = new double[n];
        for (int i = 0; i < n; i++) {
            f[i] = sin(w * x[i]);
        }

        // Compute the product of matrix R and f
        double *result = new double[n];
        cblas_dgemv(CblasRowMajor, CblasNoTrans, n, n, alpha, R, n, f, 1, beta, result, 1);

        // Calculate the analytical solution and error
        double *analytical = new double[n];
        double *error = new double[n];
        for (int i = 0; i < n; i++) {
            analytical[i] = 2 * M_PI * cos(w * x[i]);
            error[i] = result[i] - analytical[i];
        }

        // Save the results and errors to data files
        std::ofstream resultFile("result_" + std::to_string(n) + ".dat");
        std::ofstream errorFile("error_" + std::to_string(n) + ".dat");
        for (int i = 0; i < n; i++) {
            resultFile << x[i] << " " << result[i] << std::endl;
            errorFile << x[i] << " " << error[i] << std::endl;
        }
        resultFile.close();
        errorFile.close();

        // Free memory
        delete[] P;
        delete[] Q;
        delete[] ipiv;
        delete[] Pinv;
        delete[] R;
        delete[] x;
        delete[] f;
        delete[] result;
        delete[] analytical;
        delete[] error;

        // Measure the end time
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        // Print and save the timing information
        std::cout << "Size " << n << " took " << elapsed.count() << " seconds.\n";
        timingFile << "Size " << n << " took " << elapsed.count() << " seconds." << std::endl;
    }

    timingFile.close();
    return 0;
}

#include <cmath>
#include<iostream>

using namespace std;

double* inverseMbar(int n, double h) {
    
    double* Mbar = new double[n * n]();

    for (int i = 0; i < ceiling(n/2); i++) {
        for (int j = 0; j < n; j++) {
            if() /*eta^2 < 0*/ {
               if (i==1 && j == 1) {
                    
                    Mbar[i * n + j] = b*(2*b*cos(l)*sin((n-5)*l)+(a*b-8*cos(l)^2)*sin((n-4)*l)+2*cos(l)*(4*cos(l)^2-a*b)*sin((n-3)l));
                } else if (i == 1 && j ==2 ) {
                    Mbar[i * n + j] = a*((a*b-2*cos(2*l)-2)*sin((j-n+1)l)-2*b*cos(l)sin((n-j-2)l));
                } else if (i == 1 && (j >= 3 && j <= n-1)) {
                    Mbar[i * n + j] = a*b*((a*b-2*cos(2*l)-2)*sin((j-n+1)l)-2*b*cos(l)sin((n-j-2)l));
                } else if (i == 1 && j == n) {
                    Mbar[i * n + j] = a*b^2*sin(l);
                } else if (i == 2 && (j >= 3 && j <= n-1)) {
                    Mbar[i * n + j] = 2*b*cos(l)*((a*b-2*cos(2*l)-2)*sin((j-n+1)l)-2*b*cos(l)sin((n-j-2)l));
                } else if (i == 2 && j == n) {
                    Mbar[i * n + j] = b^2*cos(2*l);
                } else if (i >= 2 && j == 1) {
                    Mbar[i * n + j] = b*(a*b-2*cos(2*l)-2)*sin((j-n+1)l)-2*b*cos(l)sin((n-j-2)l);
                } else if (i >== 3 && j == n) {
                    Mbar[i * n + j] = ;
                } else {
                    Mbar[i * n + j] = ;
                }

            } else /*eta^2 >= 0*/ {
                if (i==1 && j == 2) {
                    Mbar[i * n + j] = ;
                } else if (i == 1 && j >= 3) {
                    Mbar[i * n + j] = ;
                } else if (i == 2 && j >= 3) {
                    Mbar[i * n + j] = ;
                } else {
                    Mbar[i * n + j] = ;
               }
            }

            Mbar[i * n + j] * = (-1)^(i+j)
        }
    }

}
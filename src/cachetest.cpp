#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <string>
using namespace std;

void clasica(double* A, double* B, double* C, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            double s = 0;
            for (int k = 0; k < N; k++) {
                s += A[i*N + k] * B[k*N + j];
            }
            C[i*N + j] = s;
        }
    }
}

void bloques(double* A, double* B, double* C, int N, int bs) {
    for (int i = 0; i < N*N; i++) C[i] = 0;

    for (int ii = 0; ii < N; ii += bs) {
        for (int kk = 0; kk < N; kk += bs) {
            for (int jj = 0; jj < N; jj += bs) {
                for (int i = ii; i < min(ii + bs, N); i++) {
                    for (int k = kk; k < min(kk + bs, N); k++) {
                        double a = A[i*N + k];
                        for (int j = jj; j < min(jj + bs, N); j++) {
                            C[i*N + j] += a * B[k*N + j];
                        }
                    }
                }
            }
        }
    }
}

int main(int argc, char** argv) {
    string modo = "clasica";
    int N = 256;
    int bs = 64;

    if (argc > 1) modo = argv[1];
    if (argc > 2) N = atoi(argv[2]);
    if (argc > 3) bs = atoi(argv[3]);

    double* A = new double[N*N];
    double* B = new double[N*N];
    double* C = new double[N*N];

    for (int i = 0; i < N*N; i++) {
        A[i] = 1.0;
        B[i] = 1.0;
        C[i] = 0.0;
    }

    if (modo == "clasica") {
        clasica(A, B, C, N);
        cout << "modo=" << modo << " N=" << N << endl;
    } else {
        bloques(A, B, C, N, bs);
        cout << "modo=" << modo << " N=" << N
             << " bs=" << bs << endl;
    }

    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
}
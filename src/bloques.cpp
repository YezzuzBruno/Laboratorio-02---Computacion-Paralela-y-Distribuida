#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <algorithm>
using namespace std;
using namespace chrono;

void clasica(const vector<double>& A,
             const vector<double>& B,
             vector<double>& C,
             int N) {
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

void bloques(const vector<double>& A,
             const vector<double>& B,
             vector<double>& C,
             int N, int bs) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            C[i*N + j] = 0;

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

int main() {
    vector<int> tamanos = {200, 400, 600, 800, 1000};
    vector<int> bloques_tam = {16, 32, 64, 128};

    cout << fixed << setprecision(6);
    cout << "N\tbs\tclasica\tbloques\n";
    cout << "------------------------------------\n";

    for (int N : tamanos) {
        vector<double> A(N*N, 1.0);
        vector<double> B(N*N, 1.0);
        vector<double> C(N*N, 0.0);

        // clasica
        auto t0 = high_resolution_clock::now();
        clasica(A, B, C, N);
        auto t1 = high_resolution_clock::now();
        double t_clasica = duration<double>(t1 - t0).count();

        cout << N << "\t-\t" << t_clasica << "\t-\n";

        // bloques con distintos bs
        for (int bs : bloques_tam) {
            auto t2 = high_resolution_clock::now();
            bloques(A, B, C, N, bs);
            auto t3 = high_resolution_clock::now();
            double t_bloques = duration<double>(t3 - t2).count();

            cout << N << "\t" << bs << "\t-\t" << t_bloques << "\n";
        }
    }

    return 0;
}
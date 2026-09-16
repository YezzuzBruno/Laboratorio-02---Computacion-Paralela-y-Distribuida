#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
using namespace std;
using reloj = chrono::high_resolution_clock;

void primero(vector<double>& A, vector<double>& x, vector<double>& y, int n) {
    for (int i = 0; i < n; i++) {
        y[i] = 0;
        for (int j = 0; j < n; j++) {
            y[i] += A[i*n + j] * x[j];
        }
    }
}

void segundo(vector<double>& A, vector<double>& x, vector<double>& y, int n) {
    for (int i = 0; i < n; i++) y[i] = 0;
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            y[i] += A[i*n + j] * x[j];
        }
    }
}

int main(int argc, char** argv) {
    int n = 1000;
    int rep = 3;
    if (argc > 1) n = atoi(argv[1]);
    if (argc > 2) rep = atoi(argv[2]);

    vector<double> A(n*n), x(n), y(n);
    for (int i = 0; i < n*n; i++) A[i] = (i % 100) * 0.01;
    for (int i = 0; i < n; i++) x[i] = (i % 100) * 0.01;

    double t_prim = 0, t_seg = 0;

    for (int r = 0; r < rep; r++) {
        auto t0 = reloj::now();
        primero(A, x, y, n);
        auto t1 = reloj::now();
        t_prim += chrono::duration<double>(t1 - t0).count();
    }

    for (int r = 0; r < rep; r++) {
        auto t0 = reloj::now();
        segundo(A, x, y, n);
        auto t1 = reloj::now();
        t_seg += chrono::duration<double>(t1 - t0).count();
    }

    t_prim /= rep;
    t_seg /= rep;

    cout << "n=" << n
         << " primero=" << t_prim
         << " segundo=" << t_seg
         << " razon=" << t_seg / t_prim << endl;
}
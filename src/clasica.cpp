#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
using namespace std;
using namespace chrono;

void multiplicarMatrices(const vector<double>& A,
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

int main() {
    vector<int> tamanos = {100, 200, 300, 400, 500, 600, 800, 1000};

    cout << fixed << setprecision(6);
    cout << "Multiplicacion clasica de matrices\n\n";
    cout << "N\tTiempo (segundos)\n";
    cout << "--------------------------------\n";

    for (int N : tamanos) {
        vector<double> A(N*N, 1.0);
        vector<double> B(N*N, 1.0);
        vector<double> C(N*N, 0.0);

        auto inicio = high_resolution_clock::now();
        multiplicarMatrices(A, B, C, N);
        auto fin = high_resolution_clock::now();

        double seg = duration<double>(fin - inicio).count();
        
        cout << N << "\t" << seg << "\n";

    }

    return 0;
}
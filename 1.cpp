#include <iostream>
#include <vector>
#include <chrono> // Para medir tiempo

#define MAX 1000

// Función para inicializar A, x y y
void initialize(std::vector<std::vector<double>>& A, std::vector<double>& x, std::vector<double>& y) {
    for (int i = 0; i < MAX; ++i) {
        for (int j = 0; j < MAX; ++j) {
            A[i][j] = static_cast<double>(i + j);
        }
        x[i] = static_cast<double>(i);
        y[i] = 0.0;
    }
}

// Primer par de bucles
void first_loop(const std::vector<std::vector<double>>& A, const std::vector<double>& x, std::vector<double>& y) {
    for (int i = 0; i < MAX; ++i) {
        for (int j = 0; j < MAX; ++j) {
            y[i] += A[i][j] * x[j];
        }
    }
}

// Segundo par de bucles
void second_loop(const std::vector<std::vector<double>>& A, const std::vector<double>& x, std::vector<double>& y) {
    for (int j = 0; j < MAX; ++j) {
        for (int i = 0; i < MAX; ++i) {
            y[i] += A[i][j] * x[j];
        }
    }
}

int main() {
    // Inicializar matrices y vectores
    std::vector<std::vector<double>> A(MAX, std::vector<double>(MAX));
    std::vector<double> x(MAX), y(MAX);

    // Inicialización
    initialize(A, x, y);

    // Medir tiempo del primer par de bucles
    auto start = std::chrono::high_resolution_clock::now();
    first_loop(A, x, y);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Tiempo para el primer par de bucles: " << elapsed.count() << " segundos\n";

    // Reiniciar y = 0
    std::fill(y.begin(), y.end(), 0.0);

    // Medir tiempo del segundo par de bucles
    start = std::chrono::high_resolution_clock::now();
    second_loop(A, x, y);
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Tiempo para el segundo par de bucles: " << elapsed.count() << " segundos\n";

    return 0;
}

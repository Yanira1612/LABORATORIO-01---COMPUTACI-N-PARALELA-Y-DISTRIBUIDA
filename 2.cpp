#include <iostream>
#include <vector>
#include <chrono> // Para medir el tiempo de ejecución

// Función para inicializar las matrices con valores aleatorios
void initialize_matrix(std::vector<std::vector<double>>& matrix, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = static_cast<double>(rand() % 100); // valores aleatorios entre 0 y 99
        }
    }
}

// Función para multiplicar matrices utilizando tres bucles anidados
void multiply_matrices(const std::vector<std::vector<double>>& A, const std::vector<std::vector<double>>& B, std::vector<std::vector<double>>& C, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            C[i][j] = 0; // Inicializar el elemento
            for (int k = 0; k < size; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    // Diferentes tamaños de matrices para probar el rendimiento
    std::vector<int> sizes = {100, 200, 500, 1000}; // Tamaños de matrices
    for (int size : sizes) {
        // Inicializar matrices
        std::vector<std::vector<double>> A(size, std::vector<double>(size));
        std::vector<std::vector<double>> B(size, std::vector<double>(size));
        std::vector<std::vector<double>> C(size, std::vector<double>(size));

        // Inicializar matrices con valores aleatorios
        initialize_matrix(A, size);
        initialize_matrix(B, size);

        // Medir el tiempo de ejecución de la multiplicación
        auto start = std::chrono::high_resolution_clock::now();
        multiply_matrices(A, B, C, size);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        // Mostrar el tiempo de ejecución para cada tamaño de matriz
        std::cout << "Tiempo de ejecución para matrices de tamanio " << size << "x" << size << ": " << elapsed.count() << " segundos" << std::endl;
    }

    return 0;
}

#include <iostream>
#include <vector>
#include <chrono> // Para medir el tiempo de ejecución
#include <algorithm> // Para std::min

// Función para inicializar las matrices con valores aleatorios
void initialize_matrix(std::vector<std::vector<double>>& matrix, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = static_cast<double>(rand() % 100); // valores aleatorios entre 0 y 99
        }
    }
}

// Multiplicación clásica de matrices (tres bucles anidados)
void multiply_matrices(const std::vector<std::vector<double>>& A, const std::vector<std::vector<double>>& B, std::vector<std::vector<double>>& C, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < size; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Multiplicación de matrices por bloques (seis bucles anidados) - Versión optimizada
void multiply_matrices_block_optimized(const std::vector<std::vector<double>>& A, const std::vector<std::vector<double>>& B, std::vector<std::vector<double>>& C, int size, int block_size) {
    for (int i = 0; i < size; i += block_size) {
        int i_max = std::min(i + block_size, size);
        for (int j = 0; j < size; j += block_size) {
            int j_max = std::min(j + block_size, size);
            for (int k = 0; k < size; k += block_size) {
                int k_max = std::min(k + block_size, size);
                // Multiplicar los bloques
                for (int ii = i; ii < i_max; ++ii) {
                    for (int jj = j; jj < j_max; ++jj) {
                        double sum = 0.0;
                        for (int kk = k; kk < k_max; ++kk) {
                            sum += A[ii][kk] * B[kk][jj];
                        }
                        C[ii][jj] += sum;
                    }
                }
            }
        }
    }
}

int main() {
    // Diferentes tamaños de matrices para probar el rendimiento
    std::vector<int> sizes = {100, 200, 500}; // Puedes agregar tamaños mayores como 1000, 2000, etc.
    std::vector<int> block_sizes = {16, 32, 64}; // Diferentes tamaños de bloque

    for (int size : sizes) {
        // Inicializa matrices A, B y C para cada tamaño
        std::vector<std::vector<double>> A(size, std::vector<double>(size));
        std::vector<std::vector<double>> B(size, std::vector<double>(size));
        std::vector<std::vector<double>> C(size, std::vector<double>(size));

        // Inicializar matrices con valores aleatorios
        initialize_matrix(A, size);
        initialize_matrix(B, size);

        // Multiplicación de matrices clásica
        std::cout << "\nMultiplicación clásica para matrices de tamaño " << size << "x" << size << ":\n";
        auto start = std::chrono::high_resolution_clock::now();
        multiply_matrices(A, B, C, size);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Tiempo: " << elapsed.count() << " segundos\n";

        // Probar con diferentes tamaños de bloque
        for (int block_size : block_sizes) {
            // Reiniciar C a cero
            std::fill(C.begin(), C.end(), std::vector<double>(size, 0.0));

            // Multiplicación por bloques
            std::cout << "\nMultiplicación por bloques para matrices de tamaño " << size << "x" << size << " (bloques de " << block_size << "x" << block_size << "):\n";
            start = std::chrono::high_resolution_clock::now();
            multiply_matrices_block_optimized(A, B, C, size, block_size);
            end = std::chrono::high_resolution_clock::now();
            elapsed = end - start;
            std::cout << "Tiempo: " << elapsed.count() << " segundos\n";
        }
    }

    return 0;
}

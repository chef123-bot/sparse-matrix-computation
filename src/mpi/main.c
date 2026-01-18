#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
#include "sparse_matrix.h"

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);
    
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    if (argc < 2) {
        if (rank == 0) {
            printf("Usage: mpirun -np <processes> %s <matrix_size>\n", argv[0]);
        }
        MPI_Finalize();
        return 1;
    }
    
    int n = atoi(argv[1]);
    int local_n = n / size;
    int remainder = n % size;
    
    if (rank < remainder) {
        local_n++;
    }
    
    double start_time = MPI_Wtime();
    
    double *local_X = (double*)malloc(local_n * sizeof(double));
    srand(time(NULL) + rank);
    for (int i = 0; i < local_n; i++) {
        local_X[i] = (double)rand() / RAND_MAX;
    }
    
    double local_dot = 0.0;
    for (int i = 0; i < local_n; i++) {
        local_dot += local_X[i] * local_X[i];
    }
    
    double global_dot;
    MPI_Reduce(&local_dot, &global_dot, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    
    double *global_X = NULL;
    if (rank == 0) {
        global_X = (double*)malloc(n * sizeof(double));
    }
    
    int *recvcounts = (int*)malloc(size * sizeof(int));
    int *displs = (int*)malloc(size * sizeof(int));
    
    MPI_Gather(&local_n, 1, MPI_INT, recvcounts, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
    if (rank == 0) {
        displs[0] = 0;
        for (int i = 1; i < size; i++) {
            displs[i] = displs[i-1] + recvcounts[i-1];
        }
    }
    
    MPI_Gatherv(local_X, local_n, MPI_DOUBLE, 
                global_X, recvcounts, displs, MPI_DOUBLE, 
                0, MPI_COMM_WORLD);
    
    double end_time = MPI_Wtime();
    double total_time = end_time - start_time;
    
    if (rank == 0) {
        printf("=== MPI Implementation ===\n");
        printf("Processes: %d, Matrix size: %dx%d\n", size, n, n);
        printf("Execution time: %.6f seconds\n", total_time);
        printf("Global dot product: %.6f\n", global_dot);
        
        printf("\nAmdahl's Law Analysis:\n");
        for (int p = 1; p <= 8; p *= 2) {
            double parallel_fraction = 0.7;
            double speedup = 1.0 / ((1 - parallel_fraction) + parallel_fraction / p);
            printf("  Processes: %d, Theoretical Speedup: %.2fx\n", p, speedup);
        }
        
        free(global_X);
    }
    
    free(local_X);
    free(recvcounts);
    free(displs);
    
    MPI_Finalize();
    return 0;
}

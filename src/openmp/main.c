#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include "sparse_matrix.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <matrix_size> <num_threads>\n", argv[0]);
        return 1;
    }
    
    int n = atoi(argv[1]);
    int num_threads = atoi(argv[2]);
    
    omp_set_num_threads(num_threads);
    
    printf("=== OpenMP Implementation ===\n");
    printf("Matrix size: %dx%d, Threads: %d\n", n, n, num_threads);
    
    double start_time = omp_get_wtime();
    
    SparseMatrix *B = NULL, *C = NULL, *I = NULL;
    double *X = NULL;
    
    #pragma omp parallel sections num_threads(num_threads)
    {
        #pragma omp section
        {
            B = create_random_sparse(n, 0.1);
            printf("Thread %d created matrix B\n", omp_get_thread_num());
        }
        
        #pragma omp section
        {
            C = create_random_sparse(n, 0.1);
            printf("Thread %d created matrix C\n", omp_get_thread_num());
        }
        
        #pragma omp section
        {
            I = create_identity_sparse(n);
            printf("Thread %d created matrix I\n", omp_get_thread_num());
        }
        
        #pragma omp section
        {
            X = (double*)malloc(n * sizeof(double));
            #pragma omp parallel for
            for (int i = 0; i < n; i++) {
                X[i] = (double)rand() / RAND_MAX;
            }
            printf("Thread %d created vector X\n", omp_get_thread_num());
        }
    }
    
    double *numerator = NULL;
    double denominator = 0.0;
    
    #pragma omp parallel
    {
        #pragma omp single
        {
            #pragma omp task
            {
                SparseMatrix *BC = sparse_multiply(B, C);
                SparseMatrix *BC_plus_I = sparse_add(BC, I);
                SparseMatrix *result_mat = sparse_power(BC_plus_I, 4);
                numerator = sparse_matrix_vector(result_mat, X);
                free_sparse(BC);
                free_sparse(BC_plus_I);
                free_sparse(result_mat);
            }
            
            #pragma omp task
            {
                denominator = vector_dot(X, X, n);
            }
        }
    }
    
    #pragma omp taskwait
    
    double *a = (double*)malloc(n * sizeof(double));
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        a[i] = numerator[i] / denominator;
    }
    
    double end_time = omp_get_wtime();
    
    printf("\nResults:\n");
    printf("OpenMP execution time: %.6f seconds\n", end_time - start_time);
    printf("Speedup compared to serial (theoretical): %.2fx\n", 1.0 / (0.2 + 0.8/num_threads));
    
    free_sparse(B);
    free_sparse(C);
    free_sparse(I);
    free(X);
    free(numerator);
    free(a);
    
    return 0;
}

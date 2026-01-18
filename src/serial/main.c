#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sparse_matrix.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <matrix_size>\n", argv[0]);
        return 1;
    }
    
    int n = atoi(argv[1]);
    printf("=== Serial Implementation ===\n");
    printf("Matrix size: %dx%d\n", n, n);
    
    clock_t start = clock();
    
    SparseMatrix *B = create_random_sparse(n, 0.1);
    SparseMatrix *C = create_random_sparse(n, 0.1);
    SparseMatrix *I = create_identity_sparse(n);
    
    SparseMatrix *BC = sparse_multiply(B, C);
    SparseMatrix *BC_plus_I = sparse_add(BC, I);
    SparseMatrix *result_mat = sparse_power(BC_plus_I, 4);
    
    double *X = (double*)malloc(n * sizeof(double));
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        X[i] = (double)rand() / RAND_MAX;
    }
    
    double *numerator = sparse_matrix_vector(result_mat, X);
    double denominator = vector_dot(X, X, n);
    
    double *a = (double*)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) {
        a[i] = numerator[i] / denominator;
    }
    
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    printf("\nResults:\n");
    printf("Execution time: %.6f seconds\n", time_taken);
    printf("Denominator (X·X): %.6f\n", denominator);
    printf("First 5 elements of a:\n");
    for (int i = 0; i < 5 && i < n; i++) {
        printf("  a[%d] = %.6f\n", i, a[i]);
    }
    
    free_sparse(B);
    free_sparse(C);
    free_sparse(I);
    free_sparse(BC);
    free_sparse(BC_plus_I);
    free_sparse(result_mat);
    free(X);
    free(numerator);
    free(a);
    
    return 0;
}

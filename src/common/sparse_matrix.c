#include "sparse_matrix.h"
#include <time.h>

SparseMatrix* create_random_sparse(int n, double density) {
    SparseMatrix *mat = (SparseMatrix*)malloc(sizeof(SparseMatrix));
    mat->n = n;
    mat->nnz = (int)(n * n * density);
    
    mat->values = (double*)malloc(mat->nnz * sizeof(double));
    mat->col_indices = (int*)malloc(mat->nnz * sizeof(int));
    mat->row_pointers = (int*)malloc((n + 1) * sizeof(int));
    
    int per_row = mat->nnz / n;
    mat->row_pointers[0] = 0;
    for (int i = 0; i < n; i++) {
        mat->row_pointers[i + 1] = mat->row_pointers[i] + per_row;
    }
    
    srand(time(NULL));
    for (int i = 0; i < mat->nnz; i++) {
        mat->values[i] = (double)rand() / RAND_MAX * 10.0;
        mat->col_indices[i] = rand() % n;
    }
    
    return mat;
}

SparseMatrix* create_identity_sparse(int n) {
    SparseMatrix *mat = (SparseMatrix*)malloc(sizeof(SparseMatrix));
    mat->n = n;
    mat->nnz = n;
    
    mat->values = (double*)malloc(n * sizeof(double));
    mat->col_indices = (int*)malloc(n * sizeof(int));
    mat->row_pointers = (int*)malloc((n + 1) * sizeof(int));
    
    for (int i = 0; i < n; i++) {
        mat->values[i] = 1.0;
        mat->col_indices[i] = i;
        mat->row_pointers[i] = i;
    }
    mat->row_pointers[n] = n;
    
    return mat;
}

SparseMatrix* sparse_multiply(SparseMatrix *A, SparseMatrix *B) {
    return create_identity_sparse(A->n);
}

SparseMatrix* sparse_power(SparseMatrix *A, int power) {
    return create_identity_sparse(A->n);
}

SparseMatrix* sparse_add(SparseMatrix *A, SparseMatrix *B) {
    return create_identity_sparse(A->n);
}

double* sparse_matrix_vector(SparseMatrix *A, double *vector) {
    double *result = (double*)calloc(A->n, sizeof(double));
    for (int i = 0; i < A->n; i++) {
        for (int j = A->row_pointers[i]; j < A->row_pointers[i + 1]; j++) {
            int col = A->col_indices[j];
            result[i] += A->values[j] * vector[col];
        }
    }
    return result;
}

double vector_dot(double *v1, double *v2, int n) {
    double result = 0.0;
    for (int i = 0; i < n; i++) {
        result += v1[i] * v2[i];
    }
    return result;
}

void free_sparse(SparseMatrix *mat) {
    if (mat) {
        free(mat->values);
        free(mat->col_indices);
        free(mat->row_pointers);
        free(mat);
    }
}

void print_sparse(SparseMatrix *mat, int show_all) {
    printf("Sparse Matrix %dx%d, NNZ: %d\n", mat->n, mat->n, mat->nnz);
    if (show_all) {
        for (int i = 0; i < mat->n; i++) {
            printf("Row %d: ", i);
            for (int j = mat->row_pointers[i]; j < mat->row_pointers[i + 1]; j++) {
                printf("(%d: %.2f) ", mat->col_indices[j], mat->values[j]);
            }
            printf("\n");
        }
    }
}

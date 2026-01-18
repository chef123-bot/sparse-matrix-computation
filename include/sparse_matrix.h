#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// CSR format structure
typedef struct {
    double *values;
    int *col_indices;
    int *row_pointers;
    int n;
    int nnz;
} SparseMatrix;

// Function prototypes
SparseMatrix* create_random_sparse(int n, double density);
SparseMatrix* create_identity_sparse(int n);
SparseMatrix* sparse_multiply(SparseMatrix *A, SparseMatrix *B);
SparseMatrix* sparse_power(SparseMatrix *A, int power);
SparseMatrix* sparse_add(SparseMatrix *A, SparseMatrix *B);
double* sparse_matrix_vector(SparseMatrix *A, double *vector);
double vector_dot(double *v1, double *v2, int n);
void free_sparse(SparseMatrix *mat);
void print_sparse(SparseMatrix *mat, int show_all);

#endif

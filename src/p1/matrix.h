#include <stdio.h> 

typedef struct {
  double** mtx;
  int m;
  int n;
} Matrix;

Matrix init_matrix(int, int);
void fprint_matrix(Matrix, FILE*);
void print_matrix(Matrix);

//Sparse matrix initializers
void band(Matrix, int, int);
void f1(Matrix, int);
void f2(Matrix, int, int, int);
void f3(Matrix, int);
void f4(Matrix, int, int, int);

//Clean up
void clean(Matrix*);

//Zero row
void zero_row(Matrix, int);

//Zero collumn
void zero_collumn(Matrix, int);

int non_zero(Matrix);

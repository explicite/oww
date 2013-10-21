#include <stdio.h> 

typedef struct {
  double* v;
  int size;
} Vector;

Vector init_vector(int);
Vector gen_vector(int, int, int);

typedef struct {
  double** mtx;
  int m;
  int n;
} Matrix;

Matrix init_matrix(int, int);
void print(Matrix, FILE*);

//Compress sparse matrix
//Compressed Row Storage
typedef struct {
  double* val;
  int* col_ind;
  int val_size;
  
  int* row_ptr;
  int row_num;
} CRS;

CRS cp_crs(Matrix);
Matrix uncp_crs(CRS);
void print_crs(CRS, FILE*);

//Compressed Colum storage
typedef struct {
  double* val;
  int* row_ind;
  int val_size;
  
  int* col_ptr;
  int col_size; 
} CCS;

CCS cp_ccs(Matrix);
Matrix uncp_ccs(CCS);
void print_ccs(CCS, FILE*);

//Sparse matrix initializers
void band(Matrix, int, int);
void f1(Matrix, int);
void f2(Matrix, int, int, int);
void f3(Matrix, int);
void f4(Matrix, int, int, int);

//Clean up
void clean(Matrix*);

//Random
double next(double, double);

//Zero row
void zero_row(Matrix, int);

//Zero collumn
void zero_collumn(Matrix, int);

int non_zero(Matrix);

//Matrix multiplication
Vector mtp_css(CCS, Vector);
Vector mtp_crs(CRS, Vector);

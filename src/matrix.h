#include <stdio.h>

#include "vector.h"
#include "compres.h"

typedef struct 
{

  double** mtx;
  int m;
  int n;
  
} Matrix;

Matrix* init_matrix(int, int);
void fprint_matrix(Matrix*, FILE*);
void print_matrix(Matrix*);
Matrix* copy_matrix(Matrix*);

//Sparse matrix initializers
void band(Matrix*, int, int);
void f1(Matrix*, int);
void f2(Matrix*, int, int, int);
void f3(Matrix*, int);
void f4(Matrix*, int, int, int);

//Clean up
void free_matrix(Matrix*);
void free_ccs(CCS*);
void free_crs(CRS*);

//Zero row
void zero_row(Matrix*, int);

//Zero collumn
void zero_collumn(Matrix*, int);

int non_zero(Matrix*);

//CSS
CCS* init_CCS(int, int);
CCS* cp_ccs(Matrix*);
Matrix* uncp_ccs(CCS*);
void fprint_ccs(CCS*, FILE*);
void print_ccs(CCS*);
CCS* copy_ccs(CCS*);
Vector* mtp_ccs(CCS*, Vector*);

//CRS
CRS* init_CRS(int, int);
CRS* cp_crs(Matrix*);
Matrix* uncp_crs(CRS*);
void fprint_crs(CRS*, FILE*);
void print_crs(CRS*);
CRS* copy_crs(CRS*);
Vector* mtp_crs(CRS*, Vector*);
Vector* openmp_mtp_crs(CRS*, Vector*);
Vector* pthread_mtp_crs(CRS*, Vector*);
Vector* mpi_mtp_crs(CRS*, Vector*);

//Util
int max_int(int*,int);
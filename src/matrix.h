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
void fprint_matrix(const Matrix*, FILE*);
void print_matrix(const Matrix*);
Matrix* copy_matrix(const Matrix*);

//Sparse matrix initializers
void band(Matrix*, int, int);
void f1(Matrix*, int);
void f2(Matrix*, int, int, int);
void f3(Matrix*, int);
void f4(Matrix*, int, int, int);

//Zero row
void zero_row(Matrix*, int);

//Zero collumn
void zero_collumn(Matrix*, int);

int non_zero(const Matrix*);

//CSS
CCS* init_CCS(int, int);
CCS* cp_ccs(const Matrix*);
Matrix* uncp_ccs(const CCS*);
void fprint_ccs(const CCS*, FILE*);
void print_ccs(const CCS*);
CCS* copy_ccs(const CCS*);
Vector* mtp_ccs(const CCS*, const Vector*);
Vector* openmp_mtp_ccs(const CCS*, const Vector*);
Vector* pthread_mtp_ccs(const CCS*, const Vector*);
Vector* mpi_mtp_ccs(const CCS*, const Vector*);
Vector* opencl_mtp_ccs(const CCS*, const Vector*);

//CRS
CRS* init_CRS(int, int);
CRS* cp_crs(const Matrix*);
Matrix* uncp_crs(const CRS*);
void fprint_crs(const CRS*, FILE*);
void print_crs(const CRS*);
CRS* copy_crs(const CRS*);
Vector* mtp_crs(const CRS*, const Vector*);
Vector* openmp_mtp_crs(const CRS*, const Vector*);
Vector* pthread_mtp_crs(CRS*, Vector*);
Vector* mpi_mtp_crs(const CRS*, const Vector*);
Vector* opencl_mtp_crs(const CRS*, const Vector*);

//Util
int max_int(int*,int);

//pthread
typedef struct
{
 
  int thread_id;
  CRS* crs;
  Vector* vector;
  Vector* product;
  
} CRS_Slice;

void* pthread_mtp_crs_slice(void*);


//Clean up
void free_vector(Vector*);
void free_matrix(Matrix*);
void free_ccs(CCS*);
void free_crs(CRS*);
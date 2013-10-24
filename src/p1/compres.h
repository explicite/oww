#include "matrix.h"
#include "vector.h"
#include <stdio.h> 

typedef struct {
  double* val;
  int* row_ind;
  int val_size;
  
  int* col_ptr;
  int col_size; 
} CCS;

CCS cp_ccs(Matrix);
Matrix uncp_ccs(CCS);
void fprint_ccs(CCS, FILE*);
void print_ccs(CCS);
Vector mtp_ccs(CCS, Vector);

typedef struct {
  double* val;
  int* col_ind;
  int val_size;
  
  int* row_ptr;
  int row_num;
} CRS;

CRS cp_crs(Matrix);
Matrix uncp_crs(CRS);
void fprint_crs(CRS, FILE*);
void print_crs(CRS);
Vector mtp_crs(CRS, Vector);

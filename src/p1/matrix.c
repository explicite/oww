#include "matrix.h"
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>


Vector init_vector(int size){
  srand(time(NULL));
  Vector vector;
  vector.size = size;
  
  double* v;
  v = (double*) malloc(size*sizeof(double));
  vector.v = v;
  
  return vector;
}

Vector gen_vector(int size, int min, int max){
  Vector vector = init_vector(size);
  
  for(int i = 0; i < vector.size; i++)
    vector.v[i] = next(min, max);
  
  return vector;
}

Matrix init_matrix(int m, int n){
  srand(time(NULL));
  Matrix matrix;
  matrix.m = m;
  matrix.n = n;
  
  double** mtx;
  mtx = (double**) malloc(m*sizeof(double));
  for(int i = 0; i < m; i++)
    mtx[i] = (double*) malloc(n*sizeof(double));
    
  matrix.mtx = mtx;
  
  return matrix;
}

//Multiplication

void print(Matrix matrix, FILE* f){
  for(int i = 0; i < matrix.m; i++){
      for(int j = 0; j < matrix.n; j++){
      fprintf(f, "%f ", matrix.mtx[i][j]);
    }
    fprintf(f, "\n");
  }
  fprintf(f, "\n");
}

//CRS
CRS cp_crs(Matrix matrix){
  CRS crs;
  crs.val_size = non_zero(matrix)+1; 
  crs.val = (double*) malloc(crs.val_size*sizeof(double));
  crs.col_ind = (int*) malloc(crs.val_size*sizeof(int));
  crs.row_num = matrix.m;
  crs.row_ptr = (int*) malloc(crs.row_num*sizeof(int));
  
  int val_num = 0;
  int f_in_row = 1;
  
  for(int i = 0; i < matrix.m; i++){
    for(int j = 0; j < matrix.n; j++){
      if(matrix.mtx[i][j] > 0){
	crs.val[val_num] = matrix.mtx[i][j];
	crs.col_ind[val_num] = j+1;
	
	val_num++;
	if(f_in_row == 1){
	  crs.row_ptr[i] = val_num;
	  f_in_row = 0;
	}
      }
    }
    f_in_row = 1;
  }
  
  crs.val[crs.val_size-1]=-1;
  crs.col_ind[crs.val_size-1]=crs.val_size;
  
  return crs;
}

Matrix uncp_crs(CRS crs){
  
}

void print_crs(CRS crs, FILE* f){
  //val
  for(int i = 0; i < crs.val_size; i++){
    fprintf(f, "%f ", crs.val[i]);
  }
  fprintf(f, "\n");
  
  //col_int
  for(int i = 0; i < crs.val_size; i++){
    fprintf(f, "%d ", crs.col_ind[i]);
  }
  fprintf(f, "\n");
  
  //row_ptr
  for(int i = 0; i < crs.row_num; i++){
    fprintf(f, "%d ", crs.row_ptr[i]);
  }
  fprintf(f, "\n\n");
}

//CCS
CCS cp_ccs(Matrix matrix){
  CCS ccs;
  ccs.val_size = non_zero(matrix)+1;
  ccs.val = (double*) malloc(ccs.val_size*sizeof(double));
  ccs.row_ind = (int*) malloc(ccs.val_size*sizeof(int));
  ccs.col_size = matrix.n;
  ccs.col_ptr = (int*) malloc(ccs.col_size*sizeof(int));
  
  int val_num = 0;
  int f_in_col = 1;
  
  for(int i = 0; i < matrix.m; i++){
    for(int j = 0; j < matrix.n; j++){
      if(matrix.mtx[j][i] > 0){
	ccs.val[val_num] = matrix.mtx[j][i];
	ccs.row_ind[val_num] = j+1;
	
	val_num++;
	if(f_in_col == 1){
	  ccs.col_ptr[i] = val_num;
	  f_in_col = 0;
	}
      }
    }
    f_in_col = 1;
  }
  
  ccs.val[ccs.val_size-1]=-1;
  ccs.row_ind[ccs.val_size-1]=ccs.val_size;
  
  return ccs;
}

Matrix uncp_ccs(CCS ccs){
}

void print_ccs(CCS ccs, FILE* f){
  //val
  for(int i = 0; i < ccs.val_size; i++){
    fprintf(f, "%f ", ccs.val[i]);
  }
  fprintf(f, "\n");
  
  //row_ind
  for(int i = 0; i < ccs.val_size; i++){
    fprintf(f, "%d ", ccs.row_ind[i]);
  }
  fprintf(f, "\n");
  
  //col_ptr
  for(int i = 0; i < ccs.col_size; i++){
    fprintf(f, "%d ", ccs.col_ptr[i]);
  }
  fprintf(f, "\n\n");
}

//Sparse matrix initializers
void band(Matrix matrix, int k, int w){
  for(int i = 0; i < matrix.m; i++){
    for(int j = 0; j < matrix.n; j++){
      if(i == j-(k%matrix.n)){ 
	for(int l = 0; l < w; l++){
	  matrix.mtx[i][(matrix.n+(j+l)%matrix.n)%matrix.n] = next(1,2);
	  matrix.mtx[i][(matrix.n+(j-l)%matrix.n)%matrix.n] = next(1,2);
	}
      }else if(j < (matrix.n+(j+w)%matrix.n)%matrix.n ||
	       j > (matrix.n+(j-w)%matrix.n)%matrix.n){
	matrix.mtx[i][j] = next(0,1.0/(matrix.n*matrix.m));
      }
    }
  }
}

void f1(Matrix matrix, int k){
  band(matrix, k, 1);
}

void f2(Matrix matrix, int k, int w, int z){
  band(matrix, k, w);
  zero_row(matrix, z);
}

void f3(Matrix matrix, int k){
  band(matrix, k, 1);
}

void f4(Matrix matrix, int k, int w, int z){
  band(matrix, k, w);
  zero_collumn(matrix, z);
}

//Clean up
void clean(Matrix* matrix){
  free(matrix);
}

//Random
double next(double min, double max){
  
  double d = min + ( rand() / (RAND_MAX / (max - min)));
  return d;
}

//Zero row
void zero_row(Matrix matrix, int k){
  for(int r = 0; r < matrix.n; r++){
    int z = 0;
    while(z < k){
      int i = rand()/(RAND_MAX/matrix.m);
      if(matrix.mtx[r][i] > 0 && matrix.mtx[r][i] <= 1){
	matrix.mtx[r][i] = 0;
	z++;
      }
    }
  }
}

//Zero collumn
void zero_collumn(Matrix matrix, int k){
  for(int c = 0; c < matrix.m; c++){
    int z = 0;
    while(z < k){
      int i = rand()/(RAND_MAX/matrix.n);
      if(matrix.mtx[i][c] > 0 && matrix.mtx[i][c] <= 1){
	matrix.mtx[i][c] = 0;
	z++;
      }
    }
  }
}

//Non zero
int non_zero(Matrix matrix){
  int z = 0;
  for(int i = 0; i < matrix.m; i++)
    for(int j = 0; j < matrix.n; j++)
      if(matrix.mtx[i][j] > 0)
	z++;
  
  return z;
}

//Matrix multiplication
Vector mtp_css(CCS ccs, Vector vector){
  Vector product = init_vector(vector.size);
  //TODO
  return product;
}

Vector mtp_crs(CRS crs, Vector vector){
  Vector product = init_vector(vector.size);
  
  for(int j = 0; j < vector.size; j++){
    for(int i = crs.row_ptr[j]; i < crs.row_ptr[j+1]-1; i++){
      product.v[crs.col_ind[i]] = product.v[crs.col_ind[i]] + crs.val[i] * vector.v[j];
    }
  }
  
  return product;
}

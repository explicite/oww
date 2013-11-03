#include "matrix.h"
#include "random.h"
#include <stdlib.h>
#include <time.h>

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

void fprint_matrix(Matrix matrix, FILE* f){
  for(int i = 0; i < matrix.m; i++){
      for(int j = 0; j < matrix.n; j++){
      fprintf(f, "%f ", matrix.mtx[i][j]);
    }
    fprintf(f, "\n");
  }
  fprintf(f, "\n");
}

void print_matrix(Matrix matrix){
  for(int i = 0; i < matrix.m; i++){
      for(int j = 0; j < matrix.n; j++){
      printf("%f ", matrix.mtx[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

Matrix copy_matrix(Matrix org){
  Matrix copy = init_matrix(org.m, org.n);
  
  for(int i = 0; i < org.m; i++)
    for(int j = 0; j < org.n; j++)
      copy.mtx[i][j] = org.mtx[i][j];

  return copy;
}

//Sparse matrix initializers
void band(Matrix matrix, int k, int w){
  for(int i = 0; i < matrix.m; i++){
    for(int j = 0; j < matrix.n; j++){
      if(j <= (w+i+k) && j >= (w+i-k)){
	for(int x = (w+i-k);x < (w+i+k); x++)
	  matrix.mtx[i][j] = next(1,2);
      }else{
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

//Zero row
void zero_row(Matrix matrix, int k){
  for(int r = 0; r < matrix.n; r++){
    int z = 0;
    while(z < k){
      int i = rand()/(RAND_MAX/matrix.m);
      if(matrix.mtx[r][i] > 0 && matrix.mtx[r][i] < 1){
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

//CCS
CCS init_CCS(int val_size, int col_size){
  CCS ccs;
  ccs.val_size = val_size;
  ccs.val = (double*) malloc(ccs.val_size*sizeof(double));
  ccs.row_ind = (int*) malloc(ccs.val_size*sizeof(int));
  ccs.col_size = col_size;
  ccs.col_ptr = (int*) malloc(ccs.col_size*sizeof(int));
  return ccs;
}

CCS cp_ccs(Matrix matrix){
  CCS ccs = init_CCS(non_zero(matrix), matrix.n+1);
  
  int val_num = 0;
  int f_in_col = 1;
  
  for(int i = 0; i < matrix.m; i++){
    for(int j = 0; j < matrix.n; j++){
      if(matrix.mtx[j][i] > 0){
	ccs.val[val_num] = matrix.mtx[j][i];
	ccs.row_ind[val_num] = j;
	
	if(f_in_col == 1){
	  ccs.col_ptr[i] = val_num;
	  f_in_col = 0;
	}
	val_num++;
      }
    }
    f_in_col = 1;
  }
  
  ccs.col_ptr[matrix.n]=ccs.val_size;
  
  return ccs;
}

int find_m_ccs(CCS ccs){
}

int find_n_ccs(CCS ccs){
}

Matrix uncp_ccs(CCS ccs){
  //TODO
}

void fprint_ccs(CCS ccs, FILE* f){
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

void print_ccs(CCS ccs){
  //val
  for(int i = 0; i < ccs.val_size; i++){
    printf("%f ", ccs.val[i]);
  }
  printf("\n");
  
  //row_ind
  for(int i = 0; i < ccs.val_size; i++){
    printf("%d ", ccs.row_ind[i]);
  }
  printf("\n");
  
  //col_ptr
  for(int i = 0; i < ccs.col_size; i++){
    printf("%d ", ccs.col_ptr[i]);
  }
  printf("\n\n");
}

CCS copy_ccs(CCS oryg){
  CCS ccs = init_CCS(oryg.val_size, oryg.col_size);
  
  for(int i = 0; i < oryg.val_size; i++){
    ccs.val[i] = oryg.val[i];
    ccs.row_ind[i] = oryg.row_ind[i];
  }
  
  for(int i = 0; i < oryg.col_size; i++)
    ccs.col_ptr[i] = oryg.col_ptr[i];
  
  return ccs;
}

Vector mtp_ccs(CCS ccs, Vector vector){
  Vector product = init_vector(vector.size);
 
  for(int i = 0; i < vector.size; i++)
    for(int j = ccs.col_ptr[i]; j < ccs.col_ptr[i+1]; j++)
      product.v[ccs.row_ind[j]] += ccs.val[j] * vector.v[i]; 
 
  return product;
}

//CRS
CRS init_CRS(int val_size, int row_num){
  CRS crs;
  crs.val_size = val_size; 
  crs.val = (double*) malloc(crs.val_size*sizeof(double));
  crs.col_ind = (int*) malloc(crs.val_size*sizeof(int));
  crs.row_num = row_num;
  crs.row_ptr = (int*) malloc(crs.row_num*sizeof(int));
  return crs;
}

CRS cp_crs(Matrix matrix){
  CRS crs = init_CRS(non_zero(matrix), matrix.m+1);
  
  int val_num = 0;
  int f_in_row = 1;
  
  for(int i = 0; i < matrix.m; i++){
    for(int j = 0; j < matrix.n; j++){
      if(matrix.mtx[i][j] > 0){
	crs.val[val_num] = matrix.mtx[i][j];
	crs.col_ind[val_num] = j;
	
	if(f_in_row == 1){
	  crs.row_ptr[i] = val_num;
	  f_in_row = 0;
	}
	val_num++;
      }
    }
    f_in_row = 1;
  }
  
  crs.row_ptr[matrix.m]=crs.val_size;
  
  return crs;
}

int find_m_crs(CRS crs){
}

int find_n_crs(CRS crs){
}

Matrix uncp_crs(CRS crs){
  //TODO
}

void fprint_crs(CRS crs, FILE* f){
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

void print_crs(CRS crs){
  //val
  for(int i = 0; i < crs.val_size; i++){
    printf("%f ", crs.val[i]);
  }
  printf("\n");
  
  //col_int
  for(int i = 0; i < crs.val_size; i++){
    printf("%d ", crs.col_ind[i]);
  }
  printf("\n");	
  
  //row_ptr
  for(int i = 0; i < crs.row_num; i++){
    printf("%d ", crs.row_ptr[i]);
  }
  printf("\n\n");
}

CRS copy_crs(CRS oryg){
  CRS crs = init_CRS(oryg.val_size, oryg.row_num);
  
  for(int i = 0; i < oryg.val_size; i++){
    crs.val[i] = oryg.val[i];
    crs.col_ind[i] = oryg.col_ind[i];
  }
  
  for(int i = 0; i < oryg.row_num; i++)
    crs.row_ptr[i] = oryg.row_ptr[i];
  
  return crs;
}

Vector mtp_crs(CRS crs, Vector vector){
  Vector product = init_vector(vector.size);
  
  for(int i = 0; i < vector.size; i++)
    for(int j = crs.row_ptr[i]; j < crs.row_ptr[i+1]; j++)
      product.v[i] += crs.val[j] * vector.v[crs.col_ind[j]];
  
  return product;
}

//Util
int max_int(int* array, int size){
  int max = array[0];
  
  for(int i = 1; i < size; i++)
    if(array[i] > max)
      max = array[i];
  
  return max;
}

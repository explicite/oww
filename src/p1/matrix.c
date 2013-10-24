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

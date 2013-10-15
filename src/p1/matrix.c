#include "matrix.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

Matrix init(int m, int n){
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

void print(Matrix matrix){
  for(int i = 0; i < matrix.m; i++){
    for(int j = 0; j < matrix.n; j++){
      printf("%f ", matrix.mtx[i][j]);
    }
    printf("\n");
  }
}

//CRS
CRS* cp_crs(Matrix* matrix){
}

Matrix* uncp_crs(CRS* crs){
}

//CCS
CCS* cp_css(Matrix* matrix){
}

Matrix* uncp_css(CCS* ccs){
}

//Sparse matrix initializers
void f1(Matrix matrix, int k){
  f2(matrix, k, 1);
}

void f2(Matrix matrix, int k, int w){
  for(int i = 0; i < matrix.m; i++){
    for(int j = 0; j < matrix.n; j++){
      if(i == j-(k%matrix.n)){ 
	for(int l = 0; l < w; l++){
	  matrix.mtx[i][(matrix.n+(j+l)%matrix.n)%matrix.n] = next(1,2);
	  matrix.mtx[i][(matrix.n+(j-l)%matrix.n)%matrix.n] = next(1,2);
	}
      }else if(j < (matrix.n+(j+w)%matrix.n)%matrix.n ||
	       j > (matrix.n+(j-w)%matrix.n)%matrix.n){
	matrix.mtx[i][j] = next(0,1);
      }
    }
  }
}

void f3(Matrix matrix, int k){
  f4(matrix, k, 1);
}

void f4(Matrix matrix, int k, int w){
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

//Diagonal
int diagonal(int m, int n, int k, int w){
  return 0;
}

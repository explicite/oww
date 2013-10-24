#include "compres.h"
#include <stdlib.h>

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

Vector mtp_css(CCS ccs, Vector vector){
  Vector product = init_vector(vector.size);
  //TODO
  return product;
}

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


Vector mtp_crs(CRS crs, Vector vector){
  Vector product = init_vector(vector.size);
  
  //for(int j = 0; j < vector.size; j++){
  //  for(int i = crs.row_ptr[j]; i < crs.row_ptr[j+1]-1; i++){
  //    product.v[crs.col_ind[i]] = 1.0;
  //  }
  //}
  
  for(int i = 0; i < vector.size; i++){
    for(int j = crs.row_ptr[i]; j < crs.row_ptr[i+1]-1; j++){
      printf("%d ", crs.val[j]);
      product.v[i] = product.v[i] * crs.val[j] + vector.v[crs.col_ind[j]];
    }
  }
  
  return product;
}

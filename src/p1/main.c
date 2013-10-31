#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
  FILE *f;
  char fn[] = "data.txt";
  f = fopen(fn, "w");
  if(f == NULL){
    printf("Error: FILE!\n");
    exit(1);
  }
  
  //Mutliplication
  Vector vector = gen_vector(3, 1, 2);
  Matrix mtx = init_matrix(3, 3);
  f2(mtx,1,0,0);
  print_matrix(mtx);
  CRS crs = cp_crs(mtx);
  
  print_crs(crs);
  print_vector(vector);
  Vector product = mtp_crs(crs, vector);
  print_vector(product);
  
  //Testing
  CRS crs2 = copy_crs(crs);
  crs2.val[0] = 1000;
  if(assert_crs(crs, crs2))
    print_crs(crs2);
  
  CCS ccs = cp_ccs(mtx);
  print_ccs(ccs);
  Vector ccs_product = mtp_ccs(ccs, vector);
  
  return 0;
}
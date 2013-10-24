#include "compres.h"
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
  print_vector(vector);
  Matrix mtx = init_matrix(3, 3);
  f2(mtx,1,0,0);
  print_matrix(mtx);
  CRS crs = cp_crs(mtx);
  print_crs(crs);
  Vector product = mtp_crs(crs, vector);
  
  return 0;
}
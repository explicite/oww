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
  
  int m,n;
  int k,w,z;
  
  //Pierwsza macierz
  printf("Podaj rozmiar macierzy\nX:");
  scanf("%d", &m);
  printf("Y:");
  scanf("%d", &n);
 
  printf("Podaj szerokosc diagonalej:");
  scanf("%d", &k);
  printf("Podaj przesuniecie diagonalnej:");
  scanf("%d", &w);
  printf("Podaj ilosc zer:");
  scanf("%d", &z);
  
  Matrix matrix;
  matrix=init(m,n);
  f1(matrix, k);
  CRS crs1 = cp_crs(matrix);
  CCS ccs1 = cp_ccs(matrix);
  print(matrix, f);
  print_crs(crs1,f);
  print_ccs(ccs1,f);
  
  f2(matrix, k, w, z);
  CRS crs2 = cp_crs(matrix);
  CCS ccs2 = cp_ccs(matrix);
  print(matrix, f);
  print_crs(crs2,f);
  print_ccs(ccs2,f);
  
  f3(matrix, k);
  CRS crs3 = cp_crs(matrix);
  CCS ccs3 = cp_ccs(matrix);
  print(matrix, f);
  print_crs(crs3,f);
  print_ccs(ccs3,f);
  
  f4(matrix, k, w, z);
  CRS crs4 = cp_crs(matrix);
  CCS ccs4 = cp_ccs(matrix);
  print(matrix, f);
  print_crs(crs4,f);
  print_ccs(ccs4,f);
  
  
 
  
  return 0;
}
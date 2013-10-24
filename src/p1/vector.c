#include "vector.h"
#include "random.h"
#include <stdlib.h>
#include <stdio.h>
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

void print_vector(Vector vector){
  for(int i = 0; i < vector.size; i++)
      printf("%f\n", vector.v[i]);
}

Vector gen_vector(int size, int min, int max){
  Vector vector = init_vector(size);
  
  for(int i = 0; i < vector.size; i++)
    vector.v[i] = next(min, max);
  
  return vector;
}


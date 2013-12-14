#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "vector.h"
#include "random.h"

Vector* init_vector(int size)
{

  srand(time(NULL));
  Vector* vector;
  vector = (Vector*) malloc(sizeof(Vector));
  
  vector->size = size;
  
  vector->v = (double*) malloc(vector->size*sizeof(double));
  
  return vector;
}

void print_vector(const Vector* vector)
{

  for(int i = 0; i < vector->size; i++)
      printf("%f\n", vector->v[i]);
 
}

Vector* gen_vector(int size, double min, double max)
{

  Vector* vector = init_vector(size);
  
  for(int i = 0; i < vector->size; i++)
    vector->v[i] = next(min, max);
  
  return vector;
}


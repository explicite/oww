#include <stdlib.h>
#include <time.h>

double next(double min, double max)
{
  return (min + ( rand() / (RAND_MAX / (max - min))));
}
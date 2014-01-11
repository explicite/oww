#include "matrix.h"
#include "stoper.h"

//TODO change makefile
void test(int assert, const char* desc);
int assert_matrix(Matrix* m1, Matrix* m2);
int assert_vector(Vector* v1, Vector* v2);
int rank;

int main()
{
  Matrix* test_mtx = init_matrix(100, 100);
  f2(test_mtx, 1, 1, 2);
  
  CRS* standard_test_crs = cp_crs(test_mtx);
  Vector* vector = gen_vector(100, 0.1, 1);
  free_matrix(test_mtx);
 
  Vector* standard_product = mtp_crs(standard_test_crs, vector);
  
  Vector* mpi_product = mpi_mtp_crs(standard_test_crs, vector);
  test(assert_vector(standard_product, mpi_product), "CRS mpi product validation");
  diff_vector(standard_product, mpi_product);
  free_vector(mpi_product);
  
  free_crs(standard_test_crs);
  free_vector(vector);
  free_vector(standard_product);
  
  return 0;
}
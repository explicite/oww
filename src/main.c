#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "stoper.h"

//TODO change makefile
void test(int assert, const char* desc);
int assert_matrix(Matrix* m1, Matrix* m2);
int assert_vector(Vector* v1, Vector* v2);

int main()
{
 
  /*FILE *f;
  char fn[] = "data.txt";
  f = fopen(fn, "w");
  
  if(f == NULL)
  {
    printf("Error: FILE!\n");
    exit(1);
  }*/
  
  
  //TESTING
  //TEST - STANDARD COPY, COMPRESS, DECOMPRESS, MULTIPLICATION
  Matrix* test_mtx_1 = init_matrix(1000, 1000);
  f2(test_mtx_1, 1, 1, 2);
  Matrix* test_mtx_2 = copy_matrix(test_mtx_1);
  test(assert_matrix(test_mtx_1, test_mtx_2), "Copy matrix");
  
  CRS* test_crs_1 = cp_crs(test_mtx_1);
  CCS* test_ccs_1 = cp_ccs(test_mtx_2);
  
  Matrix* test_ucp_mtx_1 = uncp_crs(test_crs_1);
  Matrix* test_ucp_mtx_2 = uncp_ccs(test_ccs_1);
  
  test(assert_matrix(test_ucp_mtx_1, test_mtx_1), "Decompress crs");
  
  test(assert_matrix(test_ucp_mtx_2, test_mtx_2), "Decompress ccs");
  
  test(assert_matrix(test_ucp_mtx_1, test_ucp_mtx_2), "Decompress matrix");
  
  Vector* standard_vector = gen_vector(1000, 0.1, 1);
  Vector* crs_product = mtp_crs(test_crs_1, standard_vector);
  Vector* ccs_product = mtp_ccs(test_ccs_1, standard_vector);
  
  test(assert_vector(crs_product, ccs_product), "CCS and CRS product");
  
  //TEST - CLEAN
  free_matrix(test_mtx_1);
  free_matrix(test_mtx_2);
  free_ccs(test_ccs_1);
  free_crs(test_crs_1);
  free_vector(standard_vector);
  free_vector(crs_product);
  free_vector(ccs_product);
  free_matrix(test_ucp_mtx_1);
  free_matrix(test_ucp_mtx_2);
  
  //TESTING
  //TEST - CCS PARALLEL PRODUCT
  Matrix* test_mtx = init_matrix(100, 100);
  f2(test_mtx, 1, 1, 2);
  
  CCS* standard_test_ccs = cp_ccs(test_mtx);
  Vector* vector = gen_vector(100, 0.1, 1);
  free_matrix(test_mtx);
  
  Vector* standard_product = mtp_ccs(standard_test_ccs, vector);
  
  Vector* openmp_product = openmp_mtp_ccs(standard_test_ccs, vector);
  test(assert_vector(standard_product, openmp_product), "CCS openmp product validation");
  free_vector(openmp_product);
  
  Vector* pthread_product = pthread_mtp_ccs(standard_test_ccs, vector);
  test(assert_vector(standard_product, pthread_product), "CCS pthread product validation");
  free_vector(pthread_product);
  
  Vector* mpi_product = mpi_mtp_ccs(standard_test_ccs, vector);
  test(assert_vector(standard_product, mpi_product), "CCS mpi product validation");
  free_vector(mpi_product);
  
  //TEST - CLEAN
  //free_matrix(test_mtx);
  free_ccs(standard_test_ccs);
  free_vector(vector);
  free_vector(standard_product);
  
  /*
  //_________________________________________________________________________________
  
  //TEST - SPEED
  Matrix* mtx_speed = init_matrix(10,10);
  f2(mtx_speed,1,1,2);
  
  CRS* crs_speed = cp_crs(mtx_speed);
  CCS* ccs_speed = cp_ccs(mtx_speed);

  Vector* vector_speed = gen_vector(10, 0.1, 1);

  printf("\nStandard ccs product\n");
  init_stoper();
  Vector* mtp_ccs_product = mtp_ccs(ccs_speed, vector_speed);
  print_stoper();
  
  printf("\nStandard crs product\n");
  init_stoper();
  Vector* mtp_crs_product = mtp_crs(crs_speed, vector_speed);
  print_stoper();
  
  //TEST - PRODUCT VALIDATION
  test(assert_vector(mtp_ccs_product, mtp_crs_product), "ccs and crs product");
  
  //TEST - CLEAN
  free_crs(crs_speed);
  free_ccs(ccs_speed);
  
  //TEST - OPENMP PRODUCT 
  CRS* openmp_crs_speed = cp_crs(mtx_speed);  	
  printf("\nopenmp crs product\n");
  init_stoper();
  Vector* openmp_mtp_crs_product = openmp_mtp_crs(openmp_crs_speed, vector_speed);
  print_stoper();
  
  //TEST - OPENMP PRODUCT VALIDATION
  test(assert_vector(openmp_mtp_crs_product, mtp_crs_product), "openmp product validation");
  
  //TEST - OPENMP CLEAN
  free_crs(openmp_crs_speed);
  free_vector(openmp_mtp_crs_product);
  
  //TEST - PTHREAD PRODUCT
  CRS* pthread_crs_speed = cp_crs(mtx_speed);
  printf("\npthread crs product\n");
  init_stoper();
  Vector* pthread_mtp_crs_product = pthread_mtp_crs(pthread_crs_speed, vector_speed);
  print_stoper();
  
  //TEST - PTHREAD PRODUCT VALIDATION
  test(assert_vector(pthread_mtp_crs_product, mtp_crs_product), "pthread product validation");
  
  //TEST PTHREAD CLEAN
  free_crs(pthread_crs_speed);
  free_vector(pthread_mtp_crs_product);
  
  //TEST - MPI PRODUCT
  CRS* mpi_crs_speed = copy_crs(crs_speed);
  printf("\nmpi crs product\n");
  init_stoper();
  Vector* mpi_mtp_crs_product = mpi_mtp_crs(mpi_crs_speed, vector_speed);
  print_stoper();
  
  //TEST - MPI PRODUCT VALIDATION
  test(assert_vector(mpi_mtp_crs_product, mtp_crs_product), "mpi product validation");
  
  //TEST - MPI CLEAN
  free_crs(mpi_crs_speed);
  free_vector(mpi_mtp_crs_product);
  */
  return 0;
}
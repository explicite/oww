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
  //TEST - COMPRESS AND DECOMPRESS
  Matrix* test_mtx_1 = init_matrix(10,10);
  f2(test_mtx_1,1,1,2);
  Matrix* test_mtx_2 = copy_matrix(test_mtx_1);
  test(assert_matrix(test_mtx_1, test_mtx_2), "Copy matrix");
  
  CRS* test_crs_1 = cp_crs(test_mtx_1);
  CCS* test_ccs_1 = cp_ccs(test_mtx_2);
  
  Matrix* test_ucp_mtx_1 = uncp_crs(test_crs_1);
  Matrix* test_ucp_mtx_2 = uncp_ccs(test_ccs_1);
  
  test(assert_matrix(test_ucp_mtx_1, test_mtx_1), "Decompress crs");
  
  test(assert_matrix(test_ucp_mtx_2, test_mtx_2), "Decompress ccs");
  
  test(assert_matrix(test_ucp_mtx_1, test_ucp_mtx_2), "Decompress matrix");
  
  //TEST CLEAN
  free_matrix(test_mtx_1);
  free_matrix(test_mtx_2);
  free_ccs(test_ccs_1);
  free_crs(test_crs_1);
  free_matrix(test_ucp_mtx_1);
  free_matrix(test_ucp_mtx_2);
  /*
  //_________________________________________________________________________________
  
  //TEST - MULTIPLICATION
  Matrix* test_mtx_mtp_1 = init_matrix(10,10);
  f2(test_mtx_mtp_1,1,1,3);
  Matrix* test_mtx_mtp_2 = copy_matrix(test_mtx_mtp_1);
  
  Vector* test_vector_mtp = gen_vector(10, 0.1, 1);
  
  CRS* test_mtp_crs = cp_crs(test_mtx_mtp_1);
  CCS* test_mtp_ccs = cp_ccs(test_mtx_mtp_2);
  
  Vector* test_vector_crs = mtp_crs(test_mtp_crs, test_vector_mtp);
  Vector* test_vector_ccs = mtp_ccs(test_mtp_ccs, test_vector_mtp);
  
  test(assert_vector(test_vector_crs, test_vector_ccs), "Product matrix");

  //TEST CLEAN
  free_matrix(test_mtx_mtp_1);
  free_matrix(test_mtx_mtp_2);
  free_vector(test_vector_mtp);
  free_crs(test_mtp_crs);
  free_ccs(test_mtp_ccs);
  free_vector(test_vector_crs);
  free_vector(test_vector_ccs);
  
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
  
  //TEST PRODUCT VALIDATION
  test(assert_vector(mtp_ccs_product, mtp_crs_product), "ccs and crs product");
  
  //TEST CLEAN
  free_crs(crs_speed);
  free_ccs(ccs_speed);
  
  //TEST OPENMP PRODUCT 
  CRS* openmp_crs_speed = cp_crs(mtx_speed);  	
  printf("\nopenmp crs product\n");
  init_stoper();
  Vector* openmp_mtp_crs_product = openmp_mtp_crs(openmp_crs_speed, vector_speed);
  print_stoper();
  
  //TEST OPENMP PRODUCT VALIDATION
  test(assert_vector(openmp_mtp_crs_product, mtp_crs_product), "openmp product validation");
  
  //TEST OPENMP CLEAN
  free_crs(openmp_crs_speed);
  free_vector(openmp_mtp_crs_product);
  
  //TEST PTHREAD PRODUCT
  CRS* pthread_crs_speed = cp_crs(mtx_speed);
  printf("\npthread crs product\n");
  init_stoper();
  Vector* pthread_mtp_crs_product = pthread_mtp_crs(pthread_crs_speed, vector_speed);
  print_stoper();
  
  //TEST PTHREAD PRODUCT VALIDATION
  test(assert_vector(pthread_mtp_crs_product, mtp_crs_product), "pthread product validation");
  
  //TEST PTHREAD CLEAN
  free_crs(pthread_crs_speed);
  free_vector(pthread_mtp_crs_product);
  
  //TEST MPI PRODUCT
  CRS* mpi_crs_speed = copy_crs(crs_speed);
  printf("\nmpi crs product\n");
  init_stoper();
  Vector* mpi_mtp_crs_product = mpi_mtp_crs(mpi_crs_speed, vector_speed);
  print_stoper();
  
  //TEST MPI PRODUCT VALIDATION
  test(assert_vector(mpi_mtp_crs_product, mtp_crs_product), "mpi product validation");
  
  //TEST MPI CLEAN
  free_crs(mpi_crs_speed);
  free_vector(mpi_mtp_crs_product);
  */
  return 0;
}
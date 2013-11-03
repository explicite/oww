#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
  
  FILE *f;
  char fn[] = "data.txt";
  f = fopen(fn, "w");
  
  if(f == NULL)
  {
    printf("Error: FILE!\n");
    exit(1);
  }
  
  //TESTING
  //TEST - COMPRESS AND DECOMPRESS
  Matrix test_mtx_1 = init_matrix(10,10);
  f2(test_mtx_1,1,1,2);
  Matrix test_mtx_2 = copy_matrix(test_mtx_1);
  test(assert_matrix(test_mtx_1, test_mtx_2), "copy matrix");
  
  CRS test_crs_1 = cp_crs(test_mtx_1);
  CCS test_ccs_1 = cp_ccs(test_mtx_2);
  
  Matrix test_ucp_mtx_1 = uncp_crs(test_crs_1);
  Matrix test_ucp_mtx_2 = uncp_ccs(test_ccs_1);
  
  test(assert_matrix(test_ucp_mtx_1, test_mtx_1), "decompress crs");
  
  test(assert_matrix(test_ucp_mtx_2, test_mtx_2), "decompress ccs");
  
  test(assert_matrix(test_ucp_mtx_1, test_ucp_mtx_2), "decompress matrix");
  
  //TEST - MULTIPLICATION
  Matrix test_mtx_mtp_1 = init_matrix(10,10);
  f2(test_mtx_mtp_1,1,1,3);
  Matrix test_mtx_mtp_2 = copy_matrix(test_mtx_mtp_1);
  
  Vector test_vector_mtp = gen_vector(10, 0.1, 1);
  
  CRS test_mtp_crs = cp_crs(test_mtx_mtp_1);
  CCS test_mtp_ccs = cp_ccs(test_mtx_mtp_2);
  
  Vector test_vector_crs = mtp_crs(test_mtp_crs, test_vector_mtp);
  Vector test_vector_ccs = mtp_ccs(test_mtp_ccs, test_vector_mtp);
  
  test(assert_vector(test_vector_crs, test_vector_ccs), "product matrix");

  
  return 0;
}
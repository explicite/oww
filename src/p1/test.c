#include "test.h"

int assert_vector(Vector v1, Vector v2){
  if(v1.size != v2.size)
    return 0;
  else 
    for(int i = 0; i < v1.size; i++)
      if(v1.v[i] != v2.v[i])
	return 0;    

  return 1;
}

int assert_matrix(Matrix m1, Matrix m2){
  if(m1.m != m2.m || m1.n != m2.n)
    return 0;
  else
    for(int i = 0; i < m1.m; i++)
      for(int j = 0; j < m1.m; j++)
	if(m1.mtx[i][j] != m2.mtx[i][j])
	  return 0;
	
  return 1;
}

int assert_ccs(CCS c1, CCS c2){
  if(c1.val_size != c2.val_size || c1.col_size != c2.col_size)
    return -1;
  else {
    for(int i = 0; i < c1.val_size; i++)
      if(c1.val[i] != c2.val[i])
	return 0;
      else if(c1.row_ind[i] != c2.row_ind[i])
	return 0;
    for(int i = 0; i < c1.col_size; i++)
      if(c1.col_ptr[i] != c2.col_ptr[i])
	return 0;
  }
  return 1;
}

int assert_crs(CRS c1, CRS c2){
  if(c1.val_size != c2.val_size || c1.row_num != c2.row_num)
    return 0;
  else {
    for(int i = 0; i < c1.val_size; i++)
      if(c1.val[i] != c2.val[i])
	return 0;
      else if(c1.col_ind[i] != c2.col_ind[i])
	return 0;
    for(int i = 0; i < c1.row_num; i++)
      if(c1.row_ptr[i] != c2.row_ptr[i])
	return 0;
  }
  return 1;
}

void test(int assert, const char* desc){
  if(assert)
    printf("Test %s succed!\n", desc);
  else
    printf("Test %s failed!\n", desc);
}
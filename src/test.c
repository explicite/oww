#include "test.h"

bool assert_vector(const Vector* v1, const Vector* v2)
{
  
  register int i;
  if(v1->size != v2->size)
    return false;
  else 
    for(i = 0; i < v1->size; i++)
      if(!equal(v1->v[i], v2->v[i]))
	return false;    

  return true;
}

bool assert_matrix(const Matrix* m1, const Matrix* m2)
{
  
  register int i, j;
  if(m1->m != m2->m || m1->n != m2->n)
    return false;
  else
    for(i = 0; i < m1->m; i++)
      for(j = 0; j < m1->m; j++)
	if(!equal(m1->mtx[i+m1->n*j], m2->mtx[i+m2->n*j]))
	  return false;
	
  return true;
}

bool assert_ccs(const CCS* c1, const CCS* c2)
{

  register int i;
  if(c1->val_size != c2->val_size || c1->col_size != c2->col_size)
    return false;
  else 
  {
    for(i = 0; i < c1->val_size; i++)
      if(!equal(c1->val[i], c2->val[i]))
	return false;
      else if(!equal(c1->row_ind[i], c2->row_ind[i]))
	return false;
    for(i = 0; i < c1->col_size; i++)
      if(!equal(c1->col_ptr[i], c2->col_ptr[i]))
	return false;
  }
  
  return true;
}

bool assert_crs(const CRS* c1, const CRS* c2)
{

  register int i;
  if(c1->val_size != c2->val_size || c1->row_num != c2->row_num)
    return false;
  else 
  {
    for(i = 0; i < c1->val_size; i++)
      if(c1->val[i] != c2->val[i])
	return false;
      else if(!equal(c1->col_ind[i], c2->col_ind[i]))
	return false;
    for(i = 0; i < c1->row_num; i++)
      if(!equal(c1->row_ptr[i], c2->row_ptr[i]))
	return false;
  }
  
  return true;
}

//Diff
int diff_vector(const Vector* v1, const Vector* v2)
{
  
  if(v1->size != v2->size)
    return 1;
  
  register int i, f;
  f = 0;
  for(i = 0; i < v1->size; i++)
    if(!equal(v1->v[i], v2->v[i])){
      printf("index %d should be %.17g but found %.17g\n", i, v1->v[i], v2->v[i]);
      f++;
    }
  
  return f;  
}

int diff_matrix(const Matrix* m1, const Matrix* m2)
{
  
  if(m1->m != m2->m)
    return 1;
  
  if(m1->n != m2->n)
    return 1;
  
  register int i, j, f;
  f = 0;
  for(i = 0; i < m1->m; i++)
    for(j = 0; j < m1->n; j++)
      if(!equal(m1->mtx[i+m1->n*j], m2->mtx[i+m2->n*j])){
	printf("index %d, %d should be %.17g but found %.17g\n", i, j, m1->mtx[i+m1->n*j], m2->mtx[i+m2->n*j]);
	f++;
      }

  return f;
}

int diff_ccs(const CCS* ccs1, const CCS* ccs2)
{
  
  if(ccs1->val_size != ccs2->val_size)
    return 1;
  
  if(ccs1-> col_size != ccs2->col_size)
    return 1;
  
  register i, f;
  f = 0;
  for(i = 0; i < ccs1->val_size; i++)
  {
    if(!equal(ccs1->row_ind[i], ccs2->row_ind[i])){
      printf("row_ind %d should be %.17g but found %.17g\n", i, ccs1->row_ind[i], ccs2->row_ind[i]);
      f++;
    }
    
    if(!equal(ccs1->val[i], ccs2->val[i])){
      printf("val %d should be %.17g but found %.17g\n", i, ccs1->val[i], ccs2->val[i]);
      f++;
    }
  } 
  
  for(i = 0; i < ccs1->col_size; i++)
  {
    if(!equal(ccs1->col_ptr[i], ccs2->col_ptr[i])){
      printf("col_ptr %d should be %.17g but found %.17g\n", i, ccs1->col_ptr[i], ccs2->col_ptr[i]);
      f++;
    }
  }
  
  return 0;
}

int diff_crs(const CRS* crs1, const CRS* crs2)
{
  
  if(crs1->val_size != crs2->val_size)
    return 1;
  
  if(crs1->row_num != crs2->row_num)
    return 1;
  
  register i, f;
  f = 0;
  for(i = 0; i < crs1->val_size; i++)
  {
      if(!equal(crs1->val[i], crs2->val[i])){
	printf("val %d should be %.17g but found %.17g\n", i, crs1->val[i], crs2->val[i]);
	f++;
      }
      
      if(!equal(crs1->col_ind[i], crs2->col_ind[i])){
	printf("col_ind %d should be %.17g but found %.17g\n", i, crs1->col_ind[i], crs2->col_ind[i]);
	f++;
      }
  }
  
  for(i = 0; i < crs1->row_num; i++)
  {
    if(!equal(crs1->row_ptr[i], crs2->row_ptr[i])){
      printf("row_ptr %d should be %.17g but found %.17g\n", i, crs1->row_ptr[i], crs2->row_ptr[i]);  
      f++;
    }
  }
  
  return f;
}

//Test
void test(bool assert, const char* desc)
{

  if(assert)
    printf("Test: %s succed!\n", desc);
  else
    printf("Test: %s failed!\n", desc);

}

bool equal(double d1, double d2)
{
  
  if ((((int) (d1 * PRECISION)) / PRECISION) == (((int) (d2 * PRECISION)) / PRECISION))
    return true;
  else 
    return false;
  
}
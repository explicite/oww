#include "matrix.h"
#include "random.h"
#include "mtp_mpi.h"
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define THREAD_NUM 2

Matrix* init_matrix(int m, int n)
{
  
  srand(time(NULL));
  
  Matrix* matrix = (Matrix*) malloc(sizeof(Matrix));
  matrix->m = m;
  matrix->n = n;
  
  matrix->mtx = (double*) malloc(m*sizeof(double)*n*sizeof(double));
  
  return matrix;
}

void fprint_matrix(const Matrix* matrix, FILE* f)
{
  
  register int i, j;
  for(i = 0; i < matrix->m; i++)
  {
      for(j = 0; j < matrix->n; j++)
	fprintf(f, "%f ", matrix->mtx[i+matrix->n*j]);
      
    fprintf(f, "\n");
  }
  fprintf(f, "\n");
  
}

void print_matrix(const Matrix* matrix)
{
  
  register int i, j;
  for(i = 0; i < matrix->m; i++)
  {
      for(j = 0; j < matrix->n; j++)
	printf("%f ", matrix->mtx[i+matrix->n*j]);
    
    printf("\n");
  }
  printf("\n");
  
}

Matrix* copy_matrix(const Matrix* matrix)
{
  
  Matrix* copy = init_matrix(matrix->m, matrix->n);
  
  register int i, j;
  for(i = 0; i < matrix->m; i++)
    for(j = 0; j < matrix->n; j++)
      copy->mtx[i+copy->n*j] = matrix->mtx[i+matrix->n*j];

  return copy;
}

Vector* mtp(const Matrix* matrix, const Vector* vector)
{
  
  Vector* product = init_vector(matrix->m);
  
  register int i, j, nj;
  register double xj;
  
  register int i0, i1, i2;
  register double yi0, yi1, yi2;
  
  for(i = 0; i < matrix->m; i += 3)
  {
    i0 = i;
    i1 = i + 1;
    i2 = i + 2;
    
    yi0 = 0.0;
    yi1 = 0.0;
    yi2 = 0.0;
    
    for(j = 0; j < matrix->n; j++)
    {     
      nj=matrix->n*j;
      xj=vector->v[j];
      yi0+=matrix->mtx[i0+nj]*xj;
      yi1+=matrix->mtx[i1+nj]*xj;
      yi2+=matrix->mtx[i2+nj]*xj;
    }
    
    product->v[i0]=yi0;
    product->v[i1]=yi1;
    product->v[i2]=yi2;
  }
  
  return product;
}

//Sparse matrix initializers
void band(Matrix* matrix, int k, int w)
{
  
  register int i, j, x;
  for(i = 0; i < matrix->m; i++)
  {
    for(j = 0; j < matrix->n; j++)
    {
      if(j <= (w+i+k) && j >= (w+i-k))
      {
	for(x = (w+i-k);x < (w+i+k); x++)
	  matrix->mtx[i+matrix->n*j] = next(1,2);
      }
      else
      {
	matrix->mtx[i+matrix->n*j] = next(0,1.0/(matrix->n*matrix->m));
      }
    }
  }
  
}

void f1(Matrix* matrix, int k)
{ 
  
  band(matrix, k, 1);
  
}

void f2(Matrix* matrix, int k, int w, int z)
{ 
  
  band(matrix, k, w);
  zero_row(matrix, z);
  
}

void f3(Matrix* matrix, int k)
{
  
  band(matrix, k, 1);
  
}

void f4(Matrix* matrix, int k, int w, int z)
{
  
  band(matrix, k, w);
  zero_collumn(matrix, z);

}

//Zero row
void zero_row(Matrix* matrix, int k)
{
  
  register int r, z;
  for(r = 0; r < matrix->n; r++)
  {
    z = 0;
    while(z < k)
    {
      int i = rand()/(RAND_MAX/matrix->m);
      if(matrix->mtx[r+matrix->n*i] > 0 && matrix->mtx[r+matrix->n*i] < 1)
      {
	matrix->mtx[r+matrix->n*i] = 0;
	z++;
      }
    }
  }
  
}

//Zero collumn
void zero_collumn(Matrix* matrix, int k)
{ 
  
  register int c, z;
  for(c = 0; c < matrix->m; c++)
  {
    z = 0;
    while(z < k)
    {
      int i = rand()/(RAND_MAX/matrix->n);
      if(matrix->mtx[i+matrix->n*c] > 0 && matrix->mtx[i+matrix->n*c] <= 1)
      {
	matrix->mtx[i+matrix->n*c] = 0;
	z++;
      }
    }
  }
  
}

//Non zero
int non_zero(const Matrix* matrix)
{
  
  register int z, i, j;
  z = 0;
  for(i = 0; i < matrix->m; i++)
    for(j = 0; j < matrix->n; j++)
      if(matrix->mtx[i+matrix->n*j] > 0)
	z++;
  
  return z;
}

//CCS
CCS* init_CCS(int val_size, int col_size)
{

  CCS* ccs = (CCS*) malloc(sizeof(CCS));
  ccs->val_size = val_size;
  ccs->val = (double*) malloc(ccs->val_size*sizeof(double));
  ccs->row_ind = (int*) malloc(ccs->val_size*sizeof(int));
  ccs->col_size = col_size;
  ccs->col_ptr = (int*) malloc(ccs->col_size*sizeof(int));
  
  return ccs;
}

CCS* cp_ccs(const Matrix* matrix)
{

  CCS* ccs = init_CCS(non_zero(matrix), matrix->n+1);
  
  int val_num = 0;
  int f_in_col = 1;
  
  register int i, j;
  for(i = 0; i < matrix->m; i++)
  {
    for(j = 0; j < matrix->n; j++)
    {
      if(matrix->mtx[j+matrix->n*i] > 0)
      {
	ccs->val[val_num] = matrix->mtx[j+matrix->n*i];
	ccs->row_ind[val_num] = j;
	
	if(f_in_col == 1)
	{
	  ccs->col_ptr[i] = val_num;
	  f_in_col = 0;
	}
	val_num++;
      }
    }
    f_in_col = 1;
  }
  
  ccs->col_ptr[matrix->n]=ccs->val_size;
  
  return ccs;
}

Matrix* uncp_ccs(const CCS* ccs)
{

  Matrix* mtx = init_matrix(ccs->col_size-1,ccs->col_size-1);
   
   register int i, j;
   for(i = 0; i < ccs->col_size-1; i++)
    for(j = ccs->col_ptr[i]; j < ccs->col_ptr[i+1]; j++)
      mtx->mtx[ccs->row_ind[j]+mtx->n*i] = ccs->val[j]; 
      
  return mtx;
}

void fprint_ccs(const CCS* ccs, FILE* f)
{
  
  register int i;
  for(i = 0; i < ccs->val_size; i++)
    fprintf(f, "%f ", ccs->val[i]);
 
  fprintf(f, "\n");
  
  for(i = 0; i < ccs->val_size; i++)
    fprintf(f, "%d ", ccs->row_ind[i]);
  
  fprintf(f, "\n");
  
  for(i = 0; i < ccs->col_size; i++)
    fprintf(f, "%d ", ccs->col_ptr[i]);
  
  fprintf(f, "\n\n");
  
}

void print_ccs(const CCS* ccs)
{
  
  register int i;
  for(i = 0; i < ccs->val_size; i++)
    printf("%f ", ccs->val[i]);
  
  printf("\n");
  
  for(i = 0; i < ccs->val_size; i++)
    printf("%d ", ccs->row_ind[i]);
  
  printf("\n");
  
  for(i = 0; i < ccs->col_size; i++)
    printf("%d ", ccs->col_ptr[i]);
  
  printf("\n\n");
  
}

CCS* copy_ccs(const CCS* oryg)
{

  CCS* ccs = init_CCS(oryg->val_size, oryg->col_size);
  
  register int i;
  for(i = 0; i < oryg->val_size; i++)
  {
    ccs->val[i] = oryg->val[i];
    ccs->row_ind[i] = oryg->row_ind[i];
  }
  
  for(i = 0; i < oryg->col_size; i++)
    ccs->col_ptr[i] = oryg->col_ptr[i];
  
  return ccs;
}

Vector* mtp_ccs(const CCS* ccs, const Vector* vector)
{

  Vector* product = init_vector(vector->size);
 
  register int i, j;
  for(i = 0; i < vector->size; i++)
    for(j = ccs->col_ptr[i]; j < ccs->col_ptr[i+1]; j++)
      product->v[ccs->row_ind[j]] += ccs->val[j] * vector->v[i]; 
 
  return product;
}

Vector* openmp_mtp_ccs(const CCS* ccs, const Vector* vector)
{
  
  Vector* product = init_vector(vector->size);
 
  register int i, j;
  #pragma omp parallel for schedule(static) private(i, j)
  for(i = 0; i < vector->size; i++)
    for(j = ccs->col_ptr[i]; j < ccs->col_ptr[i+1]; j++)
      product->v[ccs->row_ind[j]] += ccs->val[j] * vector->v[i]; 
  
  return product;
}

Vector* pthread_mtp_ccs(CCS* ccs, Vector* vector)
{
  
  pthread_t* threads = (pthread_t*) malloc(sizeof(pthread_t)*THREAD_NUM);
  
  Vector* product = init_vector(vector->size);
  
  CCS_Slice* slice = (CCS_Slice*) malloc(sizeof(CCS_Slice)*THREAD_NUM);
  register int i;
  for(i = 0; i < THREAD_NUM; i++){
    slice[i].thread_id = i;
    slice[i].ccs = ccs;
    slice[i].vector = vector;
    slice[i].product = product;
  }
  
  for(i = 0; i < THREAD_NUM; i++)
    pthread_create(&threads[i], NULL, pthread_mtp_ccs_slice, (void*) &slice[i]);
  
  for(i = 0; i < THREAD_NUM; i++)
    pthread_join(threads[i], NULL);
  
  free(threads);
  free(slice);
  
  return product;
}

Vector* opencl_mtp_ccs(const CCS* ccs, const Vector* vector)
{
  
  Vector* product = init_vector(vector->size);
  //TODO
  
  return product;
}

//CRS
CRS* init_CRS(int val_size, int row_num)
{

  CRS* crs = (CRS*) malloc(sizeof(CRS));
  crs->val_size = val_size; 
  crs->val = (double*) malloc(crs->val_size*sizeof(double));
  crs->col_ind = (int*) malloc(crs->val_size*sizeof(int));
  crs->row_num = row_num;
  crs->row_ptr = (int*) malloc(crs->row_num*sizeof(int));
  
  return crs;
}

CRS* cp_crs(const Matrix* matrix)
{

  CRS* crs = init_CRS(non_zero(matrix), matrix->m+1);
  
  register int val_num = 0;
  register int f_in_row = 1;
  register int i, j;
  
  for(i = 0; i < matrix->m; i++)
  {
    for(j = 0; j < matrix->n; j++)
    {
      if(matrix->mtx[i+matrix->n*j] > 0)
      {
	crs->val[val_num] = matrix->mtx[i+matrix->n*j];
	crs->col_ind[val_num] = j;
	
	if(f_in_row == 1)
	{
	  crs->row_ptr[i] = val_num;
	  f_in_row = 0;
	}
	val_num++;
      }
    }
    f_in_row = 1;
  }
  
  crs->row_ptr[matrix->m]=crs->val_size;
  
  return crs;
}

Matrix* uncp_crs(const CRS* crs)
{

  Matrix* mtx = init_matrix(crs->row_num-1,crs->row_num-1);
  
  register int i, j;
  for(i = 0; i < crs->row_num-1; i++)
    for(j = crs->row_ptr[i]; j < crs->row_ptr[i+1]; j++)
      mtx->mtx[i+mtx->n*crs->col_ind[j]] = crs->val[j];
  
 return mtx;
}

void fprint_crs(const CRS* crs, FILE* f)
{

  register int i;
  for(i = 0; i < crs->val_size; i++)
    fprintf(f, "%f ", crs->val[i]);
  
  fprintf(f, "\n");
  
  for(i = 0; i < crs->val_size; i++)
    fprintf(f, "%d ", crs->col_ind[i]);
  
  fprintf(f, "\n");
  
  for(i = 0; i < crs->row_num; i++)
    fprintf(f, "%d ", crs->row_ptr[i]);
  
  fprintf(f, "\n\n");
  
}

void print_crs(const CRS* crs)
{

  register int i;
  for(i = 0; i < crs->val_size; i++)
    printf("%f ", crs->val[i]);
  
  printf("\n");
  
  for(i = 0; i < crs->val_size; i++)
    printf("%d ", crs->col_ind[i]);
  
  printf("\n");	
  
  for(i = 0; i < crs->row_num; i++)
    printf("%d ", crs->row_ptr[i]);
  
  printf("\n\n");
  
}

CRS* copy_crs(const CRS* oryg)
{

  CRS* crs = init_CRS(oryg->val_size, oryg->row_num);
  
  register int i;
  for(i = 0; i < oryg->val_size; i++)
  {
    crs->val[i] = oryg->val[i];
    crs->col_ind[i] = oryg->col_ind[i];
  }
  
  for(i = 0; i < oryg->row_num; i++)
    crs->row_ptr[i] = oryg->row_ptr[i];
  
  return crs;
}

Vector* mtp_crs(const CRS* crs, const Vector* vector)
{
  
  Vector* product = init_vector(vector->size);
 
  register int i, j;
  for(i = 0; i < vector->size; i++)
    for(j = crs->row_ptr[i]; j < crs->row_ptr[i+1]; j++)
      product->v[i] += crs->val[j] * vector->v[crs->col_ind[j]];
  
  return product;
}

Vector* openmp_mtp_crs(const CRS* crs, const Vector* vector)
{

  Vector* product = init_vector(vector->size);
  
  register int i, j;
  #pragma omp parallel for schedule(static) private(i, j)
  for(i = 0; i < vector->size; i++)
    for(j = crs->row_ptr[i]; j < crs->row_ptr[i+1]; j++)
      product->v[i] += crs->val[j] * vector->v[crs->col_ind[j]];
  
  return product;
}

Vector* pthread_mtp_crs(CRS* crs, Vector* vector)
{
  
  pthread_t* threads = (pthread_t*) malloc(sizeof(pthread_t)*THREAD_NUM);
  
  Vector* product = init_vector(vector->size);
  
  CRS_Slice* slice = (CRS_Slice*) malloc(sizeof(CRS_Slice)*THREAD_NUM);
  register int i;
  for(i = 0; i < THREAD_NUM; i++){
    slice[i].thread_id = i;
    slice[i].crs = crs;
    slice[i].vector = vector;
    slice[i].product = product;
  }
  
  for(i = 0; i < THREAD_NUM; i++)
    pthread_create(&threads[i], NULL, pthread_mtp_crs_slice, (void*) &slice[i]);
  
  for(i = 0; i < THREAD_NUM; i++)
    pthread_join(threads[i], NULL);
  
  free(threads);
  free(slice);
  
  return product;
}


Vector* mpi_mtp_crs(CRS* crs, Vector* vector)
{
#ifdef MPI
  return mtp_mpi(crs, vector);
#else
  return vector;
#endif
}


Vector* opencl_mtp_crs(const CRS* crs, const Vector* vector)
{
 
  Vector* product = init_vector(vector->size);
  //TODO
  
  return product;
}

//Util
int max_int(int* array, int size)
{

  register int max = array[0];
  
  register int i;
  for(i = 1; i < size; i++)
    if(array[i] > max)
      max = array[i];
  
  return max;
}

//pthread
void* pthread_mtp_crs_slice(void* s)
{

  CRS_Slice* slice = (CRS_Slice*) s;
  register int start = (slice->thread_id*slice->vector->size)/THREAD_NUM;
  register int stop = ((slice->thread_id+1)*slice->vector->size)/THREAD_NUM;
  
  register int i, j;
  for(i = start; i < stop; i++)
    for(j = slice->crs->row_ptr[i]; j < slice->crs->row_ptr[i+1]; j++)
      slice->product->v[i] += slice->crs->val[j] * slice->vector->v[slice->crs->col_ind[j]];
    
}

void* pthread_mtp_ccs_slice(void* s)
{
  
  CCS_Slice* slice = (CCS_Slice*) s;
  register int start = (slice->thread_id*slice->vector->size)/THREAD_NUM;
  register int stop = ((slice->thread_id+1)*slice->vector->size)/THREAD_NUM;
  
  register int i, j;
  for(i = start; i < stop; i++)
    for(j = slice->ccs->col_ptr[i]; j < slice->ccs->col_ptr[i+1]; j++)
      slice->product->v[slice->ccs->row_ind[j]] += slice->ccs->val[j] * slice->vector->v[i]; 
  
}

//Clean up
void free_vector(Vector* vector)
{
  
  free(vector->v);
  free(vector);

}

void free_matrix(Matrix* matrix)
{  
  
  free(matrix->mtx);
  
  free(matrix);
  
}

void free_ccs(CCS* ccs)
{
  
  free(ccs->val);
  free(ccs->row_ind);
  free(ccs->col_ptr);
  free(ccs);
  
}

void free_crs(CRS* crs)
{
  
  free(crs->val);
  free(crs->col_ind);
  free(crs->row_ptr);
  free(crs);
  
}
#include "mtp_mpi.h"
#include "mpi.h"
#include <stdio.h>

Vector* mtp_mpi(CRS* crs, Vector* vector)
{
  int numtask, rank, len, rc;
  char hostname[MPI_MAX_PROCESSOR_NAME];
  
  rc = MPI_Init(NULL, NULL);

  
  if(rc != MPI_SUCCESS){
    printf("Error starting MPI subprogram. Terminating.\n");
    MPI_Abort(MPI_COMM_WORLD, rc);
  }
  
  MPI_Comm_size(MPI_COMM_WORLD, &numtask);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Get_processor_name(hostname, &len);
  
  if(rank == 0)
  {  
    printf("Number of tasks= %d My rank= %d Runnung on %s\n", numtask, rank, hostname);
    
    register unsigned i, j;
    
    //CRS
    
    //index
    int val_size = crs->val_size;
    int row_num = crs->row_num;
    MPI_Bcast(&val_size, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&row_num, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
    //data
    double val[val_size];
    int col_ind[val_size];
    
    for(i = 0; i < val_size; i++){
      val[i] = crs->val[i];
      col_ind[i] = crs->col_ind[i];
    }
    
    MPI_Bcast(&val[0], val_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&col_ind[0], val_size, MPI_INT, 0, MPI_COMM_WORLD);
   
    int row_ptr[row_num];
    for(i = 0; i < row_num; i++)
      row_ptr[i] = crs->row_ptr[i];
   
    MPI_Bcast(&row_ptr[0], row_num, MPI_INT, 0, MPI_COMM_WORLD);
    
    //Vector
    
    //index
    int size = vector->size;
    MPI_Bcast(&size, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
    //data
    double v[size];
    for(i = 0; i < size; i++)
      v[i] = vector->v[i];
    
    MPI_Bcast(&v[0], size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    
    Vector* product = init_vector(vector->size);
    
    for(i = 1; i < numtask; i++)
    {
      register unsigned start = ((i-1)*vector->size)/(numtask-1);
      register unsigned stop = (i*vector->size)/(numtask-1);
      printf("start %d stop %d\n", start, stop);
      double p[stop-start];
      
      MPI_Recv(&p, stop-start, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      
      for(j = 0; j < stop - start; j++){
	product->v[start+j] = p[j];
      }
    }
    
    return product;
  } else { 
    //CRS
    
    //index 
    int val_size;
    int row_num;
   
    MPI_Bcast(&val_size, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&row_num, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
    //data
    double val[val_size];
    MPI_Bcast(&val, val_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    
    int col_ind[val_size];
    MPI_Bcast(&col_ind, val_size, MPI_INT, 0, MPI_COMM_WORLD);
    
    int row_ptr[row_num];
    MPI_Bcast(&row_ptr, row_num, MPI_INT, 0, MPI_COMM_WORLD);
    
    //Vector
    
    //index
    int size;
    MPI_Bcast(&size, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
    //data
    double v[size];
    MPI_Bcast(&v, size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    
    //computation
    register unsigned start = ((rank-1)*size)/(numtask-1);
    register unsigned stop = (rank*size)/(numtask-1);
    
    //product
    double p[stop-start];
    
    register unsigned i, j;
    for(i = start; i < stop; i++)
      for(j = row_ptr[i]; j < row_ptr[i+1]; j++)
	p[i-start] += val[j] * v[col_ind[j]];
      
    MPI_Send(&p[0], stop-start, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
  }
  
  MPI_Finalize();
}
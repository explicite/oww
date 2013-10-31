typedef struct {
  double* val;
  int* row_ind;
  int val_size;
  
  int* col_ptr;
  int col_size; 
} CCS;

typedef struct {
  double* val;
  int* col_ind;
  int val_size;
  
  int* row_ptr;
  int row_num;
} CRS;

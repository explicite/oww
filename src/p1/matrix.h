
typedef struct {
  double** mtx;
  int m;
  int n;
  
} Matrix;

Matrix init(int, int);
void print(Matrix);

//Compress sparse matrix
//Compressed Row Storage
typedef struct {
  double* val;
  double* col_ind;
  int val_size;
  
  double* row_ptr;
  int row_size;
} CRS;

CRS* cp_crs(Matrix*);
Matrix* uncp_crs(CRS*);

//Compressed Colum storage
typedef struct {
  double* val;
  double* row_ind;
  int val_size;
  
  double* col_ptr;
  int col_size; 
} CCS;

CCS* cp_css(Matrix*);
Matrix* uncp_css(CCS*);

//Sparse matrix initializers
void f1(Matrix, int);
void f2(Matrix, int, int);
void f3(Matrix, int);
void f4(Matrix, int, int);

//Clean up
void clean(Matrix*);

//Random
double next(double, double);

//Diagonal
int diagonal(int, int, int, int);
typedef struct {
  double* v;
  int size;
} Vector;

Vector init_vector(int);
Vector gen_vector(int,int,int);
void print_vector(Vector);

typedef struct {
  double* v;
  int size;
} Vector;

Vector* init_vector(int);
Vector* gen_vector(int,double,double);
void print_vector(const Vector*);

#include "matrix.h"

#define PRECISION 10000.0
//0 == true
int assert_vector(const Vector*, const Vector*);
int assert_matrix(const Matrix*, const Matrix*);
int assert_ccs(const CCS*, const CCS*);
int assert_crs(const CRS*, const CRS*);

//Diff
int diff_vector(const Vector*, const Vector*);
int diff_matrix(const Matrix*, const Matrix*);
int diff_ccs(const CCS*, const CCS*);
int dif_crs(const CRS*, const CRS*);

//Test
void test(int, const char*);

//Util
double tr(double);
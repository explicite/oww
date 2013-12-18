#include "matrix.h"
#include "bool.h"

#define PRECISION 10000.0
//0 == true
bool assert_vector(const Vector*, const Vector*);
bool assert_matrix(const Matrix*, const Matrix*);
bool assert_ccs(const CCS*, const CCS*);
bool assert_crs(const CRS*, const CRS*);

//Diff
int diff_vector(const Vector*, const Vector*);
int diff_matrix(const Matrix*, const Matrix*);
int diff_ccs(const CCS*, const CCS*);
int dif_crs(const CRS*, const CRS*);

//Test
void test(bool, const char*);
bool equal(double, double);
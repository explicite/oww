#include "matrix.h"
//0 == true
int assert_vector(const Vector*, const Vector*);
int assert_matrix(const Matrix*, const Matrix*);
int assert_ccs(const CCS*, const CCS*);
int assert_crs(const CRS*, const CRS*);

//Test
void test(int, const char*);
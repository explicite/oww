#include "matrix.h"
#include <stdio.h>

int main(){
  Matrix m_1 = init(10,10);
  f1(m_1,0);
  print(m_1);
  
  Matrix m_2 = init(10,10);
  f4(m_2,0,3);
  //print(m_2);
  return 0;
}
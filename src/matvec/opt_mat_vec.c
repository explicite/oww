#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void opt_mat_vec(double* a, double* x, double* y, int n)
{
  register int i, j, nj;
  register double xj;
  
  register int i0, i1, i2, i3, i4, i5, i6, i7, i8, i9, i10, i11;
  register double yi0, yi1, yi2, yi3, yi4, yi5, yi6, yi7, yi8, yi9, yi10, yi11;
  
  for(i=0;i<n;i+=12){
	  
    i0=i;
    i1=i+1;
    i2=i+2;
    i3=i+3;
    i4=i+4;
    i5=i+5;
    i6=i+6;
    i7=i+7;
    i8=i+8;
    i9=i+9;
    i10=i+10;
    i11=i+11;
    
    yi0=0.0;
    yi1=0.0;
    yi2=0.0;
    yi3=0.0;
    yi4=0.0;
    yi5=0.0;
    yi6=0.0;
    yi7=0.0;
    yi8=0.0;
    yi9=0.0;
    yi10=0.0;
    yi11=0.0;
    
    for(j=0;j<n;j++){     
	  nj=n*j;
	  xj=x[j];
	  yi0+=a[i0+nj]*xj;
	  yi1+=a[i1+nj]*xj;
	  yi2+=a[i2+nj]*xj;
	  yi3+=a[i3+nj]*xj;
	  yi4+=a[i4+nj]*xj;
	  yi5+=a[i5+nj]*xj;
	  yi6+=a[i6+nj]*xj;
	  yi7+=a[i7+nj]*xj;
	  yi8+=a[i8+nj]*xj;  
	  yi9+=a[i9+nj]*xj;  
	  yi10+=a[i10+nj]*xj;  
	  yi11+=a[i11+nj]*xj;  
    }
    
    y[i0]=yi0;
    y[i1]=yi1;
    y[i2]=yi2;
    y[i3]=yi3;
    y[i4]=yi4;
    y[i5]=yi5;
    y[i6]=yi6;
    y[i7]=yi7;
    y[i8]=yi8;
    y[i9]=yi9;
    y[i10]=yi10;
    y[i11]=yi11;
    
  }
}

#include <stdio.h>
#include <math.h>

int root(double a, double b, double c, double *x1, double *x2)
{
double D=b*b-4*a*c;
	    if (D<0) return 0;
			else if (D==0) 
				{
					*x1=((-b)/(2*a));
					return 1;
				}
				else if (D>0) 
					{
						*x1=(((-b)+(sqrt(D)))/(2*a));
						*x2=(((-b)-(sqrt(D)))/(2*a));
						return 2;
					}
}

int main()
{
  double a,b,c,r,x1,x2;
  printf ("Enter coefficients:");
  scanf ("\n %lf%lf%lf", &a,&b,&c);
  r=root(a,b,c,&x1,&x2);
  if (r==0) printf("There is no real roots");
	else if (r==1) printf("The root is %lf ", x1);
		else if (r==2) printf("The roots is %lf %lf", x1,x2);

  return 0;
}
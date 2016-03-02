#include <stdio.h>
#include <math.h>
#include <limits.h>

int skal (int* arr, int* brr, int n)
{ int s = 0;
  int count;
for (count = 0; count < n; count ++)
 s = s + ( arr[count] * brr[count]);
printf("%d\n", s);
return s;
}

int dl (int* arr,int n)
{ int d = 0;
  int count;
for (count = 0; count < n; count ++)
 d = d + (arr[count]*arr[count]);
 d = sqrt(d);
printf("%d\n", d);
return d;
}


int Cal (int* arr, int* brr, int n)
{ int cos1;
  int cos2;
  int d;
  int s;
d = (dl (arr, n)) * (dl (brr, n));
s = skal ( arr, brr, n);
cos1 = s / d;
cos2 = s % d;

if ( (cos1 == 1)&&(cos2 == 0) )
    return 1; 
 else { if ( (cos1 == - 1)&&(cos2 == 0) ) 
     return 1;
 else return 0; }
 }
    

int main ()

{
int r;
  int arr[5];
	arr[0]=1;
	arr[1]=2;
	arr[2]=3;
	arr[3]=5;
	arr[4]=0;
 
  int brr[5];
     brr[0]= 1;
     brr[1]= 2;
     brr[2]= 3;
     brr[3]= 5;
     brr[4]= 0;

	 r=Cal(arr, brr, 5);
if (r == 0) printf("No");
else printf("yes");

return 0;

}
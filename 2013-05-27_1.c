#include <stdio.h>

int fact (int n)
{
  if (n <= 0)
    return 1;
  else
    return n*fact(n-1);
}

int main()
{
  int k, f;
  printf ("Enter an integer: ");
  scanf ("%d", &k);
  f = fact(k);

  printf ("%d! = %d, %d! = %d\n", 
    k, f, k+1, fact(k+1));

  return 0;
}








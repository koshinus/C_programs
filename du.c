#include <stdio.h>

int main()
{
  int a;
  printf ("Enter signed integer: ");
  scanf ("%d", &a);
  printf ("%u\n", a);
  
  unsigned int b;
  printf ("Enter unsigned integer: ");
  scanf ("%u", &b);
  printf ("%d\n", b);
  
  return 0;
}
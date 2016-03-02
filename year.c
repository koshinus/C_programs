#include <stdio.h>

int main ()
{
  int n;
  printf ("Enter a year: ");
  scanf ("%d", &n);

  // multiple 400 or (multimple 4 and not multiple 100)
  if (n%400 == 0 || (n%4 == 0 && n%100 != 0))
  {
    printf ("The year %d is leap\n", n);
  }
  else
  {
    printf ("The year %d is not leap\n", n);
  }
  return 0;
}
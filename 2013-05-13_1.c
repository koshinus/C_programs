#include <stdio.h>

int main()
{
  int val = 2;
  int *addr = &val;

  printf ("#1: val = %d\n", val);

  val = 2 * *addr;
  printf ("#2: val = %d\n", val);

  *addr = val + 1;
  printf ("#3: val = %d\n", val);

  printf ("#4: addr = %X\n", addr);

  return 0;
}

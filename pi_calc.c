#include <stdio.h>

double great(double num)
{
	return (num > 0)? num : -num;
}

double find_pi()
{
	double real_pi = 3.14159265358979;
	double my_pi = 0;
	double step_sign = 1;
	unsigned long long i = 1;
	while(great(real_pi - my_pi) > 0.00000001)
	{
		my_pi += 4.0/i * step_sign;
		step_sign *= -1;
		i += 2;
		printf("%lf\n", my_pi);
	}
	return my_pi;
}

int main(void) 
{
	// your code goes here
	printf("%lf", find_pi());
	return 0;
}

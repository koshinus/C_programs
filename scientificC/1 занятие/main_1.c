#include <stdio.h>
#include <string.h>
#include <math.h>

void reverse(char s[])
{
	int i, j;
	char c;
	
	for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
	{
		c = s[i];
		s[i] = s[j];
		s[j] = c;	
	}	
}

void itoa(int n, char s[])
{
	int i, sign;
	
	if ((sign = n) < 0)
		n = -n;
	i = 0;
	do
	{
		s[i++] = n % 10 + '0';	
	}
	while ((n /= 10) > 0);
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);			
}

void main()
{
//------------------------------------------------		
	int xMax, yMax, nFrames;
	
	printf("Amount of points (vertical and horizontal) ""x y"": ");
	scanf("%d %d", &xMax, &yMax);
	printf("Amount of frames: ");
	scanf("%d", &nFrames);
//------------------------------------------------

	const int NPoints = xMax * yMax;
	const int NCells = (xMax - 1) * (yMax - 1);
	int i, x, y;
	char fileName[15];
	char nStr[6];
	FILE* vtk_out;
	
	for (i = 0; i < nFrames; ++i)
	{
		itoa(i, nStr);
		fileName[0] = '\0';
		strcat(fileName, "frame");
		strcat(fileName, nStr);
		strcat(fileName, ".vtk");
		vtk_out = fopen(fileName, "w");
		
		fprintf(vtk_out, "# vtk DataFile Version 2.0\n");
		fprintf(vtk_out, "Unstructured Grid Example\n");
		fprintf(vtk_out, "ASCII\n");
		fprintf(vtk_out, "DATASET UNSTRUCTURED_GRID\n\n");
		fprintf(vtk_out, "POINTS %d %s\n", NPoints, "float");

		for (y = 0; y < yMax; ++y)
			for (x = 0; x < xMax; ++x)
				fprintf(vtk_out, "%d %d %f\n", x, y, sin(y + i * 2 * 3.14 / nFrames));
		
		fprintf(vtk_out, "\nCELLS %d %d\n", NCells, 5 * NCells);
	
		for (y = 0; y < yMax - 1; ++y)
			for (x = 0; x < xMax - 1; ++x)
				fprintf(vtk_out, "4 %d %d %d %d\n", y * xMax + x, y * xMax + x + 1, (y + 1) * xMax + x, (y + 1) * xMax + x + 1);
	
		fprintf(vtk_out, "\nCELL_TYPES %d\n", NCells);

		for (x = 0; x < NCells; ++x)
			fprintf(vtk_out, "8 ");

		fclose(vtk_out);
	}
}

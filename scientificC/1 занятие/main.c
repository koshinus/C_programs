#include <stdio.h>

main(){

	FILE* vtk_out = fopen("plane.vtk", "w");

	fprintf(vtk_out, "# vtk DataFile Version 2.0\n"); // так и оставляем
	fprintf(vtk_out, "Unstructured Grid Example\n");  // пишем сюда свое описание (на английском) в одну строку
	fprintf(vtk_out, "ASCII\n"); // так и оставляем
	fprintf(vtk_out, "DATASET UNSTRUCTURED_GRID\n"); // так и оставляем, это значет что дальше идет описание неструктурированной сетки
	printf("Enter the number of points: ");
	int n;
	scanf("%d", n);
	fprintf(vtk_out, "POINTS %d %s\n", n, "float"); // описание точек: количество точек и их тип.
	printf("Enter the number of points: ");
	fprintf(vtk_out, "0 0 0\n"); // координаты точек x, y, z
	fprintf(vtk_out, "0 1 0\n");
	fprintf(vtk_out, "1 0 0\n");
	fprintf(vtk_out, "1 1 0\n");
	fprintf(vtk_out, "CELLS %d %d\n", 1, 5); // Описание ячеек: кол-во ячеек, кол-во чисел в этом блоке вообще
	fprintf(vtk_out, "4 0 1 2 3\n");
	fprintf(vtk_out, "CELL_TYPES %d\n", 1); // Типы ячеек, пишем количество ячеек
	fprintf(vtk_out, "8\n"); // нам нужно написать 8 для каждой ячейки

	fclose(vtk_out);

}

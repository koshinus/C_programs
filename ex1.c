#include <stdio.h>
#include <windows.h>
#include <conio.h>
main()
{

int i,j; // счетчики циклов: внешнего и внутреннего
/*char str[50];
// Очистить экран
textbackground(4);
textcolor(15);
clrscr();*/

// Внешний цикл
for(i=1;i<10;i++)
{

// Внутренний цикл
for(j=1;j<5;j++)
{
printf("%d * %d = %d", i, j, i*j);
printf("\n");
}

printf("\n");
}

/*CharToOem("\nДля выхода нажмите любую клавишу", str);
printf(str);
getch();*/
return 0;
}
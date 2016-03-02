#include <stdio.h>
#include <conio.h>
//#include <string.h>
//#include <stdlib.h>
 
int main()
{
	int bal;
	FILE *f;
	
	if ((f = fopen("3.txt","wb")) == NULL)
		printf("Impossible to open or make file\n");
	else
		{
			for(int i=0;i<5;i++)
				{
				scanf("%d",&bal);
				fwrite (&bal,sizeof(int),1,f);
				}
		}		
		fclose(f);
		getch();
	return 0;
}	
/*int main()
{
	int n;
	n = 2365;
    FILE *fp;
    size_t count;
    //char const *str = n;
 
    fp = fopen("example.txt", "wb+");
    if(fp == NULL) 
	{
        perror("error of open example.txt");
        return EXIT_FAILURE;
    }
    count = fwrite(&n, sizeof(int), 4, fp);
    printf("Write %lu byte. fclose(fp) %s.\n", (unsigned long)count, fclose(fp) == 0 ? "successful" : "with error");
 
    return 0;
}*/
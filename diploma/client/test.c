#include <stdio.h>

int main()
{
    char option[1];
    char message[256];
    while(1)
    {
        scanf("%s", option);
        //printf("%c\n", option[0]);
        switch(option[0])
        {
            case 'a':
            {
                printf("A-Case\n");
                scanf("%s: ", message);
                printf("%s\n", message);
                break;
            }
            case 'p':
            {
                printf("P-Case\n");
                scanf("%s: ", message);
                printf("%s\n", message);
                break;
            }
            case 't':
            {
                printf("T-Case\n");
                scanf("%s: ", message);
                printf("%s\n", message);
                break;
            }
            default:
            {
                return 0;
            }
        }
    }
    return 0;
}

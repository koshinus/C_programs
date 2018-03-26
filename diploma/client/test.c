#include <stdio.h>

int main()
{
    uint64_t id, len, offset;
    char * target_machine_addr;
    uint16_t target_machine_port;
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
                printf("Print block id: ");
                scanf("%lu", &id);
                printf("Print block len: ");
                scanf("%lu", &len);
                break;
            }
            case 'p':
            {
                printf("P-Case\n");
                scanf("%s: ", message);
                printf("%s\n", message);
                printf("Print block id: ");
                scanf("%lu", &id);
                printf("Print block len: ");
                scanf("%lu", &len);
                printf("Print offset in block: ");
                scanf("%lu", &offset);
                break;
            }
            case 't':
            {
                printf("T-Case\n");
                scanf("%s: ", message);
                printf("%s\n", message);
                printf("Print block id: ");
                scanf("%lu", &id);
                printf("Print block len: ");
                scanf("%lu", &len);
                printf("Print offset in block: ");
                scanf("%lu", &offset);
                printf("Print ip address of target machine: ");
                scanf("%s", target_machine_addr);
                printf("Print port of target machine: ");
                scanf("%hu", &target_machine_port);
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

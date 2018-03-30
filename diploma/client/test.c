#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
    char st[16];
    struct in_addr addr;
    scanf("%s", st);
    inet_aton(st, &addr);
    printf("%d\n", addr.s_addr);
    printf("%d\n", be32toh(addr.s_addr));
    return 0;
}

#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

uint32_t parseIPV4string(char* ipAddress)
{
    char ipbytes[4];
    sscanf(ipAddress, "%u.%u.%u.%u", &ipbytes[3], &ipbytes[2], &ipbytes[1], &ipbytes[0]);
    return ipbytes[0] | ipbytes[1] << 8 | ipbytes[2] << 16 | ipbytes[3] << 24;
}

int main()
{
    /*
    char ipv4_addr[16];
    //printf("%u\n", (uint32_t)(-1));
    scanf("%s", ipv4_addr);
    printf("%s\n", ipv4_addr);
    printf("%u\n", parseIPV4string(ipv4_addr));
    */
    uint32_t ipv4_addr[4];
    scanf("%u.%u.%u.%u", &ipv4_addr[3], &ipv4_addr[2], &ipv4_addr[1], &ipv4_addr[0]);
    uint32_t ipv4 = (uint32_t)(-1) + (ipv4_addr[0] | ipv4_addr[1] << 8 | ipv4_addr[2] << 16 | ipv4_addr[3] << 24) + 1;
    printf("%u\n", ipv4);
    return 0;
}

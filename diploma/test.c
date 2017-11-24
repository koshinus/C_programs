#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <cstring>
using namespace std;

void fill_buffer(char * buf, uint64_t first, uint64_t second, char * addr, uint8_t addr_len, const char * data)
{
    if(addr)
    {
        buf[0] = 't';
        strncpy(buf + sizeof('t') + sizeof(first) + sizeof(second), addr, addr_len);
        strcpy (buf + sizeof('t') + sizeof(first) + sizeof(second) + addr_len, data);
    }
    else
    {
        buf[0] = 'p';
        strcpy(buf + sizeof('p') + sizeof(first) + sizeof(second), data);
    }
    
	buf[8] = (first >> 56) & 0xFF;
	buf[7] = (first >> 48) & 0xFF;
	buf[6] = (first >> 40) & 0xFF;
	buf[5] = (first >> 32) & 0xFF;
	buf[4] = (first >> 24) & 0xFF;
	buf[3] = (first >> 16) & 0xFF;
	buf[2] = (first >> 8 ) & 0xFF;
	buf[1] =  first        & 0xFF;

	buf[16] = (second >> 56) & 0xFF;
	buf[15] = (second >> 48) & 0xFF;
	buf[14] = (second >> 40) & 0xFF;
	buf[13] = (second >> 32) & 0xFF;
	buf[12] = (second >> 24) & 0xFF;
	buf[11] = (second >> 16) & 0xFF;
	buf[10] = (second >> 8 ) & 0xFF;
	buf[9] =   second        & 0xFF;
}

int atollu(const char * str, uint64_t * res)
{
    uint64_t cur = *res;
    while(*str)
    {
        if(!isdigit(*str))
        {
            *res = cur;
            return 1;
        }
        *res *= 10;
        *res += *str - 48;
        str++;
    }
    return 0;
}

int main()
{
    uint64_t res = 0;
	printf("%lu\n", atollu("36742983d", &res));
	return 0;
}

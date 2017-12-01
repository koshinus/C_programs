#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <sys/types.h>
using namespace std;

union char_representation
{
    uint64_t num;
    char representation[8];
};

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

typedef struct m_struct_
{
    int id;
    char data[];
} m_struct;

m_struct * create(int id_, const char *data_)
{
    size_t size = offsetof(m_struct, data_) + sizeof(char) * (strlen(data_) + 1);
    m_struct *new_struct = malloc(size);
    strcpy(new_struct->data, data_);
    return new_struct;
}

int main()
{
    return 0;
}

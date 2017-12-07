// Except header, because in ../test/RiDE_test.cpp file
// first including is RiDE_server.c which include RiDE_server.h
//#include "RiDE_server.h"

void fill_buffer(char * buf, char type, uint64_t id, uint64_t offset, 
        uint64_t len, uint32_t address, uint16_t port, char * data)
{
    rep64 nr1;
    rep64 nr2;
    rep64 nr3;
    rep32 nr4;
    rep16 nr5;
    uint64_t full_offset;
    switch(type)
    {
        case 'a': 
        {
            buf[0] = type;
            nr1.num = htobe64(id);
            nr2.num = htobe64(len);
            for(int i = 0; i < 8; i++)
            {
                buf[i+1]  = nr1.representation[i];
                buf[i+9]  = nr2.representation[i];
            }
            break;
        }
        case 'p': 
        {
            buf[0] = type;
            nr1.num = htobe64(id);
            nr2.num = htobe64(offset);
            nr3.num = htobe64(len);
            for(int i = 0; i < 8; i++)
            {
                buf[i+1]  = nr1.representation[i];
                buf[i+9]  = nr2.representation[i];
                buf[i+17] = nr3.representation[i];
            }
            full_offset = sizeof(type) + sizeof(id) + sizeof(offset) + 
                            sizeof(len) + offset; 
            strncpy(buf + full_offset, data, len);
            break;
        }
        case 't':
        {
            buf[0] = type;
            nr1.num = htobe64(id);
            nr2.num = htobe64(offset);
            nr3.num = htobe64(len);
            nr4.num = htobe32(address);
            nr5.num = htobe16(port);
            for(int i = 0; i < 4; i++)
                buf[i+1] = nr4.representation[i];
            buf[5] = nr5.representation[0];
            buf[6] = nr5.representation[1];
            for(int i = 0; i < 8; i++)
            {
                buf[i+7]  = nr1.representation[i];
                buf[i+15] = nr2.representation[i];
                buf[i+23] = nr3.representation[i];
            }
            break;
        }
        default : break;
    }
}

int unknown_command()
{
    datas_configuration();
    char str[80];
    fill_buffer(str, 'd', 0, 0, 100, 0, 0, NULL);
    int result = parse_buffer(str);
    datas_dealloc();
    return result;
}

int simple_alloc()
{
    datas_configuration();
    char str[80];
    fill_buffer(str, 'a', 0, 0, 100, 0, 0, NULL);
    int result = parse_buffer(str);
    datas_dealloc();
    return result;
}

int resize_alloc()
{
    datas_configuration();
    char str1[80];
    char str2[80];
    char str3[80];
    fill_buffer(str1, 'a', 0, 0, 100, 0, 0, NULL);
    fill_buffer(str2, 'a', 1, 0, 100, 0, 0, NULL);
    fill_buffer(str3, 'a', 2, 0, 100, 0, 0, NULL);
    int result = 0;
    result += parse_buffer(str1);
    result += parse_buffer(str2);
    result += parse_buffer(str3);
    datas_dealloc();
    return result;
}

int repeated_alloc()
{
    datas_configuration();
    char str1[80];
    char str2[80];
    fill_buffer(str1, 'a', 0, 0, 100, 0, 0, NULL);
    fill_buffer(str2, 'a', 0, 0, 100, 0, 0, NULL);
    int result = 0;
    result += parse_buffer(str1);
    result += parse_buffer(str2);
    datas_dealloc();
    return result;
}

int too_big_block_alloc()
{
    datas_configuration();
    char str1[80];
    fill_buffer(str1, 'a', 0, 0, uint64_t(-1), 0, 0, NULL);
    int result = 0;
    result += parse_buffer(str1);
    datas_dealloc();
    return result;
}

int correct_placing()
{
    datas_configuration();
    char str1[80];
    char str2[80];
    fill_buffer(str1, 'a', 0, 0, 100, 0, 0, NULL);
    fill_buffer(str2, 'p', 0, 0,   7, 0, 0, (char *)"Hello, ");
    int result = 0;
    result += parse_buffer(str1);
    result += parse_buffer(str2);
    datas_dealloc();
    return result;
}

int placing_on_wrong_id()
{
    datas_configuration();
    char str1[80];
    fill_buffer(str1, 'p', 0, 0, 7, 0, 0, (char *)"Hello, ");
    int result = 0;
    result += parse_buffer(str1);
    datas_dealloc();
    return result;
}

int placing_out_of_range()
{
    datas_configuration();
    char str1[80];
    char str2[80];
    fill_buffer(str1, 'a', 0, 100, 0, 0, 0, NULL);
    fill_buffer(str2, 'p', 0, 100, 99, 10, 0, NULL);
    int result = 0;
    result += parse_buffer(str1);
    result += parse_buffer(str2);
    datas_dealloc();
    return result;
}

int placing_with_resize()
{
    datas_configuration();
    char str1[80];
    char str2[80];
    fill_buffer(str1, 'a', 0, 0, 100, 0, 0, NULL);
    fill_buffer(str2, 'a', 1, 0, 100, 0, 0, NULL);
    int result = 0;
    result += parse_buffer(str1);
    result += parse_buffer(str2);
    fill_buffer(str1, 'p', 0, 0, 7, 0, 0, (char *)"Hello, ");
    fill_buffer(str2, 'p', 1, 0, 7, 0, 0, (char *)"World! ");
    result += parse_buffer(str1);
    result += parse_buffer(str2);
    fill_buffer(str1, 'a', 2, 0, 100, 0, 0, NULL);
    result += parse_buffer(str1);
    datas_dealloc();
    return result;
}

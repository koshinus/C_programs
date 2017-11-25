#include <stdio.h>
#include <string.h>
#include <uv.h>
#include <ctype.h>
#include "RiDE_server.h"

#define CHECK(r, msg)                                       \
    if ((r) < 0)                                            \
    {                                                       \
        fprintf(stderr, "%s: %s\n", (msg), uv_strerror(r)); \
        exit(1);                                            \
    }

datablock *        * datas;
uint64_t    datas_capacity;
uint64_t      datas_length;

static void datas_dealloc()
{
    for(int i = 0; i < datas_length; i++)
        free(datas[i]->data);
    free(datas);
}

static void datas_configuration()
{
    datas_capacity = 2;
    datas_length = 0;
    datas = malloc(sizeof(datablock *) * datas_length);
}

uint64_t atou64(const char * str)
{
    uint64_t res = 0;
    while(*str)
    {
        res *= 10;
        res += *str - 48;
        str++;
    }
    return res;
}

static int extract_uint64_from_buf(const char ** buf, uint64_t * num)
{
    char * num_start = (char *)*buf;
    char for_copying[100];
    // Extracting num
    while(**buf != ':')
    {
        if (!isdigit(**buf))
            return 1;
        (*buf)++;
    }
    strncpy(for_copying, num_start, (int)(*buf - num_start));
    for_copying[(int)(*buf - num_start)] = '\0'; // Function "strncpy" does not set null-terminator at end of copying line
    *num = atou64(for_copying);
    (*buf)++;// Skip ':' at end
    return 0;
}

static int read_info(const char * buf, uint64_t * id, uint64_t * len, uint64_t * busy, char **addr, char ** data_ptr)
{
    int semicolons = 0;                     // Variable for "Transmit" label
    char * addr_start = (char *)(buf + 1);  // Variable for "Transmit" label
    int error;                              // Variable for "Place" label
    // Check the first byte in received buffer
    switch(*buf)
    {
        case 'p':
        {
            //printf("Place.\n");
            buf++; // Skip 'p'
            goto Place;
        }
        case 't':
        {
            //printf("Transmit.\n");
            buf++; // Skip 't'
            goto Transmit;
        }
        default :
        {
            //printf("Error.\n");
            return UNKNOWN_COMMAND;
        }
    }
Transmit:
    while(semicolons != 2)
    {
        buf++; // Skip ':' symbol at first iteration
        if (*buf == ':')
        {
            semicolons++;
            continue;
        }
        if (!isdigit(*buf) && *buf != '.')
            return INCORRECT_ADDR;
    }
    strncpy(*addr, addr_start, (int)(buf - addr_start));
    buf++; // Skip ':' symbol at end of address
Place:
    buf++;
    error = extract_uint64_from_buf(&buf, id);
    if (error)
        return INCORRECT_ID;
    error = extract_uint64_from_buf(&buf, len);
    if (error)
        return INCORRECT_SIZE;
    error = extract_uint64_from_buf(&buf, busy);
    if (error)
        return INCORRECT_BUSY_SIZE;
    //printf("Parsing error: unacceptable symbol in host address.");
    //printf("Parsing error: unacceptable symbol in block's id.");
    //printf("Parsing error: unacceptable symbol in block's summary size.");
    //printf("Parsing error: unacceptable symbol in block's busy size.");
    *data_ptr = (char *)buf;
    return PARSING_CORRECT;
}

void process(const char * str)
{
    // Structures for datablock
    uint64_t id;
    uint64_t len;
    uint64_t busy_len;
    char addr[22];
    char *data_ptr;
    // Initialization of datablock
    read_info(str, &id, &len, &busy_len, &addr, &data_ptr);
    for (uint64_t i = 0; i < datas_length; i++)
    {
        if (datas[i]->id == id)
        {
            strncpy(datas[i]->data + datas[i]->busy_len, data_ptr, busy_len);
            datas[i]->busy_len += busy_len;
            return;
        }
    }
    datablock * new_data = datablock_alloc(data_ptr, id, len, busy_len);
    // Checking correctness of initialization
    if(!new_data)
    {
        printf("Not enough memory!");
        datas_dealloc();
        return;
    }
    // In case if array of datablocks is full
    if(datas_length == datas_capacity)
    {
        datas_capacity *= 2;
        datas = realloc(datas, datas_capacity*sizeof(datablock *));
        if(!datas)
        {
            printf("Not enough memory!");
            datas_dealloc();
            return;
        }
    }
    datas[datas_length] = new_data;
    datas_length++;
    // /*
    for(int i = 0; i < datas_length; i++)
        printf("%s", datas[i]->data);
        //for(int j = 0; j < datas[i]->busy_len; j++)
            //printf("%c", datas[i]->data[j]);
    //datas_dealloc();
    //*/
}

int main(int argc,char *argv[]) 
{
    datas_configuration();
    const char * str1 = "p:1:100:7:Hello, ";
    const char * str2 = "t:192.68.78.9:11000:2:100:6:World!";
    const char * str3 = "p:1:100:6:World!";
    process(str1);
    process(str2);
    process(str3);
    datas_dealloc();
    return 0;
}

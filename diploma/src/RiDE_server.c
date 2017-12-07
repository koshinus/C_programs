#include "RiDE_server.h"

void datas_dealloc()
{
    for(uint64_t i = 0; i < datas_length; i++)
        free(datas[i]);
    free(datas);
}

void datas_configuration()
{
    datas_capacity = 2;
    datas_length = 0;
    datas = (datablock **)malloc(sizeof(datablock *) * datas_capacity);
}

void raise_an_error(int error_type)
{
    printf("Error of type ");
    switch (error_type)
    {
        case INCORRECT_ID:
        {
            printf("INCORRECT_ID: please check the datablock id.\n");
            break;
        }
        case ALREADY_ALLOCATED:
        {
            printf("ALREADY_ALLOCATED: datablock with this id already exist.\n");
            break;
        }
        case OUT_OF_MEMORY:
        {
            printf("OUT_OF_MEMORY: system haven't enough memory to allocate this datablock.\n");
            break;
        }
        case UNKNOWN_COMMAND:
        {
            printf("UNKNOWN_COMMAND: wrong first symbol in received message.\n");
            break;
        }
        case OUT_OF_RANGE:
        {
            printf("OUT_OF_RANGE: please check offset and data length of delivered message.\n");
            break;
        }
        default: break;
    }
}

/*void*/int transmit(uint32_t addr, uint16_t port, uint64_t id, uint64_t offset, uint64_t length)
{
    return 0;
}

/*void*/int place(uint64_t id, uint64_t offset, uint64_t length, char * data_ptr)
{
    for(uint64_t i = 0; i < datas_length; i++)
        if(datas[i]->id == id)
        {
            if(datas[i]->len < offset + length)
                //raise_an_error(OUT_OF_RANGE);
                return OUT_OF_RANGE;
            else
            {
                strncpy(datas[i]->data + offset, data_ptr, length);
                //return;
                return ALL_CORRECT;
            }
        }
    //raise_an_error(INCORRECT_ID);
    return INCORRECT_ID;
}

/*void*/int allocate(uint64_t id, uint64_t length)
{
    for(uint64_t i = 0; i < datas_length; i++)
        if(datas[i]->id == id)
            //raise_an_error(ALREADY_ALLOCATED);
            return ALREADY_ALLOCATED;
    datablock *block = datablock_alloc(id, length);
    // datablock_alloc and malloc/realloc return NULL
    // if system haven't enough memory for allocation
    if (!block)
        //raise_an_error(OUT_OF_MEMORY);
        return OUT_OF_MEMORY;
    if(datas_length == datas_capacity)
    {
        datas_capacity *= 2;
        ///*
        datablock ** new_datas = (datablock **)malloc(sizeof(datablock*) * datas_capacity);
        if(!new_datas)
            //raise_an_error(OUT_OF_MEMORY);
            return OUT_OF_MEMORY;
        for(uint64_t i = 0; i  < datas_length; i++)
            new_datas[i] = datas[i];
        free(datas);
        datas = new_datas;
        //*/
        /*
        datas = (datablock **)realloc(datas, datas_capacity);
        if(!datas)
            raise_an_error(OUT_OF_MEMORY);
        //*/
    }
    datas[datas_length] = block;
    datas_length++;
    return ALL_CORRECT;
}

/*void*/int parse_buffer(const char * buf)
{
    uint64_t id, offset, length;
    uint32_t host_addr;
    uint16_t host_port;
    // Check the first byte in received buffer
    switch(*buf)
    {
        // Command beXtoh( ((uintX_t *)buf)[] ) interprets next X bits
        // as unsigned number and convert it to endian of the calling machine
        case 'a':
        {
            buf++; // Skip 'a'
            id        = be64toh( ((uint64_t *)buf)[0] );
            length    = be64toh( ((uint64_t *)buf)[1] );
            //allocate(id, length);
            return allocate(id, length);
            break;
        }
        case 'p':
        {
            buf++; // Skip 'p'
            id        = be64toh( ((uint64_t *)buf)[0] );
            offset    = be64toh( ((uint64_t *)buf)[1] );
            length    = be64toh( ((uint64_t *)buf)[2] );
            char * data_ptr = (char *)(buf + sizeof(id) + sizeof(offset) + sizeof(length));
            //place(id, offset, length, data_ptr);
            return place(id, offset, length, data_ptr);
            break;
        }
        case 't':
        {
            buf++; // Skip 't'
            host_addr = be32toh( ((uint32_t *)buf)[0] );
            buf += sizeof(host_addr); // Skip "host address"-bytes in buffer
            host_port = be16toh( ((uint16_t *)buf)[0] );
            buf += sizeof(host_port); // Skip "host port"-bytes in buffer
            id        = be64toh( ((uint64_t *)buf)[0] );
            offset    = be64toh( ((uint64_t *)buf)[1] );
            length    = be64toh( ((uint64_t *)buf)[2] );
            //transmit(host_addr, host_port, id, offset, length);
            return transmit(host_addr, host_port, id, offset, length);
            break;
        }
        default :
            //raise_an_error(UNKNOWN_COMMAND);
            return UNKNOWN_COMMAND;
            break;
    }
}

/*
int main(int argc,char *argv[]) 
{
    datas_configuration();
    char str1[80];
    char str2[80];
    char str3[80];
    union char_representation cr1;
    union char_representation cr2;
    union char_representation cr3;
    union char_representation cr4;
    union char_representation cr5;
    union char_representation cr6;
    cr1.num = htobe64(0ull);
    cr2.num = htobe64(100ull);
    cr3.num = htobe64(1ull);
    cr4.num = htobe64(100ull);
    cr5.num = htobe64(2ull);
    cr6.num = htobe64(100ull);
    str1[0] = str2[0] = str3[0] = 'a';
    for(int i = 0; i < 8; i++)
    {
        str1[i+1] = cr1.representation[i];
        str1[i+9] = cr2.representation[i];
        str2[i+1] = cr3.representation[i];
        str2[i+9] = cr4.representation[i];
        str3[i+1] = cr5.representation[i];
        str3[i+9] = cr6.representation[i];
    }
    parse_buffer(str1);
    parse_buffer(str2);
    parse_buffer(str3);
    //    
    char str4[80];
    char str5[80];
    char str6[80];
    union char_representation cr7;
    union char_representation cr8;
    union char_representation cr9;
    union char_representation cr10;
    union char_representation cr11;
    union char_representation cr12;
    union char_representation cr13;
    union char_representation cr14;
    union char_representation cr15;
    cr7.num = htobe64(0ull);
    cr8.num = htobe64(0ull);
    cr9.num = htobe64(7ull); // len("Hello, ")

    cr10.num = htobe64(1ull);
    cr11.num = htobe64(0ull);
    cr12.num = htobe64(7ull); // len("World! ")

    cr13.num = htobe64(2ull);
    cr14.num = htobe64(0ull);
    cr15.num = htobe64(7ull); // len("- Vadim")
    str4[0] = str5[0] = str6[0] = 'p';
    for(int i = 0; i < 8; i++)
    {
        str4[i+1]  = cr7.representation[i];
        str4[i+9]  = cr8.representation[i];
        str4[i+17] = cr9.representation[i];
        str5[i+1]  = cr10.representation[i];
        str5[i+9]  = cr11.representation[i];
        str5[i+17] = cr12.representation[i];
        str6[i+1]  = cr13.representation[i];
        str6[i+9]  = cr14.representation[i];
        str6[i+17] = cr15.representation[i];
    }
    strcpy(str4 + 25, "Hello, ");
    strcpy(str5 + 25, "World! ");
    strcpy(str6 + 25, "- Vadim");
    parse_buffer(str4);
    parse_buffer(str5);
    parse_buffer(str6);
    
    char str7[80];
    char str8[80];
    char str9[80];
    union char_representation cr16;
    union char_representation cr17;
    union char_representation cr18;
    union char_representation cr19;
    union char_representation cr20;
    union char_representation cr21;
    cr16.num = htobe64(3ull);
    cr17.num = htobe64(100ull);
    cr18.num = htobe64(4ull);
    cr19.num = htobe64(100ull);
    cr20.num = htobe64(5ull);
    cr21.num = htobe64(100ull);
    str7[0] = str8[0] = str9[0] = 'a';
    for(int i = 0; i < 8; i++)
    {
        str7[i+1] = cr16.representation[i];
        str7[i+9] = cr17.representation[i];
        str8[i+1] = cr18.representation[i];
        str8[i+9] = cr19.representation[i];
        str9[i+1] = cr20.representation[i];
        str9[i+9] = cr21.representation[i];
    }
    parse_buffer(str7);
    parse_buffer(str8);
    parse_buffer(str9);
    for(uint64_t i = 0; i < datas_length; i++)
        for(uint64_t j = 0; j < 7; j++)
            printf("%c", datas[i]->data[j]);
    datas_dealloc();
    return 0;
}
//*/
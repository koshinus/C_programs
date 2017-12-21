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

void raise_an_error(ERROR error_type)
{
    printf("Error of type ");
    printf("%s", error_messages[(int)error_type]);
}

/*void*/ERROR transmit(uint32_t addr, uint16_t port, uint64_t id, uint64_t offset, uint64_t length)
{
    return ALL_CORRECT;
}

/*void*/ERROR place(uint64_t id, uint64_t offset, uint64_t length, char * data_ptr)
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

/*void*/ERROR allocate(uint64_t id, uint64_t length)
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
            //raise_an_error(OUT_OF_MEMORY);
            return ERRORS.OUT_OF_MEMORY;
        //*/
    }
    datas[datas_length] = block;
    datas_length++;
    return ALL_CORRECT;
}

/*void*/ERROR parse_buffer(const char * buf)
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

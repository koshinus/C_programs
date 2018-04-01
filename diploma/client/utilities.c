#include <stdio.h>
#include "utilities.h"

const char * error_messages[7] =
{
    "ALL_CORRECT: everything is fine.\n",
    "UNKNOWN_COMMAND: wrong first symbol in received message.\n",
    "INCORRECT_ID: please check the datablock id.\n",
    "ALREADY_ALLOCATED: datablock with this id already exist.\n",
    "OUT_OF_MEMORY: system haven't enough memory to allocate this datablock.\n",
    "OUT_OF_RANGE: please check offset and data length of delivered message.\n",
    "NO_DATA_RECEIVED: received message have no data.\n"
};

void fill_buffer_for_placing(char * buf, uint64_t id, uint64_t block_len,
                             uint64_t offset, uint64_t data_len, char * data)
{
    rep64 nr1, nr2, nr3, nr4;
    buf[0] = 'p';
    nr1.num = htobe64(id);
    nr2.num = htobe64(block_len);
    nr3.num = htobe64(offset);
    nr4.num = htobe64(data_len);
    for(int i = 0; i < 8; i++)
    {
        buf[i+1]  = nr1.representation[i];
        buf[i+9]  = nr2.representation[i];
        buf[i+17] = nr3.representation[i];
        buf[i+25] = nr4.representation[i];
    }
    uint64_t full_offset = sizeof('p') + sizeof(id) + sizeof(block_len)
            + sizeof(offset) + sizeof(data_len);
    strncpy(buf + full_offset, data, data_len);
}


void fill_buffer_for_transmition(char * buf, uint64_t id, uint64_t offset,
                                 uint64_t len, uint32_t address, uint16_t port)
{
    rep64 nr1, nr2, nr3;
    rep32 nr4;
    rep16 nr5;
    buf[0] = 't';
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
    //31 == sizeof(type)+sizeof(nr1)+..+sizeof(nr5)
    buf[31] = '\0';
}

void fill_buffer(char * buf, char type, uint64_t id, uint64_t block_len, uint64_t offset,
        uint64_t data_len, uint32_t address, uint16_t port, char * data)
{
    if (type == 'p')
        fill_buffer_for_placing(buf, id, block_len, offset, data_len, data);
    else
        fill_buffer_for_transmition(buf, id, offset, data_len, address, port);
}

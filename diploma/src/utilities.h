#pragma once

typedef enum err {ALL_CORRECT, UNKNOWN_COMMAND, INCORRECT_ID, ALREADY_ALLOCATED, OUT_OF_MEMORY, OUT_OF_RANGE, NO_DATA_RECEIVED} ERROR;

const char * error_messages[] =
{
    "ALL_CORRECT: everything is fine.\n",
    "UNKNOWN_COMMAND: wrong first symbol in received message.\n",
    "INCORRECT_ID: please check the datablock id.\n",
    "ALREADY_ALLOCATED: datablock with this id already exist.\n",
    "OUT_OF_MEMORY: system haven't enough memory to allocate this datablock.\n",
    "OUT_OF_RANGE: please check offset and data length of delivered message.\n",
    "NO_DATA_RECEIVED: received message have no data.\n"
};

typedef union num_representation_64
{
    uint64_t num;
    char representation[8];
} rep64;

typedef union num_representation_32
{
    uint32_t num;
    char representation[4];
} rep32;

typedef union num_representation_16
{
    uint16_t num;
    char representation[2];
} rep16;

/*
union char_representation
{
    uint64_t num;
    char representation[8];
};
*/
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

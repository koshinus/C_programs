#pragma once
#include <endian.h>
#include <stdint.h>
#include <string.h>

typedef enum err {ALL_CORRECT, UNKNOWN_COMMAND, INCORRECT_ID, ALREADY_ALLOCATED,
                  OUT_OF_MEMORY, OUT_OF_RANGE, NO_DATA_RECEIVED} ERROR;

const char * error_messages[7];

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

//uint32_t parseIPV4string(char* ipAddress);

void fill_buffer(char * buf, char type, uint64_t id, uint64_t block_len, uint64_t offset,
        uint64_t data_len, uint32_t address, uint16_t port, char * data);

void fill_buffer_for_placing(char * buf, uint64_t id, uint64_t block_len,
                             uint64_t offset, uint64_t data_len, char * data);

void fill_buffer_for_transmition(char * buf, uint64_t id, uint64_t offset,
                                 uint64_t len, uint32_t address, uint16_t port);

void parse_buffer(const char * buf);

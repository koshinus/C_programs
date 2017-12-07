#pragma once

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <uv.h>

#define ALL_CORRECT         0
#define UNKNOWN_COMMAND     1
#define INCORRECT_ID        2
#define ALREADY_ALLOCATED   3
#define OUT_OF_MEMORY       4
#define OUT_OF_RANGE        5

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

typedef struct datablock_
{
    uint64_t id;
    uint64_t len;
    char data[];
} datablock;

union char_representation
{
    uint64_t num;
    char representation[8];
};

datablock * datablock_alloc(uint64_t id, uint64_t len)
{
    size_t size = offsetof(datablock, data) + sizeof(char) * (len + 1);
    datablock *block = (datablock *)malloc(size);
    if (!block)
        return NULL;
    block->id = id;
    block->len = len;
    return block;
}

datablock *        * datas;
uint64_t    datas_capacity;
uint64_t      datas_length;

void datas_configuration();
void datas_dealloc();
void raise_an_error(int error_type);
/*void*/int transmit(uint32_t addr, uint16_t port, uint64_t id, uint64_t offset, uint64_t length);
/*void*/int place(uint64_t id, uint64_t offset, uint64_t length, char * data_ptr);
/*void*/int allocate(uint64_t id, uint64_t length);
/*void*/int parse_buffer(const char * buf);
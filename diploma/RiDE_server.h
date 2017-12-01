#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

#define UNKNOWN_COMMAND     1
#define INCORRECT_ID        2
#define ALREADY_ALLOCATED   3
#define OUT_OF_MEMORY       4
#define OUT_OF_RANGE        5

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
    datablock *block = malloc(size);
    if (!block)
        return NULL;
    block->id = id;
    block->len = len;
    return block;
}

/*
void datablock_copy(datablock *self, datablock * other)
{
    printf("%lu", self->id);
    printf("%lu", other->id);
    self->id = other->id;
    self->len = other->len;
    strncpy(self->data, other->data, self->len);
}
//*/
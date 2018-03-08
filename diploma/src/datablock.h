#pragma once

#include <stdint.h>

// Datablock structures and functions
//--------------------------------------
typedef struct datablock_
{
    uint64_t id;
    uint64_t len;
    char data[];
} datablock;

datablock * datablock_alloc(uint64_t id, uint64_t len);
void datablock_dealloc(datablock *block);

#pragma once

typedef enum err {ALL_CORRECT, UNKNOWN_COMMAND, INCORRECT_ID, ALREADY_ALLOCATED, OUT_OF_MEMORY, OUT_OF_RANGE} ERRORS;

const char * error_messages[] =
{
    "INCORRECT_ID: please check the datablock id.\n",
    "ALREADY_ALLOCATED: datablock with this id already exist.\n",
    "OUT_OF_MEMORY: system haven't enough memory to allocate this datablock.\n",
    "UNKNOWN_COMMAND: wrong first symbol in received message.\n",
    "OUT_OF_RANGE: please check offset and data length of delivered message.\n"
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

union char_representation
{
    uint64_t num;
    char representation[8];
};

#pragma once

#include <uv.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

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
    size_t size = offsetof(datablock, data) + sizeof(char) * len;
    datablock *block = (datablock *)malloc(size);
    if (!block)
        return NULL;
    block->id = id;
    block->len = len;
    return block;
}

void datablock_dealloc(datablock * block)
{
    free(block);
}

//Server strucures
//--------------------------------------
datablock *   * datas;
uint64_t        datas_capacity;
uint64_t        datas_length;
uv_loop_t     * event_loop;
uv_udp_t        recv_socket;
//--------------------------------------

void datas_configuration();
void datas_dealloc();
void server_start();
void server_stop();
void raise_an_error(ERRORS error_type);
void on_alloc(uv_handle_t* client, size_t suggested_size, uv_buf_t* buf);
void on_recv(uv_udp_t* handle, ssize_t nread, const uv_buf_t* rcvbuf, const struct sockaddr* addr, unsigned flags);
/*void*/ERRORS transmit(uint32_t addr, uint16_t port, uint64_t id, uint64_t offset, uint64_t length);
/*void*/ERRORS place(uint64_t id, uint64_t offset, uint64_t length, char * data_ptr);
/*void*/ERRORS allocate(uint64_t id, uint64_t length);
/*void*/ERRORS parse_buffer(const char * buf);

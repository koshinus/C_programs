#pragma once

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <uv.h>

/*
    serv->data = malloc(1000*sizeof(uint8_t));
    serv->info = malloc(100*sizeof(datablock));
    free(serv->data);
    free(serv->info);
*/

//#define PLACE_FLAG           0
//#define TRANSFER_FLAG        1
#define PARSING_CORRECT     0
#define UNKNOWN_COMMAND     1
#define INCORRECT_ADDR      2
#define INCORRECT_ID        3
#define INCORRECT_SIZE      4
#define INCORRECT_BUSY_SIZE 5

typedef struct datapack_
{
    uint64_t id;
    //uint64_t data_len;
    const int8_t data[];
} datapack;

typedef struct datablock_
{
    uint64_t id;
    uint64_t len;
    uint64_t busy_len;
    char data[];
} datablock;

datablock * datablock_alloc(const char *buf, uint64_t id, uint64_t len, uint64_t busy)
{
    size_t size = offsetof(datablock, data) + sizeof(char) * len;
    datablock *block = malloc(size);
    if (!block)
        return NULL;
    strncpy(block->data, buf, busy);
    //for(int i = 0; i < busy; i++)
        //block->data[i] = buf[i];
    block->data[busy] = '\0';
    block->id = id;
    block->len = len;
    block->busy_len = busy;
    return block;
}

/*
typedef struct RiDE_server_
{
    //uv_loop_t *loop;
    uv_udp_t recv_socket;
    //datablock * info;
    //uint8_t * data;
    uint8_t buffer[4096];
} RiDE_server;

void start(RiDE_server *serv, uv_loop_t *loop)
{
    uv_udp_init(loop, &serv->recv_socket);
    struct sockaddr_in recv_addr;
    uv_ip4_addr("0.0.0.0", 600, &recv_addr);
    uv_udp_bind(&serv->recv_socket, (const struct sockaddr *)&recv_addr, UV_UDP_REUSEADDR);
    uv_udp_recv_start(&serv->recv_socket, serv->buffer, on_read);
}

void on_read(RiDE_server *serv)
{
    
}

void stop(RiDE_server *serv)
{
}
*/

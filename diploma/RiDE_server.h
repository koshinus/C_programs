#pragma once

#include <stdint.h>
#include <uv.h>

/*
    serv->data = malloc(1000*sizeof(uint8_t));
    serv->info = malloc(100*sizeof(datablock));
    free(serv->data);
    free(serv->info);
*/

typedef struct datapack_
{
    uint64_t id;
    //uint64_t data_len;
    const uint8_t * data;
} datapack;

typedef struct datablock_
{
    uint64_t id;
    uint8_t * start;
    uint8_t * end;
} datablock;

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

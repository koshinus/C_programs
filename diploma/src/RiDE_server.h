#pragma once

#include <uv.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>
#include "datablock.h"
#include "logger.h"

// Server strucures and functions
//--------------------------------------
typedef struct RiDE_server_
{
    datablock *   * datas;
    uint64_t        datas_capacity;
    uint64_t        datas_length;
    uv_loop_t     * event_loop;
    RiDE_logger   * logger;
    uv_udp_t        recv_socket;
    char            started;
} RiDE_server;

void datas_configure(RiDE_server * server);
void datas_reset(RiDE_server * server);
void server_start(RiDE_server * server);
void server_stop(RiDE_server * server);
void on_allocate(uv_handle_t* client, size_t suggested_size, uv_buf_t* buf);
void on_recieve(uv_udp_t* handle, ssize_t nread, const uv_buf_t* rcvbuf, const struct sockaddr* addr, unsigned flags);
void on_sending(uv_udp_send_t* req, int status);
void transmition(RiDE_server * server, uint32_t addr, uint16_t port, uint64_t id, uint64_t offset, uint64_t length);
void placing(RiDE_server * server, uint64_t id, uint64_t block_len, uint64_t offset, uint64_t data_len, char * data_ptr);
void allocation(RiDE_server *server, uint64_t id, uint64_t length);
void parse_buffer(RiDE_server * server, const char * buf);
void wait_for_message();

RiDE_server * server;

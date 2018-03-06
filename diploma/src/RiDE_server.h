#pragma once

#include <uv.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>
#include "utilities.h"
#include "datablock.h"
#include "logger.h"

// Server strucures and functions
//--------------------------------------
struct RiDE_server
{
    datablock *   * datas;
    uint64_t        datas_capacity;
    uint64_t        datas_length;
    uv_loop_t     * event_loop;
    uv_udp_t        recv_socket;
    RiDE_logger   * logger;
    char            started;
    void (* configure)(RiDE_server * server);
    void (* reset    )(RiDE_server * server);
    void (* start    )(RiDE_server * server, RiDE_logger * log);
    void (* stop     )(RiDE_server * server);
    void (* on_alloc )(uv_handle_t* client, size_t suggested_size, uv_buf_t* buf);
    void (* on_recv  )(uv_udp_t* handle, ssize_t nread, const uv_buf_t* rcvbuf, const struct sockaddr* addr, unsigned flags);
    void (* on_send  )(uv_udp_send_t* req, int status);
    void (* transmit )(RiDE_server *server, uint32_t addr, uint16_t port, uint64_t id, uint64_t offset, uint64_t length);
    void (* place    )(RiDE_server *server, uint64_t id, uint64_t offset, uint64_t length, char * data_ptr);
    void (* alloc    )(RiDE_server *server, uint64_t id, uint64_t length);
    void (* parse    )(RiDE_server * server, const char * buf);
};

void datas_configure(RiDE_server * server);
void datas_reset(RiDE_server * server);
void server_start(RiDE_server * server, RiDE_logger * log);
void server_stop(RiDE_server * server);
void on_allocate(uv_handle_t* client, size_t suggested_size, uv_buf_t* buf);
void on_recieve(uv_udp_t* handle, ssize_t nread, const uv_buf_t* rcvbuf, const struct sockaddr* addr, unsigned flags);
void on_sending(uv_udp_send_t* req, int status);
void/*ERROR*/ transmition(RiDE_server *server, uint32_t addr, uint16_t port, uint64_t id, uint64_t offset, uint64_t length);
void/*ERROR*/ placing(RiDE_server *server, uint64_t id, uint64_t offset, uint64_t length, char * data_ptr);
void/*ERROR*/ allocation(RiDE_server *server, uint64_t id, uint64_t length);
void/*ERROR*/ parse_buffer(RiDE_server * server, const char * buf);

RiDE_server * server;

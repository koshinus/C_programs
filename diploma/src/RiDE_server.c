#include "RiDE_server.h"
//#include <omp.h>

void datas_configure(RiDE_server * server)
{
    server->datas_capacity = 2;
    server->datas_length = 0;
    server->datas = (datablock **)malloc(sizeof(datablock *) * server->datas_capacity);
}

void datas_reset(RiDE_server * server)
{
    for(uint64_t i = 0; i < server->datas_length; i++)
        datablock_dealloc(server->datas[i]);
    free(server->datas);
}

void on_recieve(uv_udp_t * handle, ssize_t nread, const uv_buf_t * rcvbuf, const struct sockaddr * addr, unsigned flags)
{
    if (nread > 0)
        parse_buffer(server, rcvbuf->base);
    else
        log_an_error(server->logger, NO_DATA_RECEIVED);
    free(rcvbuf->base);
}

void on_allocate(uv_handle_t * client, size_t suggested_size, uv_buf_t * buf)
{
    buf->base = (char *)malloc(suggested_size + 1);
    buf->len = suggested_size;
    buf->base[suggested_size] = '\0';
}

void on_sending(uv_udp_send_t * req, int status)
{
}

void server_start(RiDE_server * server)
{
    datas_configure(server);
    server->started = 1; // started = true
    struct sockaddr_in addr;
    server->event_loop = uv_default_loop();
    uv_udp_init(server->event_loop, &server->recv_socket);
    uv_ip4_addr("0.0.0.0", 68, &addr);
    uv_udp_bind(&server->recv_socket, (const struct sockaddr *)&addr, UV_UDP_REUSEADDR);
    uv_udp_recv_start(&server->recv_socket, on_allocate, on_recieve);

    /*return*/ uv_run(server->event_loop, UV_RUN_DEFAULT);
}

void server_stop(RiDE_server * server)
{
    uv_udp_recv_stop(&server->recv_socket);
    server->started = 0; // started = false
    datas_reset(server);
}

void/*ERROR*/ transmition(RiDE_server * server, uint32_t addr, uint16_t port, uint64_t id, uint64_t offset, uint64_t length)
{
    uv_udp_t send_socket;
    uv_udp_send_t send_req;
    struct in_addr ip_addr;
    ip_addr.s_addr = addr;
    struct sockaddr_in send_addr;
    
    uv_udp_init(server->event_loop, &send_socket);
    uv_ip4_addr(inet_ntoa(ip_addr), port, &send_addr);
    uv_udp_bind(&send_socket, (const struct sockaddr *)&send_addr, 0);
    uv_udp_set_broadcast(&send_socket, 1);
    uv_buf_t * send_buf = &(uv_buf_t){.base = NULL, .len = 0};
    for (uint64_t i = 0; i < server->datas_length; i++)
    {
        if (server->datas[i]->id == id)
        {
            uint64_t block_len = server->datas[i]->len;
            uint64_t full_offset = sizeof(char) + sizeof(id) + sizeof(block_len) +
                    sizeof(offset) + sizeof(length);
            send_buf->base = (char *)malloc(sizeof(char) * (full_offset + length + 1));
            // If we do not do this, the remote machine will not be able to parse
            fill_buffer_for_placing(send_buf->base, id, block_len, offset, length, server->datas[i]->data);
            send_buf->len = length;
            uv_udp_send(&send_req, &send_socket, send_buf, 1, (const struct sockaddr *)&send_addr, on_sending);
            free(send_buf->base);
            return;
        }
        else
            log_an_error(server->logger, INCORRECT_ID);
    }
    //return ALL_CORRECT;
}

void/*ERROR*/ placing(RiDE_server * server, uint64_t id, uint64_t block_len, uint64_t offset, uint64_t data_len, char * data_ptr)
{
    for(uint64_t i = 0; i < server->datas_length; i++)
        if(server->datas[i]->id == id)
        {
            if(server->datas[i]->len < offset + data_len)
            {
                log_an_error(server->logger, OUT_OF_RANGE);
                //return OUT_OF_RANGE;
            }
            else
            {
                memcpy(server->datas[i]->data + offset, data_ptr, data_len);
                if (!server->datas[i]->data)
                    log_an_error(server->logger, OUT_OF_MEMORY);
                //return ALL_CORRECT;
            }
        }
    // If we are here then block with this id doesn't exist yet
    allocation(server, id, block_len);
    if(server->datas[server->datas_length - 1]->len < offset + data_len)
    {
        log_an_error(server->logger, OUT_OF_RANGE);
        //return OUT_OF_RANGE;
    }
    else
    {
        memcpy(server->datas[server->datas_length - 1]->data + offset, data_ptr, data_len);
        if (!server->datas[server->datas_length - 1]->data)
            log_an_error(server->logger, OUT_OF_MEMORY);
        //return ALL_CORRECT;
    }
}

void/*ERROR*/ allocation(RiDE_server * server, uint64_t id, uint64_t length)
{
    datablock *block = datablock_alloc(id, length);
    // datablock_alloc and malloc/realloc return NULL
    // if system haven't enough memory for allocation
    if (!block)
    {
        log_an_error(server->logger, OUT_OF_MEMORY);
        return;
        //return OUT_OF_MEMORY;
    }
    if(server->datas_length == server->datas_capacity)
    {
        server->datas_capacity *= 2;
        datablock ** new_datas = (datablock **)malloc(sizeof(datablock*) * server->datas_capacity);
        if(!new_datas)
        {
            log_an_error(server->logger, OUT_OF_MEMORY);
            return;
            //return OUT_OF_MEMORY;
        }
        for(uint64_t i = 0; i < server->datas_length; i++)
            new_datas[i] = server->datas[i];
        free(server->datas);
        server->datas = new_datas;
    }
    server->datas[server->datas_length] = block;
    server->datas_length++;
    //return ALL_CORRECT;
}

void/*ERROR*/ parse_buffer(RiDE_server * server, const char * buf)
{
    uint64_t id, offset, data_len, block_len;
    uint32_t remote_addr;
    uint16_t remote_port;
    // Check the first byte in received buffer
    if (*buf == 'p')
    {
        buf++; // Skip 'p'
        id        = be64toh( ((uint64_t *)buf)[0] );
        block_len = be64toh( ((uint64_t *)buf)[1] );
        offset    = be64toh( ((uint64_t *)buf)[2] );
        data_len  = be64toh( ((uint64_t *)buf)[3] );
        char * data_ptr = (char *)(buf + sizeof(id) + sizeof(offset) + sizeof(data_len) + sizeof(block_len));
        printf("p-%lu-%lu-%lu-%lu-%s\n", id, block_len, offset, data_len, data_ptr);
        placing(server, id, block_len, offset, data_len, data_ptr);
    }
    else if (*buf == 't')
    {
        buf++; // Skip 't'
        remote_addr = be32toh( ((uint32_t *)buf)[0] );
        buf += sizeof(remote_addr); // Skip "remote machine address"-bytes in buffer
        remote_port = be16toh( ((uint16_t *)buf)[0] );
        buf += sizeof(remote_port); // Skip "remote machine port"-bytes in buffer
        id        = be64toh( ((uint64_t *)buf)[0] );
        offset    = be64toh( ((uint64_t *)buf)[1] );
        data_len  = be64toh( ((uint64_t *)buf)[2] );
        printf("t-%u-%i-%lu-%lu-%lu\n", remote_addr, remote_port, id, offset, data_len);
        transmition(server, remote_addr, remote_port, id, offset, data_len);
    }
    else
        log_an_error(server->logger, UNKNOWN_COMMAND);
}

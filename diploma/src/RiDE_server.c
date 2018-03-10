#include "RiDE_server.h"

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

void on_recieve(uv_udp_t* handle, ssize_t nread, const uv_buf_t* rcvbuf, const struct sockaddr* addr, unsigned flags)
{
    if (nread > 0)
        server->parse(server, rcvbuf->base);
    else
        server->logger->logging(server->logger, NO_DATA_RECEIVED);
    free(rcvbuf->base);
}

void on_allocate(uv_handle_t* client, size_t suggested_size, uv_buf_t* buf)
{
    buf->base = (char *)malloc(suggested_size + 1);
    buf->len = suggested_size;
    buf->base[suggested_size] = '\0';
}

void on_sending(uv_udp_send_t* req, int status)
{

}

void server_start(RiDE_server * server, RiDE_logger * logger)
{
    server->logger = logger;
    server->configure(server);
    server->started = 1; // started = true
    struct sockaddr_in addr;
    server->event_loop = uv_default_loop();
    uv_udp_init(server->event_loop, &server->recv_socket);
    uv_ip4_addr("127.0.0.1", 11000, &addr);
    uv_udp_bind(&server->recv_socket, (const struct sockaddr *)&addr, UV_UDP_REUSEADDR);
    uv_udp_recv_start(&server->recv_socket, server->on_alloc, server->on_recv);
    uv_run(server->event_loop, UV_RUN_DEFAULT);
}

void server_stop(RiDE_server * server)
{
    uv_udp_recv_stop(&server->recv_socket);
    server->started = 0; // started = false
    server->reset(server);
}

void/*ERROR*/ transmition(RiDE_server * server, uint32_t addr, uint16_t port, uint64_t id, uint64_t offset, uint64_t length)
{
    uv_udp_send_t send_socket;
    struct in_addr ip_addr;
    ip_addr.s_addr = addr;
    struct sockaddr_in send_addr;
    
    uv_udp_init(server->event_loop, &send_socket);
    uv_ip4_addr(inet_ntoa(ip_addr), port, &send_addr);
    uv_udp_bind(&send_socket, (const struct sockaddr *)&send_addr, 0);
    uv_udp_set_broadcast(&send_socket, 1);
    uv_buf_t * send_buf;
    for (uint64_t i = 0; i < server->datas_length; i++)
    {
        if (server->datas[i]->id == id)
        {
            send_buf->base = (char *)malloc(sizeof(char) * (length + 1));
            strncpy(send_buf->base, server->datas[id]->data + offset, length + 1);
            send_buf->len = length;
            uv_udp_send(&send_socket, &server->recv_socket, (const uv_buf_t *)send_buf, 1, (const struct sockaddr *)&send_addr, server->on_send);
            free(send_buf->base);
            return;
        }
        else
            server->logger->logging(server->logger, INCORRECT_ID);
    }
    //return ALL_CORRECT;
}

void/*ERROR*/ placing(RiDE_server * server, uint64_t id, uint64_t offset, uint64_t length, char * data_ptr)
{
    for(uint64_t i = 0; i < server->datas_length; i++)
        if(server->datas[i]->id == id)
        {
            if(server->datas[i]->len < offset + length)
            {
                server->logger->logging(server->logger, OUT_OF_RANGE);
                return;
                //return OUT_OF_RANGE;
            }
            else
            {
                strncpy(server->datas[i]->data + offset, data_ptr, length);
                return;
                //return ALL_CORRECT;
            }
        }
    server->logger->logging(server->logger, INCORRECT_ID);
    return;
    //return INCORRECT_ID;
}

void/*ERROR*/ allocation(RiDE_server * server, uint64_t id, uint64_t length)
{
    for(uint64_t i = 0; i < server->datas_length; i++)
        if(server->datas[i]->id == id)
        {
            server->logger->logging(server->logger, ALREADY_ALLOCATED);
            return;
            //return ALREADY_ALLOCATED;
        }
    datablock *block = datablock_alloc(id, length);
    // datablock_alloc and malloc/realloc return NULL
    // if system haven't enough memory for allocation
    if (!block)
    {
        server->logger->logging(server->logger, OUT_OF_MEMORY);
        return;
        //return OUT_OF_MEMORY;
    }
    if(server->datas_length == server->datas_capacity)
    {
        server->datas_capacity *= 2;
        datablock ** new_datas = (datablock **)malloc(sizeof(datablock*) * server->datas_capacity);
        if(!new_datas)
        {
            server->logger->logging(server->logger, OUT_OF_MEMORY);
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
    uint64_t id, offset, length;
    uint32_t host_addr;
    uint16_t host_port;
    // Check the first byte in received buffer
    switch(*buf)
    {
        // Command "beXtoh( ((uintX_t *)buf)[] )" interprets next X bits
        // as unsigned number and convert it to endian of the calling machine
        case 'a':
        {
            buf++; // Skip 'a'
            id        = be64toh( ((uint64_t *)buf)[0] );
            length    = be64toh( ((uint64_t *)buf)[1] );
            server->alloc(server, id, length);
            //return allocate(id, length);
            break;
        }
        case 'p':
        {
            buf++; // Skip 'p'
            id        = be64toh( ((uint64_t *)buf)[0] );
            offset    = be64toh( ((uint64_t *)buf)[1] );
            length    = be64toh( ((uint64_t *)buf)[2] );
            char * data_ptr = (char *)(buf + sizeof(id) + sizeof(offset) + sizeof(length));
            server->place(server, id, offset, length, data_ptr);
            //return place(server, id, offset, length, data_ptr);
            break;
        }
        case 't':
        {
            buf++; // Skip 't'
            host_addr = be32toh( ((uint32_t *)buf)[0] );
            buf += sizeof(host_addr); // Skip "host address"-bytes in buffer
            host_port = be16toh( ((uint16_t *)buf)[0] );
            buf += sizeof(host_port); // Skip "host port"-bytes in buffer
            id        = be64toh( ((uint64_t *)buf)[0] );
            offset    = be64toh( ((uint64_t *)buf)[1] );
            length    = be64toh( ((uint64_t *)buf)[2] );
            server->transmit(server, host_addr, host_port, id, offset, length);
            //return transmit(host_addr, host_port, id, offset, length);
            break;
        }
        default :
            server->logger->logging(server->logger, UNKNOWN_COMMAND);
            //return UNKNOWN_COMMAND;
            break;
    }
}

#include <stdio.h>
#include <string.h>
#include <uv.h>
//#include <pthread.h>
#include "RiDE_server.h"

/*
uv_loop_t *loop;
uv_udp_t send_socket;
uv_udp_t recv_socket;

int main() 
{
    loop = uv_default_loop();

    uv_udp_init(loop, &recv_socket);
    struct sockaddr_in recv_addr;
    uv_ip4_addr("0.0.0.0", 68, &recv_addr);
    uv_udp_bind(&recv_socket, (const struct sockaddr *)&recv_addr, UV_UDP_REUSEADDR);
    uv_udp_recv_start(&recv_socket, alloc_buffer, on_read);

    uv_udp_init(loop, &send_socket);
    struct sockaddr_in broadcast_addr;
    uv_ip4_addr("0.0.0.0", 0, &broadcast_addr);
    uv_udp_bind(&send_socket, (const struct sockaddr *)&broadcast_addr, 0);
    uv_udp_set_broadcast(&send_socket, 1);

    uv_udp_send_t send_req;
    uv_buf_t discover_msg = make_discover_msg();

    struct sockaddr_in send_addr;
    uv_ip4_addr("255.255.255.255", 67, &send_addr);
    uv_udp_send(&send_req, &send_socket, &discover_msg, 1, (const struct sockaddr *)&send_addr, on_send);

    return uv_run(loop, UV_RUN_DEFAULT);
}

int main()
{
    int *ptr = malloc(4*sizeof(int));
    for (int i = 0; i < 4; i++)
        ptr[i] = i;
    for (int i = 0; i < 4; i++)
        printf("%d ", ptr[i]);
    
    printf("\n");
    ptr = realloc(ptr, 10);
    for (int i = 0; i < 10; i++)
        printf("%d ", ptr[i]);
    
    printf("\n");
    return 0;
}
*/

#define CHECK(r, msg)                                       \
    if ((r) < 0)                                            \
    {                                                       \
        fprintf(stderr, "%s: %s\n", (msg), uv_strerror(r)); \
        exit(1);                                            \
    }

static uv_loop_t *  uv_loop;
static uv_udp_t   recv_sock;
static uv_udp_t   send_sock;
datablock *      *    datas;

static void place(uv_udp_t * handle, const uv_buf_t * rcvbuf, const struct sockaddr * addr)
{
    
}

static void transmit(uv_udp_t * handle, const uv_buf_t * rcvbuf, const struct sockaddr * addr)
{
    
}

static void recv_acception()
{
    
}
 
static void on_recv(uv_udp_t* handle, ssize_t nread, const uv_buf_t* rcvbuf, const struct sockaddr* addr, unsigned flags) 
{
    /*
    if (nread > 0) 
    {
        printf("%lu\n",nread);
        printf("%s",rcvbuf->base);
    }
    printf("free  :%lu %p\n",rcvbuf->len,rcvbuf->base);
    free(rcvbuf->base);
    */
    if (nread <= 0)
    {
        printf("Message from client %s is empty.", addr->sa_data);
        return;
    }
    if (*rcvbuf->base == 'p') // place flag
    {
        place(handle, rcvbuf, addr);
    }
    else if (*rcvbuf->base == 't') // transfer-to flag
    {
        transmit(handle, rcvbuf, addr);
    }
    else
        printf("Incorrect request in message from client %s.", addr->sa_data);
}

static void on_alloc(uv_handle_t* client, size_t suggested_size, uv_buf_t* buf) 
{
    buf->base = malloc(suggested_size);
    buf->len = suggested_size;
    printf("malloc:%lu %p\n",buf->len,buf->base);
}

static void read_info(const char * buf, uint64_t * id, uint64_t * len, uint64_t * busy, char **addr, char ** data_ptr)
{
    // Check the first byte in received buffer
    switch(*buf)
    {
        case 'p':
        {
            printf("Place.\n");
            buf++;
            goto Place;
        }
        case 't':
        {
            printf("Transmit.\n");
            buf++;
            goto Transmit;
        }
        default :
        {
            printf("Error.\n");
            return;
        }
    }
Transmit:
    // Copy address of host where need to transmit data
    strncpy(*addr, buf, 14);
    buf += 14;
Place:
    // Interpret next 24 bytes as 3 unsigned 64-bit numbers
    *id   = ((uint64_t *)buf)[0];
    *len  = ((uint64_t *)buf)[1];
    *busy = ((uint64_t *)buf)[2];
    *data_ptr = (char  *)(buf + 24);
}

int main(int argc,char *argv[]) 
{
    /*
    int status;
    struct sockaddr_in addr;
    uv_loop = uv_default_loop();
    
    status = uv_udp_init(uv_loop,&recv_sock);
    CHECK(status,"init");
    
    uv_ip4_addr("0.0.0.0", 11000, &addr);

    status = uv_udp_bind(&recv_sock, (const struct sockaddr*)&addr, UV_UDP_REUSEADDR);
    CHECK(status,"bind");
    
    status = uv_udp_recv_start(&recv_sock, on_alloc, on_recv);
    CHECK(status,"recv");
    
    uv_run(uv_loop, UV_RUN_DEFAULT);
    */
    int datas_len = 2;
    datas = malloc(sizeof(datablock *) * datas_len);
    int len = 100, j = 0;
    char str[len];
    while(1)
    {
        printf("Enter your data:\n");
        int c = 1, i = 0;
        // Read string from stdin
        while((c = getc(stdin)) != '\n' && i < len)
        {            
            str[i] = (char)c;
            i++;
        }
        // Structures for datablock
        uint64_t id;
        uint64_t len;
        uint64_t busy_len;
        char addr[14];
        char *data_ptr = NULL;
        // Initialization of datablock
        read_info(str, &id, &len, &busy_len, &addr, &data_ptr);
        datablock * new_data = datablock_alloc(data_ptr, id, len, busy_len);
        // Checking correctness of initialization
        if(!new_data)
        {
            printf("Not enough memory!");
            for(int k = 0; k < j; k++)
                free(datas[i]->data);
            free(datas);
        }
        // In case if array of datablocks is full
        if(j == datas_len)
        {
            datas_len *= 2;
            datas = realloc(datas, datas_len*sizeof(datablock *));
            if(!datas)
            {
                printf("Not enough memory!");
                for(int k = 0; k < j; k++)
                    free(datas[i]->data);
                free(datas);
            }
        }
        datas[j] = new_data;
        j++;
        for(int k = 0; k < j; k++)
            for(int l = 0; l < datas[k]->busy_len; l++)
                printf("%c", datas[k]->data[l]);
    }
    for(int k = 0; k < j; k++)
        free(datas[k]->data);
    free(datas); 
    return 0;
}

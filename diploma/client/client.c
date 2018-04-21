#include <uv.h>
#include "utilities.h"

char buffer[1024];
char message[256];
char option[1];
const char sending_machine_addr[] = "127.0.0.1";
const uint16_t sending_machine_port = 68;
uint32_t ipv4_addr[4];
uint32_t target_machine_addr;
uint16_t target_machine_port;
uint64_t id, block_len, offset, msg_len;
uv_loop_t * event_loop;
uv_udp_t send_socket;
uv_udp_send_t send_req;
uv_buf_t * uv_buf = &((uv_buf_t){.base = buffer, .len = 0});
struct sockaddr_in send_addr;

void on_send(uv_udp_send_t * req, int status)
{
}

int client_loop()
{
    return 0;
}

int main()
{
    event_loop = uv_default_loop();
    uv_udp_init(event_loop, &send_socket);
    uv_ip4_addr(sending_machine_addr, sending_machine_port, &send_addr);
    uv_udp_bind(&send_socket, (const struct sockaddr *)&send_addr, 0);
    uv_udp_set_broadcast(&send_socket, 1);
    ///*    
    while(1)
    {
        printf("Wait for option symbol: ");
        // We need to ignore the newline symbol after the input
        scanf("%s", option);
        if (!(option[0] == 'p' || option[0] == 't'))
            return 0;
        else
        {
            printf("Enter the block id: ");
            scanf("%lu", &id);
            printf("Enter offset in block: ");
            scanf("%lu", &offset);
            printf("Enter the length of a piece of data in the block: ");
            scanf("%lu", &msg_len);
            if (option[0] == 'p')
            {
                printf("Print full length of block: ");
                scanf("%lu", &block_len);
                printf("Print message: ");
                scanf("%s", message);
                fill_buffer(buffer, option[0], id, block_len, offset, msg_len, 0, 0, message);
                uv_buf->len = sizeof(char) + sizeof(id) + sizeof(block_len) + sizeof(offset) +
                                sizeof(msg_len) + msg_len;
            }
            else if (option[0] == 't')
            {
                printf("Enter ip address of target machine: ");
                scanf("%u.%u.%u.%u", &ipv4_addr[3], &ipv4_addr[2], &ipv4_addr[1], &ipv4_addr[0]);
                target_machine_addr = ipv4_addr[0] | ipv4_addr[1] << 8 | ipv4_addr[2] << 16 | ipv4_addr[3] << 24;
                printf("Enter port of target machine: ");
                scanf("%hu", &target_machine_port);
                fill_buffer(buffer, option[0], id, 0, offset, msg_len, target_machine_addr, target_machine_port, NULL);
                uv_buf->len = sizeof(char) + sizeof(id) + sizeof(offset) + sizeof(msg_len) + 
                                sizeof(target_machine_addr) + sizeof(target_machine_port);
            }
            uv_udp_send(&send_req, &send_socket, uv_buf, 1, (const struct sockaddr *)&send_addr, on_send);
        }
    }
    //*/
    return uv_run(event_loop, UV_RUN_DEFAULT);
}


#include <uv.h>
#include <stdio.h>
#include <string.h>
#include <curses.h>
#include "utilities.h"


uint32_t parseIPV4string(char* ipAddress)
{
  char ipbytes[4];
  sscanf(ipAddress, "%uhh.%uhh.%uhh.%uhh", &ipbytes[3], &ipbytes[2], &ipbytes[1], &ipbytes[0]);
  return ipbytes[0] | ipbytes[1] << 8 | ipbytes[2] << 16 | ipbytes[3] << 24;
}

void read_message_from_stdin_getch(char * message, ssize_t msg_size)
{
    char c;
    for(ssize_t i = 0; i < msg_size; i++)
    {
        if ((c = getch()) == EOF)
        {
            message[i] = '\0';
            return;
        }
        else
            message[i] = c;
    }
    while(c != EOF)
        c = getch();
}

void read_message_from_stdin_getc(char * message, ssize_t msg_size)
{
    char c;
    for(ssize_t i = 0; i < msg_size; i++)
    {
        if ((c = getc(stdin)) == '\n')
        {
            message[i] = '\0';
            return;
        }
        else
            message[i] = c;
    }
    while(c != '\n')
        c = getc(stdin);
}

char buffer[1024];
//int msg_size = 256;
char message[256];
char option[1];
const char sending_machine_addr[] = "192.168.1.40";
const uint16_t sending_machine_port = 68;
char target_machine_addr[16];
uint16_t target_machine_port;
uint64_t id, len, offset;
uv_loop_t * event_loop;
uv_udp_t send_socket;
uv_udp_send_t send_req;
uv_buf_t * uv_buf = &((uv_buf_t){.base = buffer, .len = 0});
struct sockaddr_in send_addr;

void on_send(uv_udp_send_t * req, int status)
{
}

int main()
{
    ///*
    event_loop = uv_default_loop();
    uv_udp_init(event_loop, &send_socket);
    uv_ip4_addr(sending_machine_addr, sending_machine_port, &send_addr);
    uv_udp_bind(&send_socket, (const struct sockaddr *)&send_addr, 0);
    uv_udp_set_broadcast(&send_socket, 1);
    //*/
    while(1)
    {
        printf("Wait for option symbol: ");
        // We need to ignore the newline symbol after the input
        scanf("%s", option);
        switch(option[0])
        {
            case 'a': 
            {
                //printf("Print message: ");
                //scanf("%s", message);
                printf("Print block id: ");
                scanf("%lu", &id);
                printf("Print block len: ");
                scanf("%lu", &len);
                fill_buffer(buffer, option[0], id, 0, len, 0, 0, message);
                printf("Case-a\n");
                break;
            }
            case 'p': 
            {
                printf("Print message: ");
                //read_message_from_stdin_getch(message, sizeof(message));
                //read_message_from_stdin_getc(message, sizeof(message));
                scanf("%s", message);
                //getline(&message, &msg_size, stdin);
                printf("Print block id: ");
                scanf("%lu", &id);
                printf("Print block len: ");
                scanf("%lu", &len);
                printf("Print offset in block: ");
                scanf("%lu", &offset);
                fill_buffer(buffer, option[0], id, offset, len, 0, 0, message);
                printf("Case-p\n");
                break;
            }
            case 't': 
            {
                printf("Print message: ");
                //read_message_from_stdin_getch(message, sizeof(message));
                //read_message_from_stdin_getc(message, sizeof(message));
                scanf("%s", message);
                //getline(&message, &msg_size, stdin);
                printf("Print block id: ");
                scanf("%lu", &id);
                printf("Print block len: ");
                scanf("%lu", &len);
                printf("Print offset in block: ");
                scanf("%lu", &offset);
                printf("Print ip address of target machine: ");
                scanf("%s", target_machine_addr);
                printf("Print port of target machine: ");
                scanf("%hu", &target_machine_port);
                fill_buffer(buffer, option[0], id, offset, len, parseIPV4string(target_machine_addr), target_machine_port, message);
                printf("Case-t\n");
                break;
            }
            default:
            {
                //printf("Default\n");
                return 0;
            }
        }
        uv_buf->len = strlen(buffer);
        printf("%s\n", buffer);
        //uv_udp_send(&send_req, &send_socket, uv_buf, 1, (const struct sockaddr *)&send_addr, on_send);
    }
    return uv_run(event_loop, UV_RUN_DEFAULT);
}

#pragma once

#include <uv.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>

typedef enum err {ALL_CORRECT, UNKNOWN_COMMAND, INCORRECT_ID, ALREADY_ALLOCATED, OUT_OF_MEMORY, OUT_OF_RANGE} ERROR;

const char * error_messages[] =
{
    "ALL_CORRECT: everything is fine.\n",
    "UNKNOWN_COMMAND: wrong first symbol in received message.\n",
    "INCORRECT_ID: please check the datablock id.\n",
    "ALREADY_ALLOCATED: datablock with this id already exist.\n",
    "OUT_OF_MEMORY: system haven't enough memory to allocate this datablock.\n",
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

/*
union char_representation
{
    uint64_t num;
    char representation[8];
};
*/

// Datablock structures and functions
//--------------------------------------
typedef struct datablock_
{
    uint64_t id;
    uint64_t len;
    char data[];
} datablock;

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

// Server strucures and functions
//--------------------------------------
datablock *   * datas;
uint64_t        datas_capacity;
uint64_t        datas_length;
uv_loop_t     * event_loop;
uv_udp_t        recv_socket;
char            started;


// Logger part
//--------------------------------------
const uint64_t MAX_LOG_TIME = 10*60*60; // 10 hours
const uint64_t MAX_LOG_SIZE = 100*1024*1024; // 100 Mb
FILE * log_file;
time_t log_creation_time;
uint64_t current_log_size;

void open_log_file()
{
    char filename[100];
    struct tm *timenow;
    log_creation_time = time(NULL);
    timenow = gmtime(&log_creation_time);
    strftime(filename, sizeof(filename), "log/SERVER_%Y-%m-%d_%H:%M:%S", timenow);
    log_file = fopen(filename,"w");
    current_log_size = 0;
}

void close_log_file()
{
    fclose(log_file);
    current_log_size = 0;
}

void log_an_error(ERROR error_type)
{
    char time_string[20];
    struct tm *timenow;

    time_t error_time = time(NULL);
    timenow = gmtime(&error_time);

    strftime(time_string, sizeof(time_string), "%Y-%m-%d %H:%M:%S", timenow);

    // All strings here are null-terminated, so we need to deduct
    // summary size of null-terminators except the last one
    uint64_t current_err_msg_size = sizeof("ERROR| ")                       +
                                    sizeof(time_string)                     +
                                    sizeof(" of type ")                     +
                                    sizeof(error_messages[(int)error_type]) -
                                    sizeof('\0') * 3;
    if(current_log_size + current_err_msg_size >= MAX_LOG_SIZE)
    {
        close_log_file();
        open_log_file();
    }
    current_log_size += current_err_msg_size;
    fprintf(log_file, "ERROR| %s of type %s", error_string, error_messages[(int)error_type]);
}
//--------------------------------------
// Logger part end

void datas_configure();
void datas_dealloc();
void server_start();
void server_stop();
//void raise_an_error(ERROR error_type);
void on_alloc(uv_handle_t* client, size_t suggested_size, uv_buf_t* buf);
void on_recv(uv_udp_t* handle, ssize_t nread, const uv_buf_t* rcvbuf, const struct sockaddr* addr, unsigned flags);
void/*ERROR*/ transmit(uint32_t addr, uint16_t port, uint64_t id, uint64_t offset, uint64_t length);
void/*ERROR*/ place(uint64_t id, uint64_t offset, uint64_t length, char * data_ptr);
void/*ERROR*/ allocate(uint64_t id, uint64_t length);
void/*ERROR*/ parse_buffer(const char * buf);

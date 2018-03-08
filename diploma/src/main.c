/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: vadim
 *
 * Created on 7 декабря 2017 г., 7:23
 */
#include "RiDE_server.h"
#include <time.h>

/*
 * 
 */
int main(int argc, char** argv)
{
    RiDE_logger * logger = &(RiDE_logger)
    {
            .MAX_LOG_TIME = 10*10*1024, .MAX_LOG_SIZE = 100*1024*1024,
            .open = open_log_file, .close = close_log_file,
            .reopen = reopen_log_file, .logging = log_an_error
    };
    server = &(RiDE_server)
    {
            .start = server_start, .stop = server_stop,
            .configure = datas_configure, .reset = datas_reset,
            .on_alloc = on_allocate, .on_recv = on_recieve,
            .on_send = on_sending, .transmit = transmition,
            .place = placing, .parse = parse_buffer,
            .alloc = allocation
    };
    logger->open(logger);
    while(1)
    {
        if (!server->started)
            server->start(server, logger);
        if (clock() - logger->log_creation_time >= logger->MAX_LOG_TIME)
            logger->reopen(logger);
    }
    logger->close(logger);
    return 0;
}

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
//#include <time.h>
#include <omp.h>
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>

/*
 * 
 */
int main(int argc, char** argv)
{
    char message[40];
    RiDE_logger * logger = &(RiDE_logger)
    {
            .MAX_LOG_TIME = 10*60*60, .MAX_LOG_SIZE = 100*1024*1024,
            .open = open_log_file, .close = close_log_file,
            .reopen = reopen_log_file, .logging = log_an_error,
            .close_time = time_to_close
    };
    server = &(RiDE_server)
    {
            .start = server_start, .stop = server_stop,
            .configure = datas_configure, .reset = datas_reset,
            .on_alloc = on_allocate, .on_recv = on_recieve,
            .on_send = on_sending, .transmit = transmition,
            .place = placing, .parse = parse_buffer,
            .alloc = allocation, .logger = logger
    };
    logger->open(logger);
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            while(1)
            {
                if (!server->started)
                    server->start(server);
                if (logger->close_time(logger))
                    logger->reopen(logger);
            }
        }
        #pragma omp section
        {
            while(1)
            {
                scanf("%s", message);
                if (!strcmp(message, "server_stop"))
                {
                    server->stop(server);
                    logger->close(logger);
                    exit(0);
                }
            }
        }
    }
}

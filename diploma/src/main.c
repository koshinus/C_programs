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
#include <omp.h>

/*
 * 
 */
int main(int argc, char** argv)
{
    char message[40];
    RiDE_logger * logger = &(RiDE_logger) { .MAX_LOG_TIME = 10*60*60, .MAX_LOG_SIZE = 100*1024*1024 };
    server = &(RiDE_server){ .logger = logger };
    open_log_file(logger);
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            while(1)
            {
                if (!server->started)
                    server_start(server);
                if (time_to_close(logger))
                    reopen_log_file(logger);
            }
        }
        #pragma omp section
        {
            while(1)
            {
                scanf("%s", message);
                if (!strcmp(message, "server_stop"))
                {
                    server_stop(server);
                    close_log_file(logger);
                    exit(0);
                }
            }
        }
    }
}

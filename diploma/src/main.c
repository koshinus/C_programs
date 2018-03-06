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
    RiDE_logger * logger;
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

#pragma once

#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include "utilities.h"

typedef struct RiDE_logger_
{
    uint64_t MAX_LOG_TIME;// = 10*60*60; // 10 hours
    uint64_t MAX_LOG_SIZE;// = 100*1024*1024; // 100 Mb
    FILE * log_file;
    time_t log_creation_time;
    uint64_t current_log_size;
    void (* open)(struct RiDE_logger_ * log);
    void (* close)(struct RiDE_logger_ * log);
    void (* reopen)(struct RiDE_logger_ * log);
    void (* logging)(struct RiDE_logger_ * log, ERROR error_type);
    int (* close_time)(struct RiDE_logger_ * log);
} RiDE_logger;

void open_log_file(RiDE_logger * log);
void close_log_file(RiDE_logger * log);
void reopen_log_file(RiDE_logger * log);
void log_an_error(RiDE_logger * log, ERROR error_type);
int time_to_close(RiDE_logger * log);

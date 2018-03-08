#include "logger.h"

void open_log_file(RiDE_logger * log)
{
    char filename[40];
    struct tm *timenow;
    log->log_creation_time = time(NULL);
    timenow = gmtime(&log->log_creation_time);
    strftime(filename, sizeof(filename), "log/SERVER_%Y-%m-%d_%H:%M:%S", timenow);
    log->log_file = fopen(filename, "w");
    log->current_log_size = 0;
}

void close_log_file(RiDE_logger * log)
{
    fclose(log->log_file);
    log->current_log_size = 0;
}

void reopen_log_file(RiDE_logger * log)
{
    log->close(log);
    log->open(log);
}

void log_an_error(RiDE_logger *log, ERROR error_type)
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
    if(log->current_log_size + current_err_msg_size >= log->MAX_LOG_SIZE)
        log->reopen(log);
    log->current_log_size += current_err_msg_size;
    fprintf(log->log_file, "ERROR| %s of type %s", time_string, error_messages[(int)error_type]);
}

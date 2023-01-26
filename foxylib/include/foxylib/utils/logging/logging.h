#ifndef FOXYTOOLS_LOGGING_H
#define FOXYTOOLS_LOGGING_H
#include <foxylib/utils/logging/loglevel.h>
#include <foxylib/utils/logging/types.h>
#include <foxylib/utils/helpers.h>
#include <foxylib/status.h>

#define ENABLE_DEV_LOG

static logging_defaults logging_default_options = {
    .filename_ext = ".log",
    .filename_timestamp_format = "%Y%m%d_%H%M%S",
    .entry_timestamp_format = "%Y-%m-%d %H:%M:%S",
    .base_format_string = "%s %-9s %s\n",
};

static logging_ctx log_ctx = {
    .module_name="default",
    .log_levels=FOXY_LOG_ALL,
    .file_ptr=NULL,
    .file_path="",
    .is_initialized=0
};

foxy_status_code_t logging_init(char* module_name, int log_levels);
char* __logging_build_format_string(foxy_log_level_t log_level, const char* format);
void __logging_va_msg(FILE* output_stream, char* format, va_list args);

// macro to avoid unneccessary code duplication in the LOG* inline functions below
#define _LOG_VA_MSG(output_stream, log_level, format) \
    if((log_ctx.log_levels & (int)log_level) == (int)log_level) \
    { \
        char* final_fmt = __logging_build_format_string(log_level, format); \
        va_list args; \
        va_start(args, format); \
            __logging_va_msg(output_stream, final_fmt, args); \
        va_end(args); \
    }

// write a log message with a choosable prefix to stdout + log file (if set)
__inline void LOG(foxy_log_level_t log_level, char* format, ...)
{
    _LOG_VA_MSG(stdout, log_level, format);
}

// write a development log message to stdout + log file (if set) (does nothing when ENABLE_DEV_MODE is undefined)
__inline void LOG_DEV(char* format, ...)
{
#ifdef ENABLE_DEV_LOG
    _LOG_VA_MSG(stdout, FOXY_LOG_DEV, format);
#endif
}

// write a debug log message to stdout + log file (if set)
__inline void LOG_DEBUG(char* format, ...)
{
    _LOG_VA_MSG(stdout, FOXY_LOG_DEBUG, format);
}

// write an error log message to stderr + log file (if set)
__inline void LOG_ERROR(char* format, ...)
{
    _LOG_VA_MSG(stdout, FOXY_LOG_ERROR, format);
}

// write a warning log message to stdout + log file (if set)
__inline void LOG_WARN(char* format, ...)
{
    _LOG_VA_MSG(stdout, FOXY_LOG_WARNING, format);
}

// write an information log message to stdout + log file (if set)
__inline void LOG_INFO(char* format, ...)
{
    _LOG_VA_MSG(stdout, FOXY_LOG_INFO, format);
}

#endif //FOXYTOOLS_LOGGING_H

#ifndef FOXYTOOLS_LOGGING_TYPES_H
#define FOXYTOOLS_LOGGING_TYPES_H

#include <foxylib/platform.h>
#include <foxylib/constants.h>

struct logging_ctx_t {
    char module_name[32];
    int log_levels;
    FILE* file_ptr;
    char file_path[MAX_PATH];
    uint8_t is_initialized;
} typedef logging_ctx, *logging_ctx_p;

struct logging_defaults_t {
    char filename_ext[8];
    char filename_timestamp_format[DEFAULT_FORMAT_STRING_BUFFER_SIZE];
    char entry_timestamp_format[DEFAULT_FORMAT_STRING_BUFFER_SIZE];
    char base_format_string[DEFAULT_FORMAT_STRING_BUFFER_SIZE];
} typedef logging_defaults, *logging_defaults_p;

#endif //FOXYTOOLS_LOGGING_TYPES_H

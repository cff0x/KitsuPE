#include <foxylib/utils/logging/logging.h>



foxy_status_code_t logging_init(char* module_name, int log_levels) {
    if(log_ctx.is_initialized == 1) {
        LOG_ERROR("logging_init(): logger is already initialized! aborting init...");
        return FOXY_LOGGING_ERROR_MODULE_ALREADY_EXISTS;
    }

    strcpy(log_ctx.module_name, module_name);
    log_ctx.log_levels = log_levels;


    // build log file name based on timestamp and log module name
    char* filename_timestamp = malloc(DEFAULT_FORMAT_STRING_BUFFER_SIZE);
    get_formatted_timestamp(filename_timestamp, logging_default_options.filename_timestamp_format);
    if (sprintf_s(log_ctx.file_path, MAX_PATH + 1, "%s_%s%s",
                  filename_timestamp, log_ctx.module_name, logging_default_options.filename_ext) < 0) {
        LOG_ERROR("logging_init(): failed to create log file name");
        return FOXY_LOGGING_ERROR_FILE_NAME_GENERATION;
    }

    free(filename_timestamp);

    int ret = fopen_s(&log_ctx.file_ptr, log_ctx.file_path, "w+");
    if(ret != 0) {
        printf("failed to open log file %s!\n", log_ctx.file_path);
        return FOXY_LOGGING_ERROR_FILE_CREATION;
    }

    log_ctx.is_initialized = 1;
    return FOXY_STATUS_SUCCESS;
}

char* __logging_build_format_string(foxy_log_level_t log_level, const char* format) {
    // log entry base format
    const size_t base_len = strlen(format) + (DEFAULT_FORMAT_STRING_BUFFER_SIZE * 3);
    char tmp_prefix[9] = "";
    sprintf(tmp_prefix, "[%s]", FOXY_LOG_LEVEL_TAGS[log_level]);

    char tmp_timestamp[DEFAULT_FORMAT_STRING_BUFFER_SIZE] = "";
    get_formatted_timestamp(tmp_timestamp, logging_default_options.entry_timestamp_format);

    // create new format string based on base format and the format given as function parameter
    char* result = malloc(base_len + 1);
    sprintf_s(result, base_len,
              logging_default_options.base_format_string,
              tmp_timestamp, tmp_prefix, format);

    return result;
}

void __logging_va_msg(FILE* output_stream, char* format, va_list args) {
    vfprintf(output_stream, format, args);

    if(log_ctx.file_ptr != NULL) {
        vfprintf(log_ctx.file_ptr, format, args);
        fflush(log_ctx.file_ptr);
    }
}
#ifndef FOXYTOOLS_STATUS_H
#define FOXYTOOLS_STATUS_H

// status code classification type
enum FOXY_STATUS_TYPE {
    STATUS_TYPE_OK = 0,
    STATUS_TYPE_ERROR = 1
} typedef foxy_status_type_t;

// table containing all foxylib status codes
#define FOXY_STATUS_CODE_TABLE \
/* X(status code name, value, status type, description) */ \
/* general status codes */ \
X(FOXY_STATUS_SUCCESS, 0x00, STATUS_TYPE_OK, "success") \
X(FOXY_STATUS_ERROR, 0x01, STATUS_TYPE_ERROR, "error") \
X(FOXY_STATUS_ERROR_C_LIB_FUNC, 0x02, STATUS_TYPE_ERROR, "failure while executing native c function") \
/* logging status codes */ \
X(FOXY_LOGGING_FILE_CREATED, 0x50, STATUS_TYPE_OK, "created log file") \
X(FOXY_LOGGING_STARTED, 0x51, STATUS_TYPE_OK, "started logging") \
X(FOXY_LOGGING_STOPPED, 0x52, STATUS_TYPE_OK, "stopped logging") \
X(FOXY_LOGGING_ERROR_FILE_CREATION, 0x55, STATUS_TYPE_ERROR, "failed to create log file") \
X(FOXY_LOGGING_ERROR_FILE_NAME_GENERATION, 0x56, STATUS_TYPE_ERROR, "failed to generate log file name")  \
X(FOXY_LOGGING_ERROR_MODULE_ALREADY_EXISTS, 0x57, STATUS_TYPE_ERROR, "the requested log module already exists") \
X(FOXY_LOGGING_ERROR_MODULE_FAILED_TO_CREATE, 0x58, STATUS_TYPE_ERROR, "failed to create the logging module")  \
X(FOXY_LOGGING_ERROR_FILE_ALREADY_EXISTS, 0x59, STATUS_TYPE_ERROR, "failed to format log entry")  \
X(FOXY_LOGGING_ERROR_ENTRY_FORMATTING, 0x60, STATUS_TYPE_ERROR, "failed to format log entry")  \
/* console status codes */ \
X(FOXY_CONSOLE_INITIALIZED, 0x100, STATUS_TYPE_OK, "console context initialized") \
X(FOXY_CONSOLE_THREAD_STARTED, 0x101, STATUS_TYPE_OK, "console processing thread started successfully") \
X(FOXY_CONSOLE_THREAD_STOPPED, 0x102, STATUS_TYPE_OK, "console processing thread stopped") \
X(FOXY_CONSOLE_COMMAND_ADDED, 0x103, STATUS_TYPE_OK, "command added successfully") \
X(FOXY_CONSOLE_COMMAND_EXECUTED, 0x104, STATUS_TYPE_OK, "successfully executed command") \
X(FOXY_CONSOLE_UNLOADED, 0x105, STATUS_TYPE_OK, "console has been unloaded") \
X(FOXY_CONSOLE_ERROR_CMD_NOT_FOUND, 0x110, STATUS_TYPE_ERROR, "command not found") \
X(FOXY_CONSOLE_ERROR_CMD_FAILED, 0x111, STATUS_TYPE_ERROR, "command execution failed") \
X(FOXY_CONSOLE_ERROR_CMD_MISSING_ARGS, 0x112, STATUS_TYPE_ERROR, "missing command arguments") \
X(FOXY_CONSOLE_ERROR_CMD_ALREADY_EXISTS, 0x113, STATUS_TYPE_ERROR, "command already exists") \
X(FOXY_CONSOLE_ERROR_THREAD_START_FAILED, 0x114, STATUS_TYPE_ERROR, "console thread failed to start") \
X(FOXY_CONSOLE_ERROR_STDIN_OPEN_FAILED, 0x120, STATUS_TYPE_ERROR, "failed to open stdin stream") \
X(FOXY_CONSOLE_ERROR_STDOUT_OPEN_FAILED, 0x121, STATUS_TYPE_ERROR, "failed to open stdout stream") \
X(FOXY_CONSOLE_ERROR_STDERR_OPEN_FAILED, 0x122, STATUS_TYPE_ERROR, "failed to open stderr stream") \
X(FOXY_CONSOLE_ERROR_ALLOC_FAILED, 0x130, STATUS_TYPE_ERROR, "failed to allocate console") \
X(FOXY_CONSOLE_ERROR_INPUT_FAILED, 0x131, STATUS_TYPE_ERROR, "failed to process input") \
/* unknown/undefined */ \
X(FOXY_STATUS_NONE, 0x31337, STATUS_TYPE_OK, "not set")

// enum mapping status code to (hexadecimal) value
#define X(a, b, c, d) a=b,
enum FOXY_STATUS_CODE {
    FOXY_STATUS_CODE_TABLE
} typedef foxy_status_code_t;
#undef X

// array mapping status code to status type (success/failure)
#define X(a, b, c, d) [a]=c,
static foxy_status_type_t FOXY_STATUS_CODE_TYPES[] = {
    FOXY_STATUS_CODE_TABLE
};
#undef X

// array mapping status code to description text
#define X(a, b, c, d) [a]=d,
static char *FOXY_STATUS_CODE_DESCRIPTIONS[] = {
    FOXY_STATUS_CODE_TABLE
};
#undef X

#endif //STATUS
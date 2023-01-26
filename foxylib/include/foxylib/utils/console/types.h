#ifndef FOXYTOOLS_TYPES_H
#define FOXYTOOLS_TYPES_H
#include <foxylib/platform.h>
#include <foxylib/constants.h>
#include <foxylib/status.h>

#define CONSOLE_CMD_NAME_SIZE 16
#define CONSOLE_CMD_DESC_SIZE 256


typedef struct console_ctx_t *console_ctx_p;

// function type definition as executed by commands
typedef foxy_status_code_t (console_cmd_func_t)(console_ctx_p ctx, char* command, size_t arg_count, char** arguments);
typedef console_cmd_func_t* console_cmd_func_p;

// data structure for console command definitions
struct console_cmd_t {
    char name[CONSOLE_CMD_NAME_SIZE];
    char desc[CONSOLE_CMD_DESC_SIZE];
    console_cmd_func_p func;
} typedef console_cmd, *console_cmd_p;

// data structure for console runtime context parameters
struct console_ctx_t {
    // title of the console window
    char console_title[MAX_WINDOW_TITLE];

    // pointers to stdio streams
    FILE* stdin_ptr;
    FILE* stdout_ptr;
    FILE* stderr_ptr;

    // flag to indicate whether the console has been initialized or not
    uint8_t is_initialized;

    // flag to indicate whether the console thread is running or not
    uint8_t is_running;

    // console thread handle and id
    void* thread_handle;
    uint32_t thread_id;

    // last native error code
    int last_error;

    // last internal status code
    foxy_status_code_t last_status;

    // array of all registered console commands + command count
    size_t command_count;
    console_cmd_p command_list;
} typedef console_ctx, *console_ctx_p;



static console_ctx cmd_ctx = {
    .console_title="FoxyConsole",
    .command_list=NULL,
    .command_count=0,
    .stdin_ptr=NULL,
    .stdout_ptr=NULL,
    .stderr_ptr=NULL,
    .is_initialized=0,
    .is_running=0,
    .thread_handle=NULL,
    .thread_id=0,
    .last_error=0,
    .last_status=FOXY_STATUS_NONE
};



#endif //FOXYTOOLS_TYPES_H

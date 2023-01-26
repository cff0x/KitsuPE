#include <foxylib/utils/console/commands.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

const console_cmd default_commands[] = {
    {.name="help", .desc="Show usage and help regarding the available commands", .func=cmd_help},
    {.name="quit", .desc="Exit this application", .func=cmd_quit}
};

void init_commands(console_ctx_p ctx) {
    ctx->command_count = ARRAY_SIZE(default_commands);
    for(int i = 0; i < ctx->command_count; ++i) {
        ctx->command_list = realloc(ctx->command_list, ctx->command_count * sizeof(console_cmd));
        ctx->command_list[i] = default_commands[i];
    }
}

void add_command(console_ctx_p ctx, console_cmd cmd) {
    ctx->command_count++;
    ctx->command_list = realloc(ctx->command_list, ctx->command_count * sizeof(console_cmd));
    ctx->command_list[ctx->command_count] = cmd;
}


foxy_status_code_t cmd_help(console_ctx_p ctx, char* command, size_t arg_count, char** arguments) {
    printf("Showing help for the %zd available commands:\n", ctx->command_count);
    for(int i = 0; i < ctx->command_count; ++i) {
        console_cmd cmd_info = ctx->command_list[i];
        printf("  - \"%s\": %s\n", cmd_info.name, cmd_info.desc);
    }

    return FOXY_CONSOLE_COMMAND_EXECUTED;
}

foxy_status_code_t cmd_quit(console_ctx_p ctx, char* command, size_t arg_count, char** arguments) {
    uint8_t prompt_done = 0;

    while(prompt_done == 0) {
        printf("Do you really want to exit? (y/N): ");
        char input = getchar();

        if(toupper(input) == 'N' || isspace(input)) {
            prompt_done = 1;
        } else if(toupper(input) == 'Y') {
            _exit(0);
        } else {
            printf("Invalid input!\n");
        }
    }

    return FOXY_CONSOLE_COMMAND_EXECUTED;
}
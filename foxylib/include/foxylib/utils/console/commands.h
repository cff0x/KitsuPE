#ifndef FOXYTOOLS_COMMANDS_H
#define FOXYTOOLS_COMMANDS_H
#include <foxylib/utils/console/types.h>

void init_commands(console_ctx_p ctx);
int cmd_help(console_ctx_p ctx, char* command, size_t arg_count, char** arguments);
int cmd_quit(console_ctx_p ctx, char* command, size_t arg_count, char** arguments);

#endif//FOXYTOOLS_COMMANDS_H
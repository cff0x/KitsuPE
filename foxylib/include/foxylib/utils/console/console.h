#ifndef FOXYTOOLS_CONSOLE_H
#define FOXYTOOLS_CONSOLE_H
#include <foxylib/utils/console/types.h>

foxy_status_code_t console_init(char* console_title);
foxy_status_code_t console_start();
foxy_status_code_t console_close();



console_ctx_p console_get_context(void);
void console_set_context(console_ctx_p context);

uint32_t __stdcall console_main_thread(void* lp_param);

#endif //FOXYTOOLS_CONSOLE_H
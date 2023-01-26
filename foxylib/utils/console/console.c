#include <foxylib/utils/console/console.h>
#include <foxylib/utils/logging/logging.h>
#include <foxylib/utils/console/commands.h>

// initialize context with default values
foxy_status_code_t console_init(char* console_title) {
    if(console_title != NULL) {
        strcpy(cmd_ctx.console_title, console_title);
    }

    // allocate console window
    AllocConsole();

    // set window title
    SetConsoleTitle(cmd_ctx.console_title);

    // open stdin console input stream
    cmd_ctx.last_error =
        freopen_s(&cmd_ctx.stdin_ptr, "CONIN$", "r", stdin);
    if(cmd_ctx.last_error != 0)
    {
        printf_s("Failed to open stdin! Error code: %d", cmd_ctx.last_error);
        cmd_ctx.last_status = FOXY_CONSOLE_ERROR_STDIN_OPEN_FAILED;
        return cmd_ctx.last_status;
    }

    // open stdout console output stream
    cmd_ctx.last_error =
        freopen_s(&cmd_ctx.stdout_ptr, "CONOUT$", "w", stdout);
    if(cmd_ctx.last_error != 0)
    {
        printf_s("Failed to open stdout! Error code: %d", cmd_ctx.last_error);
        cmd_ctx.last_status = FOXY_CONSOLE_ERROR_STDOUT_OPEN_FAILED;
        return cmd_ctx.last_status;
    }

    // open stderr console error output stream
    cmd_ctx.last_error =
        freopen_s(&cmd_ctx.stderr_ptr, "CONOUT$", "w", stderr);
    if(cmd_ctx.last_error != 0)
    {
        printf_s("Failed to open stderr! Error code: %d", cmd_ctx.last_error);
        cmd_ctx.last_status = FOXY_CONSOLE_ERROR_STDERR_OPEN_FAILED;
        return cmd_ctx.last_status;
    }

    if(logging_init("console", FOXY_LOG_ALL) != FOXY_STATUS_SUCCESS) {
        printf("ERROR WHILE STARTING LOGGING\n");
        return FOXY_STATUS_ERROR;
    }


    init_commands(&cmd_ctx);
    //console_add_command("help", "Prints a help text", console_cmd_help);

    // set status to initialized, awaiting command setup and main
    // thread creation from now
    cmd_ctx.is_initialized = 1;
    cmd_ctx.last_status = FOXY_CONSOLE_INITIALIZED;
    return cmd_ctx.last_status;
}

foxy_status_code_t console_start() {
    // start main console loop to process commands etc
    cmd_ctx.is_running = 1;
    cmd_ctx.thread_handle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)console_main_thread, NULL, 0, (LPDWORD)&cmd_ctx.thread_id);

    // check if thread has been started
    if(cmd_ctx.thread_handle == NULL) {
        cmd_ctx.is_running = 0;
        cmd_ctx.last_status = FOXY_CONSOLE_ERROR_THREAD_START_FAILED;
    } else {
        cmd_ctx.last_status = FOXY_CONSOLE_THREAD_STARTED;
    }

    return cmd_ctx.last_status;
}

foxy_status_code_t console_close() {
    // stop main thread
    cmd_ctx.is_running = 0;

    // free command array
    free(cmd_ctx.command_list);

    // free console
    FreeConsole();

    // free input/output streams
    fflush(cmd_ctx.stdin_ptr);
    fflush(cmd_ctx.stdout_ptr);
    fflush(cmd_ctx.stderr_ptr);
    fclose(cmd_ctx.stdin_ptr);
    fclose(cmd_ctx.stdout_ptr);
    fclose(cmd_ctx.stderr_ptr);

    cmd_ctx.last_status = FOXY_CONSOLE_THREAD_STOPPED;
    return cmd_ctx.last_status;
}

uint32_t __stdcall console_main_thread(void* lp_param) {
    // variable for user input storage
    char* user_input_buf = malloc(MAX_INPUT_BUFFER);

    // main loop for processing command input etc
    while(cmd_ctx.is_running) {
        // will be set to 1 when command has been found
        uint8_t found_cmd = 0;

        // will be used to store the command arguments
        char** command_arguments = NULL;
        unsigned int argument_idx = 0;

        // reset input buffer
        memset(user_input_buf, 0, MAX_INPUT_BUFFER);

        // fetch user input line from stdin
        printf("> ");
        fgets(user_input_buf, MAX_INPUT_BUFFER, stdin);

        // remove newline(s) from input string
        user_input_buf[strcspn(user_input_buf, "\r\n")] = 0;

        // split user input into tokens separated by whitespace
        char* part = strtok(user_input_buf, " ");

        // loop until nothing is left to split
        while(part != NULL) {
            // calculate array and part sizes
            size_t calc_arguments_size, part_size;
            calc_arguments_size = sizeof(char**) * (argument_idx + 1);
            part_size = sizeof(char) * (strlen(part) + 1);

            // add argument to the array
            command_arguments = realloc(command_arguments, calc_arguments_size);
            command_arguments[argument_idx] = malloc(part_size);
            strcpy(command_arguments[argument_idx], part);
            ++argument_idx;

            // look for next part
            part = strtok(NULL, " ");
        }

        // empty command given, ignore
        if (command_arguments == NULL || command_arguments[0] == NULL) {
            continue;
        }

        // try to find the given command in the command list
        for (int i = 0; i < cmd_ctx.command_count; ++i) {
            // value holding the current command info
            const console_cmd cmd_info = cmd_ctx.command_list[i];

            // call command function if match was found
            if (_stricmp(cmd_info.name, command_arguments[0]) == 0) {
                found_cmd = 1;

                LOG_DEV("Executing command: %s", cmd_info.name);
                const foxy_status_code_t ret = cmd_info.func(&cmd_ctx, command_arguments[0], argument_idx, command_arguments);
                if(ret != FOXY_STATUS_SUCCESS && ret != FOXY_CONSOLE_COMMAND_EXECUTED)
                {
                    LOG_ERROR("Command execution failed! (status code: %d)", ret);
                }

                break;
            }
        }

        // show error message if command was not found
        if(found_cmd == 0) {
            LOG_ERROR("Command not found! Type \"help\" for a list of commands.");
        }

    }
}
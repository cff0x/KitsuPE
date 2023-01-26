#include "main.h"

#define BUFFER_SIZE 2048
#define EXIT_PHRASE "go away"

//#include <foxylib/utils/console/status.h>
#include <foxylib/utils/logging/logging.h>


int main(int argc, char** argv) {
	// register SIGINT handler (CTRL+C)
	signal(SIGINT, sigint_handler);


    int ENABLED_LOG_LEVEL = FOXY_LOG_INFO | FOXY_LOG_WARNING | FOXY_LOG_DEBUG | FOXY_LOG_DEV;
    printf("LogLevel idx: %d, LogLevel naem: %s\n", ENABLED_LOG_LEVEL, FOXY_LOG_LEVEL_TAGS[ENABLED_LOG_LEVEL]);

    printf("ENABLED_LOG_LEVEL & FOXY_LOG_INFO = %d\n", ENABLED_LOG_LEVEL & FOXY_LOG_WARNING);

	printf("Henlo! I'm a smol and basic application written in C.\n");
	pong_loop();

	return 0;
}

void pong_loop() {
	// variables used
	char input_buffer[BUFFER_SIZE + 1];
	uint8_t is_running = 1;

	// start input loop
	while (is_running) {
		// clear input buffer
		memset(input_buffer, 0, BUFFER_SIZE + 1);

		// retrieve user input
		printf("\nTell me something (say \"%s\" and I'll stop): ", EXIT_PHRASE);
		fgets(input_buffer, BUFFER_SIZE, stdin);

		// remove any trailing newlines (LF, CR, CRLF and LFCR)
		input_buffer[strcspn(input_buffer, "\r\n")] = 0;

		// stop if user wants us to, otherwise repeat what he said
		if (strcmp(input_buffer, EXIT_PHRASE) == 0) {
			is_running = 0;
			printf("Oh noooo! Bai baii~ QwQ\n\n");
		} else if(strlen(input_buffer) > 0) {
			printf("That's what you said: %s\n", input_buffer);
		}
		
		sleep(10);
	}
}

void sigint_handler(int val)
{
	printf("\nOH NO OH NO HELP! WHY ARE YOU DOING THIS TO ME? :C\n");
	exit(val);
}

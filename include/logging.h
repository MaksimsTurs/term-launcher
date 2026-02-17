#ifndef H_LAUNCHER_LOGGING
#define H_LAUNCHER_LOGGING

#include <stdio.h>
#include <stdlib.h>

#define LAUNCHER_LOG_AND_EXIT(code, message, ...) do { 	\
	printf("\x1b[38;2;137;180;250m[app-launcher (%i)]:\x1b[0m " message "\n", code, ##__VA_ARGS__);	\
	exit(code);																						\
} while(0)

#endif

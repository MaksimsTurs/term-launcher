#ifndef H_LAUNCHER_UTILITY
#define H_LAUNCHER_UTILITY

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define LAUNCHER_KEY_ARROW_RIGHT 	67
#define LAUNCHER_KEY_ARROW_LEFT  	68

#define LAUNCHER_RESET_STYLES			"\x1b[0m"

#define LAUNCHER_BG		"\x1b[48;2;"
#define LAUNCHER_FG		"\x1b[38;2;"

#define LAUNCHER_RGB(r, g, b) #r ";" #g ";" #b "m"

#define LAUNCHER_LOG_INFO(message, ...) do {\
	printf(LAUNCHER_FG LAUNCHER_RGB(137, 180, 250) "[app-launcher]: " LAUNCHER_RESET_STYLES message "\n", ##__VA_ARGS__);\
} while(0)

#define LAUNCHER_LOG_ERR(message, ...) do { \
	printf(LAUNCHER_FG LAUNCHER_RGB(250, 180, 137) "[app-launcher (%i)]: " LAUNCHER_RESET_STYLES message "\n", errno, ##__VA_ARGS__);\
} while(0)

#define LAUNCHER_ASSERT(condition, message, ...) do {	\
	if(condition) { 																		\
		LAUNCHER_LOG_ERR(message, ##__VA_ARGS__); 				\
		exit(errno);																			\
	} 																									\
} while(0)

#define LAUNCHER_IN_ARR_BOUND(index, size) ((index < size) && (index >= 0))

int 					launcher_compare_names(const char* f_str, const char* s_str, int length);
unsigned char launcher_is_valid_key(char ch);

#endif

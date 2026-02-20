#ifndef H_LAUNCHER_UTILITY
#define H_LAUNCHER_UTILITY

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define LAUNCHER_KEY_ARROW_RIGHT 	67
#define LAUNCHER_KEY_ARROW_LEFT  	68
#define LAUNCHER_KEY_DEL         	127
#define LAUNCHER_KEY_ESCAPE				27
#define LAUNCHER_KEY_ARROW_UP    	65
#define LAUNCHER_KEY_ARROW_DOWN  	66
#define LAUNCHER_KEY_ARROW_RIGHT 	67
#define LAUNCHER_KEY_ARROW_LEFT  	68
#define LAUNCHER_KEY_ENTER       	10
#define LAUNCHER_ASCII_FG					"\x1b[48;2;"
#define LAUNCHER_ASCII_BG					"\x1b[38;2;"
#define LAUNCHER_ASCII_UNDERLINE  "\x1b[4m"
#define LAUNCHER_ASCII_BOLD       "\x1b[1m"
#define LAUNCHER_ASCII_RESET			"\x1b[0m"

#define LAUNCHER_RGB_TO_ASCII(r, g, b) #r ";" #g ";" #b "m"
#define LAUNCHER_RGB_RED(color) 	(color >> 16) & 0xFF
#define LAUNCHER_RGB_GREEN(color) (color >> 8) & 0xFF
#define LAUNCHER_RGB_BLUE(color) 	(color >> 0) & 0xFF

#define LAUNCHER_LOG_INFO(message, ...) do {\
	printf(LAUNCHER_ASCII_BG LAUNCHER_RGB_TO_ASCII(137, 180, 250) "[app-launcher]: " LAUNCHER_ASCII_RESET message "\n", ##__VA_ARGS__);\
} while(0)

#define LAUNCHER_LOG_ERR(message, ...) do { \
	printf(LAUNCHER_ASCII_BG LAUNCHER_RGB_TO_ASCII(250, 180, 137) "[app-launcher (%i)]: " LAUNCHER_ASCII_RESET message "\n", errno, ##__VA_ARGS__);\
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

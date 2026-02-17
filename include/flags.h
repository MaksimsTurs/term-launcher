#ifndef H_LAUNCHER_FLAGS
#define H_LAUNCHER_FLAGS

#include <string.h>
#include <stdio.h>

typedef struct s_launcher_flags {
	unsigned char h;
	unsigned char c;
} t_launcher_flags;

void launcher_print_flags();
void launcher_set_flags(t_launcher_flags* flags, int argc, const char** argv);

#endif

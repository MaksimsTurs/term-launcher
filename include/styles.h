#ifndef H_LAUNCHER_STYLES
#define H_LAUNCHER_STYLES

#include "tomlc17.h"
#include "utility.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LAUNCHER_BG "\x1b[48;2"
#define LAUNCHER_FG "\x1b[38;2"

typedef struct s_launcher_styles {
	char*						input_format;
	unsigned char*	input_bg;
	unsigned char*	input_fg;

	char*						selected_format;
	unsigned char*	selected_bg;
	unsigned char*	selected_fg;

	char*						unselected_format;
	unsigned char*	unselected_bg;
	unsigned char*	unselected_fg;
} t_launcher_styles;

void 	launcher_parse_styles(t_launcher_styles* styles);
char* launcher_parse_string(const char* path, toml_result_t* res);
unsigned char* 	launcher_parse_color(const char* path, toml_result_t* res);

void 	launcher_apply_color(const char* location, const unsigned char* color);
void	launcher_apply_format(const char* format, const char* value, const char* default_format);

#endif

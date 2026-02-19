#ifndef H_LAUNCHER_STYLES
#define H_LAUNCHER_STYLES

#include "tomlc17.h"
#include "utility.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_launcher_styles {
	char* input_format;

	unsigned char	input_bg[3];
	unsigned char	input_fg[3];

	unsigned char	selected_bg[3];
	unsigned char	selected_fg[3];

	unsigned char	unselected_bg[3];
	unsigned char	unselected_fg[3];
} t_launcher_styles;

void launcher_parse_styles(t_launcher_styles* styles);
char* launcher_parse_string(const char* path, toml_result_t* res);
void launcher_parse_color(const char* path, unsigned char* color, toml_result_t* res);

#endif

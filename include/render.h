#ifndef H_LAUNCHER_RENDER
#define H_LAUNCHER_RENDER

#include "config.h"
#include "utility.h"

#include <stdio.h>

void launcher_clear_screen();
void launcher_render_input();
void launcher_render_input_value(const char* value);
void launcher_render_unselected_item(const char* label);
void launcher_render_selected_item(const char* label);

void launcher_style_reset();
void launcher_style_apply(const t_launcher_element_config* config);

#endif

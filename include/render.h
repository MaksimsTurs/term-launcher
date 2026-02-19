#ifndef H_LAUNCHER_RENDER
#define H_LAUNCHER_RENDER

#include "utility.h"
#include "styles.h"

#include <stdio.h>

void launcher_clear_screen();
void launcher_render_input(const t_launcher_styles* styles, const char* value);
void launcher_render_unselected_list_item(const t_launcher_styles* styles, const char* label);
void launcher_render_selected_list_item(const t_launcher_styles* styles, const char* label);

#endif

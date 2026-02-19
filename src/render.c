#include "render.h"

void launcher_clear_screen()
{
	printf("\x1b[1;1H");
	printf("\x1b[0J");
	printf("\x1b[1J");
}

void launcher_render_input(const t_launcher_styles* styles, const char* value)
{
	launcher_apply_color(LAUNCHER_FG, styles->input_fg);
	launcher_apply_color(LAUNCHER_BG, styles->input_bg);

	printf(styles->input_format, value);
}

void launcher_render_unselected_list_item(const t_launcher_styles* styles, const char* label)
{
	launcher_apply_color(LAUNCHER_FG, styles->unselected_fg);
	launcher_apply_color(LAUNCHER_BG, styles->unselected_bg);

	printf(styles->unselected_format, label);
}

void launcher_render_selected_list_item(const t_launcher_styles* styles, const char* label)
{
	launcher_apply_color(LAUNCHER_FG, styles->selected_fg);
	launcher_apply_color(LAUNCHER_BG, styles->selected_bg);

	printf(styles->selected_format, label);
}

#include "render.h"

void launcher_clear_screen()
{
	printf("\x1b[1;1H");
	printf("\x1b[0J");
	printf("\x1b[1J");
}

void launcher_render_input()
{
	t_launcher_config* config = launcher_get_config();

	launcher_style_apply(&config->input);
	printf(config->input.format);
	launcher_style_reset();
}

void launcher_render_input_value(const char* value)
{
	t_launcher_config* config = launcher_get_config();

	launcher_style_apply(&config->value);
	printf(config->value.format, value);
	launcher_style_reset();
	printf("\n");
}

void launcher_render_unselected_item(const char* label)
{
	t_launcher_config* config = launcher_get_config();

	launcher_style_apply(&config->unselected);
	printf(config->unselected.format, label);
	launcher_style_reset();
	printf("\n");
}

void launcher_render_selected_item(const char* label)
{
	t_launcher_config* config = launcher_get_config();

	launcher_style_apply(&config->selected);
	printf(config->selected.format, label);
	launcher_style_reset();
	printf("\n");
}

void launcher_style_apply(const t_launcher_element_config* config)
{
	int r = 0;
	int g = 0;
	int b = 0;

	if(config->fg != -1)
	{
		r = LAUNCHER_RGB_RED(config->fg);
		g = LAUNCHER_RGB_GREEN(config->fg);
		b = LAUNCHER_RGB_BLUE(config->fg);

		printf("\x1b[48;2;%i;%i;%im", r, g, b);
	}

	if(config->bg != -1)
	{
		r = LAUNCHER_RGB_RED(config->bg);
		g = LAUNCHER_RGB_GREEN(config->bg);
		b = LAUNCHER_RGB_BLUE(config->bg);

		printf("\x1b[38;2;%i;%i;%im", r, g, b);
	}

	if(config->make_bold)
	{
		printf(LAUNCHER_ASCII_BOLD);
	}

	if(config->make_underlined)
	{
		printf(LAUNCHER_ASCII_UNDERLINE);
	}
}

void launcher_style_reset()
{
	printf(LAUNCHER_ASCII_RESET);
}

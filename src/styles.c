#include "styles.h"

void launcher_parse_styles(t_launcher_styles* styles)
{
	char* home_path = getenv("HOME");
	char* file_path = ".config/launcher/conf.toml";

	int home_path_length = 0;
	int file_path_length = 0;

	char full_path[255] = {0};
	
	LAUNCHER_ASSERT(home_path == NULL, "Can not create full path to configuration file!");

	home_path_length = strlen(home_path);
	file_path_length = strlen(file_path) + 1;

	strncpy(full_path, home_path, home_path_length);
	strncpy(full_path + home_path_length, "/.config/launcher/conf.toml", file_path_length);
	full_path[home_path_length + file_path_length] = '\0';

	toml_result_t res = toml_parse_file_ex(full_path);

	LAUNCHER_ASSERT(res.ok == 0, "Can not open configuration file %s!", full_path);

	styles->input_format	= launcher_parse_string("input.format",	&res);
	
	launcher_parse_color("input.bg",			(unsigned char*)&styles->input_bg, 			&res);
	launcher_parse_color("input.fg",			(unsigned char*)&styles->input_fg, 			&res);
	launcher_parse_color("selected.bg",		(unsigned char*)&styles->selected_bg, 	&res);
	launcher_parse_color("selected.fg",		(unsigned char*)&styles->selected_fg, 	&res);
	launcher_parse_color("unselected.bg",	(unsigned char*)&styles->unselected_bg, &res);
	launcher_parse_color("unselected.fg",	(unsigned char*)&styles->unselected_fg, &res);

	toml_free(res);
}

char* launcher_parse_string(const char* path, toml_result_t* res)
{
	toml_datum_t string = toml_seek(res->toptab, path);

	if(string.type == TOML_UNKNOWN)
	{
		return NULL;
	}

	return (char*)string.u.s;
}

void launcher_parse_color(const char* path, unsigned char* color, toml_result_t* res)
{
	toml_datum_t color_values = toml_seek(res->toptab, path);
	toml_datum_t element = {0};
	int color_value = 0;

	LAUNCHER_ASSERT(color_values.u.arr.size > 3, "Color should have only 3 elements for R, G and B!");

	for(int index = 0; index < color_values.u.arr.size; index++)
	{
		element = color_values.u.arr.elem[index];

		LAUNCHER_ASSERT(element.type != TOML_INT64, "Element under index %i in path %s is not of type int8!", index, path);

		color_value = (int)element.u.int64;

		LAUNCHER_ASSERT(color_value > 255 || color_value < 0, "Invalid RGB value %i!", color_value);
		color[index] = (unsigned char)color_value;
	}
}

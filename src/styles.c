#include "styles.h"

static char* DEFAULT_INPUT_FORMAT						= "Run » \x1b[0m%s\n";
static char* DEFAULT_LIST_ITEM_FORMAT				= "%s\x1b[0m\n";
static unsigned char DEFAULT_INPUT_FG[3] 		= { 137, 180, 250 };
static unsigned char DEFAULT_SELECTED_FG[3]	= { 250, 179, 138 }; 

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
	styles->input_bg 			= launcher_parse_color("input.bg",			&res);
	styles->input_fg 			= launcher_parse_color("input.fg",			&res);

	styles->selected_format = launcher_parse_string("selected.format", 	&res);
	styles->selected_bg 		= launcher_parse_color("selected.bg",				&res);
	styles->selected_fg 		= launcher_parse_color("selected.fg",				&res);

	styles->unselected_format	= launcher_parse_string("unselected.format", 	&res);
	styles->unselected_bg 		= launcher_parse_color("unselected.bg",				&res);
	styles->unselected_fg 		= launcher_parse_color("unselected.fg",				&res);

	if(styles->input_format == NULL)
	{
		styles->input_format = DEFAULT_INPUT_FORMAT;
	}

	if(styles->selected_format == NULL)
	{
		styles->selected_format = DEFAULT_LIST_ITEM_FORMAT;
	}

	if(styles->unselected_format == NULL)
	{
		styles->unselected_format = DEFAULT_LIST_ITEM_FORMAT;
	}

	if(styles->input_fg == NULL)
	{
		styles->input_fg = (unsigned char*)&DEFAULT_INPUT_FG;
	}

	if(styles->selected_fg == NULL)
	{
		styles->selected_fg = (unsigned char*)&DEFAULT_SELECTED_FG;
	}

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

unsigned char* launcher_parse_color(const char* path, toml_result_t* res)
{
	toml_datum_t toml_array = toml_seek(res->toptab, path);
	toml_datum_t toml_array_element = {0};
	int color_value = 0;
	unsigned char* color = NULL;

	LAUNCHER_ASSERT(toml_array.type == TOML_ARRAY && toml_array.u.arr.size != 3, "Color should have only 3 elements for R, G and B!");

	if(toml_array.u.arr.size != 0)
	{
		color = (unsigned char*)calloc(3, sizeof(unsigned char));
		
		LAUNCHER_ASSERT(color == NULL, "Can not initialize a memory for color value!");
	}

	for(int index = 0; index < toml_array.u.arr.size; index++)
	{
		toml_array_element = toml_array.u.arr.elem[index];

		LAUNCHER_ASSERT(toml_array_element.type != TOML_INT64, "Element under index %i in path %s is not of type int8!", index, path);

		color_value = (int)toml_array_element.u.int64;

		LAUNCHER_ASSERT(color_value > 255 || color_value < 0, "Invalid RGB value %i!", color_value);
		color[index] = (unsigned char)color_value;
	}

	return color;
}

void launcher_apply_color(const char* location, const unsigned char* color)
{
	if(color)
	{
		printf("%s;%i;%i;%im", location, color[0], color[1], color[2]);
	}
}

#include "config.h"

static t_launcher_config g_launcher_config = {0};
static char							 g_config_path[LAUNCHER_CONFIG_PATH_BUFF_SIZE] = {0};
static t_toml_result		 g_parsing_result = {0};

const static char*			 g_file_path = ".config/launcher/conf.toml";

t_launcher_config* launcher_get_config()
{
	return &g_launcher_config;
}

void launcher_load_config()
{
	launcher_create_config_path();
		
	g_parsing_result = toml_parse_file_ex(g_config_path);

	g_launcher_config.main.close_after_executing = launcher_config_parser_get_bool("main.close_after_executing", 0);

	g_launcher_config.input.format = launcher_config_parser_get_str("input.format", "Run: ");
	g_launcher_config.input.fg = launcher_hex_to_int(launcher_config_parser_get_str("input.fg", NULL));
	g_launcher_config.input.bg = launcher_hex_to_int(launcher_config_parser_get_str("input.bg", NULL));
	g_launcher_config.input.make_bold = launcher_config_parser_get_bool("input.bold", 0);
	g_launcher_config.input.make_underlined = launcher_config_parser_get_bool("input.underline", 0);

	g_launcher_config.value.format = launcher_config_parser_get_str("value.format", "%s");
	g_launcher_config.value.fg = launcher_hex_to_int(launcher_config_parser_get_str("value.fg", NULL));
	g_launcher_config.value.bg = launcher_hex_to_int(launcher_config_parser_get_str("value.bg", NULL));
	g_launcher_config.value.make_bold = launcher_config_parser_get_bool("value.bold", 0);
	g_launcher_config.value.make_underlined = launcher_config_parser_get_bool("value.underline", 0);

	g_launcher_config.selected.format = launcher_config_parser_get_str("selected.format", " » %s");
	g_launcher_config.selected.fg = launcher_hex_to_int(launcher_config_parser_get_str("selected.fg", NULL));
	g_launcher_config.selected.bg = launcher_hex_to_int(launcher_config_parser_get_str("selected.bg", NULL));
	g_launcher_config.selected.make_bold = launcher_config_parser_get_bool("selected.bold", 0);
	g_launcher_config.selected.make_underlined = launcher_config_parser_get_bool("selected.underline", 0);
	
	g_launcher_config.unselected.format = launcher_config_parser_get_str("unselected.format", "%s");
	g_launcher_config.unselected.fg = launcher_hex_to_int(launcher_config_parser_get_str("unselected.fg", NULL));
	g_launcher_config.unselected.bg = launcher_hex_to_int(launcher_config_parser_get_str("unselected.bg", NULL));
	g_launcher_config.unselected.make_bold = launcher_config_parser_get_bool("unselected.bold", 0);
	g_launcher_config.unselected.make_underlined = launcher_config_parser_get_bool("unselected.underline", 0);	
}

char*	launcher_config_parser_get_str(const char* path, char* _default)
{
	t_toml_datum maybe_str = toml_seek(g_parsing_result.toptab, path);

	if(maybe_str.type == TOML_STRING)
	{
		return (char*)maybe_str.u.s;
	}

	return _default;
}

unsigned char	launcher_config_parser_get_bool(const char* path, unsigned char _default)
{
	t_toml_datum maybe_bool = toml_seek(g_parsing_result.toptab, path);

	if(maybe_bool.type == TOML_BOOLEAN)
	{
		return (unsigned char)maybe_bool.u.boolean;
	}

	return _default;
}

int	launcher_config_parser_get_int(const char* path, int _default)
{
	t_toml_datum maybe_int = toml_seek(g_parsing_result.toptab, path);

	if(maybe_int.type == TOML_INT64)
	{
		return (int)maybe_int.u.int64;
	}

	return _default;
}

void launcher_create_config_path()
{
	char* home_path = getenv("HOME");

	LAUNCHER_ASSERT(home_path == NULL, "Home path is not defined!");
	LAUNCHER_ASSERT(snprintf(
		g_config_path, 
		LAUNCHER_CONFIG_PATH_BUFF_SIZE, 
		"%s/%s", 
		home_path, g_file_path) == -1, "Can not create full path to configuration file!");
}

int launcher_hex_to_int(const char* hex_str)
{
	if(hex_str == NULL)
	{
		return -1;
	}

	if(*hex_str == '#')
	{
		return (int)strtoll(hex_str + 1, NULL, 16);
	}
	else
	{
		return (int)strtoll(hex_str, NULL, 16);
	}

	return 0;
}

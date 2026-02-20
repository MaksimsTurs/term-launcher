#ifndef H_LAUNCHER_CONFIG
#define H_LAUNCHER_CONFIG

#include "utility.h"

#include "tomlc17.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LAUNCHER_CONFIG_PATH_BUFF_SIZE 128

typedef toml_result_t t_toml_result;
typedef toml_datum_t t_toml_datum;

typedef struct s_launcher_main_config {
	unsigned char close_after_executing;
} t_launcher_main_config;

typedef struct s_launcher_element_config {
	char* 				format;

	int						fg;
	int						bg;

	unsigned char make_bold;
	unsigned char make_underlined;
} t_launcher_element_config;

typedef struct s_launcher_config {
	t_launcher_main_config 		main;
	t_launcher_element_config input;
	t_launcher_element_config value;
	t_launcher_element_config selected;
	t_launcher_element_config unselected;
} t_launcher_config;

t_launcher_config* 	launcher_get_config();

void								launcher_load_config();

void								launcher_create_config_path();
int									launcher_hex_to_int(const char* hex_str);

char*								launcher_config_parser_get_str(const char* path, char* _default);
unsigned char				launcher_config_parser_get_bool(const char* path, unsigned char _default);
int									launcher_config_parser_get_int(const char* path, int _default);


#endif

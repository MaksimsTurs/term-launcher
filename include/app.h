#ifndef H_LAUNCHER_APP
#define H_LAUNCHER_APP

#include "logging.h"
#include "input.h"

#include <string.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

typedef DIR 					t_directory;
typedef struct dirent t_dirent;

#define LAUNCHER_EQU_FACTOR 0.4f

#define LAUNCHER_APPS_DEFAULT_CAPACITY 50

typedef struct s_app {
	char* name;
	int		name_length;
	float	equ;
} t_app;

typedef struct s_apps {
	int			size;
	int 		capacity;
	t_app* 	items;
} t_apps;

void launcher_collect_apps(const char** paths, int paths_length, t_apps* apps);
void launcher_filter(t_input_buffer* app_name, t_apps* source, t_apps* dist);
void launcher_sort(t_apps* apps);
void launcher_replace_worst_match(float equ, t_app* app, t_apps* apps);

unsigned char launcher_is_apps_full(t_apps* apps);
unsigned char launcher_is_ignored_path(t_dirent dirent);

void launcher_init_apps(t_apps* apps);
void launcher_realloc_apps(t_apps* apps);
void launcher_free_apps(t_apps* apps);

#endif

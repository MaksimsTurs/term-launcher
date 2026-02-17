#include "app.h"
#include "utility.h"

void launcher_collect_apps(const char** paths, int paths_length, t_apps* apps)
{
	t_directory* directory = NULL;
	t_dirent* dirent = NULL;

	for(int index = 0; index < paths_length; index++)
	{
		directory = opendir(paths[index]);

		if(directory)
		{
			while((dirent = readdir(directory)) != NULL)
			{
				if(launcher_is_apps_full(apps))
				{
					launcher_realloc_apps(apps);
				}

				if(!launcher_is_ignored_path(*dirent))
				{
					apps->items[apps->size].name = strdup(dirent->d_name);
					apps->items[apps->size].name_length = strlen(dirent->d_name);
					apps->items[apps->size].equ = 0.0f;
					apps->size++;
				}
			}
		}
		else
		{
			LAUNCHER_LOG_AND_EXIT(-1, "Can not open a directory %s!", paths[index]);
		}

		closedir(directory);
	}
}

void launcher_filter(t_input_buffer* app_name, t_apps* source, t_apps* dist)
{
	dist->size = 0;

	int sum = 0;
	float equ = 0.0f;

	for(int index = 0; index < source->size; index++)
	{
		sum = launcher_compare_names(app_name->value, source->items[index].name, source->items[index].name_length);
		
		if(sum != 0)
		{
			equ = (float)sum / source->items[index].name_length;

			// As long as dist is not full, simple push new item.
			if(equ >= LAUNCHER_EQU_FACTOR && dist->size < dist->capacity)
			{
				dist->items[dist->size] = source->items[index];
				dist->items[dist->size].equ = equ;
				dist->size++;
			}
			// As long as dist is full, replace items with smalles equ.
			else if(equ >= LAUNCHER_EQU_FACTOR)
			{
				launcher_replace_worst_match(equ, &source->items[index], dist);
			}
		}
	}
}

void launcher_sort(t_apps* apps)
{
	for(int index = 0; index < apps->size; index++)
	{
		for(int jndex = 0; jndex < apps->size; jndex++)
		{
			if(apps->items[index].equ > apps->items[jndex].equ)
			{
				const t_app tmp = apps->items[index];
				
				apps->items[index] = apps->items[jndex];
				apps->items[jndex] = tmp;
			}
		}
	}
}

void launcher_replace_worst_match(float equ, t_app* app, t_apps* apps)
{
	t_app* worst_match = NULL;
	int worst_match_index = -1;

	for(int index = 0; index < apps->size; index++)
	{
		if(worst_match == NULL && equ > apps->items[index].equ)
		{
			worst_match = &apps->items[index];
			worst_match_index = index;
		}
		else if(worst_match != NULL && worst_match->equ > apps->items[index].equ)
		{
			worst_match = &apps->items[index];
			worst_match_index = index;
		}
	}

	if(worst_match != NULL && worst_match_index != -1)
	{
		apps->items[worst_match_index] = *app;
		apps->items[worst_match_index].equ = equ;
	}
}

void launcher_init_apps(t_apps* apps)
{
	apps->size = 0;
	apps->capacity = LAUNCHER_APPS_DEFAULT_CAPACITY;
	apps->items = (t_app*)malloc(sizeof(t_app) * apps->capacity);

	if(apps->items == NULL)
	{
		LAUNCHER_LOG_AND_EXIT(-1, "Can not initialize memory for applications!");
	}
}

void launcher_realloc_apps(t_apps* apps)
{
	t_app* tmp = NULL;
	
	apps->capacity *= 2;
	tmp = (t_app*)realloc(apps->items, sizeof(t_app) * apps->capacity);
	
	if(tmp == NULL)
	{
		LAUNCHER_LOG_AND_EXIT(-1, "Can not reallocate memory for applications!");
	}

	apps->items = tmp;
}

void launcher_free_apps(t_apps* apps)
{
	apps->size = 0;
	apps->capacity = 0;
	free(apps->items);
	apps->items = NULL;
}

unsigned char launcher_is_apps_full(t_apps* apps)
{
	return apps->size >= apps->capacity;
}

unsigned char launcher_is_ignored_path(t_dirent dirent)
{
	return dirent.d_name[0] == '.';
}

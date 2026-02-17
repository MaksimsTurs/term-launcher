#include "launcher.h"

static t_launcher_state launcher_state = { 
	.selected_app = 0,
	.is_running = 1
};
static const char* usr_paths[2] = { 
	"/usr/local/bin", 
	"/usr/bin" 
};
static const long long usr_paths_count = sizeof(usr_paths) / sizeof(usr_paths[0]);

void launcher_run_app()
{
	t_app* app = &launcher_state.finded_apps.items[launcher_state.selected_app];
	char* args[] = { app->name, NULL };
	pid_t pid = fork();

	if(pid == 0)
	{
		setsid();

    freopen("/dev/null", "r", stdin);
    freopen("/dev/null", "w", stdout);
    freopen("/dev/null", "w", stderr);
		
		execvp(app->name, args);
	}

	exit(0);
}

void launcher_init()
{
	launcher_init_apps(&launcher_state.usr_apps);
	launcher_init_apps(&launcher_state.finded_apps);
	launcher_collect_apps(usr_paths, usr_paths_count, &launcher_state.usr_apps);
}

void launcher_run()
{
	launcher_clear_screen();

	while(launcher_state.is_running)
	{
		launcher_render();
		launcher_process_input();
		launcher_process_data();
	}
}

void launcher_destroy()
{
	launcher_free_apps(&launcher_state.usr_apps);
	launcher_free_apps(&launcher_state.finded_apps);
}

void launcher_process_data()
{
	launcher_filter(&launcher_state.searched_app, &launcher_state.usr_apps, &launcher_state.finded_apps);
	launcher_sort(&launcher_state.finded_apps);	
}

void launcher_process_input()
{
	char ch = launcher_read_char();

	if(launcher_is_valid_key(ch))
	{
		switch(ch)
		{
			case LAUNCHER_KEY_ESCAPE:
				launcher_state.is_running = 0;
				launcher_clear_screen();
			break;
			case LAUNCHER_KEY_ARROW_UP:
				launcher_cursor_up();
			break;
			case LAUNCHER_KEY_ARROW_DOWN:
				launcher_cursor_down();
			break;
			case LAUNCHER_KEY_ENTER:
				if(launcher_state.selected_app >= 0)
				{
					launcher_run_app();
				}
			break;
			default:
				if(ch == LAUNCHER_KEY_DEL)
				{
					launcher_input_buffer_pop(&launcher_state.searched_app);
				}
				else
				{
					launcher_input_buffer_push(&launcher_state.searched_app, ch);
				}
		}
	}
}

void launcher_render()
{
	launcher_clear_screen();
	
	LAUNCHER_RENDER_INPUT(launcher_state.searched_app.value);

	for(int index = 0; index < launcher_state.finded_apps.size; index++)
	{
		if(launcher_state.selected_app != index)
		{
			LAUNCHER_RENDER_UNSELECTED_APPLICATION(launcher_state.finded_apps.items[index]);
		}
		else
		{
			LAUNCHER_RENDER_SELECTED_APPLICATION(launcher_state.finded_apps.items[index]);
		}
	}
}

void launcher_cursor_up()
{
	if(launcher_state.selected_app > 0)
	{
		launcher_state.selected_app--;
	}
}

void launcher_cursor_down()
{
	if(launcher_state.selected_app + 1 < launcher_state.finded_apps.size)
	{
		launcher_state.selected_app++;
	}
}

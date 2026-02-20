#include "launcher.h"

static t_launcher_state launcher_state = { 
	.selected_app = -1,
	.is_running = 1,
	.flags = {0},
};
static const char* usr_paths[2] = { 
	"/usr/local/bin", 
	"/usr/bin" 
};
static const long long usr_paths_count = sizeof(usr_paths) / sizeof(usr_paths[0]);

void launcher_run_app()
{
	LAUNCHER_ASSERT(!LAUNCHER_IN_ARR_BOUND(launcher_state.selected_app, launcher_state.finded_apps.size), "Can not run unknown application!");

	t_app* app = &launcher_state.finded_apps.items[launcher_state.selected_app];
	t_launcher_config* config = launcher_get_config();
	char* args[] = { app->name, NULL };
	pid_t pid = fork();

	LAUNCHER_ASSERT(pid == -1, "Can not create new process!");

	if(pid == 0)
	{
		LAUNCHER_ASSERT(setsid() == -1, "Can not create new session!");

    freopen("/dev/null", "r", stdin);
    freopen("/dev/null", "w", stdout);
    freopen("/dev/null", "w", stderr);
		
		LAUNCHER_ASSERT(execvp(app->name, args) == -1, "Can not execute programm %s", app->name);
	}

	if(config->main.close_after_executing)
	{
		kill(getppid(), SIGHUP);
	}

	exit(0);
}

void launcher_init(int argc, const char** argv)
{
	launcher_load_config();
	launcher_init_apps(&launcher_state.usr_apps);
	launcher_init_apps(&launcher_state.finded_apps);
	launcher_collect_apps(usr_paths, usr_paths_count, &launcher_state.usr_apps);
}

void launcher_run()
{
	launcher_clear_screen();

	if(launcher_state.flags.h)
	{
		launcher_print_flags();
	}
	else
	{
		while(launcher_state.is_running)
		{
			launcher_render();
			launcher_process_input();
			launcher_process_data();
		}
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
				launcher_run_app();
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
	launcher_render_input();
	launcher_render_input_value(launcher_state.searched_app.value);

	for(int index = 0; index < launcher_state.finded_apps.size; index++)
	{
		t_app* item = &launcher_state.finded_apps.items[index];

		if(launcher_state.selected_app != index)
		{
			launcher_render_unselected_item(item->name);
		}
		else
		{
			launcher_render_selected_item(item->name);
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

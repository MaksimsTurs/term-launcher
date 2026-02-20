#ifndef H_LAUNCHER
	#include "input.h"
	#include "render.h"
	#include "app.h"
	#include "utility.h"
	#include "flags.h"

	#include <stdlib.h>
	#include <unistd.h>
	#include <signal.h>

	typedef struct s_launcher_state {
		unsigned char 		is_running;

		t_input_buffer		searched_app;
		
		int				     		selected_app;
		
		t_apps				 		usr_apps;
		t_apps 						finded_apps;
	} t_launcher_state;

	// Core functions
	void launcher_init(int argc, const char** argv);
	void launcher_run();
	void launcher_destroy();

	void launcher_render();
	void launcher_process_input();
	void launcher_process_data();

	void launcher_run_app();
	// Keyboard event.
	void					launcher_cursor_up();
	void					launcher_cursor_down();
#endif

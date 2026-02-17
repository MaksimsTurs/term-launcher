#ifndef H_LAUNCHER
	#include "input.h"
	#include "render.h"
	#include "app.h"
	#include "utility.h"
	#include "flags.h"

	#include <stdlib.h>
	#include <errno.h>
	#include <unistd.h>
	#include <signal.h>

	#define LAUNCHER_KEY_DEL         	127
	#define LAUNCHER_KEY_ESCAPE				27
	#define LAUNCHER_KEY_ARROW_UP    	65
	#define LAUNCHER_KEY_ARROW_DOWN  	66
	#define LAUNCHER_KEY_ARROW_RIGHT 	67
	#define LAUNCHER_KEY_ARROW_LEFT  	68
	#define LAUNCHER_KEY_ENTER       	10

	typedef struct s_launcher_state {
		unsigned char 		is_running;

		t_input_buffer		searched_app;
		
		int				     		selected_app;
		
		t_apps				 		usr_apps;
		t_apps 						finded_apps;

		t_launcher_flags 	flags;
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

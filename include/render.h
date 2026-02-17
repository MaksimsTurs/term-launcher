#ifndef H_LAUNCHER_RENDER
#define H_LAUNCHER_RENDER

#include <stdio.h>

#define LAUNCHER_RENDER_INPUT(value) do { 														\
	printf("\x1b[38;2;137;180;250m Run »\x1b[0m %s\n", value); 		\
} while(0)
#define LAUNCHER_RENDER_UNSELECTED_APPLICATION(application) do {			\
	printf(" %s\n", application.name);																	\
} while(0)
#define LAUNCHER_RENDER_SELECTED_APPLICATION(application) do {				\
	printf("\x1b[48;2;69;71;90m  » %s «  \x1b[0m\n", application.name);	\
} while(0)

void launcher_clear_screen();

#endif

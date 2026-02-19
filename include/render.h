#ifndef H_LAUNCHER_RENDER
#define H_LAUNCHER_RENDER

#include "utility.h"

#include <stdio.h>

#define LAUNCHER_RENDER_INPUT(value) do { 																					\
	printf(LAUNCHER_BG LAUNCHER_RGB(137, 180, 250) "Run » \x1b[0m%s\n", value);	\
} while(0)
#define LAUNCHER_RENDER_UNSELECTED_APPLICATION(application) do {	\
	printf(LAUNCHER_BG LAUNCHER_RGB(137, 180, 250) "%s \x1b[0m\n", application.name);\
} while(0)
#define LAUNCHER_RENDER_SELECTED_APPLICATION(application) do {																\
	printf(LAUNCHER_BG LAUNCHER_RGB(137, 180, 250) "  » %s «  \x1b[0m\n", application.name);	\
} while(0)

void launcher_clear_screen();

#endif

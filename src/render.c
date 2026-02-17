#include "render.h"

void launcher_clear_screen()
{
	printf("\x1b[1;1H");
	printf("\x1b[0J");
	printf("\x1b[1J");
}

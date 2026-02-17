#include "launcher.h"

int main(void)
{
	launcher_init();
	launcher_run();
	launcher_destroy();

	return 0;
}

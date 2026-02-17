#include "launcher.h"

int main(int argc, const char** argv)
{
	launcher_init(argc, argv);
	launcher_run();
	launcher_destroy();

	return 0;
}

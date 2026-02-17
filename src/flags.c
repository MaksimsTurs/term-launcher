#include "flags.h"

void launcher_print_flags()
{
	printf("launcher -[flag]\n");
	printf("  -h: Print example of usage and list of flags.\n");
	printf("  -c: Close the terminal when application is executed.\n");
}

void launcher_set_flags(t_launcher_flags* flags, int argc, const char** argv)
{
	for(int index = 1; index < argc; index++)
	{
		if(!strncmp(argv[index], "-h", 3))
		{
			flags->h = 1;
		} 
		else if(!strncmp("-c", argv[index], 3))
		{
			flags->c = 1;
		}
	}
}

#include "utility.h"

int launcher_compare_names(const char* f_str, const char* s_str, int length)
{
	int sum = 0;

	for(int index = 0; index < length; index++)
	{
		if(f_str[index] == s_str[index])
		{
			sum++;
		}
	}

	return sum;
}

unsigned char launcher_is_valid_key(char ch)
{
	return(
		ch != LAUNCHER_KEY_ARROW_RIGHT &&
		ch != LAUNCHER_KEY_ARROW_LEFT
	);
}

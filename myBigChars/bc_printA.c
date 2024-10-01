#include "myBigChars.h"
#include <unistd.h>

int bc_printA(const char *str)
{
	if (str == NULL)
	{
		return -1;
	}

	EN_GRAPHIC;
	write(STDOUT_FILENO, str, strlen(str));
	DIS_GRAPHIC;

	return 0;
}
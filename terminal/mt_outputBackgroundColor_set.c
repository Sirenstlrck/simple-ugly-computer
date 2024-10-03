#include "terminal.h"

int mt_outputBackgroundColor_set(colors color)
{
	char str[256];
	sprintf(str, "\033[%dm", color + 10);
	write(STDOUT_FILENO, str, strlen(str));
	return 0;
}
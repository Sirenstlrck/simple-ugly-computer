#include "myTerm.h"

int mt_setForegroundColor(colors color)
{
	char str[256];
	sprintf(str, "\033[%dm", color);
	write(STDOUT_FILENO, str, strlen(str));
	return 0;
}
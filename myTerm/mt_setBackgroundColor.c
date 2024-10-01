#include "myTerm.h"

int mt_setBackgroundColor(colors color)
{
	char str[256];
	sprintf(str, "\033[%dm", color + 10);
	write(STDOUT_FILENO, str, strlen(str));
	return 0;
}
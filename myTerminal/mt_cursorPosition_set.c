#include "myTerminal.h"

int mt_cursorPosition_set(int x, int y)
{
	char str[256];
	sprintf(str, "\033[%d;%dH", y, x);
	write(STDOUT_FILENO, str, strlen(str));
	return 0;
}
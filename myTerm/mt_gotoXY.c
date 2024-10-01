#include "myTerm.h"

int mt_gotoXY(int x, int y)
{
	char str[256];
	sprintf(str, "\033[%d;%dH", y, x);
	write(STDOUT_FILENO, str, strlen(str));
	return 0;
}
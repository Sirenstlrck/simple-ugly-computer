#include "myTerm.h"

int mt_getScreenSize(int *rows, int *cols)
{
	int flag = 0;
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	*rows = w.ws_row;
	*cols = w.ws_col;
	if (*rows == 0 || *cols == 0)
	{
		flag = -1;
	}
	return flag;
}
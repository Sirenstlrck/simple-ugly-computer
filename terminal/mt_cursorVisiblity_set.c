#include "terminal.h"

int mt_cursorVisiblity_set(int value)
{
	if (value == 1)
	{
		write(STDOUT_FILENO, "\033[?25h", 7);
	}
	else
	{
		write(STDOUT_FILENO, "\033[?25l", 7);
	}
	return 0;
}
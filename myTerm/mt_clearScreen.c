#include "myTerm.h"

int mt_clearScreen(void)
{
	write(STDOUT_FILENO, "\033[2J\033[H", 7);
	return 0;
}
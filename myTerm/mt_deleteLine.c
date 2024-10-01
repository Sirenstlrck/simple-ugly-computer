#include "myTerm.h"

int mt_deleteLine(void)
{
	write(STDOUT_FILENO, "\033[K", 4);
	return 0;
}
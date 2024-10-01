#include "myTerm.h"

int mt_setDefaultColor(void)
{
	write(STDOUT_FILENO, "\033[0m", 4);
	return 0;
}
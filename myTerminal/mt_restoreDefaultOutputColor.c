#include "myTerminal.h"

int mt_restoreDefaultOutputColor(void)
{
	write(STDOUT_FILENO, "\033[0m", 4);
	return 0;
}
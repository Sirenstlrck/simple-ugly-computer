#include "myTerminal.h"

int mt_screen_clear(void)
{
	write(STDOUT_FILENO, "\033[2J\033[H", 7);
	return 0;
}
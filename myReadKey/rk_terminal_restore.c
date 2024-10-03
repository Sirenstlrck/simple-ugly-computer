#include "myReadKey.h"

int rk_terminal_restore()
{
	return tcsetattr(STDIN_FILENO, TCSAFLUSH, &lastSavedTermios);
}
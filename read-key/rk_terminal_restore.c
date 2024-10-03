#include "read_key.h"

int rk_terminal_restore()
{
	return tcsetattr(STDIN_FILENO, TCSAFLUSH, &lastSavedTermios);
}
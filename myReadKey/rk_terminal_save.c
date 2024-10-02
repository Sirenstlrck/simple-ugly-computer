#include "myReadKey.h"

int rk_terminal_save()
{
	if (tcgetattr(STDIN_FILENO, &lastSavedTermios) == -1)
	{
		return -1;
	}
	lastSavedTermios_echoMode = lastSavedTermios.c_lflag & ECHO;
	lastSavedTermios_signalValue = lastSavedTermios.c_lflag & ISIG;
	return 0;
}
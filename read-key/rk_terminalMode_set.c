#include "read_key.h"

int rk_terminalMode_set(int isCannonicalMode, int inputTimeoutValue,
						int minChars, int isEchoEnabled, int isSignalProcessed)
{
	struct termios newTermios;

	if (tcgetattr(STDIN_FILENO, &newTermios) == -1)
	{
		return -1;
	}

	if (isCannonicalMode == 0)
	{
		newTermios.c_lflag |= ICANON;
		newTermios.c_cc[VTIME] = 1;
		newTermios.c_cc[VMIN]  = 1;
		newTermios.c_lflag |= ISIG;
		newTermios.c_lflag |= ECHO;
	}
	else if (isCannonicalMode == 1)
	{
		newTermios.c_lflag &= ~(ICANON);
		newTermios.c_cc[VTIME] = inputTimeoutValue;
		newTermios.c_cc[VMIN]  = minChars;
	}

	if (isEchoEnabled == 0)
		newTermios.c_lflag &= ~(ECHO);

	else if (isEchoEnabled == 1)
		newTermios.c_lflag |= ECHO;

	if (isSignalProcessed == 0)
		newTermios.c_lflag &= ~(ISIG);

	else if (isSignalProcessed == 1)
		newTermios.c_lflag |= ISIG;

	if (tcsetattr(STDIN_FILENO, TCSANOW, &newTermios) == -1)
		return -1;

	return 0;
}
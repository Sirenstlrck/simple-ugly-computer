#include "console.h"

void mc_cpuInfo_render()
{
	mt_cursorPosition_set(4, 32);
	write(STDOUT_FILENO, "Andrey Mischuk IP-212", 24);
}

void mc_inputRequest_render()
{
	mt_cursorPosition_set(4, 31);
	rk_terminal_save();
	rk_terminalMode_set(1, 100, 0, 1, 0);
	write(STDOUT_FILENO, "Enter value: ", 14);
	fflush(stdin);
	char buffer[100];
	int size;
	size	  = read(0, buffer, sizeof(buffer));
	int value = atoi(buffer);
	sc_intHandler_writeInput(value);
	rk_terminal_restore();
}
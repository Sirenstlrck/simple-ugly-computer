#include "console.h"

extern char inoutMem[INOUT_MEM_SIZE][256];

void mc_cpuInfo_render()
{
	for (int i = 0; i < INOUT_MEM_SIZE - 1; ++i)
	{
		strcpy(inoutMem[i], inoutMem[i + 1]);
	}
	// sprintf(inoutMem[INOUT_MEM_SIZE - 1], "%s", "Andrey Mischuk IP-212");
	mc_history_render();
}

void mc_outputRequest_render()
{
	int result = sc_intHandlet_getWriteData();

	for (int i = 0; i < INOUT_MEM_SIZE - 1; ++i)
	{
		strcpy(inoutMem[i], inoutMem[i + 1]);
	}
	sprintf(inoutMem[INOUT_MEM_SIZE - 1], "%d", result);
	mc_history_render();
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
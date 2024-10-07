#include "console.h"
#include "memory/controller.h"

extern char inoutMem[INOUT_MEM_SIZE][256];

void mc_history_render()
{
	int x = 3;
	int y = 25;
	mt_cursorPosition_set(x, y);
	for (int i = INOUT_MEM_SIZE - 1; i >= 0; --i)
	{
		mt_cursorPosition_set(x, y + 4);
		--y;
		write(STDOUT_FILENO, inoutMem[i], strlen(inoutMem[i]));
	}
}
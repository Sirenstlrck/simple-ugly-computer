#include "console.h"

void mc_clearSpace(int x_start, int y_start, int x_end, int y_end)
{
	for (int i = x_start; i < x_end; i++)
	{
		for (int j = y_start; j < y_end; j++)
		{
			mt_outputBackgroundColor_set(Black);
			mt_outputForegroundColor_set(White);
			mt_cursorPosition_set(i, j);
			write(STDIN_FILENO, " ", 1);
		}
	}
	mt_restoreDefaultOutputColor();
}
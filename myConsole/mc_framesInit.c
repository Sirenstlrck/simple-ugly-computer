#include "myConsole.h"
#include "mySimpleComputer.h"
#include "myTerm.h"

void strtoupper(char *s)
{
	while (*s)
	{
		*s = toupper((unsigned char)*s);
		s++;
	}
}

void mc_memoryManipulatorInit()
{
	int x_point = 7, y_point = 3, x_startPoint = x_point;

	srand(time(NULL));
	for (int i = 0; i < MEMORY_SIZE; ++i)
	{
		int value = rand() % MAX_WORD - 1;
		sc_memory_set(i, value);
		if (i % 8 == 0)
		{
			x_point = x_startPoint;
			y_point++;
		}
		mt_gotoXY(x_point, y_point);
		x_point += 7;
		char str[6];
		sprintf(str, "+%04x", value);
		strtoupper(str);
		write(STDOUT_FILENO, (str), 5);
	}
}

void mc_clearSpace(int x_start, int y_start, int x_end, int y_end)
{
	for (int i = x_start; i < x_end; i++)
	{
		for (int j = y_start; j < y_end; j++)
		{
			mt_setBackgroundColor(Black);
			mt_setForegroundColor(White);
			mt_gotoXY(i, j);
			write(STDIN_FILENO, " ", 1);
			mt_setDefaultColor();
		}
	}
}

void mc_framesInit()
{
	mt_clearScreen();
	bc_drawBox(1, 1, 120, 35, 2, White, Black, "Simple Computer", Green, White);

	bc_drawBox(80, 2, 37, 11, 2, White, Black, " Edit cell ", Green, Black);

	bc_drawBox(66, 2, 12, 11, 2, White, Black, " Formats ", Green, Black);

	bc_drawBox(3, 2, 61, 20, 27, White, Black, "  RAM  ", Red, Black);

	mc_memoryManipulatorInit();

	bc_printBigChar(82, 4, "+0000");
}
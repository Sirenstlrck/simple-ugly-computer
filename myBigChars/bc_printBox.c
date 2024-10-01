#include "myBigChars.h"
#include <unistd.h>

int bc_printBox(int x, int y, int width, int height, colors box_fg,
				colors box_bg, char *header, colors header_fg, colors header_bg)
{
	if (header != NULL && strlen(header) > 0)
	{
		int available_width = width - x - 2;
		int header_x = x + (available_width - strlen(header)) / 2;
		int header_y = y;

		mt_setForegroundColor(header_fg);
		mt_setBackgroundColor(header_bg);

		mt_gotoXY(header_x, header_y);
		write(STDOUT_FILENO, header, strlen(header));
	}

	EN_GRAPHIC;
	mt_setBackgroundColor(box_bg);
	mt_setForegroundColor(box_fg);

	mt_gotoXY(x, y);

	write(STDOUT_FILENO, "l", 1);
	for (int i = 0; i < width; ++i)
	{
		write(STDOUT_FILENO, "q", 1);
	}
	write(STDOUT_FILENO, "k", 1);

	for (int i = 0; i < height; ++i)
	{
		mt_gotoXY(x, i);
		write(STDOUT_FILENO, "x", 1);
		if (x == 0)
		{
			mt_gotoXY(width + 1, i);
			write(STDOUT_FILENO, "x", 1);
		}
		else
		{
			mt_gotoXY(width, i);
			write(STDOUT_FILENO, "x", 1);
		}
	}

	mt_gotoXY(x, height);
	write(STDOUT_FILENO, "m", 1);
	for (int i = x + 1; i < width; ++i)
	{
		write(STDOUT_FILENO, "q", 1);
	}
	write(STDOUT_FILENO, "j", 1);
	DIS_GRAPHIC;

	mt_setDefaultColor();
	return 0;
}
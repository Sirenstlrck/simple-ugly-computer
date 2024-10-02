#include "myBigChars.h"
#include "myTerm.h"
#include <unistd.h>

int bc_drawBox(int x, int y, int width, int height, int header_shift,
			   colors box_fg, colors box_bg, char *header, colors header_fg,
			   colors header_bg)
{
	EN_GRAPHIC;
	mt_setBackgroundColor(box_bg);
	mt_setForegroundColor(box_fg);

	mt_gotoXY(x, y);

	write(STDOUT_FILENO, "l", 1);
	for (int i = 0; i < width - 1; ++i)
	{
		write(STDOUT_FILENO, "q", 1);
	}
	write(STDOUT_FILENO, "k", 1);

	for (int i = 1; i < height; ++i)
	{
		mt_gotoXY(x, y + i);
		write(STDOUT_FILENO, "x", 1);
		mt_gotoXY(x + width, y + i);
		write(STDOUT_FILENO, "x", 1);
	}

	mt_gotoXY(x, y + height - 1);
	write(STDOUT_FILENO, "m", 1);
	for (int i = 0; i < width - 1; ++i)
	{
		write(STDOUT_FILENO, "q", 1);
	}
	write(STDOUT_FILENO, "j", 1);
	DIS_GRAPHIC;

	if (header != NULL && strlen(header) > 0)
	{

		mt_setForegroundColor(header_fg);
		mt_setBackgroundColor(header_bg);

		mt_gotoXY(x + header_shift, y);
		write(STDOUT_FILENO, header, strlen(header));
	}

	mt_setDefaultColor();
	return 0;
}
#include "big_chars.h"
#include "terminal.h"
#include <unistd.h>

int bc_frame_draw(int x, int y, int width, int height, int header_shift,
				  colors box_fg, colors box_bg, char *header, colors header_fg,
				  colors header_bg)
{
	EN_GRAPHIC;
	mt_outputBackgroundColor_set(box_bg);
	mt_outputForegroundColor_set(box_fg);

	mt_cursorPosition_set(x, y);

	write(STDOUT_FILENO, "l", 1);
	for (int i = 0; i < width - 1; ++i)
	{
		write(STDOUT_FILENO, "q", 1);
	}
	write(STDOUT_FILENO, "k", 1);

	for (int i = 1; i < height; ++i)
	{
		mt_cursorPosition_set(x, y + i);
		write(STDOUT_FILENO, "x", 1);
		mt_cursorPosition_set(x + width, y + i);
		write(STDOUT_FILENO, "x", 1);
	}

	mt_cursorPosition_set(x, y + height - 1);
	write(STDOUT_FILENO, "m", 1);
	for (int i = 0; i < width - 1; ++i)
	{
		write(STDOUT_FILENO, "q", 1);
	}
	write(STDOUT_FILENO, "j", 1);
	DIS_GRAPHIC;

	if (header != NULL && strlen(header) > 0)
	{

		mt_outputForegroundColor_set(header_fg);
		mt_outputBackgroundColor_set(header_bg);

		mt_cursorPosition_set(x + header_shift, y);
		write(STDOUT_FILENO, header, strlen(header));
	}

	mt_restoreDefaultOutputColor();
	return 0;
}
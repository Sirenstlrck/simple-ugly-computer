#include "console.h"

int mc_label_render(Label_t label)
{
	mt_cursorPosition_set(label.x_position, label.y_position);
	mt_outputBackgroundColor_set(label.background_color);
	mt_outputForegroundColor_set(label.foreground_color);

	char *str = mc_wordToHex(label.content);
	write(STDOUT_FILENO, str, strlen(str));

	mt_restoreDefaultOutputColor();
}
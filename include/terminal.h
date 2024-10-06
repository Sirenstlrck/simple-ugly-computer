#ifndef _MY_TERMINAL_H
#define _MY_TERMINAL_H

#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

typedef enum
{
	Black = 30,
	Red,
	Green,
	Yellow,
	Blue,
	Magenta,
	Cyan,
	White
} colors;

#define MIN_SCREEN_WITDH  128
#define MIN_SCREEN_HEIGHT 36

int mt_screen_clear();

int mt_screenSize_get(int *rows, int *cols);

int mt_cursorPosition_set(int x, int y);

int mt_cursorVisiblity_set(int value);

int mt_outputForegroundColor_set(colors color);

int mt_outputBackgroundColor_set(colors color);

int mt_restoreDefaultOutputColor();

int mt_deleteLine();

#endif // _MY_TERMINAL_H
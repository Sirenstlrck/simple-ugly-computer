#ifndef _MY_TERM_H
#define _MY_TERM_H

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

#define MIN_SCREEN_WITDH 128
#define MIN_SCREEN_HEIGHT 36

int mt_clearScreen();

int mt_gotoXY(int x, int y);

int mt_getScreenSize(int *rows, int *cols);

int mt_setForegroundColor(colors color);

int mt_setBackgroundColor(colors color);

int mt_setDefaultColor();

int mt_setCursorVisible(int value);

int mt_deleteLine();

#endif // _MY_TERM_H
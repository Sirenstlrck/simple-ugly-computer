#ifndef _MY_TERM_H
#define _MY_TERM_H

#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

typedef enum
{
	BLACK = 30,
	RED,
	GREEN,
	YELLOW,
	BLUE,
	MAGENTA,
	CYAN,
	WHITE
} colors;

#define MIN_SCREEN_WITDH 110
#define MIN_SCREEN_HEIGHT 28
/**
 * @brief Clear the screen
 */
int mt_clearScreen();
/**
 * @brief Set the cursor position
 * @param x row pos
 * @param y col pos
 */
int mt_gotoXY(int x, int y);
/**
 * @brief Get screen size
 * @param rows screen height
 * @param cols screen width
 */
int mt_getScreenSize(int *rows, int *cols);
/**
 * @brief Set the foreground color
 * @param color foreground color
 */
int mt_setForegroundColor(colors color);
/**
 * @brief Set the background color
 * @param color background color
 */
int mt_setBackgroundColor(colors color);
/**
 * @brief Set the default color
 */
int mt_setDefaultColor();
/**
 * @brief Changes cursor visibility
 * @param visibility 1 for visible, 0 for invisible
 */
int mt_setCursorVisible(int value);
/**
 * @brief Deletes the current line
 */
int mt_deleteLine();

#endif // _MY_TERM_H
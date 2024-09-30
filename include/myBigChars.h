#ifndef _MY_BIG_CHARS_H
#define _MY_BIG_CHARS_H

#include "myGraphics.h"
#include "mySimpleComputer.h"
#include "myTerm.h"
#include <stddef.h>
#include <stdlib.h>

#define BIG_CHAR_SIZE 8
#define EN_GRAPHIC write(1, "\E(0", 4)
#define DIS_GRAPHIC write(1, "\E(B", 4)

/**
 * @brief finds the length of the UTF-8 string
 * @return length of the UTF-8 string, if can't decode or pointer is NULL,
 * returns 0
 * @param str pointer to the UTF-8 string
 */
size_t bc_strlen(const char *str);
/**
 * @brief prints the UTF-8 string
 * @param str pointer to the UTF-8 string
 */
int bc_printA(const char *str);
/**
 * @brief prints the border of x,y and header of border with colors
 * @param x1 start x position
 * @param y1 start y position
 * @param x2 end x position
 * @param y2 end y position
 * @param box_fg color of the border foreground
 * @param box_bg color of the border background
 * @param header pointer to the UTF-8 string
 * @param header_fg color of the header foreground
 * @param header_bg color of the header background
 */
int bc_box(int x1, int y1, int x2, int y2, colors box_fg, colors box_bg,
		   char *header, colors header_fg, colors header_bg);
/**
 * @brief manipulates the font element and sets the value of the character
 * space in it to value in the x row and y column to value;
 * @return 0
 * @param big pointer to the font element
 * @param x row of the character space
 * @param y column of the character space
 * @param value value of the character
 */
int bc_setBigCharPos(int *big, int x, int y, int value);
/**
 * @brief gets the font element and sets the value of the character space in it
 * to value in the x row and y column to value;
 * @return 0
 * @param big pointer to the font element
 * @param x row of the character space
 * @param y column of the character space
 * @param value pointer to get value of the character
 */
int bc_getBigCharPos(int *big, int x, int y, int *value);
/**
 * @brief displays a "large symbol" with a size of eight rows by eight columns\
 * @param x left corner
 * @param y top corner
 * @param fg foreground color
 * @param bg background color
 */
int bc_printBigChar(int ch[2], int x, int y, colors fg, colors bg);
/**
 * @brief writes number of big characters to the file
 * @attention binary mode
 * @param fd file descriptor
 * @param big pointer to the font element
 * @param count number of big characters
 */
int bc_bigCharWrite(int fd, int *big, int count);
/**
 * @brief reads number of big characters from the file
 * @attention binary mode
 * @param fd file descriptor
 * @param big pointer to the font element
 * @param need_count number of big characters
 * @param count pointer to the number of big characters read
 */
int bc_bigCharRead(int fd, int *big, int need_count, int *count);

int bc_printBigCell(int address, int big_arr[18][2]);
#endif // _MY_BIG_CHARS_H

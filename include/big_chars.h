#ifndef _MY_BIG_CHARS_H
#define _MY_BIG_CHARS_H

#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "terminal.h"

#define EN_GRAPHIC write(1, "\E(0", 4)
#define DIS_GRAPHIC write(1, "\E(B", 4)

#define BIG_CHAR_LETTER_HEIGHT 6
#define BIG_CHAR_LETTER_WIDTH 19

size_t bc_strlen(const char *str);

int bc_printBigChar(int x, int y, const char *str);

int bc_drawBox(int x1, int y1, int width, int height, int header_shift,
			   colors box_fg, colors box_bg, char *header, colors header_fg,
			   colors header_bg);

int bc_setBigCharPos(int *big, int x, int y, int value);

int bc_getBigCharPos(int *big, int x, int y, int *value);

int bc_bigCharWrite(int fd, int *big, int count);

int bc_bigCharRead(int fd, int *big, int need_count, int *count);

int bc_printBigCell(int address, int big_arr[18][2]);
#endif // _MY_BIG_CHARS_H

#ifndef _MY_CONSOLE_H
#define _MY_CONSOLE_H

#include <stdlib.h>
#include <time.h>

#include "big_chars.h"
#include "cpu/registers.h"
#include "memory/config.h"
#include "read_key.h"
#include "terminal.h"

typedef struct Label
{
	int x_position;
	int y_position;
	char *content;
	colors background_color;
	colors foreground_color;
} Label_t;

static Label_t memoryManipulator[MEMORY_SIZE];
static int selectedAddressIndex = 0;
static int isImpulseTact		= 0;
static int exitFlag				= 0;

void mc_frames_render();
void mc_clearSpace(int x_start, int y_start, int x_end, int y_end);

void mc_memoryManipulator_init();
void mc_memoryManipulator_render();
void mc_memoryManipulator_move(enum Keys key);

int mc_label_set(Label_t *label, Label_t newLabel);
int mc_label_render(Label_t *label);
void mc_selectedLabel_set(int address);

#endif // _MY_CONSOLE_H
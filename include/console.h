#ifndef _MY_CONSOLE_H
#define _MY_CONSOLE_H

#include <signal.h>
#include <stdlib.h>
#include <time.h>

#include "big_chars.h"
#include "cpu/cpu.h"
#include "cpu/registers.h"
#include "memory/config.h"
#include "read_key.h"
#include "terminal.h"
#include "word/def.h"
#include "word/word.h"

typedef struct Label
{
	int x_position;
	int y_position;
	Word_t content;
	colors background_color;
	colors foreground_color;
} Label_t;

extern Label_t memoryManipulator[MEMORY_SIZE];
extern Label_t instractionCounterLabel;
extern Label_t accumulatorLabel;
extern Label_t selecionLabel;
extern int selectedAddressIndex;

void mc_clearSpace(int x_start, int y_start, int x_end, int y_end);

void mc_memoryManipulator_move(enum Keys key);

int mc_label_set(Label_t *label, Label_t newLabel);
int mc_label_render(Label_t label);
void mc_selectedLabel_set(int address);

void mc_start();

void mc_staticFrames_render();
void mc_updateRender();
void mc_memoryManipulator_render();
void mc_instructionCounter_render();
void mc_accumulator_render();
void mc_flags_render();
void mc_cache_render();
void mc_formats_render(Word_t word);
void mc_inputRequest_render();
void mc_cpuInfo_render();

char *mc_wordToOct(Word_t word);
char *mc_wordToDec(Word_t word);
char *mc_wordToHex(Word_t word);

#endif // _MY_CONSOLE_H
#ifndef _MY_CONSOLE_H
#define _MY_CONSOLE_H

#include <stdlib.h>
#include <time.h>

#include "big_chars.h"
#include "simple_computer.h"
#include "terminal.h"

extern int memory[MEMORY_SIZE];

void mc_framesInit();
void mc_clearSpace(int x_start, int y_start, int x_end, int y_end);

#endif // _MY_CONSOLE_H
#ifndef _MY_CONSOLE_H
#define _MY_CONSOLE_H

#include "myBigChars.h"
#include "mySimpleComputer.h"
#include "myTerm.h"

#include <stdlib.h>
#include <time.h>

extern int memory[MEMORY_SIZE];

void mc_framesInit();
void mc_clearSpace(int x_start, int y_start, int x_end, int y_end);

#endif // _MY_CONSOLE_H
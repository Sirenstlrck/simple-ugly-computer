#include "mySimpleComputer.h"

int memory[MEMORY_SIZE];
int accumulator;
int instructionCounter;
int clockCounter;
int flags;

CacheLine_t cache[CACHE_SIZE];
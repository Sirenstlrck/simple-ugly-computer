#ifndef SC_MEMORY_CONTROLLER_H
#define SC_MEMORY_CONTROLLER_H

#include "memory/config.h"
#include "word/def.h"
#include "word/word.h"

#define INOUT_MEM_SIZE 5

void sc_memoryController_init();

typedef struct MemoryAccessResult
{
	unsigned char outOfBoundsError;
	unsigned char cost;
} MemoryAccessResult_t;

void sc_memoryController_flushCache();

// for ui :)
int sc_memoryController_getDirect(int address, Word_t *out);
int sc_memoryController_setDirect(int address, Word_t out);
//

MemoryAccessResult_t sc_memoryController_get(int address, Word_t *out);
MemoryAccessResult_t sc_memoryController_set(int address, Word_t value);

extern char inoutMem[INOUT_MEM_SIZE][256];

#endif
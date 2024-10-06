#ifndef SC_MEMORY_CONTROLLER_H
#define SC_MEMORY_CONTROLLER_H

#include "memory/config.h"
#include "word/def.h"

void sc_memoryController_init();

typedef struct MemoryAccessResult
{
	unsigned char outOfBoundsError;
	unsigned char cost;
} MemoryAccessResult_t;

void sc_memoryController_flushCache();

MemoryAccessResult_t sc_memoryController_get(int address, Word_t *out);
MemoryAccessResult_t sc_memoryController_set(int address, Word_t value);

#endif
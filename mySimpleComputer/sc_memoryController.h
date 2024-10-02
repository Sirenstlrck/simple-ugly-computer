#ifndef SC_MEMORY_CONTROLLER_H
#define SC_MEMORY_CONTROLLER_H

#define CACHE_MISS_COST 10
#define CACHE_HIT_COST 1

void sc_memoryController_init();

typedef struct MemoryAccessResult
{
	unsigned char outOfBoundsError;
	unsigned char cost;
} MemoryAccessResult_t;

MemoryAccessResult_t sc_memoryController_get(int address, int *out);
MemoryAccessResult_t sc_memoryController_set(int address, int value);

#endif
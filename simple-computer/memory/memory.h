#ifndef SC_MEMORY_H
#define SC_MEMORY_H

#include "memory/config.h"

inline static int sc_memory_isAddressValid(int address)
{
	return !(address < 0 || address >= MEMORY_SIZE);
}

void sc_memory_init();

int sc_memory_get(int address, int *out);
int sc_memory_set(int address, int value);

int sc_memory_save(const char *filename);
int sc_memory_load(const char *filename);

#endif
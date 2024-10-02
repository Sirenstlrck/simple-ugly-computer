#include "sc_memory.h"
#include <memory.h>
#include <stdio.h>
#include <unistd.h>

static int memory[MEMORY_SIZE];

void sc_memory_init() { memset(memory, 0, MEMORY_SIZE * sizeof(*memory)); }

int sc_memory_set(int address, int value)
{
	if (sc_memory_isAddressValid(address) == -1)
		return -1;

	memory[address] = value;
	return 0;
}

int sc_memory_get(int address, int *out)
{
	if (sc_memory_isAddressValid(address) == -1)
		return -1;

	*out = memory[address];
	return 0;
}

int sc_memory_save(const char *filename)
{
	FILE *fd = fopen(filename, "w");
	if (!fd)
		return -1;
	return write(fileno(fd), memory, MEMORY_SIZE * sizeof(*memory));
}

int sc_memory_load(const char *filename)
{
	FILE *fd = fopen(filename, "r");
	if (!fd)
		return -1;
	return read(fileno(fd), memory, MEMORY_SIZE * sizeof(*memory));
}
#include "mySimpleComputer.h"

int memory[MEMORY_SIZE];
int accumulator;
int instructionCounter;
int clockCounter;
int flags;

CacheLine_t cache[CACHE_SIZE];

void sc_memoryInit() { memset(memory, 0, MEMORY_SIZE * sizeof(*memory)); }

int sc_isAddressValid(int address)
{
	return (address < 0 || address >= MEMORY_SIZE);
}

int sc_memorySet(int address, int value)
{
	if (sc_isAddressValid(address) == -1)
		return -1;

	memory[address] = value;
	return 0;
}

int sc_memoryGet(int address, int *out)
{
	if (sc_isAddressValid(address) == -1)
		return -1;

	*out = memory[address];
	return 0;
}

int sc_memorySave(const char *filename)
{
	FILE *fd = fopen(filename, "w");
	if (!fd)
		return -1;
	return write(fileno(fd), memory, MEMORY_SIZE * sizeof(*memory));
}

int sc_memoryLoad(const char *filename)
{
	FILE *fd = fopen(filename, "r");
	if (!fd)
		return -1;
	return read(fileno(fd), memory, MEMORY_SIZE * sizeof(*memory));
}

void sc_regInit() { flags = 0; }

int sc_verifyReg(int reg)
{
	if ((reg == OVERFLOW_MASK				 //
		 || reg == ZERO_DIV_MASK			 //
		 || reg == MEM_BOUND_ERR_MASK		 //
		 || reg == IGNORE_IMPULSE_MASK		 //
		 || reg == WRONG_COMMAND_MASK) == 0) //
		return -1;
	return 0;
}

int sc_regSet(int reg, int value)
{
	if (sc_verifyReg(reg) == -1)
		return -1;

	if (value == 1)
	{
		flags = flags | reg;
	}
	else if (value == 0)
	{
		flags = (~flags) & reg;
	}
	else
		return -1;
	return 0;
}

int sc_regGet(int reg, int *out)
{
	if (sc_verifyReg(reg) == -1)
		return -1;

	*out = (reg & flags) == 0 ? 0 : 1;
	return 0;
}

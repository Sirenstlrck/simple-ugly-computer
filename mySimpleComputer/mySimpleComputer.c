#include "mySimpleComputer.h"
#include "sc_word.h"

int memory[MEMORY_SIZE];
int accumulator;
int instructionCounter;
int clockCounter;
int flags;

CacheLine_t cache[CACHE_SIZE];

int sc_isAddressValid(int address)
{
	return (address < 0 || address >= MEMORY_SIZE);
}

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

int sc_isValidInt(int value) { return 0; }

void sc_memoryInit() { memset(memory, 0, MEMORY_SIZE * sizeof(*memory)); }

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

void sc_accumulatorInit() { accumulator = 0; }

int sc_accumulatorSet(int value) {}

int sc_accumulatorGet() { return accumulator; }

void sc_icounterInit() { instructionCounter = 0; }

int sc_icounterSet(int value) {}

int sc_icounterGet() { return instructionCounter; }

int sc_commandEncode(int sign, int command, int operand, int *value)
{
	int result = 0;
	int err = 0;
	err = sc_word_setSign(&result, sign);
	if (err)
		return err;
	err = sc_word_setCommand(&result, command);
	if (err)
		return err;
	err = sc_word_setOperand(&result, operand);
	if (err)
		return err;
	*value = result;
	return 0;
}

int sc_commandDecode(int value, int *sign, int *command, int *operand)
{
	if (value > MAX_WORD)
		return -1;

	*sign = sc_word_getSign(value);
	*command = sc_word_getCommand(value);
	*operand = sc_word_getOperand(value);

	return 0;
}

// int sc_step() { sc_memoryGet() }
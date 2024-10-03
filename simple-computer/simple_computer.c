#include <assert.h>

#include "memory/word.h"
#include "simple_computer.h"

static int accumulator;
static int instructionCounter;
static int downtimeCounter;
static int flags;

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

int sc_isValidInt(int value)
{
	assert(0);
	return -1;
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

int sc_accumulatorSet(int value)
{
	assert(0);
	return -1;
}

int sc_accumulatorGet() { return accumulator; }

void sc_icounterInit() { instructionCounter = 0; }

int sc_icounterSet(int value)
{
	assert(0);
	return -1;
}

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
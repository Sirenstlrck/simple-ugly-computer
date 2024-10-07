#include <assert.h>

#include "cpu/registers.h"

static int accumulator;
static int instructionCounter;
static unsigned char flags;
static int downtimeCounter;

static int verifyFlag(int flag)
{
	if ((flag == OVERFLOW_FLAG				  //
		 || flag == ZERO_DIV_FLAG			  //
		 || flag == MEM_OUT_OF_BOUNDS_FLAG	  //
		 || flag == IGNORE_IMPULSE_FLAG		  //
		 || flag == WRONG_COMMAND_FLAG) == 0) //
		return -1;
	return 0;
}

int sc_reg_getAccumulator() { return accumulator; }

void sc_reg_setAccumulator(int value) { accumulator = value; }

int sc_reg_getInstructionCounter() { return instructionCounter; }
void sc_reg_setInstructionCounter(int value) { instructionCounter = value; }
void sc_reg_incInstructionCounter() { instructionCounter++; }

int sc_reg_getDowntimeCounter() { return downtimeCounter; }

int sc_reg_downtimeCounterAdd(int value)
{
	downtimeCounter += value;
	return 0;
}

void sc_reg_downtimeCounterDec()
{
	if (downtimeCounter != 0)
	{
		downtimeCounter--;
	}
}

int sc_reg_downtimeCounterIsZero() { return downtimeCounter == 0; }

int sc_reg_getFlags() { return flags; }

int sc_reg_setFlag(int flag, int value)
{
	if (verifyFlag(flag) == -1)
		return -1;

	flags = value ? flags | flag : flags & ~flag;
	return 0;
}

int sc_reg_isFlagSetted(int flag)
{
	if (verifyFlag(flag) == -1)
		return -1;

	return !!(flags & flag);
}

void sc_reg_reset()
{
	accumulator		   = 0;
	instructionCounter = 0;
	downtimeCounter	   = 0;
	flags			   = 0;
	int err			   = sc_reg_setFlag(IGNORE_IMPULSE_FLAG, 1);
	assert(!err);
}
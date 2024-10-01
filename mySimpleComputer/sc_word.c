#include "sc_word.h"
#include "mySimpleComputer.h"

static int getBits(int from, int offset, int mask)
{
	from &= mask;
	from >>= offset;
	return from;
}

static void setBits(int *dst, int value, int offset, int mask)
{
	value <<= offset;
	int store = *dst & ~mask;
	value &= mask;
	*dst = store | value;
}

int sc_word_getSign(int word) { return getBits(word, SIGN_OFFSET, SIGN_MASK); }

int sc_word_setSign(int *word, int value)
{
	if (value != 0 && value != 1)
		return -1;
	setBits(word, value, SIGN_OFFSET, SIGN_MASK);
	return 0;
}

int sc_word_getCommand(int word)
{
	return getBits(word, COMMAND_OFFSET, COMMAND_MASK);
}

int sc_word_setCommand(int *word, int value)
{
	if (value < 0 || value > MAX_COMMAND_SIZE)
		return -1;
	setBits(word, value, COMMAND_OFFSET, COMMAND_MASK);
	return 0;
}

int sc_word_getOperand(int word)
{
	return getBits(word, OPERAND_OFFSET, OPERAND_MASK);
}

int sc_word_setOperand(int *word, int value)
{
	if (value < 0 || value > MAX_OPERAND_SIZE)
		return -1;
	setBits(word, value, OPERAND_OFFSET, OPERAND_MASK);
	return 0;
}

int sc_word_setValue(int *word, int value)
{
	if (value > MAX_WORD)
		return -1;

	*word = value;
}

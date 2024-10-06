#include "word/word.h"
#include "word/arithmetic.h"

static int sc_word_getBits(int from, int offset, int mask)
{
	from &= mask;
	from >>= offset;
	return from;
}

static void sc_word_setBits(int *dst, int value, int offset, int mask)
{
	value <<= offset;
	int store = *dst & ~mask;
	value &= mask;
	*dst = store | value;
}

int sc_word_isRawValueValid(int value)
{
	int sign = value < 0;

	int nval   = -value;
	int nbound = MAX_WORD_RAW + 1;
	if (sign && ((-value) > (MAX_WORD_RAW + 1)))
		return 0;
	else if (value > MAX_WORD_RAW)
		return 0;

	return 1;
}

Word_t sc_word_fromInt(int value, Word_t *out)
{
	if (!sc_word_isRawValueValid(value))
		return -1;
	*out = value;
	return 0;
}

int sc_word_toInt(Word_t word) { return word; }

int sc_word_getSign(Word_t word)
{
	return sc_word_getBits(word, SIGN_OFFSET, SIGN_MASK);
}

int sc_word_setSign(Word_t *word, int value)
{
	if (value != 0 && value != 1)
		return -1;
	sc_word_setBits(word, value, SIGN_OFFSET, SIGN_MASK);
	int mask = value ? ~MAX_WORD : MAX_WORD;
	return 0;
}

int sc_word_getCommand(Word_t word)
{
	return sc_word_getBits(word, COMMAND_OFFSET, COMMAND_MASK);
}

int sc_word_setCommand(Word_t *word, int value)
{
	if (value < 0 || value > MAX_COMMAND_SIZE)
		return -1;
	sc_word_setBits(word, value, COMMAND_OFFSET, COMMAND_MASK);
	return 0;
}

int sc_word_getOperand(Word_t word)
{
	return sc_word_getBits(word, OPERAND_OFFSET, OPERAND_MASK);
}

int sc_word_setOperand(Word_t *word, int value)
{
	if (value < 0)
		return -1;
	if (value > MAX_OPERAND_SIZE)
	{
		value = MAX_OPERAND_SIZE;
	}
	sc_word_setBits(word, value, OPERAND_OFFSET, OPERAND_MASK);
	return 0;
}

int sc_word_setValue(Word_t *word, int value)
{
	if (value > MAX_WORD)
		return -1;

	*word = value;
	return 0;
}

int sc_word_maybeCommand(Word_t word)
{
	int sign = sc_word_getSign(word);
	if (sign == 1)
		return 0;

	// TODO:
	// int cmd;
	// int success = sc_word_detectCommand(word, &cmd);
	// return success
	return 1;
}

int sc_word_commandEncode(int sign, int command, int operand, Word_t *out)
{
	int result = 0;
	int err	   = 0;
	err		   = sc_word_setSign(&result, sign);
	if (err)
		return err;
	err = sc_word_setCommand(&result, command);
	if (err)
		return err;
	err = sc_word_setOperand(&result, operand);
	if (err)
		return err;
	*out = result;
	return 0;
}

int sc_word_commandDecode(Word_t word, int *sign, int *command, int *operand)
{
	if (word > MAX_WORD)
		return -1;

	*sign	 = sc_word_getSign(word);
	*command = sc_word_getCommand(word);
	*operand = sc_word_getOperand(word);

	return 0;
}

int sc_word_getRawValue(Word_t word)
{
	return sc_word_getBits(word, 0, COMMAND_MASK | OPERAND_MASK);
}

int sc_word_setRawValue(Word_t *word, int value)
{
	if (!sc_word_isRawValueValid(value))
		return -1;

	sc_word_setBits(word, value, 0, COMMAND_MASK | OPERAND_MASK);
	return 0;
}

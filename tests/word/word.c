#include <assert.h>

#include "word/word.h"

void assertGeneralPositive()
{
	int cmd;
	int err;

	err = sc_word_commandEncode(1, 30, 127, &cmd);
	assert(err == 0);
}

void assertSetSign()
{
	int cmd;
	int err;

	err = sc_word_commandEncode(0, 127, 0, &cmd);
	assert(err == 0);

	err = sc_word_commandEncode(2, 30, 127, &cmd);
	assert(err);

	err = sc_word_commandEncode(-1, 30, 127, &cmd);
	assert(err);
}

void assertSetCommand()
{
	int cmd;
	int err;

	err = sc_word_commandEncode(1, 128, 127, &cmd);
	assert(err);

	err = sc_word_commandEncode(1, -1, 127, &cmd);
	assert(err);
}

void assertSetOperand()
{
	int cmd;
	int err;

	err = sc_word_commandEncode(1, 03, 128, &cmd);
	assert(err);

	err = sc_word_commandEncode(1, 03, -1, &cmd);
	assert(err);
}

void assertDecode()
{
	int cmd;
	int err;

	const int sign	  = 0;
	const int command = 30;
	const int operand = 100;

	err = sc_word_commandEncode(sign, command, operand, &cmd);
	assert(err == 0);

	int decodedSign	   = -1;
	int decodedCommand = -1;
	int decodedOperand = -1;
	err = sc_word_commandDecode(cmd, &decodedSign, &decodedCommand,
								&decodedOperand);
	assert(err == 0);
	assert(decodedSign == sign);
	assert(decodedCommand == command);
	assert(decodedOperand == operand);
}

int main()
{
	assertGeneralPositive();
	assertSetSign();
	assertSetCommand();
	assertSetOperand();

	assertDecode();
}
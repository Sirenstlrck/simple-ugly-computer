#include "word/arithmetic.h"
#include "word/word.h"
#include <assert.h>
#include <stdio.h>

void fromInt()
{
	Word_t word;
	int err;
	err = sc_word_fromInt(52, &word);
	assert(!err);
	err = sc_word_fromInt(0, &word);
	assert(!err);
	err = sc_word_fromInt(MAX_WORD_RAW, &word);
	assert(!err);
	err = sc_word_fromInt(MIN_WORD_RAW, &word);
	assert(!err);
	err = sc_word_fromInt(MAX_WORD_RAW + 1, &word);
	assert(err);
	err = sc_word_fromInt(MIN_WORD_RAW - 1, &word);
	assert(err);
}

void basicArithmetic()
{
	Word_t left, right;
	sc_word_fromInt(250, &left);
	sc_word_fromInt(137, &right);
	assert(sc_word_addChecked(left, right).result == 250 + 137);
	assert(sc_word_subChecked(left, right).result == 250 - 137);
	assert(sc_word_subChecked(right, left).result == 137 - 250);

	sc_word_fromInt(2, &left);
	sc_word_fromInt(-3, &right);
	assert(sc_word_mulChecked(left, right).result == 2 * -3);
}

void checkedArithmetic()
{
	Word_t left, right;
	sc_word_fromInt(MAX_WORD_RAW, &left);
	sc_word_fromInt(30, &right);

	ArithmeticResult_t opRes = sc_word_addChecked(left, right);
	assert(opRes.overflow);
	assert(opRes.result == -16354);

	sc_word_fromInt(MIN_WORD_RAW, &left);
	sc_word_fromInt(50, &right);
	opRes = sc_word_subChecked(left, right);
	assert(opRes.overflow);
	assert(opRes.result == 16335);
}

int main()
{
	fromInt();
	basicArithmetic();
	checkedArithmetic();
}
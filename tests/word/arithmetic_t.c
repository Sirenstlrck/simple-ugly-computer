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

void edgeOverflow()
{
	Word_t left, right;
	sc_word_fromInt(MAX_WORD_RAW, &left);
	sc_word_fromInt(1, &right);
	ArithmeticResult_t res = sc_word_addChecked(left, right);
	assert(res.overflow);
	assert(res.result == MIN_WORD_RAW);

	sc_word_fromInt(MIN_WORD_RAW, &left);
	sc_word_fromInt(1, &right);
	res = sc_word_subChecked(left, right);
	assert(res.overflow);
	assert(res.result == MAX_WORD_RAW);
}

void checkedArithmetic()
{
	Word_t left, right;
	sc_word_fromInt(MAX_WORD_RAW, &left);
	sc_word_fromInt(30, &right);

	ArithmeticResult_t opRes = sc_word_addChecked(left, right);
	assert(opRes.overflow);
	assert(opRes.result == MIN_WORD_RAW + 29);

	sc_word_fromInt(MIN_WORD_RAW, &left);
	sc_word_fromInt(50, &right);
	opRes = sc_word_subChecked(left, right);
	assert(opRes.overflow);
	assert(opRes.result == MAX_WORD_RAW - 49);

	sc_word_fromInt(MAX_WORD_RAW, &left);
	sc_word_fromInt(2, &right);
	opRes = sc_word_mulChecked(left, right);

	assert(opRes.overflow);
	assert(opRes.result == -2);

	assert(sc_word_mulChecked(left, right).result ==
		   sc_word_mulChecked(right, left).result);

	sc_word_fromInt(MIN_WORD_RAW, &left);
	opRes = sc_word_mulChecked(left, 2);
	assert(opRes.overflow);
	assert(opRes.result == 0);
}

void division()
{
	assert(sc_word_div(-11, 0).zeroDiv);
	assert(sc_word_div(11, 2).result == 11 / 2);
	assert(sc_word_div(11, -2).result == 11 / -2);
	assert(sc_word_div(-11, 2).result == -11 / 2);
	assert(sc_word_div(-11, -2).result == -11 / -2);
}

int main()
{

	fromInt();
	basicArithmetic();
	edgeOverflow();
	checkedArithmetic();
	division();
}
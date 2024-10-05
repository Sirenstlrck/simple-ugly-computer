#include "word/arithmetic.h"
#include "word/word.h"
#include <stdio.h>
ArithmeticResult_t sc_word_addChecked(Word_t lhs, Word_t rhs)
{
	ArithmeticResult_t res;
	int rawResult = lhs + rhs;
	if (rawResult > MAX_WORD_RAW || rawResult < MIN_WORD_RAW)
	{
		res.overflow = 1;
		Word_t result;

		if (lhs + rhs > MAX_WORD_RAW)
		{
			result = rhs - (MAX_WORD_RAW - lhs);
			result |= ~MAX_WORD_RAW;
			result--;
		}
		else
		{
			result = rhs + (MIN_WORD_RAW + lhs);
			result &= MAX_WORD_RAW;
		}
		res.result = result;
		return res;
	}

	res.result = lhs + rhs;
	return res;
}

ArithmeticResult_t sc_word_subChecked(Word_t lhs, Word_t rhs)
{
	rhs = sc_word_negate(rhs);
	return sc_word_addChecked(lhs, rhs);
}

ArithmeticResult_t sc_word_mulChecked(Word_t lhs, Word_t rhs)
{
	// hahaha
	ArithmeticResult_t mulRes;
	mulRes.result = 0;
	mulRes.overflow = 0;

	int rhsSign = sc_word_getSign(rhs);
	int ie = rhsSign ? sc_word_negate(rhs) : rhs;
	for (int i = 0; i < ie; ++i)
	{
		ArithmeticResult_t addRes = rhsSign
									  ? sc_word_subChecked(mulRes.result, lhs)
									  : sc_word_addChecked(mulRes.result, lhs);

		mulRes.result = addRes.result;

		if (addRes.overflow)
			mulRes.overflow = 1;
	}
	return mulRes;
}

DivisionResult_t sc_word_div(Word_t lhs, Word_t rhs)
{
	DivisionResult_t divRes;
	if (rhs == 0)
	{
		divRes.zeroDiv = 1;
		return divRes;
	}

	int resSign = 0;
	if (sc_word_getSign(lhs))
	{
		resSign = !resSign;
		lhs = sc_word_negate(lhs);
	}
	if (sc_word_getSign(rhs))
	{
		resSign = !resSign;
		rhs = sc_word_negate(rhs);
	}

	int acc = lhs;
	divRes.result = -1;
	divRes.zeroDiv = 0;
	while (acc >= 0)
	{
		ArithmeticResult_t subRes = sc_word_subChecked(acc, rhs);
		acc = subRes.result;
		divRes.result++;
	}

	if (resSign)
		divRes.result = sc_word_negate(divRes.result);

	return divRes;
}

Word_t sc_word_negate(Word_t word)
{

	if (sc_word_getSign(word))
	{
		return (~word + 1);
	}
	else
	{
		return ~(word - 1);
	}
}
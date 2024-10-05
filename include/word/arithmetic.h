#ifndef SC_WORD_ARITHMETIC_H
#define SC_WORD_ARITHMETIC_H

#include "def.h"

#define U7_MAX 0x007F

typedef struct ArithmeticResult
{
	unsigned char overflow;
	Word_t result;
} ArithmeticResult_t;

typedef struct DivisionResult
{
	unsigned char zeroDiv;
	int result;
} DivisionResult_t;

ArithmeticResult_t sc_word_addChecked(Word_t lhs, Word_t rhs);
ArithmeticResult_t sc_word_subChecked(Word_t lhs, Word_t rhs);
ArithmeticResult_t sc_word_mulChecked(Word_t lhs, Word_t rhs);
DivisionResult_t sc_word_div(Word_t lhs, Word_t rhs);

Word_t sc_word_negate(Word_t word);

#endif

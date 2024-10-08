#ifndef SC_WORD_DEF_H
#define SC_WORD_DEF_H

#include <assert.h>

#define WORD_BITS_COUNT	 15

#define SIGN_OFFSET		 14
#define COMMAND_OFFSET	 7
#define OPERAND_OFFSET	 0

#define OPERAND_OFFSET	 0
#define MAX_WORD_RAW	 0b00000000000000000011111111111111
#define MIN_WORD_RAW	 (-(MAX_WORD_RAW + 1))
#define MAX_WORD		 0b00000000000000000111111111111111
#define SIGN_MASK		 0b00000000000000000100000000000000
#define COMMAND_MASK	 0b00000000000000000011111110000000
#define OPERAND_MASK	 0b00000000000000000000000001111111

#define MAX_COMMAND_SIZE 0x7F
#define MAX_OPERAND_SIZE 0x7F

typedef int Word_t;

#define ASSERT_WORD_BOUNDS(WORD)                                               \
	{                                                                          \
		assert(WORD >= MIN_WORD_RAW && WORD <= MAX_WORD_RAW);                  \
	}

#define ASSERT_2WORDS_BOUNDS(word1, word2)                                     \
	{ASSERT_WORD_BOUNDS(word1) ASSERT_WORD_BOUNDS(word2)}

#endif

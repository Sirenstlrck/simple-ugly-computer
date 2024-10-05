#ifndef SC_WORD_DEF_H
#define SC_WORD_DEF_H

// clang-format off

#define WORD_BITS_COUNT     15

#define SIGN_OFFSET         (WORD_BITS_COUNT) - 1
#define COMMAND_OFFSET      7
#define OPERAND_OFFSET      0

#define MAX_WORD_RAW        0b00000000000000000011111111111111
#define MIN_WORD_RAW        -(MAX_WORD_RAW + 1)
                                            // 0123456789ABCDE
#define MAX_WORD            0b00000000000000000111111111111111
#define SIGN_MASK           0b00000000000000000100000000000000
#define COMMAND_MASK        0b00000000000000000011111110000000
#define OPERAND_MASK        0b00000000000000000000000001111111


#define MAX_COMMAND_SIZE    0x7F
#define MAX_OPERAND_SIZE    0x7F

typedef int Word_t;

// clang-format on

#endif

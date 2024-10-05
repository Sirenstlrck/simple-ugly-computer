#ifndef SC_WORD_H
#define SC_WORD_H

#include "def.h"

int sc_word_fromInt(int value, Word_t *out);
int sc_word_toInt(Word_t word);

int sc_word_getSign(Word_t word);
int sc_word_setSign(Word_t *word, int value);

int sc_word_getCommand(Word_t word);
int sc_word_setCommand(Word_t *word, int value);

int sc_word_getOperand(Word_t word);
int sc_word_setOperand(Word_t *word, int value);

int sc_word_setValue(Word_t *word, int value);

int sc_word_maybeCommand(Word_t word);

int sc_word_commandDecode(Word_t word, int *sign, int *command, int *operand);
int sc_word_commandEncode(int sign, int command, int operand, Word_t *out);

int sc_word_getRawValue(Word_t word);

int sc_word_setRawValue(Word_t *word, int value);

#endif

#ifndef SC_WORD_H
#define SC_WORD_H

int sc_word_getSign(int word);
int sc_word_setSign(int *word, int value);

int sc_word_getCommand(int word);
int sc_word_setCommand(int *word, int value);

int sc_word_getOperand(int word);
int sc_word_setOperand(int *word, int value);

int sc_word_setValue(int *word, int value);

int sc_word_maybeCommand(int word);

#endif
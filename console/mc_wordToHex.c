#include "console.h"

char *mc_wordToHex(Word_t word)
{
	char *result = (char *)malloc(6 * sizeof(char));
	char buffer[11];
	// int sign = sc_word_getSign(word);

	int sign, command, operand;
	sc_word_commandDecode(word, &sign, &command, &operand);
	sprintf(buffer, "%c%02x%02x", sign ? '-' : '+', command, operand);

	// sprintf(buffer, "%c%04x", sign ? '-' : '+',
	// 		sign ? ((~word) & MAX_WORD) + 1 : word);
	strcpy(result, buffer);
	return result;
}

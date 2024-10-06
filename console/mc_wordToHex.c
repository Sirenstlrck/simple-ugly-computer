#include "console.h"

char *mc_wordToHex(Word_t word)
{
	char *result = (char *)malloc(6 * sizeof(char));
	char buffer[6];
	int sign = sc_word_getSign(word);
	sprintf(buffer, "%c%04x", sign ? '-' : '+',
			sign ? ((~word) & MAX_WORD) + 1 : word);
	strcpy(result, buffer);
	return result;
}

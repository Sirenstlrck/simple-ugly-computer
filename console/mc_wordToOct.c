#include "console.h"

char *mc_wordToOct(Word_t word)
{
	char *result = (char *)malloc(7 * sizeof(char));
	char buffer[7];
	int sign = sc_word_getSign(word);
	sprintf(buffer, "%c%05o", sign ? '-' : '+',
			sign ? ((~word) & MAX_WORD) + 1 : word);
	strcpy(result, buffer);
	return result;
}

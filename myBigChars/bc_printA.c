#include "myBigChars.h"
#include <string.h>
#include <unistd.h>

#define NUM_ROWS 6
#define NUM_COLS 19

typedef struct
{
	char symbol;
	char rows[NUM_ROWS][NUM_COLS];
} CustomEncoding;

const CustomEncoding custom_encoding[] = {
	{'A', {"▄████▄ ", "██░░██ ", "██░░██ ", "██████ ", "██░░██ ", "░░░░░░ "}},
	{'B', {"█████▄ ", "██░░██ ", "█████░ ", "██░░██ ", "█████▀ ", "░░░░░░ "}},
};

int bc_printA(const char *str)
{
	if (str == NULL)
	{
		return -1;
	}

	char outputBuffer[NUM_ROWS][200];

	for (int i = 0; i < strlen(str); ++i)
	{
		const CustomEncoding *current_encoding = &custom_encoding[str[i] - 'A'];
		for (int j = 0; j < NUM_ROWS; ++j)
		{
			for (int k = 0; k < NUM_COLS; ++k)
			{
				outputBuffer[j][k + i * NUM_COLS] =
					current_encoding->rows[j][k];
			}
		}
	}

	for (int i = 0; i < NUM_ROWS; ++i)
	{
		printf("%s\n", outputBuffer[i]);
	}
	return 0;
}
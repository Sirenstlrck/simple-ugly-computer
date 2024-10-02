#include "myBigChars.h"
#include "myTerm.h"
#include <unistd.h>

typedef struct
{
	char symbol;
	char rows[BIG_CHAR_LETTER_HEIGHT][BIG_CHAR_LETTER_WIDTH];
} CustomEncoding;

const CustomEncoding custom_encoding[] = {
	{'A', {"▄████▄ ", "██░░██ ", "██░░██ ", "██████ ", "██░░██ ", "░░░░░░ "}},
	{'B', {"█████▄ ", "██░░██ ", "█████░ ", "██░░██ ", "█████▀ ", "░░░░░░ "}},
	{'C', {"▄█████ ", "██░░░░ ", "██░░░░ ", "██░░░░ ", "▀█████ ", "░░░░░░ "}},
	{'D', {"█████▄ ", "██░░██ ", "██░░██ ", "██░░██ ", "█████▀ ", "░░░░░░ "}},
	{'E', {"▄█████ ", "██░░░░ ", "█████░ ", "██░░░░ ", "▀█████ ", "░░░░░░ "}},
	{'F', {"██████ ", "██░░░░ ", "█████░ ", "██░░░░ ", "██░░░░ ", "░░░░░░ "}},
	{'0', {"▄████▄ ", "██░░██ ", "██░░██ ", "██░░██ ", "▀████▀ ", "░░░░░░ "}},
	{'1', {"▄████░ ", "░░███░ ", "░░███░ ", "░░███░ ", "██████ ", "░░░░░░ "}},
	{'2', {"█████▄ ", "░░░░██ ", "▄████▀ ", "██░░░░ ", "██████ ", "░░░░░░ "}},
	{'3', {"█████▄ ", "░░░░██ ", "░████░ ", "░░░░██ ", "█████▀ ", "░░░░░░ "}},
	{'4', {"██░░██ ", "██░░██ ", "██████ ", "░░░░██ ", "░░░░██ ", "░░░░░░ "}},
	{'5', {"██████ ", "██░░░░ ", "▀████▄ ", "░░░░██ ", "█████▀ ", "░░░░░░ "}},
	{'6', {"▄█████ ", "██░░░░ ", "█████▄ ", "██░░░█ ", "██████ ", "░░░░░░ "}},
	{'7', {"██████ ", "░░░░██ ", "░░░░██ ", "░░░░██ ", "░░░░██ ", "░░░░░░ "}},
	{'8', {"▄████▄ ", "██░░██ ", "░████░ ", "██░░██ ", "▀████▀ ", "░░░░░░ "}},
	{'9', {"▄████▄ ", "██░░██ ", "░█████ ", "░░░░██ ", "█████▀ ", "░░░░░░ "}},
	{'+', {"░░░░░░ ", "░░██░░ ", "██████ ", "░░██░░ ", "░░░░░░ ", "░░░░░░ "}},
	{'-', {"░░░░░░ ", "░░░░░░ ", "██████ ", "░░░░░░ ", "░░░░░░ ", "░░░░░░ "}},
};

int bc_printBigChar(int x, int y, const char *str)
{
	if (str == NULL)
	{
		return -1;
	}

	char *outputBuffer[BIG_CHAR_LETTER_HEIGHT];
	for (int i = 0; i < BIG_CHAR_LETTER_HEIGHT; ++i)
	{
		outputBuffer[i] = malloc(BIG_CHAR_LETTER_WIDTH * strlen(str));
	}

	for (int i = 0; i < (int)strlen(str); ++i)
	{
		const CustomEncoding *current_encoding;
		if (str[i] == '+')
		{
			current_encoding = &custom_encoding[16];
		}
		else if (str[i] == '-')
		{
			current_encoding = &custom_encoding[17];
		}
		else if (!isdigit(str[i]))
		{
			current_encoding = &custom_encoding[toupper(str[i]) - 'A'];
			char str1[2] = {current_encoding->symbol, '\0'};
			char str2[2] = {toupper(str[i]), '\0'};
			if (strcmp(str1, str2) != 0)
			{
				return -1;
			}
		}
		else
		{
			current_encoding = &custom_encoding[str[i] - '0' + 6];
		}

		for (int j = 0; j < BIG_CHAR_LETTER_HEIGHT; ++j)
		{
			for (int k = 0; k < BIG_CHAR_LETTER_WIDTH; ++k)
			{
				outputBuffer[j][k + i * BIG_CHAR_LETTER_WIDTH] =
					current_encoding->rows[j][k];
			}
		}
	}

	for (int i = 0; i < BIG_CHAR_LETTER_HEIGHT; ++i)
	{
		mt_gotoXY(x, y + i);
		write(STDOUT_FILENO, outputBuffer[i], strlen(outputBuffer[i]));
	}
	return 0;
}
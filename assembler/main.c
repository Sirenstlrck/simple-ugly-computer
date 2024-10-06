#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <error.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "cpu/operation.h"
#include "memory/config.h"
#include "string_to_opcode.h"
#include "word/arithmetic.h"
#include "word/word.h"

static int isSpace(char ch) { return ch == ' ' || ch == '\t' || ch == '\n'; }

typedef char *TokenVector_t[3];
#define TOK_V_ELEMENTS_COUNT = sizeof(TokenVector_t) / sizeof(char *)

static int count(TokenVector_t v)
{
	int c = 0;
	while (v[c])
	{
		c++;
	}
	return c;
}

static void splitFirst3(char *str, TokenVector_t dst)
{
	int readedCount = 0;

	for (int i = 0, ie = strlen(str); i < ie; ++i)
	{
		if (!isSpace(str[i]))
		{
			int wordIdx = i;
			while (!isSpace(str[wordIdx]))
			{
				wordIdx++;
			}
			int wordSize = wordIdx - i;
			if (str[i] != ';')
			{
				dst[readedCount] = malloc(wordSize + 1);
				memcpy(dst[readedCount], &str[i], wordSize);
				dst[readedCount][wordSize] = '\0';
			}
			i = wordIdx;
			readedCount++;
			if (readedCount == sizeof(TokenVector_t) / sizeof(char *))
				break;
		}
	}
}

int ensureScanInt(char *str)
{
	int addr;
	errno		 = 0;
	int scanfRes = sscanf(str, "%d", &addr);
	if (scanfRes != 1)
	{
		if (errno != 0)
			perror("sscanf");
		else
			fprintf(stderr, "No matching characters");
		abort();
	}
	return addr;
}

char *trimStart(char *str)
{
	while (*str && isSpace(*str))
		str++;
	return str;
}

typedef struct
{
	int size;
	struct
	{
		unsigned char isOccupied;
		int value;
	} *content;
} ParseResult_t;

ParseResult_t parse(FILE *f)
{
	char buff[512] = {"\0"};
	TokenVector_t tokv;
	ParseResult_t res;
	res.content = calloc(MEMORY_SIZE, sizeof(*res.content));
	res.size	= MEMORY_SIZE;
	int line	= 0;

	while (fgets(buff, sizeof(buff), f))
	{
		char *str = trimStart(buff);
		line++;
		if (*str == '\0' || *str == ';')
			continue;

		memset(tokv, 0, sizeof(tokv));
		splitFirst3(str, tokv);
		assert(tokv[0]);
		if (!tokv[1])
		{
			fprintf(stderr,
					"Failed to parse line %d: Location should contain command "
					"or value\n",
					line);
			abort();
		}

		int addr = ensureScanInt(tokv[0]);
		if (res.content[addr].isOccupied)
		{
			fprintf(stderr,
					"Failed to parse line %d: There is already another record "
					"for address %x\n",
					line, addr);
			abort();
		}
		res.content[addr].isOccupied = 1;

		if (*tokv[1] == '+' || *tokv[1] == '-')
		{
			int value = ensureScanInt(tokv[1] + 1);
			if (*tokv[1] == '-')
				value = -value;
			res.content[addr].value = value;
		}
		else
		{
			if (!tokv[2])
			{
				fprintf(stderr,
						"Failed to parse line %d: Operation should have an "
						"argument\n",
						line);
				abort();
			}
			int opnd			   = ensureScanInt(tokv[2]);
			StrOpCodePair_t *match = NULL;
			convertInMatchableCase(tokv[1]);
			for (int i = 0, ie = OPERATIONS_COUNT; i < ie; ++i)
			{
				if (strcmp(tokv[1], strOpPairs[i].str) == 0)
				{
					Word_t w;
					sc_word_commandEncode(0, strOpPairs[i].code, opnd, &w);
					res.content[addr].value = w;
					break;
				}
			}
		}

		for (int i = 0; tokv[i] && i < sizeof(tokv) / sizeof(char *); ++i)
		{
			free(tokv[i]);
			tokv[i] = NULL;
		}
	}
	return res;
}

FILE *ensureFOpen(char *filename, char *mode)
{

	FILE *f = fopen(filename, mode);
	if (!f)
	{
		perror(filename);
		abort();
	}
	return f;
}

int main(int argc, char **argv)
{
	if (argc < 3)
	{
		fprintf(stderr, "Please provide source file path & out file name\n");
		return -1;
	}

	FILE *src = ensureFOpen(argv[1], "r");
	FILE *dst = ensureFOpen(argv[2], "w");

	ParseResult_t res = parse(src);

	for (int i = 0; i < res.size; ++i)
	{
		write(fileno(dst), &res.content[i].value, sizeof(res.content[i].value));
	}
	return 0;
}
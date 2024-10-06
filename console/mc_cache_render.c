#include "console.h"
#include <memory/cache_public.h>

void mc_cache_render()
{
	int x = 2;
	int y = 18;
	char buffer[256];
	mt_cursorPosition_set(x, y);
	CacheLine_t cacheLine;
	for (int i = 0; i < CACHE_SIZE; ++i)
	{
		sc_memoryCache_getLine(i, &cacheLine);
		sprintf(buffer, "%d: ", cacheLine.baseAddress / 10);
		write(STDOUT_FILENO, buffer, strlen(buffer));
		mt_cursorPosition_set(x += 4, y);
		for (int j = 0; j < CACHE_LINE_SIZE; ++j)
		{
			char *str = mc_wordToHex(cacheLine.data[j]);
			write(STDOUT_FILENO, str, strlen(str));
			mt_cursorPosition_set(x += 6, y);
		}
		mt_cursorPosition_set(x = 2, y++);
	}
}
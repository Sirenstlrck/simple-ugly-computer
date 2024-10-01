#include "mySimpleComputer.h"
#include <errno.h>

int main(int argc, const char **argv)
{
	sc_memoryInit();
	if (argc == 1)
	{
		for (int i = 0, ie = MEMORY_SIZE; i < ie; ++i)
		{
			sc_memorySet(i, i);
		}
		int saveRes = sc_memorySave("./save.bin");
		if (saveRes == -1)
		{
			fprintf(stderr, "Failed to save memory: %s\n", strerror(errno));
			return -1;
		}
		for (int i = 0, ie = MEMORY_SIZE; i < ie; ++i)
		{
			int value;
			sc_memoryGet(i, &value);
			printf("%d ", value);
		}
	}
	else
	{
		int loadRes = sc_memoryLoad("./save.bin");
		if (loadRes == -1)
		{
			fprintf(stderr, "Failed to load memory: %s\n", strerror(errno));
			return -1;
		}
		for (int i = 0, ie = MEMORY_SIZE; i < ie; ++i)
		{
			int value;
			sc_memoryGet(i, &value);
			printf("%d ", value);
		}
	}
	puts("\n");
	return 0;
}
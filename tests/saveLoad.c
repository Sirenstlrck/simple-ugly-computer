/*
** Inits memory and fills is with values from 0 to 127.
** then saves it in file
** then inits memory again and loads memory from file
** then asserts that memory values is range from 0 to 127
*/

#include "mySimpleComputer.h"
#include <assert.h>
#include <errno.h>

const char *filename = "save.bin";

void fill()
{
	sc_memoryInit();
	for (int i = 0, ie = MEMORY_SIZE; i < ie; ++i)
	{
		sc_memorySet(i, i);
	}
}

void save()
{
	int saveRes = sc_memorySave(filename);
	if (saveRes == -1)
	{
		fprintf(stderr, "Failed to save memory to file: %s\n", strerror(errno));
		abort();
	}
}

void load()
{
	sc_memoryInit();
	int loadRes = sc_memoryLoad(filename);
	if (loadRes == -1)
	{
		fprintf(stderr, "Failed to load memory from file: %s\n",
				strerror(errno));
		abort();
	}
}

void validate()
{
	for (int i = 0, ie = MEMORY_SIZE; i < ie; ++i)
	{
		int value = 0;
		int getRes = sc_memoryGet(i, &value);
		if (getRes == -1)
		{
			fprintf(stderr, "Failed to get value by %d address", i);
			abort();
		}
		assert(value == i);
	}
}

int main()
{
	fill();
	save();
	load();
	validate();
	return 0;
}
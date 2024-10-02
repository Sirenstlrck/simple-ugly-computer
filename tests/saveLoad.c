/*
** Inits memory and fills is with values from 0 to 127.
** then saves it in file
** then inits memory again and loads memory from file
** then asserts that memory values is range from 0 to 127
*/

#include "sc_memory.h"
#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

const char *filename = "save.bin";

void fill()
{
	sc_memory_init();
	for (int i = 0, ie = MEMORY_SIZE; i < ie; ++i)
	{
		sc_memory_set(i, i);
	}
}

void save()
{
	int saveRes = sc_memory_save(filename);
	if (saveRes == -1)
	{
		fprintf(stderr, "Failed to save memory to file: %s\n", strerror(errno));
		assert(0);
	}
}

void load()
{
	sc_memory_init();
	int loadRes = sc_memory_load(filename);
	if (loadRes == -1)
	{
		fprintf(stderr, "Failed to load memory from file: %s\n",
				strerror(errno));
		assert(0);
	}
}

void validate()
{
	for (int i = 0, ie = MEMORY_SIZE; i < ie; ++i)
	{
		int value = 0;
		int getRes = sc_memory_get(i, &value);
		if (getRes == -1)
		{
			fprintf(stderr, "Failed to get value by %d address", i);
			assert(0);
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
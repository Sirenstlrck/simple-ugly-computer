#ifndef SC_CACHE_PUBLIC_H
#define SC_CACHE_PUBLIC_H

#include "config.h"
#include <time.h>

typedef struct CacheLine
{
	char isOccupied;
	char isDirty;
	int baseAddress;
	time_t lastAccessTimestamp;
	int data[CACHE_LINE_SIZE];
} CacheLine_t;

int sc_memoryCache_getLine(int idx, CacheLine_t *out);
int sc_memoryCache_getOccupiedLinesCount();

#endif

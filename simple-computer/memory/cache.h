#ifndef SC_MEMORY_CACHE_H
#define SC_MEMORY_CACHE_H

#include <time.h>

#include "memory/config.h"

typedef struct CacheLine
{
	char isOccupied;
	char isDirty;
	int baseAddress;
	time_t lastAccessTimestamp;
	int data[CACHE_LINE_SIZE];
} CacheLine_t;

typedef struct CacheAddressationInfo
{
	int base;
	int offset;
} CacheAddressationInfo_t;

typedef struct CacheSeekResult
{
	char isSuccess;
	int cacheLineIdx;
	CacheAddressationInfo_t addressationInfo;
} CacheSeekResult_t;

void sc_memoryCache_init();

CacheLine_t sc_memoryCache_getLine(int idx);

CacheAddressationInfo_t sc_memoryCache_getAddressationInfo(int address);

CacheSeekResult_t sc_memoryCache_seek(int address);

int sc_memoryCache_get(CacheSeekResult_t seekResult);

void sc_memoryCache_set(CacheSeekResult_t seekResult, int value);

CacheLine_t sc_memoryCache_addLine(CacheLine_t line);

#endif

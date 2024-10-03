#include <assert.h>
#include <memory.h>
#include <stdio.h>

#include "cache.h"

CacheLine_t cache[CACHE_SIZE];

void sc_memoryCache_init() { memset(cache, 0, sizeof(cache)); }

CacheLine_t sc_memoryCache_getLine(int idx)
{
	assert(idx >= 0 && idx < CACHE_SIZE);
	return cache[idx];
}

CacheAddressationInfo_t sc_memoryCache_getAddressationInfo(int address)
{
	CacheAddressationInfo_t result;
	result.base = (address / CACHE_LINE_SIZE) * CACHE_LINE_SIZE;
	result.offset = address - result.base;
	return result;
}

CacheSeekResult_t sc_memoryCache_seek(int address)
{
	CacheSeekResult_t result;
	result.isSuccess = 0;
	result.addressationInfo = sc_memoryCache_getAddressationInfo(address);
	result.cacheLineIdx = -1;

	for (int i = 0, ie = CACHE_SIZE; i < ie; ++i)
	{
		CacheLine_t line = cache[i];
		if (!line.isOccupied)
			continue;

		if (result.addressationInfo.base == line.baseAddress)
		{
			result.isSuccess = 1;
			result.cacheLineIdx = i;
			break;
		}
	}
	return result;
}

int sc_memoryCache_get(CacheSeekResult_t seekResult)
{
	assert(seekResult.isSuccess);

	CacheLine_t line = cache[seekResult.cacheLineIdx];
	line.lastAccessTimestamp = time(NULL);
	return line.data[seekResult.addressationInfo.offset];
}

void sc_memoryCache_set(CacheSeekResult_t seekResult, int value)
{
	assert(seekResult.isSuccess);

	CacheLine_t *line = &cache[seekResult.cacheLineIdx];
	line->lastAccessTimestamp = time(NULL);
	line->data[seekResult.addressationInfo.offset] = value;
	line->isDirty = 1;
}

void dumpLines() {}

// @return Possible overrided cache line. 'isOccupied' setted in 1 if overrided.
// 'isDirty' setted in 1 if it was modified and memory should be updated.
CacheLine_t sc_memoryCache_addLine(CacheLine_t line)
{
	line.isOccupied = 1;
	line.isDirty = 0;
	line.lastAccessTimestamp = time(NULL);

	CacheLine_t *toOverride = &cache[0];
	for (int i = 1, ie = CACHE_SIZE; i < ie; ++i)
	{
		if (!toOverride->isOccupied)
			break;

		CacheLine_t *next = &cache[i];
		if (!next->isOccupied //
			|| toOverride->lastAccessTimestamp > next->lastAccessTimestamp)
		{
			toOverride = next;
			break;
		}
	}

	CacheLine_t stored = *toOverride;
	*toOverride = line;
	return stored;
}

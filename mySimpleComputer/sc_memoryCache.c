#include "sc_memoryCache.h"
#include <assert.h>
#include <memory.h>

CacheLine_t cache[CACHE_SIZE];

void sc_memoryCache_init() { memset(cache, 0, sizeof(cache)); }

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

		if (result.addressationInfo.base == line.address)
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

static int findOverrideCandidateIdx(const CacheLine_t *line)
{
	time_t minTimestamp = cache[0].lastAccessTimestamp;
	int minIdx = 0;
	for (int i = 0; i < CACHE_SIZE; ++i)
	{
		if (!cache[i].isOccupied)
			return i;
		if (minTimestamp > cache[i].lastAccessTimestamp)
		{
			minIdx = i;
			minTimestamp = cache[i].lastAccessTimestamp;
		}
	}
	return minIdx;
}

// @return Possible overrided cache line. 'isOccupied' setted in 1 if overrided.
// 'isDirty' setted in 1 if it was modified and memory should be updated.
CacheLine_t sc_memoryCache_addLine(CacheLine_t line)
{
	line.isOccupied = 1;
	line.lastAccessTimestamp = time(NULL);
	int idx = findOverrideCandidateIdx(&line);
	CacheLine_t stored = cache[idx];
	cache[idx] = line;
	return stored;
}

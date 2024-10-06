#include <assert.h>
#include <memory.h>

#include "cache.h"
#include "memory.h"
#include "memory/controller.h"

static void dumpLine(CacheLine_t line)
{
	for (int i = 0; i < CACHE_LINE_SIZE && i + line.baseAddress < MEMORY_SIZE;
		 ++i)
	{
		int err = sc_memory_set(i + line.baseAddress, line.data[i]);
		assert(!err);
	}
}

static void loadLine(int address)
{
	CacheAddressationInfo_t addressationInfo =
		sc_memoryCache_getAddressationInfo(address);

	CacheLine_t newLine;
	newLine.baseAddress = addressationInfo.base;
	for (int i = 0;
		 i < CACHE_LINE_SIZE && addressationInfo.base + i < MEMORY_SIZE; ++i)
	{
		int value;
		int err = sc_memory_get(addressationInfo.base + i, &value);
		assert(!err);
		newLine.data[i] = value;
	}
	CacheLine_t oldLine = sc_memoryCache_addLine(newLine);
	if (oldLine.isOccupied && oldLine.isDirty)
		dumpLine(oldLine);
}

static CacheSeekResult_t ensureCachedSeek(int address, char *cacheMiss)
{
	CacheSeekResult_t cacheSeekResult = sc_memoryCache_seek(address);
	*cacheMiss						  = !cacheSeekResult.isSuccess;
	if (*cacheMiss)
	{
		loadLine(address);
		cacheSeekResult = sc_memoryCache_seek(address);
	}
	return cacheSeekResult;
}

// maybe this is a messy naming
typedef struct SeekResult
{
	MemoryAccessResult_t accessResult;
	CacheSeekResult_t cacheSeekResult;
} SeekResult_t;

static SeekResult_t seek(int address)
{
	SeekResult_t result;
	if (!sc_memory_isAddressValid(address))
	{
		result.accessResult.outOfBoundsError = 1;
		return result;
	}

	char cacheMiss;
	result.cacheSeekResult = ensureCachedSeek(address, &cacheMiss);

	result.accessResult.outOfBoundsError = 0;
	result.accessResult.cost = cacheMiss ? CACHE_MISS_COST : CACHE_HIT_COST;
	return result;
}

void sc_memoryController_init()
{
	sc_memory_init();
	sc_memoryCache_init();
}

void sc_memoryController_flushCache()
{
	for (int i = 0, ie = CACHE_SIZE; i < ie; ++i)
	{
		CacheLine_t line;
		sc_memoryCache_getLine(i, &line);
		if (line.isDirty)
			dumpLine(line);
	}
	sc_memoryCache_init();
}

MemoryAccessResult_t sc_memoryController_get(int address, Word_t *out)
{
	SeekResult_t seekResult = seek(address);
	if (seekResult.accessResult.outOfBoundsError)
		return seekResult.accessResult;

	*out = sc_memoryCache_get(seekResult.cacheSeekResult);

	return seekResult.accessResult;
}

MemoryAccessResult_t sc_memoryController_set(int address, Word_t value)
{
	SeekResult_t seekResult = seek(address);
	if (seekResult.accessResult.outOfBoundsError)
		return seekResult.accessResult;

	sc_memoryCache_set(seekResult.cacheSeekResult, value);

	return seekResult.accessResult;
}

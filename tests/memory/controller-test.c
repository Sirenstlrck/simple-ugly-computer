#include <assert.h>
#include <stddef.h>
#include <stdio.h>

#include "memory/cache_public.h"
#include "memory/controller.h"

static void basic()
{
	sc_memoryController_init();
	int value;
	MemoryAccessResult_t res;

	res = sc_memoryController_get(1229, NULL);
	assert(res.outOfBoundsError);
	res = sc_memoryController_get(-1, NULL);
	assert(res.outOfBoundsError);

	assert(sc_memoryCache_getOccupiedLinesCount() == 0);

	res = sc_memoryController_set(0, 1);
	assert(!res.outOfBoundsError);

	assert(sc_memoryCache_getOccupiedLinesCount() == 1);

	res = sc_memoryController_get(0, &value);
	assert(value == 1);

	assert(sc_memoryCache_getOccupiedLinesCount() == 1);
}

static void hits()
{
	sc_memoryController_init();
	int value;
	MemoryAccessResult_t res;

	for (int i = 0, ie = 9; i < ie; ++i)
	{
		res = sc_memoryController_set(i, i);
		assert(!res.outOfBoundsError);
	}
	assert(sc_memoryCache_getOccupiedLinesCount() == 1);

	for (int i = 10, ie = 19; i < ie; ++i)
	{
		res = sc_memoryController_set(i, i);
		assert(!res.outOfBoundsError);
	}
	assert(sc_memoryCache_getOccupiedLinesCount() == 2);

	res = sc_memoryController_get(15, &value);
	assert(res.cost == CACHE_HIT_COST);
	assert(value == 15);

	res = sc_memoryController_set(25, value);
	assert(res.cost == CACHE_MISS_COST);

	res = sc_memoryController_get(35, &value);
	assert(res.cost == CACHE_MISS_COST);

	assert(sc_memoryCache_getOccupiedLinesCount() == 4);

	int err;
	CacheLine_t line;
	err = sc_memoryCache_getLine(0, &line);
	assert(!err);
	assert(line.baseAddress == 0);
	assert(line.isDirty);

	err = sc_memoryCache_getLine(1, &line);
	assert(!err);
	assert(line.baseAddress == 10);
	assert(line.isDirty);

	err = sc_memoryCache_getLine(2, &line);
	assert(!err);
	assert(line.baseAddress == 20);
	assert(line.isDirty);

	err = sc_memoryCache_getLine(3, &line);
	assert(!err);
	assert(line.baseAddress == 30);
	assert(line.isDirty == 0);
}

static void overrideLines()
{
	sc_memoryController_init();

	int a = sc_memoryCache_getOccupiedLinesCount();
	MemoryAccessResult_t res;
	int value;
	CacheLine_t line;

	res = sc_memoryController_set(4, 100);
	assert(res.cost == CACHE_MISS_COST);

	int err = sc_memoryCache_getLine(0, &line);
	assert(!err);
	assert(line.isDirty);

	res = sc_memoryController_set(5, 120);
	assert(res.cost == CACHE_HIT_COST);

	sc_memoryController_get(14, &value);
	sc_memoryController_get(24, &value);
	sc_memoryController_get(34, &value);

	// sixth load
	sc_memoryController_get(44, &value);
	err = sc_memoryCache_getLine(0, &line);
	assert(!err);
	assert(line.baseAddress == 0);
	assert(line.isDirty);

	sc_memoryController_get(54, &value);
	err = sc_memoryCache_getLine(0, &line);
	assert(!err);
	assert(line.baseAddress == 50);
	assert(!line.isDirty);

	res = sc_memoryController_get(4, &value);
	assert(res.cost == CACHE_MISS_COST);
	assert(value == 100);
}

int main()
{
	basic();
	hits();
	overrideLines();

	return 0;
}
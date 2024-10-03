#include <assert.h>
#include <stddef.h>

#include "memory/controller.h"

int main()
{
	sc_memoryController_init();
	int value;
	MemoryAccessResult_t res;

	res = sc_memoryController_get(1229, NULL);
	assert(res.outOfBoundsError);
	res = sc_memoryController_get(-1, NULL);
	assert(res.outOfBoundsError);

	res = sc_memoryController_set(0, 1);
	assert(!res.outOfBoundsError);

	res = sc_memoryController_get(0, &value);
	assert(value == 1);

	return 0;
}
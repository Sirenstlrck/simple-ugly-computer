#include "mySimpleComputer.h"
#include <assert.h>

void checkZero()
{
	int value;
	sc_regGet(ZERO_DIV_MASK, &value);
	assert(value == 0);

	sc_regGet(MEM_BOUND_ERR_MASK, &value);
	assert(value == 0);

	sc_regGet(IGNORE_IMPULSE_MASK, &value);
	assert(value == 0);

	sc_regGet(WRONG_COMMAND_MASK, &value);
	assert(value == 0);
}

int main()
{
	sc_regInit();
	checkZero();

	assert(sc_regSet(0b111111, 1) == -1);
	assert(sc_regSet(OVERFLOW_MASK, 30) == -1);

	assert(sc_regSet(OVERFLOW_MASK, 1) == 0);

	int value;
	sc_regGet(OVERFLOW_MASK, &value);
	assert(value == 1);
	sc_regSet(OVERFLOW_MASK, 0);

	sc_regGet(OVERFLOW_MASK, &value);
	assert(value == 0);

	return 0;
}
#include <assert.h>

#include "cpu/registers.h"

void checkZero()
{
	sc_reg_reset();
	assert(!sc_reg_isFlagSetted(OVERFLOW_FLAG));
	assert(!sc_reg_isFlagSetted(ZERO_DIV_FLAG));
	assert(!sc_reg_isFlagSetted(MEM_OUT_OF_BOUNDS_FLAG));
	assert(!sc_reg_isFlagSetted(WRONG_COMMAND_FLAG));
	assert(sc_reg_isFlagSetted(IGNORE_IMPULSE_FLAG));
}

int main()
{
	checkZero();

	sc_reg_reset();
	assert(sc_reg_setFlag(0xffff, 1) == -1);

	assert(sc_reg_setFlag(OVERFLOW_FLAG, 1) == 0);
	assert(sc_reg_setFlag(ZERO_DIV_FLAG, 1) == 0);

	assert(sc_reg_isFlagSetted(OVERFLOW_FLAG));
	assert(sc_reg_isFlagSetted(ZERO_DIV_FLAG));

	assert(!sc_reg_isFlagSetted(WRONG_COMMAND_FLAG));

	sc_reg_setFlag(OVERFLOW_FLAG, 0);
	assert(!sc_reg_isFlagSetted(OVERFLOW_FLAG));

	return 0;
}
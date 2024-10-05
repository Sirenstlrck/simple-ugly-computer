#include <assert.h>

#include "cpu/operation.h"

int main()
{
	assert(sc_operation_isValid(Nop));
	assert(sc_operation_isValid(CpuInfo));
	assert(!sc_operation_isValid(2));
	assert(sc_operation_isValid(Load));
	assert(sc_operation_isValid(0));
	assert(!sc_operation_isValid(250));
	assert(!sc_operation_isValid(-1));
}
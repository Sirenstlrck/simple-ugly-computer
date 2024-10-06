#ifndef SC_ARITHMETIC_LOGIC_UNIT_H
#define SC_ARITHMETIC_LOGIC_UNIT_H

#include "state.h"
#include <assert.h>

static void sc_alu_start(int op, int operand) {}

static void sc_alu_continue(int op, int operand) {}

static void sc_alu_handle(int op, int operand)
{
	if (tickData.state == es_working)
	{
		sc_alu_start(op, operand);
	}
	else if (tickData.state == es_pendingData)
	{
		sc_alu_continue(op, operand);
	}
	else
	{
		assert(0);
	}
}

#endif

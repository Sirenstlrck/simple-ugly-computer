#ifndef SC_ARITHMETIC_LOGIC_UNIT_H
#define SC_ARITHMETIC_LOGIC_UNIT_H

#include <assert.h>

#include "cpu/operation.h"
#include "state.h"

static void sc_alu_start(int op, int operand)
{
	// all of theese requires load from memory
	if (IS_OP_IN_RANGE(ALU, op) || (op >= And && op <= Xor) ||
		(op >= Chl && op <= Neg))
	// TODO: ubercomplicated funcs that requires 2 loads
	{
		loadData(operand);
	}
}

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

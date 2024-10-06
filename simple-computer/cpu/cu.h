#ifndef SC_CONTROL_UNIT_H
#define SC_CONTROL_UNIT_H

#include <assert.h>

#include "cpu/cpu.h"
#include "memory_driver.h"
#include "state.h"

static void sc_cu_start(int op, int operand)
{
	switch (op)
	{
	case Load:
		loadData(operand);
		break;
	case Store:
		storeData(operand, sc_reg_getAccumulator());
		tickData.state = es_opHandled;
		break;

	case Halt:
		tickData.state = es_halt;
		break;
	default:
		assert(0);
		break;
	}
}

static void sc_cu_continue(int op, int operand)
{
	switch (op)
	{
	case Load:
		sc_reg_setAccumulator(tickData.loadedData);
		break;
	case Store:
		break;

	default:
		assert(0);
		break;
	}
	tickData.state = es_opHandled;
}

static void sc_cu_handle(int op, int operand)
{
	if (tickData.state == es_working)
	{
		sc_cu_start(op, operand);
	}
	else if (tickData.state == es_pendingData)
	{
		sc_cu_continue(op, operand);
	}
	else
	{
		assert(0);
	}
}

#endif

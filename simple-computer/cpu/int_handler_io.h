#include "cpu/operation.h"
#include "memory_driver.h"
#include "state.h"

static void sc_intHandler_io_start(int op, int operand)
{
	switch (op)
	{
	case Read:
		tickData.state = es_pendingInput;
		break;
	case Write:
		loadData(operand);
		tickData.state = es_working;
		break;

	case Halt:
		tickData.state = es_halt;
		break;
	default:
		assert(0);
		break;
	}
}

static void sc_intHandler_io_continue(int op, int operand)
{
	switch (op)
	{
	case Read:
		sc_reg_setAccumulator(tickData.loadedData);
		break;
	case Write:

		break;

	default:
		assert(0);
		break;
	}
	tickData.state = es_opHandled;
}

static void sc_intHandler_io_handle(int op, int operand)
{
	if (tickData.state == es_working)
	{
		// sc_cu_start(op, operand);
	}
	else if (tickData.state == es_pendingData)
	{
		//	sc_cu_continue(op, operand);
	}
	else
	{
		assert(0);
	}
}

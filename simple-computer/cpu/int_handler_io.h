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
		tickData.state = es_pendingData;
		break;
	case CpuInfo:
		tickData.state = es_wantsToWriteCpuInfo;
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
		sc_reg_setAccumulator(tickData.inputedData);
		tickData.state = es_opHandled;
		break;

	case Write:
		tickData.state = es_wantsToWrite;
		break;

	default:
		assert(0);
		break;
	}
}

static void sc_intHandler_io_handle(int op, int operand)
{
	if (tickData.state == es_working)
	{
		sc_intHandler_io_start(op, operand);
	}
	else if (tickData.state == es_pendingData)
	{
		sc_intHandler_io_continue(op, operand);
	}
	else
	{
		assert(0);
	}
}

#include <stdio.h>
#include <stdlib.h>

#include "cpu/operation.h"
#include "cpu/registers.h"
#include "memory/controller.h"
#include "word/def.h"
#include "word/word.h"

// cpu features
#include "alu.h"
#include "cu.h"
#include "int_handler_io.h"
#include "memory_driver.h"
#include "state.h"
// cpu features

#include "cpu/int_handler.h"

int sc_intHandler_wantsToWriteCpuInfo()
{
	return tickData.state == es_wantsToWrite;
}

void sc_intHandler_reportCpuInfoWrited() { tickData.state = es_shouldLoadOp; }

int sc_intHandler_wantsToWrite() { return tickData.state == es_wantsToWrite; }

int sc_intHandlet_getWriteData() { return tickData.loadedData; }

int sc_intHandler_isPendingInput() { tickData.state == es_pendingInput; }

void sc_intHandler_writeInput(Word_t input)
{
	assert(tickData.state == es_pendingInput);
	tickData.state		 = es_working;
	tickData.inputedData = input;
}

void sc_intHandler_reset()
{
	sc_reg_reset();
	sc_memoryController_init();
	tickData.state = es_shouldLoadOp;
}

static void dispatch()
{
	int sign, op, operand;
	sc_word_commandDecode(tickData.loadedOp, &sign, &op, &operand);
	if (sign || !sc_operation_isValid(op))
	{
		sc_reg_setFlag(WRONG_COMMAND_FLAG, 1);
		sc_reg_setFlag(IGNORE_IMPULSE_FLAG, 1);
		tickData.state = es_halt;
	}
	else if (sc_operation_isAlu(op))
	{
		sc_alu_handle(op, operand);
	}
	else if (sc_operation_isControl(op))
	{
		sc_cu_handle(op, operand);
	}
	else if (sc_operation_isIO(op))
	{
		sc_intHandler_io_handle(op, operand);
	}
	else if (op == Nop)
	{
		tickData.state = es_opHandled;
		return;
	}
	else
	{
		sc_reg_setFlag(WRONG_COMMAND_FLAG, 1);
		tickData.state = es_halt;
	}
}

void sc_intHandler_tick()
{
	tickData.jump.requested = 0;
	tickData.jump.address	= 0;
	if (sc_reg_isFlagSetted(IGNORE_IMPULSE_FLAG) //
		|| tickData.state == es_pendingInput	 //
		|| tickData.state == es_wantsToWrite	 //
		|| tickData.state == es_wantsToWriteCpuInfo)
		return;

	if (sc_reg_getDowntimeCounter() > 0)
	{
		sc_reg_downtimeCounterDec();
		return;
	}

	switch (tickData.state)
	{
	case es_shouldLoadOp:
		loadInstruction();
		break;

	case es_working:
	case es_pendingData:
		dispatch();
		break;

	case es_opHandled:

		break;

	default:
		assert(0);
		break;
	}

	if (tickData.state == es_opHandled)
	{
		if (tickData.jump.requested)
		{
			sc_reg_setInstructionCounter(tickData.jump.address);
		}
		else
		{
			sc_reg_incInstructionCounter();
		}

		tickData.state = es_shouldLoadOp;
	}

	if (tickData.state == es_halt)
	{
		sc_reg_setFlag(IGNORE_IMPULSE_FLAG, 1);
		sc_reg_setInstructionCounter(0);
		tickData.state = es_shouldLoadOp;
	}
}

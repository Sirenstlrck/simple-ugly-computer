#include <stdio.h>
#include <stdlib.h>

#include "cpu/operation.h"
#include "cpu/registers.h"
#include "memory/controller.h"
#include "word/def.h"
#include "word/word.h"

#include "cpu/int_handler.h"

#include "alu.h"
#include "cu.h"

#include "state.h"

#include "memory_driver.h"

int sc_intHandler_wantsToWrite() {}

int sc_intHandlet_getWriteData() {}

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
		fprintf(stderr, "IO device is not supported. Command: %x\n", op);
		abort();
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
	if (sc_reg_isFlagSetted(IGNORE_IMPULSE_FLAG) ||
		tickData.state == es_pendingInput)
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
		sc_reg_incInstructionCounter();
		tickData.state = es_shouldLoadOp;
	}

	if (tickData.state == es_halt)
	{
		sc_reg_setFlag(IGNORE_IMPULSE_FLAG, 1);
		sc_reg_setInstructionCounter(0);
		tickData.state = es_shouldLoadOp;
	}
}

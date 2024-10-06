#ifndef SC_CONTROL_UNIT_H
#define SC_CONTROL_UNIT_H

#include <assert.h>

#include "cpu/cpu.h"
#include "memory_driver.h"
#include "state.h"

static void setJumpIf(int condition, int address)
{
	if (condition)
	{
		tickData.jump.requested = 1;
		tickData.jump.address	= address;
	}

	// just want to write less, maybe this shoudn't be here :p
	tickData.state = es_opHandled;
}

static void sc_cu_start(int op, int operand)
{
	if (Load || Mova)
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

#pragma region Jumps
		case Jump:
			setJumpIf(1, operand);
			break;

		case Jneg:

			setJumpIf(									  //
				sc_word_getSign(sc_reg_getAccumulator()), //
				operand									  //
			);
			break;

		case Jz:
			setJumpIf(						  //
				sc_reg_getAccumulator() == 0, //
				operand						  //
			);
			break;

		case Jns:
			setJumpIf(									   //
				!sc_word_getSign(sc_reg_getAccumulator()), //
				operand									   //
			);
			break;

		case Jc:
			setJumpIf(								//
				sc_reg_isFlagSetted(OVERFLOW_FLAG), //
				operand								//
			);
			break;

		case Jnc:
			setJumpIf(								 //
				!sc_reg_isFlagSetted(OVERFLOW_FLAG), //
				operand								 //
			);
			break;

		case Jp:
			setJumpIf(							  //
				sc_reg_getAccumulator() % 2 == 0, // I hope i got it
				operand							  //
			);
			break;

		case Jnp:
			setJumpIf(							  //
				sc_reg_getAccumulator() % 2 != 0, //
				operand							  //
			);

			break;
#pragma endregion Jumps

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

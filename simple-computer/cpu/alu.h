#ifndef SC_ARITHMETIC_LOGIC_UNIT_H
#define SC_ARITHMETIC_LOGIC_UNIT_H

#include <assert.h>

#include "cpu/operation.h"
#include "memory_driver.h"
#include "state.h"
#include "word/arithmetic.h"

static void sc_alu_start(int op, int operand)
{
	// all of theese requires load from memory
	if (IS_OP_IN_RANGE(ALU, op)		//
		|| (op >= And && op <= Xor) //
		|| (op >= Chl && op <= Neg))
	{
		loadData(operand);
	}
	else if (op == Not)
	{
		storeData(operand, sc_reg_getAccumulator());
		tickData.state = es_opHandled;
	}
	// TODO: ubercomplicated funcs that requires 2 loads
}

// In the end state sets as es_opHandled
static void sc_alu_continue(int op, int operand)
{
	Word_t res;
	switch (op)
	{
#pragma region BasicMath
	case Add:
		ArithmeticResult_t add =
			sc_word_addChecked(sc_reg_getAccumulator(), tickData.loadedData);
		sc_reg_setFlag(OVERFLOW_FLAG, add.overflow);
		sc_reg_setAccumulator(add.result);
		break;

	case Sub:
		ArithmeticResult_t sub =
			sc_word_subChecked(sc_reg_getAccumulator(), tickData.loadedData);
		sc_reg_setFlag(OVERFLOW_FLAG, sub.overflow);
		sc_reg_setAccumulator(sub.result);
		break;

	case Mul:
		ArithmeticResult_t mul =
			sc_word_mulChecked(sc_reg_getAccumulator(), tickData.loadedData);
		sc_reg_setFlag(OVERFLOW_FLAG, mul.overflow);
		sc_reg_setAccumulator(mul.result);
		break;

	case Divide:
		DivisionResult_t div =
			sc_word_div(sc_reg_getAccumulator(), tickData.loadedData);
		sc_reg_setFlag(ZERO_DIV_FLAG, div.zeroDiv);
		sc_reg_setAccumulator(div.result);
		break;
#pragma endregion BasicMath

#pragma region BasicLogic
	case Neg:
		sc_reg_setAccumulator(sc_word_getSign(tickData.loadedData));
		break;

	case And:
		sc_reg_setAccumulator(sc_reg_getAccumulator() && tickData.loadedData);
		break;

	case Or:
		sc_reg_setAccumulator(sc_reg_getAccumulator() || tickData.loadedData);
		break;

	case Xor:
		// because it should be not bitwise, i hope?
		sc_reg_setAccumulator((!!sc_reg_getAccumulator()) ^
							  (!!tickData.loadedData));
		break;
#pragma endregion BasicLogic

	case Chl:
		sc_reg_setAccumulator(sc_reg_getAccumulator() << tickData.inputedData);
		break;

	case Shr:
		sc_reg_setAccumulator(sc_reg_getAccumulator() >> tickData.inputedData);
		break;

	default:
		break;
	}

	tickData.state = es_opHandled;
}

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

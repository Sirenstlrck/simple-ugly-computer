#ifndef MEMORY_DRIVER_H
#define MEMORY_DRIVER_H

#include "cpu/cpu.h"
#include "state.h"
#include "word/word.h"

static void loadInstruction()
{
	int ic = sc_reg_getInstructionCounter();
	Word_t op;
	MemoryAccessResult_t accessResult = sc_memoryController_get(ic, &op);
	sc_reg_downtimeCounterAdd(accessResult.cost - 1);
	if (accessResult.outOfBoundsError)
	{
		sc_reg_setFlag(MEM_OUT_OF_BOUNDS_FLAG, 1);
		tickData.state = es_halt;
		return;
	}
	tickData.loadedOp = op;
	tickData.state	  = es_working;
}

static void loadData(int address)
{
	Word_t data;
	MemoryAccessResult_t accessResult = sc_memoryController_get(address, &data);
	sc_reg_downtimeCounterAdd(accessResult.cost);
	tickData.loadedData = data;
	tickData.state		= es_pendingData;
}

static void storeData(int address, Word_t data)
{
	MemoryAccessResult_t accessResult = sc_memoryController_set(address, data);
	sc_reg_downtimeCounterAdd(accessResult.cost);
}
#endif
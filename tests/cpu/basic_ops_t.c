#include "cpu/int_handler.h"
#include "cpu/operation.h"
#include "cpu/registers.h"
#include "memory/controller.h"
#include "simple-computer/cpu/state.h"
#include "simple-computer/memory/memory.h"
#include "word/word.h"
#include <stdio.h>

void dumpMemory(int limit)
{
	if (limit > 127)
		limit = 127;

	int d = 10;
	for (int i = 0; i < limit; ++i)
	{
		if (i % d == 0)
		{
			printf("\n");
		}
		int c;
		sc_memory_get(i, &c);
		printf("%x ", c);
	}
}

int main()
{
	sc_intHandler_reset();
	Word_t storeToThird;
	sc_word_commandEncode(0, Store, 2, &storeToThird);

	Word_t loadFromThird;
	sc_word_commandEncode(0, Load, 2, &loadFromThird);

	sc_memory_set(0, storeToThird);
	sc_memory_set(1, loadFromThird);
	sc_reg_setAccumulator(500);

	sc_reg_setFlag(IGNORE_IMPULSE_FLAG, 0);
	while (!sc_reg_isFlagSetted(IGNORE_IMPULSE_FLAG))
	{
		const char *stateStr;
		switch (tickData.state)
		{
		case es_pendingData:
			stateStr = "es_pendingData";
			break;
		case es_working:
			stateStr = "es_working";
			break;
		case es_shouldLoadOp:
			stateStr = "es_shouldLoadOp";
		case es_opHandled:
			stateStr = "es_tickEnd";
			break;
		default:
			break;
		}

		printf("%s\n", stateStr);
		sc_intHandler_tick();
	}
	sc_memoryController_flushCache();
	dumpMemory(5);
	printf("\n acc: %d\n", sc_reg_getAccumulator());
}
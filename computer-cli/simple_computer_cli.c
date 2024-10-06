#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../assembler/string_to_opcode.h"
#include "cpu/clock_generator.h"
#include "cpu/cpu.h"
#include "simple-computer/cpu/state.h"
#include "simple-computer/memory/memory.h"

int exitRequested = 0;

void requestExit() { exitRequested = 1; }

void disasm()
{
	for (int i = 0; i < MEMORY_SIZE; ++i)
	{
		int w;
		sc_memory_get(i, &w);

		char *op = "Unknown";
		for (int i = 0; i < OPERATIONS_COUNT; ++i)
		{
			if (((w & COMMAND_MASK) >> COMMAND_OFFSET) == strOpPairs[i].code)
			{
				op = strOpPairs[i].str;
				break;
			}
		}
		printf("%s:%x ", op, w);
	}
}

void dump()
{
	printf("=================\n");
	printf("Tick: %d\n", sc_clockGenerator_getTicksElapsed());
	printf("State: %d\n", tickData.state);
	printf("Acc: %d\n", sc_reg_getAccumulator());
	printf("IC: %d\n", sc_reg_getInstructionCounter());
	printf("DC: %d\n", sc_reg_getDowntimeCounter());
	printf("Op: %d\n", tickData.loadedOp);
}

int main(int argc, char **argv)
{
	if (argc < 3)
	{
		fprintf(stderr, "Please provide input file path & out file path\n");
		return -1;
	}

	signal(SIGINT, requestExit);

	sc_intHandler_reset();
	sc_memory_load(argv[1]);
	sc_clockGenerator_init();
	sc_clockGenerator_setTickHook(dump);
	sc_reg_setFlag(IGNORE_IMPULSE_FLAG, 0);

	sc_clockGenerator_run();

	while (!sc_reg_isFlagSetted(IGNORE_IMPULSE_FLAG) && !exitRequested)
	{
		pause();
	}

	sc_clockGenerator_stop();

	sc_memoryController_flushCache();
	sc_memory_save(argv[2]);

	return 0;
}

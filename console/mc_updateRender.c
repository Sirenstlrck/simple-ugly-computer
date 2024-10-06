#include "console.h"
#include "cpu/clock_generator.h"

void mc_updateRender()
{
	if (!sc_reg_getFlags(IGNORE_IMPULSE_FLAG))
	{
		selectedAddressIndex = sc_reg_getInstructionCounter();
	}

	mc_memoryManipulator_render();
	mc_accumulator_render();
	mc_instructionCounter_render();
	mc_flags_render();
	mc_selectedLabel_set(selectedAddressIndex);

	mt_cursorPosition_set(71, 21);
	char buffer[256];
	sprintf(buffer, "%d", sc_clockGenerator_getTicksElapsed());
	write(STDOUT_FILENO, buffer, strlen(buffer));
	mc_cache_render();
}
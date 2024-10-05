#include "console.h"

void mc_memoryManipulator_render()
{
	for (int i = 0; i < MEMORY_SIZE; ++i)
		mc_label_render(memoryManipulator[i]);
	mt_restoreDefaultOutputColor();
}
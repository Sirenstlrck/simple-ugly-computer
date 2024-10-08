#include "console.h"

void mc_memoryManipulator_render()
{
	int value;
	int x_point = 0, y_point = 2, x_startPoint = x_point;
	for (int i = 0; i < MEMORY_SIZE; ++i)
	{
		sc_memoryController_getDirect(i, &value);
		if (i % 10 == 0)
		{
			x_point = x_startPoint;
			y_point++;
		}
		x_point += 6;
		Label_t label		 = {x_point, y_point, (Word_t)value, Black, White};
		memoryManipulator[i] = label;
	}

	for (int i = 0; i < MEMORY_SIZE; ++i)
		mc_label_render(memoryManipulator[i]);
	mt_restoreDefaultOutputColor();
}
#include "console.h"

void mc_memoryManipulator_move(enum Keys key)
{
	int value = selectedAddressIndex;
	switch (key)
	{
	case Key_Up:
		value -= 10;
		if (value < 0)
			value = MEMORY_SIZE + value + 2;
		break;
	case Key_Down:
		value += 10;
		if (value >= MEMORY_SIZE + 2)
			value = value - MEMORY_SIZE - 2;
		break;
	case Key_Left:
		value--;
		if (value < 0)
			value = MEMORY_SIZE + 2 - 1;
		break;
	case Key_Right:
		value++;
		if (value >= MEMORY_SIZE + 2)
			value = 0;
		break;
	}
	if (value >= MEMORY_SIZE + 2 || value < 0)
		return;
	selectedAddressIndex = value;
	mc_selectedLabel_set(selectedAddressIndex);
}
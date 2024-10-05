#include "console.h"
#include "memory/controller.h"
#include "terminal.h"

void mc_selectedLabel_set(int address)
{
	memoryManipulator[selectedAddressIndex].background_color = Black;
	memoryManipulator[selectedAddressIndex].foreground_color = White;
	mc_label_render(&memoryManipulator[selectedAddressIndex]);
	selectedAddressIndex									 = address;
	memoryManipulator[selectedAddressIndex].background_color = White;
	memoryManipulator[selectedAddressIndex].foreground_color = Black;
	mc_label_render(&memoryManipulator[selectedAddressIndex]);
	mt_restoreDefaultOutputColor();
	bc_bigChars_print(82, 4, memoryManipulator[selectedAddressIndex].content);
	char str[256];
	int result;
	sc_memoryController_get(selectedAddressIndex, &result);
	sprintf(str, "d: %05d | o: %05o | h: %04X", result, result, result);
	mt_cursorPosition_set(72, 14);
	write(STDOUT_FILENO, str, strlen(str));

	sprintf(str, "b: %0.15b", result);
	mt_cursorPosition_set(72, 15);
	write(STDOUT_FILENO, str, strlen(str));

	mt_cursorPosition_set(82, 11);
	sprintf(str, "%03d/127", selectedAddressIndex);
	write(STDOUT_FILENO, str, strlen(str));
}

int mc_label_set(Label_t *label, Label_t newLabel)
{
	if (label == NULL)
		return -1;
	*label = newLabel;
	return 0;
}

int mc_label_render(Label_t *label)
{
	mt_cursorPosition_set(label->x_position, label->y_position);
	mt_outputBackgroundColor_set(label->background_color);
	mt_outputForegroundColor_set(label->foreground_color);
	write(STDOUT_FILENO, label->content, 6);
}

void mc_memoryManipulator_render()
{
	for (int i = 0; i < MEMORY_SIZE; ++i)
		mc_label_render(&memoryManipulator[i]);
	mt_restoreDefaultOutputColor();
}

void mc_memoryManipulator_init()
{
	int value;
	int x_point = 0, y_point = 2, x_startPoint = x_point;
	for (int i = 0; i < MEMORY_SIZE; ++i)
	{
		sc_memoryController_get(i, &value);
		if (i % 10 == 0)
		{
			x_point = x_startPoint;
			y_point++;
		}
		x_point += 6;
		char str[6];
		sprintf(str, "+%04x", value);
		Label_t label		 = {x_point, y_point, strdup(str), Black, White};
		memoryManipulator[i] = label;
	}
}
#include "console.h"

void mc_formats_render(Word_t word)
{
	char buffer[256];
	sprintf(buffer, "d: %s | o: %s | h: %s", mc_wordToDec(word),
			mc_wordToOct(word), mc_wordToHex(word));
	mt_cursorPosition_set(71, 14);
	write(STDOUT_FILENO, buffer, strlen(buffer));
	sprintf(buffer, "b: %0.15b", (int)word);

	char tempBuffer[22];
	tempBuffer[21] = '\0';
	for (int i = 0, j = i; i < 21; ++i) // 0 0000000 0000000
	{
		if (i == 4 || i == 12)
		{
			tempBuffer[i] = ' ';
			continue;
		}
		tempBuffer[i] = buffer[j];
		++j;
	}

	mt_cursorPosition_set(71, 15);
	write(STDOUT_FILENO, tempBuffer, 22);
}

void mc_selectedLabel_set(int address)
{
	selecionLabel.background_color = Black;
	selecionLabel.foreground_color = White;
	mc_label_render(selecionLabel);
	selectedAddressIndex = address;

	Label_t selectedLabel;

	int value;
	char buffer[256];
	if (selectedAddressIndex == 128)
	{
		selectedLabel = accumulatorLabel;
		mt_cursorPosition_set(82, 11);
		write(STDOUT_FILENO, "ACCUMUL", 8);
	}
	else if (selectedAddressIndex == 129)
	{
		selectedLabel = instractionCounterLabel;
		mt_cursorPosition_set(82, 11);
		write(STDOUT_FILENO, "ICOUNTR", 8);
	}
	else
	{
		selectedLabel = memoryManipulator[selectedAddressIndex];
		sprintf(buffer, "%03d/%d", selectedAddressIndex, MEMORY_SIZE - 1);
		mt_cursorPosition_set(82, 11);
		write(STDOUT_FILENO, buffer, strlen(buffer));
	}

	selectedLabel.background_color = White;
	selectedLabel.foreground_color = Black;
	mc_label_render(selectedLabel);
	mt_restoreDefaultOutputColor();
	bc_bigChars_print(82, 4, mc_wordToHex(selectedLabel.content));
	mc_formats_render(selectedLabel.content);

	selecionLabel = selectedLabel;
}
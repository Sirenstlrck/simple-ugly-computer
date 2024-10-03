#include "console.h"

void handleExit(enum Keys key)
{
	if (key == Key_Esc)
		exitFlag = 1;
}

void mc_frames_render()
{
	mt_screen_clear();
	mt_cursorVisiblity_set(0);
	bc_frame_draw(1, 1, 120, 35, 2, White, Black, "Simple Computer", Green,
				  White);
	bc_frame_draw(80, 2, 37, 11, 2, White, Black, " Edit cell ", Green, Black);
	bc_frame_draw(3, 2, 65, 15, 27, White, Black, "  RAM  ", Red, Black);

	mc_memoryManipulator_init();
	mc_memoryManipulator_render();
	mc_selectedLabel_set(selectedAddressIndex);

	bc_frame_draw(3, 17, 65, 8, 27, White, Black, "  Cache  ", Red, Black);
	bc_frame_draw(69, 2, 10, 11, 2, White, Black, " Flags ", Red, Black);
	bc_frame_draw(69, 13, 47, 4, 2, White, Black, " Format ", Green, Black);

	char flags[5];
	int value;
	sc_regGet(OVERFLOW_MASK, &value);
	flags[0] = value ? 'P' : '_';
	sc_regGet(ZERO_DIV_MASK, &value);
	flags[1] = value ? '0' : '_';
	sc_regGet(MEM_BOUND_ERR_MASK, &value);
	flags[2] = value ? 'M' : '_';
	sc_regGet(IGNORE_IMPULSE_MASK, &value);
	flags[3] = value ? 'T' : '_';
	sc_regGet(WRONG_COMMAND_MASK, &value);
	flags[4] = value ? 'E' : '_';

	int y = 1;
	mt_cursorPosition_set(74, y += 2);
	for (int i = 0; i < 5; ++i)
	{
		char bf[3];
		sprintf(bf, "%c	", flags[i]);
		write(STDOUT_FILENO, bf, 3);
		mt_cursorPosition_set(74, y += 2);
	}

	enum Keys key;
	while (!exitFlag)
	{
		if (rk_readKey(&key) == 0)
		{
			if (!sc_regGet(IGNORE_IMPULSE_MASK, &isImpulseTact) &&
				isImpulseTact)
			{
				mc_memoryManipulator_move(key);
			}
			handleExit(key);
		}
	}
}
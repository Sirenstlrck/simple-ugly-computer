#include "console.h"

void mc_flags_render()
{
	// clang-format off
	char flags[] = {
        sc_reg_isFlagSetted(OVERFLOW_FLAG)           ? 'P' : '_',
        sc_reg_isFlagSetted(ZERO_DIV_FLAG)           ? '0' : '_',
        sc_reg_isFlagSetted(MEM_OUT_OF_BOUNDS_FLAG)  ? 'M' : '_',
        sc_reg_isFlagSetted(IGNORE_IMPULSE_FLAG)     ? 'T' : '_',
        sc_reg_isFlagSetted(WRONG_COMMAND_FLAG)      ? 'E' : '_',
    };
	// clang-format on
	int y = 1;
	mt_cursorPosition_set(74, y += 2);
	for (int i = 0; i < 5; ++i)
	{
		char bf[3];
		sprintf(bf, "%c	", flags[i]);
		write(STDOUT_FILENO, bf, 3);
		mt_cursorPosition_set(74, y += 2);
	}
}
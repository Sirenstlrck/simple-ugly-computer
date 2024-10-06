#include "console.h"

void mc_staticFrames_render()
{
	mt_screen_clear();
	mt_cursorVisiblity_set(0);
	bc_frame_draw(1, 1, 118, 30, 2, White, Black, "Simple Computer", Green,
				  White);
	bc_frame_draw(80, 2, 37, 11, 2, White, Black, " Edit cell ", Green, Black);
	bc_frame_draw(3, 2, 65, 15, 27, White, Black, "  RAM  ", Red, Black);

	bc_frame_draw(1, 17, 67, 7, 27, White, Black, "  Cache  ", Red, Black);
	bc_frame_draw(69, 2, 10, 11, 2, White, Black, " Flags ", Red, Black);
	bc_frame_draw(69, 13, 48, 4, 2, White, Black, " Format ", Green, Black);

	bc_frame_draw(69, 17, 23, 3, 5, White, Black, " Accumulator ", Green,
				  Black);
	bc_frame_draw(94, 17, 23, 3, 1, White, Black, " Instraction  Counter ",
				  Green, Black);

	bc_frame_draw(69, 20, 23, 3, 8, White, Black, " Tick ", Green, Black);
	bc_frame_draw(94, 20, 23, 3, 7, White, Black, " Command ", Green, Black);
	bc_frame_draw(80, 23, 37, 7, 30, White, Black, " Keys ", Green, Black);

	mt_cursorPosition_set(82, 24);
	write(STDOUT_FILENO, "l - load  s - save  i - reset", 30);
	mt_cursorPosition_set(82, 25);
	write(STDOUT_FILENO, "r - run   t - step", 19);
	mt_cursorPosition_set(82, 26);
	write(STDOUT_FILENO, "ESC - exit", 11);
	mt_cursorPosition_set(82, 27);
	write(STDOUT_FILENO, "F5 - accumulator", 17);
	mt_cursorPosition_set(82, 28);
	write(STDOUT_FILENO, "F6 - ICounter", 14);
	Label_t label = {6, 3, 0, Black, White};
	selecionLabel = label;
	mc_updateRender();
}
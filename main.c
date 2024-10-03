#include "console.h"
#include "memory/controller.h"
#include "simple_computer.h"
#include "terminal.h"

int main()
{
	int screen_width, screen_height;

	srand(time(NULL));

	mt_screenSize_get(&screen_height, &screen_width);

	// if (screen_height < MIN_SCREEN_HEIGHT || screen_width < MIN_SCREEN_WITDH)
	// {
	// 	fprintf(stderr, "Not enough screen space\n");
	// 	return -1;
	// }

	sc_memoryController_init();
	for (int i = 0; i < MEMORY_SIZE; ++i)
	{
		sc_memoryController_set(i, rand() % MAX_WORD - 1);
	}

	rk_terminal_save();
	sc_regSet(IGNORE_IMPULSE_MASK, 1);
	mc_frames_render();

	rk_terminal_restore();
	mt_cursorVisiblity_set(1);
	rk_terminalMode_set(0, 0, 0, 1, 1);
	mt_screen_clear();
	return 0;
}
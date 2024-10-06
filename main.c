#include "console.h"
#include "cpu/registers.h"
#include "memory/controller.h"
#include "terminal.h"
#include "word/def.h"

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

	rk_terminal_save();
	sc_reg_setFlag(IGNORE_IMPULSE_FLAG, 1);

	mc_staticFrames_render();

	mc_start();

	rk_terminal_restore();
	mt_cursorVisiblity_set(1);
	rk_terminalMode_set(0, 0, 0, 1, 1);
	mt_screen_clear();
	return 0;
}
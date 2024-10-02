#include "myConsole.h"
#include "mySimpleComputer.h"
#include "myTerminal.h"

int main()
{
	int screen_width, screen_height;

	mt_screenSize_get(&screen_height, &screen_width);

	if (screen_height < MIN_SCREEN_HEIGHT || screen_width < MIN_SCREEN_WITDH)
	{
		fprintf(stderr, "Not enough screen space");
		return -1;
	}

	// sc_memoryInit();
	// mc_framesInit();
	// mt_cursorPosition_set(0, 47);

	canonical_mode_example();

	return 0;
}
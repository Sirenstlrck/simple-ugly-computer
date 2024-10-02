#include "myConsole.h"
#include "mySimpleComputer.h"
#include "myTerm.h"
#include <stdio.h>

int main()
{
	int screen_width, screen_height;

	mt_getScreenSize(&screen_height, &screen_width);

	if (screen_height < MIN_SCREEN_HEIGHT || screen_width < MIN_SCREEN_WITDH)
	{
		perror("Not enough screen space");
		return -1;
	}

	sc_memoryInit();
	mc_framesInit();
	mt_gotoXY(0, 47);
	return 0;
}
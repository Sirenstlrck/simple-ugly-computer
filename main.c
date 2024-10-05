#include "console.h"
#include "terminal.h"

int main()
{
	int screen_width, screen_height;

	mt_screenSize_get(&screen_height, &screen_width);

	if (screen_height < MIN_SCREEN_HEIGHT || screen_width < MIN_SCREEN_WITDH)
	{
		fprintf(stderr, "Not enough screen space");
		return -1;
	}

	return 0;
}
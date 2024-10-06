#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#include "cpu/clock_generator.h"
#include "cpu/int_handler.h"

static unsigned int ticksElapsed;

static unsigned char isRunning;

static void (*tickHook)() = NULL;

void sc_clockGenerator_setTickHook(void (*hook)()) { tickHook = hook; }

void sc_clockGenerator_tick()
{
	ticksElapsed++;
	sc_intHandler_tick();

	if (tickHook)
		tickHook();
}

int sc_clockGenerator_isRunning() { return isRunning; }

unsigned int sc_clockGenerator_getTicksElapsed() { return ticksElapsed; }

void sc_clockGenerator_init()
{
	signal(SIGALRM, sc_clockGenerator_tick);
	isRunning	 = 0;
	ticksElapsed = 0;
}

void sc_clockGenerator_setIsRunning(int value)
{
	if (value)
		sc_clockGenerator_run();
	else
		sc_clockGenerator_stop();
}

void sc_clockGenerator_run()
{
	if (isRunning)
		return;

	isRunning = 1;

	struct itimerval nval, oval;
	nval.it_interval.tv_sec	 = 0;
	nval.it_interval.tv_usec = 500000;
	nval.it_value.tv_sec	 = 0;
	nval.it_value.tv_usec	 = 1;
	if (setitimer(ITIMER_REAL, &nval, NULL) == -1)
	{
		perror("setitimer");
		abort();
	}
}

void sc_clockGenerator_stop()
{
	isRunning = 0;
	if (setitimer(ITIMER_REAL, NULL, NULL) == -1)
	{
		perror("setitimer");
		abort();
	}
}
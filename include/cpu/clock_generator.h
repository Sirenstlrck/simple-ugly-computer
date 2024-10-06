#ifndef SC_CLOCK_GENERATOR_H
#define SC_CLOCK_GENERATOR_H

void sc_clockGenerator_setTickHook(void (*hook)());

void sc_clockGenerator_tick();

int sc_clockGenerator_isRunning();

unsigned int sc_clockGenerator_getTicksElapsed();

void sc_clockGenerator_init();

void sc_clockGenerator_run();

void sc_clockGenerator_stop();

#endif

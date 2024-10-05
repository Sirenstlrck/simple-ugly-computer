#ifndef SC_REGISTERS_H
#define SC_REGISTERS_H

// clang-format off
#define OVERFLOW_FLAG               1 << 0
#define ZERO_DIV_FLAG               1 << 1
#define MEM_OUT_OF_BOUNDS_FLAG      1 << 2
#define IGNORE_IMPULSE_FLAG         1 << 3
#define WRONG_COMMAND_FLAG          1 << 4
// clang-format on

int sc_reg_getAccumulator();
void sc_reg_setAccumulator(int value);

int sc_reg_getInstructionCounter();
void sc_reg_setInstructionCounter(int value);

int sc_reg_getDowntimeCounter();
int sc_reg_downtimeCounterAdd(int value);
int sc_reg_downtimeCounterDec();
int sc_reg_downtimeCounterIsZero();

int sc_reg_getFlags();
int sc_reg_setFlag(int flag, int value);
int sc_reg_isFlagSetted(int flag);

void sc_reg_reset();

#endif
